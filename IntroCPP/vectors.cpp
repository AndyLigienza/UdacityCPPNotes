#include <iostream>
#include <vector>

using std::cout;
using std::vector;

int main(){
	// Lets review the three ways of declaring and initializing a vector
	vector<int> v_1{0, 1, 2};
	vector<int> v_2 = {3, 4, 5};
	vector<int> v_3;

	v_3 = {6};

	cout << "Everything Worked!" << "\n";
}




