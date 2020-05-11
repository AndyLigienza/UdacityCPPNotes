### Introduction

`A*` search is an efficient path mapping search algorithm for a graphical algorithms.
This section will start with a guide into algorithms and introduce the programming 
aspects throughout.


#### Motion Planning

The fundamental problem with motion planning is that you are given the following:
1. Map
2. Starting Location
3. Goal Location
4. Cost 

With the goal of finding the minimum cost path.

#### Basics of AStar

imagine a `5*5` grid in which you start in the upper left quadrant. You expand from 
`[0,0]` -> `[0,1]` and `[1,0]`. These new nodes all have a "cost" of 1 (g). You than 
expand from each of these new nodes to all the surrounding nodes. ie:
- `[0,1]` -> `[[0,2],[1,1]]`
- `[1,0]` -> `[[2,0],[1,1]]` 

with each node `[[0,2],[1,1],[2,0]]` (notice how 1,1 overlapped) costing 2 (g).
Each "tree" would expand (given whatever restrictions) until the smallest cost path was found.

This algorithm described by Sebastian is very similar to other search algorithms 
you may have seen before, such as [breadth-first search](https://en.wikipedia.org/wiki/Breadth-first_search),
except for the additional step of computing a heuristic and using that heuristic (in addition 
to the cost) to find the next node.

#### AStar Psuedocode
**Search**( grid, initial_point, goal_point ) :

1. Initialize an empty list of open nodes.

2. Initialize a starting node with the following:

    - x and y values given by initial_point.
    - g = 0, where g is the cost for each move.
    - h given by the heuristic function (a function of the current coordinates and the goal).
3. Add the new node to the list of open nodes.

4. while the list of open nodes is nonempty:

    1. Sort the open list by f-value
    2. Pop the optimal cell (called the current cell).
    3. Mark the cell's coordinates in the grid as part of the path.
    4. if the current cell is the goal cell:

        - return the grid.
    5. else, expand the search to the current node's neighbors. This includes the following steps:

        - Check each neighbor cell in the grid to ensure that the cell is empty: it hasn't been closed and is not an obstacle.
        - If the cell is empty, compute the cost (g value) and the heuristic, and add to the list of open nodes.
        - Mark the cell as closed.
5. If you exit the while loop because the list of open nodes is empty, you have run out of new nodes to explore and haven't found a path.


**A Star Summary**:
algorithm finds a path from the start node to the end node by checking for 
open neighbors of the current node, computing a heuristic for each of the 
neighbors, and adding those neighbors to the list of open nodes to explore 
next. The next node to explore is the one with the lowest total cost + 
heuristic (g + h). This process is repeated until the end is found, as long as
there are still open nodes to explore.


We will be using the following code structue to build the `A*` path finding algorithm:

![Udacity Image](Capture.PNG)


The code for the `A*` search algorithm has been broken down into the following 
functions:

- CellSort() - sorts the open list according to the sum of h + g
- ExpandNeighbors() - loops through the current node's neighbors and calls appropriate functions to add neighbors to the open list
- CheckValidCell() - ensures that the potential neighbor coordinates are on the grid and that the cell is open
- Heuristic() - computes the distance to the goal
- AddToOpen() - adds the node to the open list and marks the grid cell as closed

You will be implementing these functions along with a few other small helper 
functions throughout the rest of this lesson to complete the ASCII `A*`
search program.


### Pass by Reference
you've written functions that accept and return various kinds of objects. 
However, in all of the functions you've written so far, the objects returned 
by the function are different from the objects provided to the function. In other
words, when the function is called on some data, a copy of that data is made, 
and the function operates on a copy of the data instead of the original data. 
This is referred to as pass by value, since only a copy of the values of an
object are passed to the function, and not the actual objects itself.

ie: 
```cpp
include <iostream>
using std::cout;


int MultiplyByTwo(int i) {
    i = 2*i;
    return i;
}

int main() {
    int a = 5;
    cout << "The int a equals: " << a << "\n";
    int b = MultiplyByTwo(a);
    cout << "The int b equals: " << b << "\n";
    cout << "The int a still equals: " << a << "\n";
}
```

### Constants

This example highlights how to use `const` to promise not to modify a variable,
even though the variable can only be evaluated at run time.

The example also show how to use `constexpr` to guarantee that a variable can
be evaluated at compile time.

```cpp 
#include <iostream>

int main()
{
   int i;
   std::cout << "Enter an integer value for i: ";
   std::cin >> i;
   const int j = i * 2;  // "j can only be evaluated at run time."
   // "But I promise not to change it after it is initialized."
                                                  
   constexpr int k = 3;  // "k, in contrast, can be evaluated at compile time."
  
   std::cout << "j = " << j << "\n";
   std::cout << "k = " << k << "\n";
}

```
A common usage of `const` is to guard against accidentally changing a variable,
especially when it is passed-by-reference as a function argument.

```cpp
#include <iostream>
#include <vector>

int sum(const std::vector<int> &v)
{
        int sum = 0;
            for(int i : v)
                        sum += i;
                            return sum;
}

int main()
{
        std::vector<int> v {0, 1, 2, 3, 4};
            std::cout << sum(v) << "\n";
}

```

#### Arrays
**Note:** we have provided directional deltas in the form of a 2D (array)[https://www.programiz.com/cpp-programming/arrays]. 
An array is a C++ container much like a vector, although without the ability 
to change size after initialization. Arrays can be accessed and iterated over just as vectors.

In the exercise, you can iterate over these delta values to check the 
neighbors in each direction:

```cpp
// directional deltas
const int delta[4][2]{{-1, 0}, {0, -1}, {1, 0}, {0, 1}};
```

Arrays are a lower level data structure than vectors, and can be slightly more 
efficient, in terms of memory and element access. However, this efficiency comes 
with a price. Unlike vectors, which can be extended with more elements, 
arrays have a fixed length. Additionally, arrays may require careful memory 
management, depending how they are used.


The example in the project code is a good use case for an array, as it was not 
intended to be changed during the execution of the program. However, a vector 
would have worked there as well.

Due to the allocation of memory issue, Bjorne does not believe that arrays belong
within application code. This is a source of controversy between c and c++.


