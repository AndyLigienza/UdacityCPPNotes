#include <iostream>
#include <sstream>
#include <string>

using std::cout;
using std::string;
using std::istringstream;

int main(){
	// Creating a string with integers
	string int_string("123 1 2");
	
	// converting to a istringstream object
	istringstream my_stream(int_string);
	
	
	int n;
	/*
	 The extraction operator >> writes the stream to the variable on the right of the operator and returns the istringstream object, so the entire expression my_stream >> n is an istringstream object and can be used as a boolean! Because of this, a common way to use istringstream is to use the entire extraction expression in a while loop as follows:
	 */
	while (my_stream >> n){
		cout <<"The stream was successful: " <<  n << "\n";
		}
	cout <<"That stream was NOT successful" << "\n";
}	
