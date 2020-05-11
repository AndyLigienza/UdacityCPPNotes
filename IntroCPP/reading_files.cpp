#include <fstream>
#include <iostream>
#include <string>

using std::string;
using std::cout;

void ReadBoardFile(string file_path){
	std::ifstream my_file;
	my_file.open(file_path);
	if (my_file){
		string line;
		while(getline(my_file, line)){
			cout<<line<<"\n";
		}
	}	    
}

int main(){
	ReadBoardFile("files/1.board");
}
