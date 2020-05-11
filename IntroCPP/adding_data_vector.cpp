#include <vector>
#include <iostream>

using std::vector;
using std::cout;

int main(){
	vector v{1,2,3};

	for (int i:v){
		cout << i << "\n";
	}
	cout << "End of regular vector print" << "\n";

	v.push_back(4);

	for (int j:v){
		cout << j << "\n";
	}
	cout << "Pushed 4 into new vector" << '\n';
}
