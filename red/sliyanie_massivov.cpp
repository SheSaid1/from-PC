#include <iostream>
#include <vector>
#include <algorithm>

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int rows_num, numbers_cnt;
    std::cin >> rows_num >> numbers_cnt;
    std::vector<int64_t> res(rows_num * numbers_cnt);
    for (auto& i : res) {
        std::cin >> i;
    }
    if (rows_num == 1) {
        for (int i = 0; i < numbers_cnt; ++i) {
            std::cout << res[i] << " ";
        }
        std::cout << std::endl;
        return 0;
    }
    for (int i = 1; i < rows_num; ++i) {
        for (int j = i * numbers_cnt; j < (i + 1) * numbers_cnt; ++j) {
            std::cin >> res[j];
        }
        std::inplace_merge(res.begin(), res.begin() + i * numbers_cnt,
                           res.begin() + (i + 1) * numbers_cnt);
    }
    for (auto i : res) {
        std::cout << i << " ";
    }
    std::cout << std::endl;
    return 0;
}

