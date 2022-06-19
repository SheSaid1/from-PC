#include <iostream>
#include <vector>
#include <algorithm>

using Array = std::vector<unsigned int>;

int size;
int median;
unsigned int first, second;
unsigned int cur = 0;
unsigned int nextRand24() {
    cur = cur * first + second;
    return cur >> 8;
}

unsigned int nextRand32() {
    unsigned int numa = nextRand24(), numb = nextRand24();
    return (numa << 8) ^ numb;
}

unsigned int Median(Array& arr) {
    for (int left = 0, right = size - 1;;) {
        if (right <= left + 1) {
            if (right == left + 1 && arr[right] < arr[left]) {
                std::swap(arr[left], arr[right]);
            }
            return arr[median];
        }
        int mid = (left + right) >> 1;
        std::swap(arr[mid], arr[left + 1]);
        if (arr[left] > arr[right]) {
            std::swap(arr[left], arr[right]);
        }
        if (arr[left + 1] > arr[right]) {
            std::swap(arr[left + 1], arr[right]);
        }
        if (arr[left] > arr[left + 1]) {
            std::swap(arr[left], arr[left + 1]);
        }
        int it = left + 1, jt = right;
        const unsigned int pivot = arr[left + 1];
        while (arr[++it] < pivot) {
        }
        while (arr[--jt] > pivot) {
        }
        while (it <= jt) {
            std::swap(arr[it], arr[jt]);
            while (arr[++it] < pivot) {
            }
            while (arr[--jt] > pivot) {
            }
        }
        arr[left + 1] = arr[jt];
        arr[jt] = pivot;
        if (jt >= median) {
            right = jt - 1;
        }
        if (jt <= median) {
            left = it;
        }
    }
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int cnt;
    std::cin >> cnt >> first >> second;

    Array coords(cnt);
    size = cnt;
    median = cnt / 2;

    for (auto& i : coords) {
        i = nextRand32();
    }

    unsigned int med = Median(coords);
    uint64_t sum = 0;
    for (auto i : coords) {
        int64_t diff = static_cast<int64_t>(i) - static_cast<int64_t>(med);
        sum += static_cast<uint64_t>(std::abs(diff));
    }
    std::cout << sum << std::endl;
    return 0;
}
