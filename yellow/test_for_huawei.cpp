#include <iostream>
#include <fstream>
#include <algorithm>
#include <random>
#include <ctime>
#include <vector>
#include <map>
#include <set>
//using std::unordered_set<int> = Roads

struct City {
    int id;
    std::map<int, std::set<double>> route;
    std::map<int, double> route2;
    double capacity_to_next_city = 0;

};

void Print (City & city) {
    std::cout << "set \n" ;
    for(auto i : city.route) {
        std::cout << i.first << "  " << *(--i.second.end()) << std::endl;
    }
    std::cout << " map_max \n";
    for(auto i : city.route2) {
        std::cout << i.first << "  " << i.second<< std::endl;
    }

}

void Generate (int num_nodes, int num_rodas, const std::string filename) {
    std::ofstream output(filename);
    output  << num_nodes << " " << num_rodas << "\n";

    std::mt19937 gen_double(time(0));
    std::uniform_real_distribution<> urd(0, 1000);


    std::mt19937 gen_int(time(0));
    std::uniform_int_distribution<int> uid(1, num_nodes);


    int i = 1;
    while (i < num_nodes ) {
        output  << urd(gen_double) << " ";
        ++i;
    }
    //std::cout << "\n";
    //std::cout << "i is " << i << std::endl;
    output << "\n";
    while (i <= num_rodas) {
        int id_city1 = uid(gen_int);
        int id_city2 = uid(gen_int);
        while (id_city2 == id_city1) {
            id_city2 = uid(gen_int);
        }
        double width = urd(gen_double);
        output << std::min(id_city1, id_city2) << " " << std::max(id_city1, id_city2) << " " << width << "\n";
        ++i;

    }
}

std::vector <double> Width_from_cap_to_Zod(int id_cap, int id_zod,  std::vector<City>& Barzoom) {
    double min = 0;
    int num_city = Barzoom.size() - 1;
    ///проверить на связность

    std::vector<double> width_to_zod(num_city + 1);
    std::vector<double> width_to_zod2(num_city + 1);
    int k = 0;
    while ( id_zod - id_cap - k > 0) {
        if ( k == 0) {
            width_to_zod[id_zod - 1] = *(--Barzoom[id_zod - 1].route[id_zod].end()); /// last element from set
            width_to_zod2[id_zod - 1] = Barzoom[id_zod - 1].route2[id_zod];
            k++;
            continue;
        }
        width_to_zod[id_zod - k - 1] = std::min(width_to_zod[id_zod - k], *(--Barzoom[id_zod - k - 1].route[id_zod - k].end()));
        width_to_zod2[id_zod - k - 1] = std::min(width_to_zod2[id_zod - k], Barzoom[id_zod - k - 1].route2[id_zod - k]);

        if (Barzoom[id_zod - k - 1].route.find(id_zod) != Barzoom[id_zod - k - 1].route.end()) {
            width_to_zod[id_zod - k - 1] = std::max(*(--Barzoom[id_zod - k - 1].route[id_zod].end()), width_to_zod[id_zod - k - 1]);
        }
        if (Barzoom[id_zod - k - 1].route2.find(id_zod) != Barzoom[id_zod - k - 1].route2.end()) {
            width_to_zod2[id_zod - k - 1] = std::max(Barzoom[id_zod - k - 1].route2[id_zod], width_to_zod2[id_zod - k - 1]);
        }
        for (auto &cur_city : Barzoom[id_zod - k - 1].route) {
            if (cur_city.first > id_zod - k - 1 && cur_city.first < id_zod) { ///вот тут = поставил

                double tmp = std::min(*(--cur_city.second.end()), width_to_zod[cur_city.first]);
                width_to_zod[id_zod - k - 1] = std::max(tmp, width_to_zod[id_zod - k - 1]);
            }
        }

        auto begin = Barzoom[id_zod - k - 1].route2.find(id_zod - k - 1);
        begin++;
        auto end = Barzoom[id_zod - k - 1].route2.end();
        while (begin != end  && begin->first < id_zod) {
            double tmp = std::min(begin->second, width_to_zod2[begin->first]);
            width_to_zod2[id_zod - k - 1] = std::max(tmp, width_to_zod2[id_zod - k - 1]);
            begin++;
        }
        ++k;
    }

    return {width_to_zod2.begin() + id_cap, width_to_zod2.begin() + id_zod};
}

