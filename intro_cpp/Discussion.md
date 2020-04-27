### Compiled vs Interpreted
Python is a commonly known interpreted language. This means the programe will compile at runtime.

C++ however, is a compiled language. We compile using a compiler (e.g. `g++`) before running the programe. Bjarne Stroustrup claims the compiler helps to avoid runtime bugs. 

Thinking about where c++ is likely to run (Toaster, Microwaves, Servers etc) there is no programmer around who can debug if any runtime errors occur. Therefore, the compiler ensures we cannot pass sub-optimal code as it will result in a non-compile.
