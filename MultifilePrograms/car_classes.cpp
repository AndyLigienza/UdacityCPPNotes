#include <iostream>
#include <string>
using std::string;
using std::cout;

// The Car class
class Car {
public:
// Method to print data.
void PrintCarData() 
{
cout << "The distance that the " << color << " car " << number << " has traveled is: " << distance << "\n";
}

// Method to increment the distance travelled.
void IncrementDistance() 
{
distance++;
}
// adding a constructor:
Car(string c, int n){
    // setting the class attributes with the values passed onto the constructor
    color=c;
    number=n;
}
string color;
int distance = 0;
int number;
};

int main() 
{
// Create class instances for each car.
Car car_1 = Car("green", 1);
Car car_2 = Car("red", 2);
Car car_3 = Car("blue", 3);

// Increment car_1's position by 1.
car_1.IncrementDistance();

// Print out the position and color of each car.
car_1.PrintCarData();
car_2.PrintCarData();
car_3.PrintCarData();

}
