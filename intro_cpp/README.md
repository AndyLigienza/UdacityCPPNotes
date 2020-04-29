##### Preface Notes:
You may need to use `g++ -std=c++11` to specify compiler version for certain tasks (see vectors.cpp)

### Compiled vs Interpreted
Python is a commonly known interpreted language. This means the programe will compile at runtime.

C++ however, is a compiled language. We compile using a compiler (e.g. `g++`) before running the programe. Bjarne Stroustrup claims the compiler helps to avoid runtime bugs. 

Thinking about where c++ is likely to run (Toaster, Microwaves, Servers etc) there is no programmer around who can debug if any runtime errors occur. Therefore, the compiler ensures we cannot pass sub-optimal code as it will result in a non-compile.

### Types

C++ is a strongly staticly typed language which in essence means that a lot of the variables require the code author to declare types of a new variable before the usage of the variable itself.

However, when dealing with hadware we have to weaken the type checking. For instance, until to make a variable of a given type, it is simply memory reserved by the OS. There are also ways of supressing the type checking by converting an integer into a pointer for a device register.  

### Vectors

One of the most basic data types is a Vector. This is a Linear sequence of continuosly allocated memory.

There are also Linked Lists which are used adhoc, Hash Tables for lookups and more.




