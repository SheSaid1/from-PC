#include "test_runner.h"

#include <vector>
#include <algorithm>
#include <utility>
#include <list>
using namespace std;

template <typename Token>
using Sentence = vector<Token>;

template <typename Token>
vector<Sentence<Token>> SplitIntoSentences(vector<Token> tokens) {
    vector<Sentence<Token>> result;
    auto begin = tokens.begin();
    auto it = tokens.begin();
    auto end = tokens.end();
    while (it != end) {
        //Sentence<Token> v;
        std::list<Token> v;
       // result.push_back(v);
        //auto Begin = result.end();
        //--Begin;
        while( !((*it).IsEndSentencePunctuation()) && it != end) {
            v.push_back(move(*it));
            it++;
        }
        while ( (*it).IsEndSentencePunctuation() && it != end ) {
            v.push_back(move(*it));
            it++;
        }
       // Sentence<Token> ar(v.size());
       Sentence<Token> ar;
       // result.push_back(ar);
        std::move(v.begin(), v.end(), back_inserter(ar));
        result.push_back(std::move(ar));

        if (it == end) {
            break;
        }
        //it++;
        //Sentence<Token> v;
        //result.push_back(v);
       // auto Begin = result.end();
       // --Begin;
        //std::move(begin,it, Begin.begin());
        begin = it;
    }
   // Sentence<Token> v;
   // result.push_back(v);
   // std::move(begin,it, (--result.end()).begin());
    return result;

}


struct TestToken {
  string data;
  bool is_end_sentence_punctuation = false;

  bool IsEndSentencePunctuation() const {
    return is_end_sentence_punctuation;
  }
  bool operator==(const TestToken& other) const {
    return data == other.data && is_end_sentence_punctuation == other.is_end_sentence_punctuation;
  }
};

ostream& operator<<(ostream& stream, const TestToken& token) {
  return stream << token.data;
}

void TestSplitting() {
  ASSERT_EQUAL(
    SplitIntoSentences(vector<TestToken>({{"Split"}, {"into"}, {"sentences"}, {"!"}})),
    vector<Sentence<TestToken>>({
        {{"Split"}, {"into"}, {"sentences"}, {"!"}}
    })
  );

  ASSERT_EQUAL(
    SplitIntoSentences(vector<TestToken>({{"Split"}, {"into"}, {"sentences"}, {"!", true}})),
    vector<Sentence<TestToken>>({
        {{"Split"}, {"into"}, {"sentences"}, {"!", true}}
    })
  );

  ASSERT_EQUAL(
    SplitIntoSentences(vector<TestToken>({{"Split"}, {"into"}, {"sentences"}, {"!", true}, {"!", true}, {"Without"}, {"copies"}, {".", true}})),
    vector<Sentence<TestToken>>({
        {{"Split"}, {"into"}, {"sentences"}, {"!", true}, {"!", true}},
        {{"Without"}, {"copies"}, {".", true}},
    })
  );
}

int main() {
  TestRunner tr;
  RUN_TEST(tr, TestSplitting);
  return 0;
}
