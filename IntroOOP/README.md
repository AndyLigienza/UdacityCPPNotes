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




