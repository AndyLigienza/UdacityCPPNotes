#include <algorithm>
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
using std::sort; 


enum class State {kEmpty, kObstacle,
    kPath, kClosed,
    kStart, kFinish};
// directional deltas
const int delta[4][2]{{-1, 0}, {0, -1}, {1, 0}, {0, 1}};

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

// TODO: Write function to compare the f-value of two nodes here
bool Compare(vector<int> node1, vector<int> node2){
    if (node1[2]+node1[3] > node2[2]+node2[3]){
        return true;
    } else {
        return false;
    }
}

/**
 * Sort the two-dimensional vector of ints in descending order.
 * This function uses pointers which we will learn about soon.
 */
void CellSort(vector<vector<int>> *v){
    sort(v->begin(), v->end(), Compare);
}


// TODO: Write the Heruistic Function here:
int Heuristic(int x_1, int y_1, int x_2, int y_2){
    // Using Manhattan distance
   return abs(x_2 - x_1) + abs(y_2 - y_1);
}

bool CheckValidCell(int x, int y, vector<vector<State>> &grid){
    bool on_grid_x = (x >= 0 && x < grid.size());
    bool on_grid_y = (y >= 0 && y < grid[0].size());
    if (on_grid_x && on_grid_y){
        return grid[x][y] == State::kEmpty;
    } else{
        return false;
    }
}

// TODO: Write the AddToOpen function here:
void AddToOpen(int x, int y, int g, int h,
        vector<vector<int>> &openNodes,
        vector<vector<State>> &board
        ){
    openNodes.push_back(vector{x,y,g,h});
    board[x][y] = State::kClosed;
}
// TODO: ExpandNeighbors(arguments) {
void ExpandNeighbors(const vector<int> &current,
        int goal[2],
        vector<vector<int>> &openlist,
        vector<vector<State>> &grid) {
// Get current node's data.
  int x = current[0];
  int y = current[1];
  int g = current[2];

// Loop through current node's potential neighbors.
  for (int i = 0; i < 4; i++) {
    int x2 = x + delta[i][0];
    int y2 = y + delta[i][1];

    // Check that the potential neighbor's x2 and y2 values are on the grid and not closed.
    if (CheckValidCell(x2, y2, grid)) {
    // Increment g value and add neighbor to open list.
      int g2 = g + 1;
      int h2 = Heuristic(x2, y2, goal[0], goal[1]);
      AddToOpen(x2, y2, g2, h2, openlist, grid);
      }
   }
}



// TODO: Write the Search function stub here. 
vector<vector<State>> Search(vector<vector<State>> board, vector<int> start,
        vector<int> stop){

    // TODO: Initialize the starting node.
    vector<vector<int>> open {};
    
    // TODO: Initialize the starting node.
    int x = start[0];
    int y = start[1];
    int g = 0;
    
    int h = Heuristic(x,y,stop[0], stop[1]);
    AddToOpen(x,y,g,h, open, board);

    // TODO: while open vector is non empty {
    while (open.size()>0){
        // TODO: sort the open list using CellSort, and get current node.
        CellSort(&open);    
        // TODO: Get the x and y values from the current node and set grid[x][y]
        // to the kPath.
        vector<int> currentNode = open.back();
        // removing the last node:
        open.pop_back();
        x = currentNode[0];
        y = currentNode[1];

        board[x][y] = State::kPath;
        // TODO: Check if you've reach the goal. If so, return grid.
        if ((x == stop[0]) && (y == stop[1])){
            board[start[0]][start[1]] = State::kStart;
            board[stop[0]][stop[1]] = State::kFinish;
            return board;
        } 
        // If we're not done, expand search to current node's neighbors. This step will be completed in a later quiz.
        // ExpandNeighbors    
        
    //} // TODO: End while loop
    }
    
    cout << "No Path Found!" << "\n";
    vector<vector<State>> path;

    return path; 
}


string CellString(State cell){
    switch(cell) {
        case State::kObstacle: return "⛰️   ";
        case State::kPath: return "🚗   ";
        case State::kStart: return "🚦   ";
        case State::kFinish: return "🏁   ";
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
