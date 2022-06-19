#include <iostream>
#include <exception>
#include <string>
#include <cmath>
#include <vector>
#include <set>
#include <map>
#include <algorithm>
#include <locale>
#include <cctype>
#include <fstream>
#include <iomanip>

using namespace std;



string AskTimeServer() {}

class TimeServer {
public:
  string GetCurrentTime(){
      //string s;
  try {

  last_fetched_time=AskTimeServer();
  return last_fetched_time;
  }
  catch  (system_error & )  {
    return last_fetched_time;

  }


//return last_fetched_time;
  }
private:
  string last_fetched_time = "00:00:00";
};

