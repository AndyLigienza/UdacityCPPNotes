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
```bash
c17 main2.cpp increment_and_sum.cpp vect_add_one.cpp
```


if you look carefully at the files above, you will see several things:
- `vect_add_one.h` is included in `increment_and_sum.cpp`.

>This is because `AddOneToEach` is used in `IncrementAndComputeVectorSum`.
Including the `vect_add_one.h` header means that the `AddOneToEach` function 
declaration is pasted into `increment_and_sum.cpp`, so no compiler error will 
occur when the `AddOneToEach` function is used.
    
- Only the header file needs to be included in another file. 

>As long as the header file is included, the corresponding function declarations 
will be included. When the compiler finds an undefined function, it has already 
seen the function's declaration. This means the compiler can continue on without 
error until it finds the definition of the function, regardless of where that 
definition is.
        
- Some libraries, like `<vector>` are included in multiple files.

>Each file is compiled alone and must have all the declarations and libraries 
necessary to compile, so the necessary libraries must be included. This is 
another reason why 
[include guards](https://github.com/isocpp/CppCoreGuidelines/blob/master/CppCoreGuidelines.md#Rs-guards) 
are important - if multiple headers were included in `main`, each with the 
same `#include <vector>` statement, you wouldn't want the `vector` header 
pasted multiple times into the code.

- The `g++` compile command from the "Run Code" button is:

```bash
g++ -std=c++17 ./code/main.cpp ./code/increment_and_sum.cpp ./code/vect_add_one.cpp && ./a.out
```

>When compiling, each of the relevant `.cpp` files must be included in the 
compile command. The `-std=c++17` specifies that we are using the C++ 17 standard 
(which happens automatically in the terminal).

### CMake and Make

In the previous notebook, you saw how example code could be split into 
multiple .h and .cpp files, and you used g++ to build all of the files 
together. For small projects with a handful of files, this works well. But what 
would happen if there were hundreds, or even thousands, of files in the project? 
You could type the names of the files at the command line each time, but there 
tools to make this easier.

Many larger C++ projects use a [build system](https://en.wikipedia.org/wiki/List_of_build_automation_software) 
to manage all the files during the build process. The build system allows for 
large projects to be compiled with a few commands, and build systems are able 
to do this in an efficient way by only recompiling files that have been changed.

#### Object Files

When you compile a project with g++, g++ actually performs several distinct tasks:
1. The preprocessor runs and executes any statement beginning with a hash 
symbol: `#`, such as `#include` statements. This ensures all code is in the 
correct location and ready to compile.
2. Each file in the source code is compiled into an "object file" (a .o file). 
Object files are platform-specific machine code that will be used to create an executable.
3. The object files are "linked" together to make a single executable. In the 
examples you have seen so far, this executable is `a.out`, but you can specify 
whatever name you want.

It is possible to have `g++` perform each of the steps separately by using the 
`-c` flag. For example,
```bash
g++ -c main.cpp
```
will produce a `main.o` file, and that file can be converted to an executable 
with 
```bash
g++ main.o
```

##### Compiling One File of Many, Step 1
In the previous example, you compiled a single source code file to an object 
file, and that object file was then converted into an executable.

Now you are going to try the same process with multiple files. Navigate to the 
`multiple_files_example` directory in the terminal to the right. 
This directory should have the `increment_and_sum` and `vect_add_one` 
files from a previous Notebook. Try compiling with the commands below:

```bash 
root@abc123defg:/home/workspace/multiple_files_example# g++ -c *.cpp
root@abc123defg:/home/workspace/multiple_files_example# g++ *.o
root@abc123defg:/home/workspace/multiple_files_example# ./a.out
```
Here, the `*` operator is a wildcard, so any matching file is selected. If you 
compile and run these files together, the executable should print:
>The total is: 14




