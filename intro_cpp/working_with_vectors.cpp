#include <iostream>
#include <vector>
using std::vector;
using std::cout;

int main() {
    vector<vector<int>> b = {{1, 1, 2, 3},
                             {2, 1, 2, 3},
                             {3, 1, 2, 3}};
    cout << b[0][0];
    cout << b[1][0];
    cout << b[2][0];
    cout << "\n";


    vector<int> a = {0, 1, 2, 3, 4};

    // Print the length of vector a to the console.
    cout << a.size() << "\n";

    // Print the length of an inner vector of b here.
    cout << b[0].size() << "\n";
}



