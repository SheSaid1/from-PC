#include <iostream>
#include <map>
#include <string>
#include <vector>
#include <tuple>
using namespace std;


enum class Lang {
  DE, FR, IT
};



struct Region {
  string std_name;
  string parent_std_name;
  map<Lang, string> names;
  int64_t population;
};
/*
bool operator < ( const map <Lang,string> & lhs,const map <Lang,string> & rhs)
{   int i=0;
    for (auto & i : lhs)
    {
        if (i.second>rhs[i.first])
        {
            return 0;
        }
    }
    return 1;
} */
using namespace std;

bool operator<(const Region& lhs, const Region& rhs) {
  return tie(lhs.std_name, lhs.parent_std_name, lhs.names, lhs.population) <
      tie(rhs.std_name, rhs.parent_std_name, rhs.names, rhs.population);
}

int FindMaxRepetitionCount(const vector<Region>& regions) {
  int result = 0;
  map<Region, int> repetition_count;
  for (const Region& region : regions) {
    result = max(result, ++repetition_count[region]);
  }
  return result;
}


int main()
{
    return 0;
}
