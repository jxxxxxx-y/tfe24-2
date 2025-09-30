#include <fmt/chrono.h>
#include <fmt/format.h>

#include "config.h"

void changeValueByParameter (int value){
        value = 99;
        fmt::print("y inside function: {}\n", value);
    };

void changeValueByPointer (int *ptr){
    *ptr = 77;
    fmt::print("y inside function: {}\n", *ptr);
};

auto main(int argc, char **argv) -> int
{

    /**
     * The {fmt} lib is a cross platform library for printing and formatting text
     * it is much more convenient than std::cout and printf
     * More info at https://fmt.dev/latest/api.html
     */
    //fmt::print("Hello, {}!\n", tfe24::PROJECT_NAME);


    // Part 1: Pointer-basics
    int x = 10;
    int *p = &x;
    fmt::print("The value of x is: {}\n", x);
    fmt::print("Adress of x is: {}\n", fmt::ptr(&x));
    fmt::print("The value of p is: {}\n", *p);
    fmt::print("Adress of p is: {}\n", fmt::ptr(&p));
    *p = 42;
    fmt::print("The new value of x is: {}\n", x);
    fmt::print("The new value of p is: {}\n", *p);
    fmt::print("\n");

    // Part 2: Dynamic memory allocation
    double* d = new double(3.1415);
    fmt::print("The value of d is: {}\n", *d);
    fmt::print("Adress of d is: {}\n", fmt::ptr(&d));
    delete d;
    fmt::print("\n");

    // Part 3: functions with pointers
    int y = 5;
    changeValueByParameter (y); 
    fmt::print("y after function: {}\n", y);
    int *ptr = &y;
    changeValueByPointer (&y);
    fmt::print("y after function: {}\n", *ptr);



    return 0; /* exit gracefully*/
}

