#include "test_runner.h"
#include "profile.h"

#include <map>
#include <string>
#include <functional>
#include <future>
#include <string>
#include <algorithm>
#include <vector>
#include <string_view>
using namespace std;



std::vector<std::string> Split(const std::string& str, const std::string& delimiter = " ") {  /// что-то вроде  split из Python
    std::vector<std::string> s;

    std::size_t pos = 0;
    std::size_t cond = str.find(delimiter, pos);
        if(cond == std::string::npos){
            s.push_back(str);
            return s;
        }

    while ( cond != std::string::npos ){
        std::string tmp = str.substr(pos,cond - pos);
        if (tmp != "") {
            s.push_back(tmp);
        }

        pos = cond+delimiter.size();
        cond = str.find(delimiter, pos);
    }
        s.push_back(str.substr(pos, str.size()-1));

    return s;
}


std::vector<std::string> SplitIntoWords(const std::string& s) {
    auto it = s.begin();
    auto Str_begin = s.begin();
    std::vector<std::string> result;
    while(it != s.end() ) {
        it = std::find(Str_begin, s.end(), ' ');
        result.push_back(std::string(Str_begin,it));
        Str_begin = it +1;
    }
    return result;
}

std::vector<string_view> SplitInto(const std::string &s) {
    string_view str = s;
    vector<string_view> result;

    while(true) {

        size_t space = str.find(' ');
        result.push_back(str.substr(0, space));

        if(space == str.npos) {
            break;
        } else {
            str.remove_prefix(space + 1);
        }
    }

//size_t pos = 0;
    //const size_t pos_end = str.pos;
    return result;
}
struct Stats {
  map<string, int> word_frequences;

  void operator += (const Stats& other) {
    for (const auto &j : other.word_frequences) {
        word_frequences[j.first] += j.second;
    }
  }
};

Stats ExploreLine(const set<string>& key_words, const string& line) {
    /*
    std::vector<std::string> V = Split(line," ");
    Stats result;
    for (auto &j : V) {
        if (key_words.find(j) != key_words.end()) {
                result.word_frequences[j]++;
            }
        }


    string::const_iterator first = line.begin();
    string::const_iterator last = line.end();
    Stats result;
    string::const_iterator it;
    while ( (it = find(first, last, ' ')) <= last ) {
        string word(first, it);
        if (*key_words.lower_bound(word)==word) {
            result.word_frequences[word]++;
        }
        if (it!=last) first = it+1;
        else break;
    }
    return result; */
    Stats result;
    std::vector<string_view> V = SplitInto(line);
        for (auto &j : V) {
        if (key_words.find(string(j)) != key_words.end()) {
                result.word_frequences[string(j)]++;
            }
        }
    //std::cout << "222" << endl;
    /*auto begin = line.begin();
    while (true) {
        auto it = line.find(" ");
        string(begin,it);
        if (key_words.find(string(begin,it)) != key_words.end()) {
            result.word_frequences[string(begin,it)]++;
        }

    } */
    return result;
}

Stats ExploreKeyWordsSingleThread(
  const set<string>& key_words, istream& input
) {
  Stats result;
  for (string line; getline(input, line); ) {
    result += ExploreLine(key_words, line);
  }
  return result;
}

Stats ExploreKeyWords(const set<string>& key_words, istream& input) {
    // Реализуйте эту функцию
    // в один поток - элементарно
    // return ExploreKeyWordsSingleThread(key_words, input);
    vector<future<Stats>> total;
    Stats result;
    while (!input.eof() ) {
        string words;
        for(int i=0; i<100000; i++) {
            string s;
            input >> s;
            words += move(s) + " ";
        }
        total.push_back(async(ExploreLine, ref(key_words), words));
    }
    for(auto& a : total) {
        result += a.get();
    }
    return result;
  // Р РµР°Р»РёР·СѓР№С‚Рµ СЌС‚Сѓ С„СѓРЅРєС†РёСЋ
}

void TestBasic() {
  const set<string> key_words = {"yangle", "rocks", "sucks", "all"};

  stringstream ss;
  ss << "this new yangle service really rocks\n";
  ss << "It sucks when yangle isn't available\n";
  ss << "10 reasons why yangle is the best IT company\n";
  ss << "yangle rocks others suck\n";
  ss << "Goondex really sucks, but yangle rocks. Use yangle\n";

  const auto stats = ExploreKeyWords(key_words, ss);
  const map<string, int> expected = {
    {"yangle", 6},
    {"rocks", 2},
    {"sucks", 1}
  };
  cout << " all is ok";
  ASSERT_EQUAL(stats.word_frequences, expected);
}

int main() {
  TestRunner tr;
  RUN_TEST(tr, TestBasic);

  cout << "all is ok" ;
  return 0;
}
