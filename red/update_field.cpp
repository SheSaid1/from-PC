#include "airline_ticket.h"
#include "test_runner.h"

using namespace std;

#define UPDATE_FIELD(ticket, field, values)  { \
    ticket.field = values

#define PRINT_VALUES(out, x, y) out << (x) << endl; out << (y) << endl
/*
  bool operator < (const Date &lhs, const Date &rhs) {
    if (lhs.year == rhs.year ){
        if (lhs.month == rhs.month) {
            return lhs.day < rhs.day;
        }
        return lhs.month < rhs.month;
    }
    return lhs.year < rhs.year;
 }
 bool operator == (const Date &lhs, const Date &rhs) {
    if (lhs.year == rhs.year && lhs.month == rhs.month && lhs.day == rhs.day ) {
        return true;
    } else return false;
 }
 bool operator == (const Time &lhs , const Time& rhs) {
    if (lhs.hours == rhs.hours && lhs.minutes == rhs.minutes) {
        return true;
    } else return false;
 }

 Date operator = ( Date &lhs , const Date& rhs) {
    lhs.year = rhs.year;
    lhs.month = rhs.month;
    lhs.day = rhs.day;
    return lhs;
 }

 bool operator < (const Time &lhs , const Time& rhs) {
    if (lhs.hours == rhs.hours) {
        return lhs.minutes < rhs.minutes;
    }
    return lhs.hours < rhs.hours;
 }
 ostream& operator << (ostream &out, const Date& data) {
    out << data.year << " " << data.month << " " << data.day;
    return out;
 }
 ostream& operator << (ostream &out, const Time& time) {
    out << time.hours << " " << time.minutes;
    return out;
 }



void TestUpdate() {
  AirlineTicket t;
  t.price = 0;

  const map<string, string> updates1 = {
    {"departure_date", "2018-2-28"},
    {"departure_time", "17:40"},
  };
  UPDATE_FIELD(t, departure_date, updates1);
  UPDATE_FIELD(t, departure_time, updates1);
  UPDATE_FIELD(t, price, updates1);

  ASSERT_EQUAL(t.departure_date, (Date{2018, 2, 28}));
  ASSERT_EQUAL(t.departure_time, (Time{17, 40}));
  ASSERT_EQUAL(t.price, 0);

  const map<string, string> updates2 = {
    {"price", "12550"},
    {"arrival_time", "20:33"},
  };
  UPDATE_FIELD(t, departure_date, updates2);
  UPDATE_FIELD(t, departure_time, updates2);
  UPDATE_FIELD(t, arrival_time, updates2);
  UPDATE_FIELD(t, price, updates2);

  // updates2 не содержит ключей "departure_date" и "departure_time", поэтому
  // значения этих полей не должны измениться
  ASSERT_EQUAL(t.departure_date, (Date{2018, 2, 28}));
  ASSERT_EQUAL(t.departure_time, (Time{17, 40}));
  ASSERT_EQUAL(t.price, 12550);
  ASSERT_EQUAL(t.arrival_time, (Time{20, 33})); */
//}

int main() {
if (true) {
    PRINT_VALUES(cout, 2 ,3);
}
else
    PRINT_VALUES(cout, 3 ,4);

for (int i = 0; i < 5; ++i) {
    PRINT_VALUES(cout, i , i+1);
}
return 0;
}

