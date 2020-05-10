#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
using std::cout;
using std::ifstream;
using std::istringstream;
using std::string;
using std::vector;
using std::abs;

enum class State {kEmpty, kObstacle};

vector<State> ParseLine(string line){
    istringstream sline(line);
    int n;
    char c;
    vector<State> row;
    while(sline >> n >> c && c == ','){
        if(n==0){
            row.push_back(State::kEmpty);
        } else {
            row.push_back(State::kObstacle);
        }
    }
    return row;
}

vector<vector<State>> ReadBoardFile(string path) {
    ifstream myfile (path);
    vector<vector<State>> board{};
    if (myfile) {
        string line;
        while(getline(myfile, line)) {
            vector<State> row = ParseLine(line);
            board.push_back(row);
        }
    }    
    return board;
}

int Absolute

// TODO: Write the Heruistic Function here:
int Heuristic(int x_1, int, y_1, int x_2, int y_2){
    // Using Manhattan distance
   return abs(x2 - x1) + abs(y2 - y1);
}

// TODO: Write the Search function stub here. 
vector<vector<State>> Search(vector<vector<State>> board, vector<int> start,
        vector<int> stop){
    cout << "No Path Found!" << "\n";
    vector<vector<State>> path;

    return path; 
}


string CellString(State cell){
    switch(cell) {
        case State::kObstacle: return "⛰️   ";
        default: return "0   ";
    }
}


void PrintBoard(const vector<vector<State>> board){
    for (int i = 0;i < board.size(); i++){
        for (int j = 0; j<board[i].size(); j++){
            cout << CellString(board[i][j]);
        }
        cout << "\n";
    }
}

int main(){
    // TODO: Declare "init" and "goal" arrays with values {0, 0} and {4, 5} respectively.
    auto board = ReadBoardFile("1.board");
    // TODO: Call Search with "board", "init", and "goal". 
    // Store the results in the variable "solution".
    // TODO: Change the following line to pass "solution" to PrintBoard.
    vector<int>start{0,0};
    vector<int>end{4,5};

    auto solution = Search(board, start, end);
    
    PrintBoard(solution);
}
