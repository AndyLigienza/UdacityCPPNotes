#include <iostream>
#include <cassert>

// Test in main
int main()
{
    class Date {
        public:
            int Day(){return day_;}
            int Month(){return month_;}
            int Year(){return year_;}
            
            void Day(int day){
                if (day <= 31 && day > 0){
                    day_ = day;
                }
            }
            void Month(int month){
                if (month <= 12 && month > 0){
                    month_ = month;
                }
            }
            void Year(int year){
                if (year >= 0){
                    year_ = year;
                }
            }
        private:
            int day_{1};
            int month_{1};
            int year_{0};
    };
    Date date;
    date.Day(-1);
    date.Month(14);
    date.Year(2000);
    assert(date.Day() != -1);
    assert(date.Month() != 14);
    assert(date.Year() == 2000);
      std::cout << date.Day() << "/" << date.Month() << "/" << date.Year() << "\n";
}