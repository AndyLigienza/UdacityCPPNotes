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
#ing pointers with functions, some care should be taken. If a pointer is passed to a function and then assigned to a variable in the function that goes out of scope after the function finishes executing, then the pointer will have undefined behavior at that point - the memory it is pointing to might be overwritten by other parts of the program.nclude "header_example.h"

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
same `#includ <vector>` statement, you wouldn't want the `vector` header 
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
symbol: `#`, such as `#includ` statements. This ensures all code is in the 
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


##### Compiling One File of Many, Step 2

But what if you make changes to your code and you need to re-compile? In that 
case, you can compile only the file that you changed, and you can use the 
existing object files from the unchanged source files for linking.

Try changing the code in `/multiple_files_example/main.cpp` to have different 
numbers in the vector and save the file with `CTRL-s`.

When you have done that, re-compile just `main.cpp` by running:

```bash
root@abc123defg:/home/workspace/multiple_files_example# g++ -c main.cpp
root@abc123defg:/home/workspace/multiple_files_example# g++ *.o
root@abc123defg:/home/workspace/multiple_files_example# ./a.out
```

Compiling just the file you have changed saves time if there are many files 
and compilation takes a long time. However, the process above is tedious when 
using many files, especially if you don't remember which ones you have modified.

For larger projects, it is helpful to use a build system which can compile 
exactly the right files for you and take care of linking.

On the next page, we'll introduce a cross-platform build system that you'll 
be using in several of the projects in this Nanodegree program.

##### CMake and Make