std::vector <double> Width_from_Zod_to_cap(int id_cap, int id_zod,  std::vector<City>& Barzoom) {
    double min = 0;
    int num_city = Barzoom.size() - 1;
    ///проверить на связность

    std::vector<double> width_to_zod(num_city + 1);
    std::vector<double> width_to_zod2(num_city + 1);
    int k = 0;
    while ( id_zod - id_cap - k > 0) {
        if ( k == 0) {
            width_to_zod[id_cap + k] = *(--Barzoom[id_cap + k].route[id_cap + k + 1].end()); /// last element from set
            width_to_zod2[id_cap + k] = Barzoom[id_cap + k].route2[id_cap + k + 1];
            k++;
            continue;
        }
        width_to_zod[id_cap + k] = std::min(width_to_zod[id_cap + k - 1], *(--Barzoom[id_cap + k - 1].route[id_cap + k].end()));
        width_to_zod2[id_cap + k] = std::min(width_to_zod2[id_cap + k - 1], Barzoom[id_cap + k - 1].route2[id_cap + k]);

        if (Barzoom[id_cap + k].route.find(id_cap) != Barzoom[id_cap + k].route.end()) {
            width_to_zod[id_cap + k] = std::max(*(--Barzoom[id_cap + k].route[id_cap].end()), width_to_zod[id_cap + k]);
        }
        if (Barzoom[id_cap + k].route2.find(id_zod) != Barzoom[id_cap + k].route2.end()) {
            width_to_zod2[id_cap + k] = std::max(Barzoom[id_cap + k].route2[id_cap], width_to_zod2[id_cap + k]);
        }
        for (auto &cur_city : Barzoom[id_cap + k].route) {
            if (cur_city.first > id_cap && cur_city.first < id_cap + k) { ///вот тут = поставил

                double tmp = std::min(*(--cur_city.second.end()), width_to_zod[cur_city.first]);
                width_to_zod[id_cap + k] = std::max(tmp, width_to_zod[id_cap + k]);
            }
        }

        auto begin = Barzoom[id_cap + k].route2.find(id_cap + k);
        begin--;
        auto end = Barzoom[id_cap + k].route2.begin();
        while (begin != end && begin->first > id_cap) {
            double tmp = std::min(begin->second, width_to_zod2[begin->first]);
            width_to_zod2[id_cap + k] = std::max(tmp, width_to_zod2[id_cap + k]);
            begin--;
        }
        ++k;
    }

    return {width_to_zod2.begin() + id_cap, width_to_zod2.begin() + id_zod};
}



