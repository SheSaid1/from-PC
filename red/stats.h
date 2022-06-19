#pragma once

#include "http_request.h"
#include <string>
#include <string_view>
#include <map>
#include <set>
using namespace std;

class Stats {
public:
    Stats () {
    UriStats ={
    {"/", 0},
    {"/order", 0},
    {"/product", 0},
    {"/basket", 0},
    {"/help", 0},
    {"unknown", 0},
  };

     MethodStats  = {
    {"GET", 0},
    {"PUT", 0},
    {"POST", 0},
    {"DELETE", 0},
    {"UNKNOWN", 0},
  };
    }
  void AddMethod(string_view method) {
      //cout << method << endl;

    if (Method.count(string(method)) == 0) {
        auto it = Method.find("UNKNOWN");
        MethodStats[string_view(*it)]++;
    } else {
        auto it = Method.find(string(method));
        MethodStats[string_view(*it)]++;
    }
  }
  void AddUri(string_view uri) {

    if (Uri.count(string(uri)) == 0) {
        auto it = Uri.find("unknown");
        UriStats[string_view(*it)]++;
    } else {
        auto it = Uri.find(string(uri));
        UriStats[string_view(*it)]++;
    }
  }
  const map<string_view, int>& GetMethodStats() const {
     return    MethodStats;
  }
  const map<string_view, int>& GetUriStats() const {
    return UriStats;
  }

    map<string_view, int> MethodStats;
    map<string_view, int> UriStats;

private:

    const set<string> Method = { "GET", "POST", "PUT", "DELETE", "UNKNOWN"};
    const set <string> Uri = { "/", "/order", "/product", "/basket", "/help", "unknown"};
};

HttpRequest ParseRequest(string_view line2) {
    string_view line = line2;
    HttpRequest res;
    size_t pos = 0;
    if (line[pos] == ' ' ) {
    while (!isalpha(line[pos])) {
        pos ++;
    }
    }
    size_t it = line.find(' ',pos);
    res.method = line.substr(pos, it - pos);
    pos = it + 1;
   // const char* C = "HTTP";
    it = line.find(' ',pos);
    res.uri  = line.substr(pos, it -  pos);
   // pos = it + 1;
   // it = find('\\',pos);
    res.protocol = line.substr(it + 1, line.size() - it);
    return res;
}
void Print (HttpRequest a) {
    cout << a.method << " " << a.uri  << " " << a.protocol << endl;
}


