### Structures

Structures allow developers to create their own types ("user-defined" types) to 
aggregate data relevant to their needs.

For example, a user might define a Rectangle structure to hold data about 
rectangles used in a program.

```cpp
struct Rectangle {
  float length;
  float width;
};
```

### Types
Every C++ variable is defined with a [type](http://www.cplusplus.com/doc/tutorial/variables/).

In this example, the "type" of value is int. Furthermore, rectangle is "of type" 
Rectangle, and earth has type Sphere.

### Fundamental Types

C++ includes [fundamental types](https://en.cppreference.com/w/cpp/language/types), such 
as int and float. These fundamental types are sometimes 
called "[primitives](https://www.geeksforgeeks.org/c-data-types/)".

The Standard Library [includes additional types], such as `std::size_t` and `std::string`.


### User-Defined Type
Structures are "user-defined" types. Structures are a way for programmers to 
create types that aggregate and store data in way that makes sense 
in the context of a program.

For example, C++ does not have a fundamental type for storing a 
date. (The Standard Library does include types related to time, which 
can be converted to dates.)

A programmer might desire to create a type to store a date.

Consider the following example:

```cpp
struct Date {
  int day;
  int month;
  int year;
};
```

above creates a structure containing three "member variables" of type int: 
day, month and year.

If you then create an "instance" of this structure, you can initialize these 
member variables:

```cpp
// Create an instance of the Date structure
Date date;
// Initialize the attributes of Date
date.day = 1;
date.month = 10;
date.year = 2019;
```

### Member Initialization

Generally, we want to avoid instantiating an object with undefined members.
Ideally, we would like all members of an object to be in a valid state once 
the object is instantiated. We can change the values of the members later, but 
we want to avoid any situation in which the members are ever in an invalid state 
or undefined.

In order to ensure that objects of our Date structure always start in a valid 
state, we can initialize the members from within the structure definition.

```cpp
struct Date {
   int day{1};
   int month{1};
   int year{0};
};
```

There are also several other approaches to either 
initialize or assign member variables when the object is instantiated. 
For now, however, this approach ensures that every object of Date begins its 
life in a defined and valid state.

### Access Specifiers
Members of a structure can be specified as public or private.

By default, all members of a structure are public, unless 
they are specifically marked private.

Public members can be changed directly, by any user of the object, 
whereas private members can only be changed by the object itself.


### Private Members
This is an implementation of the Date 
structure, with all members marked as private.

```cpp
struct Date {
 private:
  int day{1};
  int month{1};
  int year{0};
};
```

Private members of a class are accessible only from 
within other member functions of the same class 
(or from their "friends", which we’ll talk about later).

There is a third access modifier called protected, which 
implies that members are accessible from other member 
functions of the same class (or from their "friends"), and also 
from members of their derived classes. We'll also 
discuss about derived classes later, when we learn about inheritance.

### Accessors and Mutators
To access private members, we typically define public 
"accessor" and "mutator" member functions 
(sometimes called "getter" and "setter" functions).

```cpp
struct Date {
 public:
  int Day() { return day; }
  void Day(int day) { this.day = day; }
  int Month() { return month; }
  void Month(int month) { this.month = month; }
  int Year() { return year; }
  void Year(int year) { this.year = year; }

 private:
  int day{1};
  int month{1};
  int year{0};
};
```

### Avoid Trivial Getters And Setters
Sometimes accessors are not necessary, or even advisable. The [C++ Core Guidelines](https://github.com/isocpp/CppCoreGuidelines/blob/master/CppCoreGuidelines.md#Rh-get) recommend, "A trivial getter or setter adds no semantic value; the data item could just as well be public."

Here is the example from the Core Guidelines:

```cpp
class Point {
    int x;
    int y;
public:
    Point(int xx, int yy) : x{xx}, y{yy} { }
    int get_x() const { return x; }  // const here promises not to modify the object
    void set_x(int xx) { x = xx; }
    int get_y() const { return y; }  // const here promises not to modify the object
    void set_y(int yy) { y = yy; }
    // no behavioral member functions
};
```
This class could be made into a struct, with no logic or "invariants", just passive data. The member variables could both be public, with no accessor functions:

```cpp
struct Point {   // Good: concise
    int x {0};   // public member variable with a default initializer of 0
    int y {0};   // public member variable with a default initializer of 0
};
```

### Classes
Classes, like structures, provide a way for C++ programmers to aggregate data together in a way that makes sense in the context of a specific program. By convention, programmers use structures when member variables are independent of each other, and [use classes when member variables are related by an "invariant"](http://isocpp.github.io/CppCoreGuidelines/CppCoreGuidelines#c2-use-class-if-the-class-has-an-invariant-use-struct-if-the-data-members-can-vary-independently).

### Invariants

An "invariant" is a rule that limits the values of member variables.

For example, in a Date class, an invariant would specify that the member variable day cannot be less than 0. Another invariant would specify that the value of day cannot exceed 28, 29, 30, or 31, depending on the month and year. Yet another invariant would limit the value of month to the range of 1 to 12.


#### Date Class
Let's define a Date class:
```cpp
// Use the keyword “class” to define a Date class:
class Date {
  int day{1};
  int month{1};
  int year{0};
};
```
So far, this class definition provides no invariants. The data members can vary independently of each other.

There is one subtle but important change that takes place when we change struct Date to class Date. By default, all members of a struct default to public, whereas all members of a class default to private. Since we have not specified access for the members of class Date, all of the members are private. In fact, we are not able to assign value to them at all!

#### Date Accessors And Mutators
As the first step to adding the appropriate invariants, let's specify that the member variable day is private. In order to access this member, we'll provide accessor and mutatot functions. Then we can add the appropriate invariants to the mutators.

```cpp
class Date {
 public:
  int Day() { return day_; }
  void Day(int d) { day_ = d; }

 private:
  int day_{1};
  int month_{1};
  int year_{0};
};
```
#### Date Invariants
Now we can add the invariants within the mutators.

```cpp
class Date {
 public:
  int Day() { return day; }
  void Day(int d) {
    if (d >= 1 && d <= 31) day_ = d;
  }

 private:
  int day_{1};
  int month_{1};
  int year_{0};
};
```
Now we have a set of invariants for the the class members!

As a general rule, member data subject to an invariant should be specified private, in order to enforce the invariant before updating the member's value.

### Constructors
Constructors are member functions of a class or struct that initialize an object. The Core Guidelines define a constructor) as:

>constructor: an operation that initializes (“constructs”) an object. Typically a constructor establishes an invariant and often acquires resources needed for an object to be used (which are then typically released by a destructor).

A constructor can take arguments, which can be used to assign values to member variables.

```cpp
class Date {
 public:
  Date(int d, int m, int y) {  // This is a constructor.
    Day(d);
  }
  int Day() { return day; }
  void Day(int d) {
    if (d >= 1 && d <= 31) day = d;
  }
  int Month() { return month; }
  void Month(int m) {
    if (m >= 1 && m <= 12) month = m;
  }
  int Year() { return year_; }
  void Year(int y) { year = y; }

 private:
  int day{1};
  int month{1};
  int year{0};
};
```
As you can see, a constructor is also able to call other member functions of the object it is constructing. In the example above, Date(int d, int m, int y) assigns a member variable by calling Day(int d).

### Default Constructor
A class object is always initialized by calling a constructor. That might lead you to wonder how it is possible to initialize a class or structure that does not define any constructor at all.

For example:
```cpp
class Date { 
  int day{1};
  int month{1};
  int year{0};
};
```
class Date { 
  int day{1};
  int month{1};
  int year{0};
};
We can initialize an object of this class, even though this class does not explicitly define a constructor.

This is possible because of the [default constructor](http://isocpp.github.io/CppCoreGuidelines/CppCoreGuidelines#cctor-constructors-assignments-and-destructors). [The compiler will define a default constructor](https://en.cppreference.com/w/cpp/language/default_constructor), which accepts no arguments, for any class or structure that does not contain an explicitly-defined constructor.

### Scope Resolution
C++ allows different [identifiers](https://en.cppreference.com/w/cpp/language/identifiers) (variable and function names) to have the same name, as long as they have different scope. For example, two different functions can each declare the variable int i, because each variable only exists within the scope of its parent function.

In some cases, scopes can overlap, in which case the compiler may need assistance in determining which identifier the programmer means to use. The process of determining which identifier to use is called ["scope resolution"](https://docs.microsoft.com/en-us/cpp/cpp/scope-resolution-operator?view=vs-2019).

### Scope Resultion Operator
`::` is the [scope resolution operator](https://www.ibm.com/support/knowledgecenter/en/ssw_ibm_i_74/rzarg/cplr175.htm)

```cpp
Person::move(); \\ Call the move the function that is a member of the Person class.
std::map m; \\ Initialize the map container from the C++ Standard Library. 
```

### Class
Each class provides its own scope. We can use the scope resolution operator to specify identifiers from a class.

This becomes particularly useful if we want to separate class declaration from class definition.
```cpp
class Date {
 public:
  int Day() const { return day; }
  void Day(int day);  // Declare member function Date::Day().
  int Month() const { return month; }
  void Month(int month) {
    if (month >= 1 && month <= 12) Date::month = month;
  }
  int Year() const { return year; }
  void Year(int year) { Date::year = year; }

 private:
  int day{1};
  int month{1};
  int year{0};
};

// Define member function Date::Day().
void Date::Day(int day) {
  if (day >= 1 && day <= 31) Date::day = day;
}
```
### Namespaces
[Namespaces](https://en.cppreference.com/w/cpp/language/namespace) allow programmers to group logically related variables and functions together. Namespaces also help to avoid conflicts between to variables that have the same name in different parts of a program.

```cpp
namespace English {
void Hello() { std::cout << "Hello, World!\n"; }
}  // namespace English

namespace Spanish {
void Hello() { std::cout << "Hola, Mundo!\n"; }
}  // namespace Spanish

int main() {
  English::Hello();
  Spanish::Hello();
}
```
In this example, we have two different void Hello() functions. If we put both of these functions in the same namespace, they would conflict and the program would not compile. However, by declaring each of these functions in a separate namespace, they are able to co-exist. Furthermore, we can specify which function to call by prefixing Hello() with the appropriate namespace, followed by the :: operator.

### std Namespace
You are already familiar with the std namespace, even if you didn't realize quite what it was. std is the namespace used by the C++ [Standard Library](https://en.wikipedia.org/wiki/C%2B%2B_Standard_Library).

Classes like std::vector and functions like std::sort are defined within the std namespace.

### Initializer Lists
[Initializer lists](https://en.cppreference.com/w/cpp/language/constructor) initialize member variables to specific values, just before the class constructor runs. This initialization ensures that class members are automatically initialized when an instance of the class is created.

```cpp
Date::Date(int day, int month, int year) : year_(y) {
  Day(day);
  Month(month);
}
```
In this example, the member value year is initialized through the initializer list, while day and month are assigned from within the constructor. Assigning day and month allows us to apply the invariants set in the mutator.

In general, [prefer initialization to assignment](http://isocpp.github.io/CppCoreGuidelines/CppCoreGuidelines#c49-prefer-initialization-to-assignment-in-constructors). Initialization sets the value as soon as the object exists, whereas assignment sets the value only after the object comes into being. This means that assignment creates and opportunity to accidentally use a variable before its value is set.

In fact, initialization lists ensure that member variables are initialized before the object is created. This is why class member variables can be declared const, but only if the member variable is initialized through an initialization list. Trying to initialize a const class member within the body of the constructor will not work.

### Initializing Constant Members
Initializer lists exist for a number of reasons. First, the compiler can optimize initialization faster from an initialization list than from within the constructor.

A second reason is a bit of a technical paradox. If you have a const class attribute, you can only initialize it using an initialization list. Otherwise, you would violate the const keyword simply by initializing the member in the constructor!

The third reason is that attributes defined as [references](http://isocpp.github.io/CppCoreGuidelines/CppCoreGuidelines#S-glossary) must use initialization lists.

This exercise showcases several advantages of initializer lists.
(review `initializationList.cpp`)