std::vector <double> Solution_method (int id_cap, int id_zod, double min_width, std::vector<City>& Barzoom) {

    if (Barzoom[id_zod].route.size() == 0) {
        return {};
    }

    double min = 0;
    int num_city = Barzoom.size() - 1;

    ///проверить на связность
    if (Barzoom[id_zod].route2.size() <= 1) {
        return {};
    }
    std::vector<double> width_to_zod(num_city + 1);
    std::vector<double> width_to_zod2(num_city + 1);
    int k = 0;
    while ( id_zod - id_cap - k > 0) {
        if ( k == 0) {
            width_to_zod[id_zod - 1] = *(--Barzoom[id_zod - 1].route[id_zod].end()); /// last element from set
            width_to_zod2[id_zod - 1] = Barzoom[id_zod - 1].route2[id_zod];
            k++;
            continue;
        }
        width_to_zod[id_zod - k - 1] = std::min(width_to_zod[id_zod - k], *(--Barzoom[id_zod - k - 1].route[id_zod - k].end()));
        width_to_zod2[id_zod - k - 1] = std::min(width_to_zod2[id_zod - k], Barzoom[id_zod - k - 1].route2[id_zod - k]);

        if (Barzoom[id_zod - k - 1].route.find(id_zod) != Barzoom[id_zod - k - 1].route.end()) {
            width_to_zod[id_zod - k - 1] = std::max(*(--Barzoom[id_zod - k - 1].route[id_zod].end()), width_to_zod[id_zod - k - 1]);
        }
        if (Barzoom[id_zod - k - 1].route2.find(id_zod) != Barzoom[id_zod - k - 1].route2.end()) {
            width_to_zod2[id_zod - k - 1] = std::max(Barzoom[id_zod - k - 1].route2[id_zod], width_to_zod2[id_zod - k - 1]);
        }
        for (auto &cur_city : Barzoom[id_zod - k - 1].route) {
            if (cur_city.first > id_zod - k - 1 && cur_city.first < id_zod) { ///вот тут = поставил

                double tmp = std::min(*(--cur_city.second.end()), width_to_zod[cur_city.first]);
                width_to_zod[id_zod - k - 1] = std::max(tmp, width_to_zod[id_zod - k - 1]);
            }
        }

        auto begin = Barzoom[id_zod - k - 1].route2.find(id_zod - k - 1);
        begin++;
        auto end = Barzoom[id_zod - k - 1].route2.find(id_zod);
        while (begin != end) {
            double tmp = std::min(begin->second, width_to_zod2[begin->first]);
            width_to_zod2[id_zod - k - 1] = std::max(tmp, width_to_zod2[id_zod - k - 1]);
            begin++;
        }
        ++k;
    }
    double max_element1 = width_to_zod[id_cap];
    double max_element2 = width_to_zod2[id_cap];



    auto from_cap_to_zod = Width_from_cap_to_Zod(id_cap, id_zod, Barzoom);
    auto from_first_to_cap = Width_from_cap_to_Zod(1, id_cap, Barzoom);

    std::cout << " Print 1 \n";
    for (int i = id_cap; i <= id_zod; ++i) {
        std::cout << width_to_zod2[i] << "  " << width_to_zod[i] << "\n";
    }

    std::cout << " Print 2 \n";
    for (auto i :from_cap_to_zod ) {
        std::cout << i<< "\n";
    }
    std::cout << " Print 3 \n";
    for (auto i :from_first_to_cap ) {
        std::cout << i<< "\n";
    }


    for (int i = 0; i < from_first_to_cap.size(); ++i) {
        width_to_zod[i + 1] = from_first_to_cap[i];
        width_to_zod2[i + 1] = from_first_to_cap[i];
    }
    std::cout << " Print 4 \n";
    for (auto i :width_to_zod ) {
        std::cout << i<< "\n";
    }

    std::cout << " Print 5 \n";
    for (auto i :width_to_zod2 ) {
        std::cout << i<< "\n";
    }

        ///проверить индексы  Часть до id_cap
    k = 0;
    while ( id_cap - k > 1) {
        for (auto &cur_city : Barzoom[id_cap - k - 1].route){
            if(cur_city.first > id_cap && cur_city.first <= id_zod) {

                if (cur_city.first == id_zod) {
                    double tmp = std::min(*(--cur_city.second.end()),width_to_zod[id_cap - k - 1]);
                    max_element1 = std::max(tmp , max_element1);
                    break;
                }

                double tmp = std::min(*(--cur_city.second.end()), width_to_zod[cur_city.first]);
                tmp = std::min(width_to_zod[id_cap - k - 1], tmp);
                max_element1 = std::max(tmp , max_element1);
            }
        }
        auto begin = Barzoom[id_cap - k - 1].route2.begin();
        while(begin != Barzoom[id_cap - k - 1].route2.end() && begin->first <= id_cap) {
            begin++;
        }
        while (begin != Barzoom[id_cap - k - 1].route2.end()  && begin->first > id_cap && begin->first <= id_zod) {
                if (begin->first == id_zod) {
                    double tmp = std::min(begin->second, width_to_zod2[id_cap - k - 1]);
                    max_element2 = std::max(tmp, max_element2);
                    break;
                }
                double tmp = std::min(begin->second, width_to_zod2[begin->first]);
                tmp = std::min(width_to_zod2[id_cap - k - 1], tmp);
                max_element2 = std::max(tmp, max_element2);
                begin++;
            }
        k++;
    }

        std::cout << "our massive is \n";
        for (int i = 0; i < width_to_zod2.size(); ++i) {
            std::cout << i << "   " << width_to_zod2[i] << "  " << width_to_zod[i] << "\n";

        }


        auto v = Width_from_cap_to_Zod(1, id_cap, Barzoom);
        for (auto i : v) {
            std::cout << " i fun" << i << "\n";
        }

        //auto from_zod_to_end = Width_from_cap_to_Zod(id_zod, num_city, Barzoom);
        auto from_zod_to_end = Width_from_Zod_to_cap(id_zod, num_city, Barzoom);
        for (auto i : from_zod_to_end) {
            std::cout << " i2 fun" << i << "\n";
        }
        for (int i = 0; i < from_zod_to_end.size(); ++i) {
            width_to_zod[id_zod + i] = from_zod_to_end[i];
            width_to_zod2[id_zod + i] = from_zod_to_end[i];
        }
        ///потестить


        std::cout << "our massive2 is \n";
        for (int i = 0; i < width_to_zod2.size(); ++i) {
            std::cout << i << "   " << width_to_zod[i] << "  " << width_to_zod2[i] << "\n";
            //std::cout << i << "   " << width_to_zod2[i] << "  " << width_to_zod[i] << "\n";

        }


        k = id_zod;

        while (k < num_city) {

            for (auto &cur_city : Barzoom[k + 1].route){

                    if (cur_city.first < id_zod) {

                       // std::cout  << cur_city.first <<"   " << *(--cur_city.second.end()) << "  " << width_to_zod[cur_city.first] << "TUT  \n";
                        double tmp = std::min(*(--cur_city.second.end()), width_to_zod[cur_city.first]);
                       // std::cout << tmp << " <- tmp  width_to_zod -> " << width_to_zod[k] << std::endl;
                        tmp = std::min(tmp, width_to_zod[k]);
                        max_element1 = std::max(max_element1, tmp);
                    }
            }

            auto begin = Barzoom[k + 1].route2.begin();
            while (begin->first < id_zod) {
                double tmp = std::min(width_to_zod2[begin->first], begin->second);
                tmp = std::min(tmp, width_to_zod2[k]);
                max_element2 = std::max(max_element2, tmp);
                begin++;
            }
            ++k;
        }

        ///постестить
        /*
        /// Часть после id_zod

        k = id_zod;
        while (k < num_city) {
            if (k == id_zod) {
                width_to_zod[k] = *(--Barzoom[k].route[k + 1].end());
                width_to_zod2[k] = Barzoom[k].route2[k + 1];
                ++k;
                continue;
            }

        }



        for (auto &cur_city : Barzoom[id_zod - k - 1].route) {

        }
        ++k;
    } */


    double Max1 = 0;
    double Max2 = 0;
    for (int i = 0; i < width_to_zod2.size(); ++i) {
        Max1 = std::max(Max1,  width_to_zod[i]);
        Max2 = std::max(Max2,  width_to_zod2[i]);
    }

   //for (const auto &i : Barzoom) {}
   return {max_element1 , max_element2 };
  // return {max_element1 - min_width, max_element2 - min_width};
}


