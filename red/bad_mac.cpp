#include <iostream>
#define PRINT_VALUES(out, x, y) (out) << (x) << endl << (y) << endl
using namespace std;
int main() {
if (true) {
    PRINT_VALUES(cout, 2 ,3);
}
else
    PRINT_VALUES(cout, 3 ,4);

for (int i = 0; i < 5; ++i)
    PRINT_VALUES(cout, i , i+1);

return 0;
}

