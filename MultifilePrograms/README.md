### Intro

We will learn about several key concepts for writing larger projects:
- Header Files:
    - Using headers to break a single file into multiple files
- Build Systems:
    - CMake and Make
- Tools for writing Larger Programs:
    - References
    - Pointers
    - Maps
    - Classes and Object-Oriented Programming in C++

#### Header Files
Header files, or .h files, allow related function, method, and class
declarations to be collected in one place. The corresponding definitions can 
then be placed in .cpp files. The compiler considers a header declaration a 
"promise" that the definition will be found later in the code, so if the 
compiler reaches a function that hasn't been defined yet, it can continue on 
compiling until the definition is found. This allows functions to be defined 
(and declared) in arbitrary order.

One other way to solve the code problem above (without rearranging the 
functions) would have been to declare each function at the top of the file. 
A function declaration is much like the first line of a function definition - 
it contains the return type, function name, and input variable types. The 
details of the function definition are not needed for the declaration though.

To avoid a single file from becomming cluttered with declarations and 
definitions for every function, it is customary to declare the functions in 
another file, called the header file. In C++, the header file will have 
filetype `.h`, and the contents of the header file must be included at the 
top of the `.cpp` file. See the following example for a refactoring of the 
code above into a header and a cpp file.

```cpp
// The header file with just the function declarations.
// When you click the "Run Code" button, this file will
// be saved as header_example.h.
#ifndef HEADER_EXAMPLE_H
#define HEADER_EXAMPLE_H

void OuterFunction(int);
void InnerFunction(int);

#endif
```

```cpp
// The contents of header_example.h are included in 
// the corresponding .cpp file using quotes:
#include "header_example.h"

#include <iostream>
using std::cout;

void OuterFunction(int i) 
{
        InnerFunction(i);
}

void InnerFunction(int i) 
{
        cout << "The value of the integer is: " << i << "\n";
}

int main() 
{
        int a = 5;
            OuterFunction(a);
}
```

Notice that the code from the first example was fixed without having to rearrange the functions! In the code above, you might also have noticed several other things:
- The function declarations in the header file don't need variable names, just variable types. You can put names in the declaration, however, and doing this often makes the code easier to read.
- The `#include` statement for the header used quotes `" "` around the file name, and not angle brackets `<>`. We have stored the header in the same directory as the `.cpp` file, and the quotes tell the preprocessor to look for the file in the same directory as the current file - not in the usual set of directories where libraries are typically stored.
- Finally, there is a preprocessor directive:
    ```cpp
        #ifndef HEADER_EXAMPLE_H
        #define HEADER_EXAMPLE_H
    ``` 
    
at the top of the header, along with an `#endif` at the end. This is called an 
"include guard". Since the header will be included into another file, and 
`#include` just pastes contents into a file, the include guard prevents the 
same file from being pasted multiple times into another file. This might 
happen if multiple files include the same header, and then are all included 
into the same `main.cpp`, for example. 
The `ifndef` checks if `HEADER_EXAMPLE_H` has not been defined in the file 
already. If it has not been defined yet, then it is defined with 
`#define HEADER_EXAMPLE_H`, and the rest of the header is used. If 
`HEADER_EXAMPLE_H` has already been defined, then the preprocessor does not 
enter the `ifndef` block.
**Note:** There are other ways to do this. Another common way is to use an 
`#pragma once`preprocessor directive, but we won't cover that in detail here. 
See [this Wikipedia article](https://en.wikipedia.org/wiki/Include_guard) for 
examples.

Running `main2.cpp`:
`c17 main2.cpp increment_and_sum.cpp vect_add_one.cpp`