void Test (int id_cap, int id_zod, const std::string filename) {
    std::ifstream input(filename);

    int num_cities;
    int num_roads;
    input >> num_cities >> num_roads;
    std::vector<City> Barzoom(num_cities + 1);
    double min_width;

    if (num_roads - num_cities >= -1) {

        for (int i = 1; i < num_cities; ++i) {
            Barzoom[i].id = i;
            Barzoom[i + 1].id = i + 1;
            double width = 1e+10;
            input >> width ;
            min_width = std::min(min_width, width);
            Barzoom[i].route[i + 1].insert(width);
            Barzoom[i + 1].route[i].insert(width);
            Barzoom[i].route[i].insert(0);
            Barzoom[i + 1].route[i + 1].insert(0);

            Barzoom[i].route2[i + 1] = width;
            Barzoom[i + 1].route2[i] = width;
            Barzoom[i].route2[i] = 0;
            Barzoom[i + 1].route2[i + 1] = 0;
        }
        for (int i = num_cities; i <= num_roads; ++i) {
            int from, to;
            double width;
            input >> from >> to >> width;
            min_width = std::min(min_width, width);
            Barzoom[from].route[to].insert(width);
            Barzoom[to].route[from].insert(width);

            Barzoom[from].route2[to] = std::max(width, Barzoom[from].route2[to]);
            Barzoom[to].route2[from] = std::max(width,  Barzoom[to].route2[from]);


        }

    } else {

        for (int i = 1; i <= num_roads; ++i) {
            Barzoom[i].id = i;
            Barzoom[i + 1].id = i + 1;
            double width;
            input >> width ;
            min_width = std::min(min_width, width);
            Barzoom[i].route[i + 1] .insert(width);
             Barzoom[i].route2[i + 1] = width;
        }
        for (int i = num_roads + 1; i <= num_cities; ++i) {
            Barzoom[i].id = i;
        }

    }

    std::vector<double> result = Solution_method(std::min(id_cap, id_zod), std::max(id_cap, id_zod), min_width, Barzoom);
    std::cout << result[0] << " result " << result[1] << std::endl;




}


int main(int argc, char* argv[])
{
    /*
    std::random_device rd;
    std::uniform_int_distribution<int> uid(0, 50);
    std::cout << uid(rd) << std::endl;
*/
    if (std::string(argv[1]) == "-g") {
        std::cout << "Hello" << std::endl;
       // Generate(std::stoi(std::string(argv[2])), std::stoi(std::string(argv[3])) , std::string(argv[4]));
       Generate(std::stoi(std::string(argv[2])), std::stoi(std::string(argv[3])) , "output1.txt");
    } else {
        std::cout << "-t" << std::endl;
        Test(std::stoi(std::string(argv[2])), std::stoi(std::string(argv[3])), "output1.txt");
    }
/*
    std::mt19937 gen(time(0));
    std::uniform_real_distribution<> urd(0, 2);
    std::cout << urd(gen) << std::endl;
    std::cout << urd(gen) << std::endl;

  //  std::random_device rd;
   // std::mt19937 gen2(rd());
   std::mt19937 gen2(time(0));
    std::uniform_int_distribution<int> uid(0, 2);
    std::cout << uid(gen2) << std::endl;

    std::cout << std::string(argv[1]) << std::endl; */
}
