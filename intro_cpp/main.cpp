/* iostream is the input output library  that is part of the c++ standard library*/
#include <iostream>
/* cout is using console out from the std library. This is done due to the affect of namespaces. We are directing the cout function to come from std library
 * Note that the second two lines in the example end with a semicolon ;. Coding statements end with a semicolon in C++. The #include statement is a preprocessor command, so it doesn't need one.*/
using std::cout;
/* return int from main loop */
int main () {
	/*In this line, the code is using cout to send output to the notebook. The << operator is the stream insertion operator, and it writes what's on the right side of the operator to the left side. So in this case, "Message here" is written to the output stream cout.
	 * */
	cout << "Hello!" << "\n";
}

/* run using g++ main.cpp, and read using ./a.out*/
