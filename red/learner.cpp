s
#include <algorithm>
#include <string>
#include <vector>
#include <set>
using namespace std;

class Learner {
 private:
  set<string> dict;

 public:
  int Learn(const vector<string>& words) {
    int newWords = 0;
    size_t before = dict.size();
    for (const auto& word : words) {
            dict.insert(word);
      }
    size_t after = dict.size();
    return after - before;
  }

  vector<string> KnownWords() {
      vector<string> res;
      for (auto & word : dict){
        res.push_back(word);
      }
    //sort(dict.begin(), dict.end());
    //dict.erase(unique(dict.begin(), dict.end()), dict.end());
    return res;
  }
};

int main() {
string h;
cin >> h;
return 0;
}
