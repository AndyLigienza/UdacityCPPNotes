#include <iostream>
#include <vector>

using std::vector;
using std::cout;

int vector_summator(vector<int> vect){
	int a = 0;
	for (int val:vect){
		a = a+val;
	}
	return a;
}

int main() {
	vector<int> v {1,2,3};
	cout << vector_summator(v) << "\n";
}
