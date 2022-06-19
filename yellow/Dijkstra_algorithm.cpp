//Dijkstra_algorithm
#include <iostream>
#include <set>
#include <vector>
#include <unordered_map>
#include <unordered_set>

const int INF = 1000000000;

struct Node {
    int id;
    int dist_from_source = INF;
    bool flag = false; ///if we didn't take node than it false. If we took - true
};

struct destination_node {
    int destination_id;
    int dist_to_destination;
};


bool operator < (const Node& lhs, const Node& rhs) {
    return lhs.dist_from_source < rhs.dist_from_source;
}
/*
std::unordered_set <int> dijkstra_algorithm(std::unordered_map<int, std::unordered_set <destination_node>> &adjacency_matrix) {
    std::set<Node> heap;
    std::unordered_set <int> result;

    Node first_node = {1, 0, false};
    heap.insert(first_node);
    result.insert(first_node);

    size_t num_nodes = adjacency_matrix.size();
    bool false_contition = false;
    while (num_nodes > 0) {
        auto begin = heap.begin();
        auto end = heap.end();

        while (begin != end && begin->flag == false) {
            begin++;
        }

        auto tmp = *begin;
        heap.erase(begin);

        for (auto i : adjacency_matrix[tmp.id]) {
            Node node = {i.destination_id, i.dist_to_destination, false};
            heap.insert(node);
        }

        num_nodes--;
    }

}

*/

std::vector <int> dijkstra_algorithm2(std::unordered_map<int, std::vector <destination_node>>& adjacency_matrix, int num_nodes) {
    std::vector<int> min_dist(num_nodes + 1);
    for (int i = 2; i < min_dist.size(); ++i) {
        min_dist[i] = INF;
    }

    std::vector<bool> was_here(num_nodes + 1);
    for (int i = 0; i < was_here.size(); ++i) {
        was_here[i] = false;
    }

    std::set<Node> heap;
    Node first_node = {1, 0, false};
    heap.insert(first_node);

    //int num_nodes = num_nodes + 1;
    bool false_contition = false;
    //while (num_nodes > 0 && heap.size() > 0) {
    while (heap.size() > 0) {
        int i = 0;
        auto begin = heap.begin();
        auto end = heap.end();

        while (begin != end && was_here[begin->id] == true) {
            heap.erase(begin);                                    ///зависит от того, что лучше : игнорировать или удалять? пока что удаляем
            begin = heap.begin();
        }
        if (begin == end) {
            break;
        }

        int dist_to_current_node = min_dist[begin->id];
        std::vector<Node> residue;
        for (auto dest : adjacency_matrix[begin->id]) {
            if (dist_to_current_node + dest.dist_to_destination < min_dist[dest.destination_id] && !was_here[dest.destination_id]) {
                min_dist[dest.destination_id] = dist_to_current_node + dest.dist_to_destination;
            }
            if (!was_here[dest.destination_id]) {
                std::cout << "\"" << dest.destination_id  << "\" \n";
                Node node = {dest.destination_id, min_dist[dest.destination_id], false};
                residue.push_back(node);
            }
        }

        was_here[begin->id] = true;
        heap.erase(begin);
        for (auto node : residue) {
            heap.insert(node);
        }

        num_nodes--;
    }

    return min_dist;
}


int main() {
    std::unordered_map<int, std::vector <destination_node>> adjacency_matrix;
    adjacency_matrix[1] = {{2, 7}, {3, 9}, {6, 14}};
    adjacency_matrix[2] = {{3, 10}, {4, 15}, {1, 7}};
    adjacency_matrix[3] = {{6, 2}, {4, 11}, {1, 9}};
    adjacency_matrix[4] = {{2, 15}, {3, 11}, {5, 6}};
    adjacency_matrix[5] = {{4, 6}, {6, 9}};
    adjacency_matrix[6] = {{1, 14}, {3, 2}, {5, 9}};
    std::vector<int> result = dijkstra_algorithm2(adjacency_matrix, 6);
    for (int i = 0; i < 7; ++i) {
        std::cout << result[i] << "  ";
    }


    std::cout << "SUCCESS \n";

}
