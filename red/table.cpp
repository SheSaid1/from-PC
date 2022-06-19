#include "test_runner.h"
#include <vector>
#include <tuple>
using namespace std;

template <class T>
class Table {
public:
    Table (size_t first, size_t second) {
        if (first == 0 || second == 0) {
            col = 0;
            row = 0;
        } else {
            std::vector<T> S(second);
            std::vector<std::vector<T>> SS(first,S);
            table = SS;
            row = first;
            col = second;
        }
    }

    void Resize(size_t first, size_t second) {
            std::vector<T> S(second);
            std::vector<std::vector<T>> SS(first,S);
            for (int i = 0; i < first; ++i ) {
                if (i >= row) {
                    continue;
                }
                for (int j = 0; j < second; ++j) {
                    if ( j < col){
                        SS[i][j] = table[i][j];
                    }
                }
            }
            table = SS;
            row = first;
            col = second;
    }

    std::pair<size_t, size_t> Size() const {
        return std::make_pair(row, col);
    }
    std::vector<T>& operator[] (size_t row) {
        return table[row];
    }
    std::vector<T> operator[] (size_t row) const {
    return table[row];
    }

private:
    size_t row;
    size_t col;
    std::vector<std::vector<T>> table;


};




/*

void TestTable() {
  Table<int> t(1, 1);
  ASSERT_EQUAL(t.Size().first, 1u);
  ASSERT_EQUAL(t.Size().second, 1u);
  t[0][0] = 42;
  ASSERT_EQUAL(t[0][0], 42);
  t.Resize(3, 4);
  ASSERT_EQUAL(t.Size().first, 3u);
  ASSERT_EQUAL(t.Size().second, 4u);
}

int main() {
  TestRunner tr;
  RUN_TEST(tr, TestTable);
  return 0;
}
 */
