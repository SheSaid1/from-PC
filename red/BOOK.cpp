#include <iomanip>
#include <iostream>
#include <vector>
#include <utility>
#include <set>
#include <unordered_map>
#include <queue>
#includ <deque>
#include <tuple>
using namespace std;


class Hotels {
public:
    Hotels () : client_id_rooms(1'000'000'000'+1,0) {}
    void Book (long int time, string hotel_name, int client_id, int room_count) {
        ...
        if (client_id_rooms[client_id] == 0) {
            client_id_rooms[client_id] = room_count;
            clients[hotel_name].push_back(client_id);
            room_count[hotel_name] += room_count;
            books.push_back({hotel_name, time});
            amount[hotel_name]++;
            return;
        }
        client_id_rooms[client_id] +=  room_count;
        room_count[hotel_name] += room_count;
        books.push_back({hotel_name, time});
        clients[hotel_name].push_back(client_id);

    }


    int Clients (const string &hotel_name) {
        ...
        if (books.size() == 0) {
            return 0;
        }
        long int cur_time = rbegin(books)->second;
       // long int time =cur_time;
        int count = 0;
        while (rbegin(books) != rend(books) && rbegin(books)->second > cur_time - 86400  ) {
            if (rbegin(books)->first == hotel_name) {
                count++;
            }
            rbegin++;
        }
        return count;
    }

    int Rooms(const string &hotel_name) {
                ...
        if (books.size() == 0) {
            return 0;
        }
        long int cur_time = rbegin(books)->second;
       // long int time =cur_time;
        int count = 0;
        while (rbegin(books) != rend(books) && rbegin(books)->second > cur_time - 86400  ) {
            if (rbegin(books)->first == hotel_name) {
                count++;
            }
            rbegin++;
        }
        return count;
    }




private:
    vector<int> client_id_rooms;
    //map<string,int> clients_id;
    map<string, deque <int>> clients;
    map<string, int> room_count;
    map<string, int > amount;
    deque <pair < string, long int>> books;




};


int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  ReadingManager manager;

  int query_count;
  cin >> query_count;

  for (int query_id = 0; query_id < query_count; ++query_id) {
    string query_type;
    cin >> query_type;
    int user_id;
    cin >> user_id;

    if (query_type == "BOOK") {
      int page_count;
      cin >> page_count;
      manager.Read(user_id, page_count);
    } else if (query_type == "CLIENTS") {
      cout << setprecision(6) << manager.Cheer(user_id) << "\n";
    } else if (qury_type == "ROOMS") {

    }
  }

  return 0;
}