CMake is an open-source, platform-independent build system. CMake uses text 
documents, denoted as `CMakeLists.txt` files, to manage build environments, 
like [make](https://en.wikipedia.org/wiki/Make_(software)).
A comprehensive tutorial on CMake would require an entire course, but you can 
learn the basics of CMake here, so you'll be ready to use it in the upcoming 
projects.

##### CMakeLists.txt

`CMakeLists.txt` files are simple text configuration files that tell CMake how 
to build your project. There can be multiple `CMakeLists.txt` files in a project.
In fact, One `CMakeList.txt` file can be included in each directory of the project,
indicating how the files in that directory should be built.

These files can be used to specify the locations of necessary packages, set build
flags and environment variables, specify target names and locations and other actions.

In the next few pages of this workspace you are going to create a basic 
`CMakeLists.txt` file to build a small project. 

If you have trouble with any of these steps, see the file `SolutionCMakeLists.txt`
in the tab on the right. 



The first lines that you'll want in your `CMakeLists.txt` are lines that specifies the 
minimum versions of cmake and `C++` required to build the project. Add the following 
lines to your `CMakeLists.txt` and save the file:

```bash 
cmake_minimum_required(VERSION 3.5.1)

set(CMAKE_CXX_STANDARD 14)
```
These lines set the minimum cmake version required to 3.5.1 and set the 
environment variable `CMAKE_CXX_STANDARD` so CMake uses C++ 14. On your own 
computer, if you have a recent `g++` compiler, you could use C++ 17 instead.

##### CMake Step 2
CMake requires that we name the project, so you should choose a name for the 
project and then add the following line to `CMakeLists.txt`:

```bash 
project(<your_project_name>)
```
You can choose any name you want, but be sure to change `<your_project_name>`
to the actual name of the project!

##### CMake Step 3
Next, we want to add an executable to this project. You can do that with the 
`add_executable` command by specifying the executable name, along with the 
locations of all the source files that you will need. CMake has the ability to 
automatically find source files in a directory, but for now, you can just specify each file needed:

```bash 
add_executable(your_executable_name  path_to_file_1  path_to_file_2 ...)
```
Hint: The source files you need are the *three* .cpp files in the `src/` 
directory. You can specify the path relative to the `CMakeLists.txt` file, so 
`src/main.cpp` would work, for example.


##### CMake Step 4

A typical CMake project will have a `build` directory in the same place as the 
top-level `CMakeLists.txt`. Make a build directory in the 
`/home/workspace/cmake_example` folder:

```bash
root@abc123defg:/home/workspace/cmake_example# mkdir build
root@abc123defg:/home/workspace/cmake_example# cd build
```

From within the build directory, you can now run CMake as follows:

```bash 
root@abc123defg:/home/workspace/cmake_example/build# cmake ..
root@abc123defg:/home/workspace/cmake_example/build# make
```

The first line directs the `cmake` command at the top-level `CMakeLists.txt` 
file with `..`. This command uses the `CMakeLists.txt` to configure the project 
and create a `Makefile` in the build directory.

In the second line, `make` finds the `Makefile` and uses the instructions in
the `Makefile` to build the project.

##### CMake Step 5

If everything has worked correctly, you should now be able to run your 
executable from the build folder:

```bash
root@abc123defg:/home/workspace/cmake_example/build# ./your_executable_name
```
This executable should print:

>The total is: 14

just as it did in the previous workspace.

If you dont remember the name of your executable, the last line of the `make`
output should tell you:
```bash
[100%] Built target <your_executable_name>
```

##### CMake Step 6
Now that your project builds correctly, try modifying one of the files. 
When you are ready to run the project again, you'll only need to run the `make` 
command from the build folder, and only that file will be compiled again. 
Try it now!

In general, CMake only needs to be run once for a project, unless you are 
changing build options (e.g. using different build flags or changing where 
you store your files).

`Make` will be able to keep track of which files have changed and compile only 
those that need to be compiled before building.

**Note**: If you do re-run CMake, or if you are having problems with your build, 
*it can be helpful to delete your build directory and start from scratch. 
Otherwise, some environment variables may not be reset correctly.*


#### References
As mentioned previously, a reference is another name given to an existing 
variable. On the left hand side of any variable declaration, the `&` 
operator can be used to declare a reference. 

```cpp
#include <iostream>
using std::cout;

int main() 
{
  int i = 1;
            
  // Declare a reference to i.
  int& j = i;
  cout << "The value of j is: " << j << "\n";
  
 // Change the value of i.
 i = 5;
 cout << "The value of i is changed to: " << i << "\n";
 cout << "The value of j is now: " << j << "\n";
 
  // Change the value of the reference.
  // Since reference is just another name for the variable,
  // th
  j = 7;
  cout << "The value of j is now: " << j << "\n";
  cout << "The value of i is changed to: " << i << "\n";
}
```

### Pointers

Pointers have traditionally been a stumbling block for many students 
learning C++, but they do not need to be!

>A C++ pointer is just a variable that stores the memory address of an object 
in your program.

That is the most important thing to understand and remember about pointers - 
they essentially keep track of *where* a variable is stored in the computer's memory.

in the previous lessons, you implemented `A*` search in a single file without 
using C++ pointers, except in `CellSort` code that was provided for you; a C++ 
program can be written without using pointers extensively (or at all). 
However, pointers give you better control over how your program uses memory. 
However, much like the pass-by-reference example that you saw previously, it 
can often be far more efficient to perform an operation with a pointer to an 
object than performing the same operation using the object itself.


Pointers are an extremely important part of the C++ language, and as you are 
exposed to more C++ code, you will certainly encounter them. 
In this notebook, you will become familiar with basic pointers so you get 
comfortable with the syntax, and you will be ready to use them in the 
course project code.

#### Accessing a Memory Address

Each variable in a program stores its contents in the computer's memory, and 
each chunk of the memory has an address number. For a given variable, 
the memory address can be accessed using an ampersand in front of the variable. 
To see an example of this, execute the following code which displays the 
[hexadecimal](https://en.wikipedia.org/wiki/Hexadecimal) memory addresses of 
the variables `i` and `j`:
```cpp
#include <iostream>
using std::cout;

int main() {
  int i = 5;
  int j = 6;
  
  // Print the memory addresses of i and j
  cout << "The address of i is: " << &i << "\n";
  cout << "The address of j is: " << &j << "\n";
}
```

At this point, you might be wondering why the same symbol `&` can be used to 
both access memory addresses and, as you've seen before, pass references into 
a function. This is a great thing to wonder about. The overloading of the 
ampersand symbol `&` and the `*` symbol probably contribute to much of the 
confusion around pointers.

> **The symbols `&` and `*` have a different meaning, depending on which side 
of an equation they appear.**

_This is extremely important to remember._ For the `&` symbol, if it appears 
on the left side of an equation (e.g. when declaring a variable), it means 
that the variable is declared as a reference. If the `&` appears on the right 
side of an equation, or before a previously defined variable, it is used to 
return a memory address, as in the example above.

Try using the cell above to create new variables and print out their addresses! 

#### Storing a Memory Address (int type)

Once a memory address is accessed, you can store it using a pointer. A pointer 
can be declared by using the `*` operator in the declaration. See the 
following code for an example:
```cpp
#include <iostream>
using std::cout;

int main() 
{
  int i = 5;
  // A pointer pointer_to_i is declared and initialized to the address of i.
  int* pointer_to_i = &i;
                    
  // Print the memory addresses of i and j
  cout << "The address of i is:          " << &i << "\n";
  cout << "The variable pointer_to_i is: " << pointer_to_i << "\n";
}
```

As you can see from the code, the variable `pointer_to_i` is declared as a 
pointer to an `int` using the `*` symbol, and `pointer_to_i` is set to the 
address of `i`. From the printout, it can be seen that `pointer_to_i` holds 
the same value as the address of `i`.




#### Getting an Object Back from a Pointer Address

Once you have a pointer, you may want to retrieve the object it is pointing to. 
In this case, the `*` symbol can be used again. This time, however, it will 
appear on the right hand side of an equation or in front of an already-defined 
variable, so the meaning is different. In this case, it is called the "dereferencing 
operator", and it returns the object being pointed to. You can see how this works 
with the code below:

```cpp
#include <iostream>
using std::cout;

int main() 
{
  int i = 5;
  // A pointer pointer_to_i is declared and initialized to the address of i.
  int* pointer_to_i = &i;
                    
  // Print the memory addresses of i and j
  cout << "The address of i is:          " << &i << "\n";
  cout << "The variable pointer_to_i is: " << pointer_to_i << "\n";
  cout << "The value of the variable pointed to by pointer_to_i is: " << *pointer_to_i << "\n";
}
```
In the following example, the code is similar to above, except that the object 
that is being pointed to is changed before the pointer is dereferenced. 
Before executing the following code, guess what you think will happen to the 
value of the dereferenced pointer.

```cpp
#include <iostream>
using std::cout;

int main() {
  int i = 5;
  // A pointer pointer_to_i is declared and initialized to the address of i.
  int* pointer_to_i = &i;
                    
  // Print the memory addresses of i and j
  cout << "The address of i is:          " << &i << "\n";
  cout << "The variable pointer_to_i is: " << pointer_to_i << "\n";
                                    
  // The value of i is changed.
  i = 7;
  cout << "The new value of the variable i is                     : " << i << "\n";
  cout << "The value of the variable pointed to by pointer_to_i is: " << *pointer_to_i << "\n";
}
```



### Pointers to Other Object Types

Although the type of object being pointed to must be included in a pointer 
declaration, pointers hold the same kind of value for every type of object: 
just a memory address to where the object is stored. In the following code, 
a vector is declared. Write your own code to create a pointer to the address 
of that vector. Then, dereference your pointer and print the value of the 
first item in the vector.

```cpp
#include <iostream>
#include <vector>
using std::cout;
using std::vector;

int main() {
   // Vector v is declared and initialized to {1, 2, 3}
   vector<int> v {1, 2, 3};
                
   // Declare and initialize a pointer to the address of v here:
   vector<int> *point_to_v = &v; 
   // The following loops over each int a in the vector v and prints.
   // Note that this uses a "range-based" for loop:
   // https://github.com/isocpp/CppCoreGuidelines/blob/master/CppCoreGuidelines.md#Res-for-range
   for (int a: v) {
   cout << a << "\n";
   }
   cout<<"Pointer location: " <<point_to_v<<"\n";
   cout<<"value at pointer: " <<(*point_to_v)[0]<<"\n";
   // Dereference your pointer to v and print the int at index 0 here (note: you should print 1):
}
```

#### Passing Pointers to a Function

Pointers can be used in another form of pass-by-reference when working with 
functions. When used in this context, they work much like the references that 
you used for pass-by reference previously. If the pointer is pointing to a large
object, it can be much more efficient to pass the pointer to a function than 
to pass a copy of the object as with pass-by-value.

In the following code, a pointer to an int is created, and that pointer is passed 
to a function. The object pointed to is then modified in the function.

```cpp
#include <iostream>
using std::cout;

void AddOne(int* j)
{
   // Dereference the pointer and increment the int being pointed to.
   (*j)++;
}

int main() 
{
   int i = 1;
   cout << "The value of i is: " << i << "\n";
                
   // Declare a pointer to i:
   int* pi = &i;
   AddOne(pi);
   cout << "The value of i is now: " << i << "\n";
}
```
When using pointers with functions, some care should be taken. If a pointer is 
passed to a function and then assigned to a variable in the function that goes out
of scope after the function finishes executing, then the pointer will have undefined
behavior at that point - the memory it is pointing to might be overwritten 
by other parts of the program.



#### Returning a Pointer from a Function

You can also return a pointer from a function. As mentioned just above, if you do 
this, you must be careful that the object being pointed to doesn't go out of 
scope when the function finishes executing. If the object goes out of scope, the 
memory address being pointed to might then be used for something else.

In the example below, a reference is passed into a function and a pointer is returned.
This is safe since the pointer being returned points to a reference - a variable 
that exists outside of the function and will not go out of scope in the function.

```
#include <iostream>
using std::cout;

int* AddOne(int& j) 
{
  // Increment the referenced int and return the
  // address of j.
  j++;
  return &j;
}

int main() 
{
  int i = 1;
  cout << "The value of i is: " << i << "\n";
                
  // Declare a pointer and initialize to the value
  // returned by AddOne:
  int* my_pointer = AddOne(i);
  cout << "The value of i is now: " << i << "\n";
  cout << "The value of the int pointed to by my_pointer is: " << *my_pointer << "\n";
}
```
#### References vs Pointers

Pointers and references can have similar use cases in C++. As seen previously 
both references and pointers can be used in pass-by-reference to a function. 
Additionally, they both provide an alternative way to access an existing variable: 
pointers through the variable's address, and references through another name for 
that variable. But what are the differences between the two, and when should each 
be used? The following list summarizes some of the differences between pointers and 
references, as well as when each should be used:

![Udacity Image](Capture.PNG)
