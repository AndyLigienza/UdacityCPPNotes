#include <sstream>
#include <string>
#include <iostream>

using std::cout;
using std::string;
using std::istringstream;

int main(){
	string b("1,2,3");

	istringstream my_stream(b);

	char c;
	int n;
	while(my_stream >> n >> c){
		cout << "The stream worked: " << n << " " << c << "\n";
	}
	cout << "The stream has failed" << "\n";
	
}

/*
 * In that example, notice that the `3` was not printed! The expression:
```
my_stream >> n >> c
```
tried to stream an `int` followed by a `char`. Since there was no `char` after the `3`, the stream failed and the `while` loop exited.
*/



