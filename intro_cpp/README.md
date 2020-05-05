##### Preface Notes:
You may need to use `g++ -std=c++17` to specify compiler version for certain tasks. 

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



### Comments
// You can use two forward slashes for single line comments.

/*
For longer comments, you can enclose the text with an opening
slash-star and closing star-slash.
*/ 

### Auto 

Previously we've seen the need to declare types. We can instead have the compiler determine the type based on the assigned value using the keyword `auto`.


### Working with Vectors

When working with vectors, we must remember that c++ will allow you to access elements out of bounds of the vector. This will effectively return incorrect results (typically a pointer to value of 0). We can however, determine the size of a vector using the `.size()` method on an instance of a vector.


### For Loops

the typical structure of a for loop requires an initial starting point, a termination cause and finally an increment assignment for the variable being evaluated. See below for reference:

 
`
int main() {
    for (int i=0; i < 5; i++) {
      cout << i << "\n";
    }
}
`

### Increments 

the *post-increment* operator `++` comes from the name of C++. There is also a pre increment operator which would work as `++i` instead of `i++`. This also works for decrements using `--`

### For Loops with Containers

C++ offers several ways to iterate over containers. One way is to use an index-based loop as above. Another way is using a "range-based loop"

`
int main() {
    // Add your code here.
    vector<int> a {1, 2, 3, 4, 5};
    for (int i: a) {
        cout << i << "\n";
    }
}
`

### Nested loops

Looping within nested vectors can cause a bit of a headache. However, this is not so difficult. We simply need to remember the types we're working with!

`
int main() {
	vector<vector<int>> b {{1, 2},
                           {3, 4},
                           {5, 6}};
    	for (vector v:b){
        	for (int i:v) {
            		cout <<i;
        	}
       		cout <<"\n";
    	}
}
`

### Functions 

functions operate in the same vain as the main loop. the basic syntax is as follows:
`
return_type FunctionName(paramater_list) {
	\\body of function 
}
`

##### Void Functions

Sometimes a function doesn't need to return anything. For example, a function might simply modify an object that is passed into it, or it might just print to the terminal. If a function doesn't need to return a value, the `void` type can be used for the return type. Using the function syntax provided above, write a function `PrintStrings` that takes two strings as arguments and prints both of them. If you are having trouble, click the solution button for help.

### Boolean Expressions

##### If Statements
C++ `if` statements work very similarly to if statements in other languages. In C++, the boolean condition is contained in parentheses `(` and `)`, and the body of the statement is enclosed in curly brackets `{` and `}`. 

##### While Loops
The syntax for a `while` loop looks very similar to the syntax for the `if` statement.

### Creating an Input Stream Object

In C++, you can use the `std::ifstream` object to handle input file streams. To do this, you will need to include the header file that provides the file streaming classes: `<fstream>`. 

Once the `<fstream>` header is included, a new input stream object can be declared and initialized using a file path `path`:
```
std::ifstream my_file;
my_file.open(path);
```

Alternatively, the declaration and initialization can be done in a single line as follows:
```
std::ifstream my_file(path);
```
C++ `ifstream` objects can also be used as a boolean to check if the stream has been created successfully. If the stream were to initialize successfully, then the `ifstream` object would evaluate to `true`. If there were to be an error opening the file or some other error creating the stream, then the `ifstream` object would evaluate to `false`.

The following cell creates an input stream from the file `"files/1.board"`:

`
int main()
{
    std::ifstream my_file;
    my_file.open("files/1.board");
    if (my_file) {
      std::cout << "The file stream has been created!" << "\n";
    }    
}
`

### Reading Data from the Stream

If the input file stream object has been successfully created, the lines of the input stream can be read using the `getline` method. In the cell below, a while loop has been added to the previous example to get each line from the stream and print it to the console.


`
int main() {
    std::ifstream my_file;
    my_file.open("files/1.board");
    if (my_file) {
        std::cout << "The file stream has been created!" << "\n";
        std::string line;
        while (getline(my_file, line)) {
            std::cout << line << "\n";
        }
    }
}
`





That's it! To recap, there are essentially four steps to reading a file:
1. `#include <fstream>`
2. Create a `std::ifstream` object using the path to your file.
3. Evaluate the `std::ifstream` object as a `bool` to ensure that the stream creation did not fail.
4. Use a `while` loop with `getline` to write file lines to a string.

### Processing Strings 

In C++ strings can be streamed into temporary variables, similarly to how files can be streamed into strings. Streaming a string allows us to work with each character individually.

One way to stream a string is to use an input string stream object `istringstream` from the `<sstream>` header. 

Once an `istringstream` object has been created, parts of the string can be streamed and stored using the "extraction operator": `>>`. The extraction operator will read until whitespace is reached or until the stream fails. Execute the following code to see how this works:

`
using std::istringstream;
using std::string;
using std::cout;

int main () 
{
    string a("199 2 3");

    istringstream my_stream(a);

    int n;
    my_stream >> n;
    cout << n << "\n";
}
`
### Adding data to Vectors
Now that you are able to process a string, you may want to store the results of the processing in a convenient container for later use. In the next exercise, you will store the streamed `int`s from each line of the board in a `vector<int>`. To do this, you will add the `int`s to the back of the vector, using the `vector` method `push_back`.

In this section, you have learned about two useful tools:

- String streams, and
- `vector` `push_back`.

The string streaming objects in C++ are very powerful, and there are many more ways that an `istringstream` can be used. We encourage you to have a look at all of the available functions in [the C++ reference](http://www.cplusplus.com/reference/sstream/istringstream/). However, at this point you are ready for the next exercise. In this exercise, you will parse string lines from the board and store the `int`s in a vector using the `istringstream` and `push_back` methods from above. Have a careful look at the examples again, and copy paste any code you think you might need before clicking the `Next` button below.







