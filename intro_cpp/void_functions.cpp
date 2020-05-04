#include <iostream>
#include <string>

using std::cout;
using std::string;

void PrintStrings(string s1, string s2){
	cout << s1 << s2 << "\n";
}

int main(){
	string s1 = "C++ is ";
	string s2 = "super awesome";
	PrintStrings(s1, s2);

}
