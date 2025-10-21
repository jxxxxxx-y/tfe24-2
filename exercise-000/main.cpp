#include <fmt/chrono.h>
#include <fmt/format.h>

#include "config.h"

void changeValueByParameter(int value) {
    value = 42;
}

void changeValueByPointer(double* ptr) {
    *ptr = 42;
}

auto main(int argc, char **argv) -> int
{

    /**
     * The {fmt} lib is a cross platform library for printing and formatting text
     * it is much more convenient than std::cout and printf
     * More info at https://fmt.dev/latest/api.html
     */
    fmt::print("Hello, {}!\n", tfe24::PROJECT_NAME);

    int x = 10;
    int *p = &x;
    
    fmt::println("The value of x: {},             the address of x:{}",x, fmt::ptr(&x));
    fmt::println("The value p is pointing to: {}, the address of p:{}",*p, fmt::ptr(p));

    // change the vale of the variable p is pointing at
    *p = 42;
    fmt::println("The value p is pointing to: {}, the address of p:{}",*p, fmt::ptr(p));
    fmt::println("The value of x: {},             the address of x:{}",x, fmt::ptr(&x));

    // Let's double the fun
    double bar = 100.001;
    double* pD = &bar;

    fmt::println("The value pD is pointing to: {}, the address of pD:{}",*pD, fmt::ptr(pD));
    fmt::println("The value of x: {},             the address of x:{}",bar, fmt::ptr(&bar));

    pD = new double(3.1415);
    fmt::println("The value pD is pointing to: {}, the address of pD:{}",*pD, fmt::ptr(pD));
    fmt::println("The value of x: {},             the address of x:{}",bar, fmt::ptr(&bar));


    *pD = 47.11;
    fmt::println("The value pD is pointing to: {}, the address of pD:{}",*pD, fmt::ptr(pD));
    fmt::println("The value of x: {},             the address of x:{}",bar, fmt::ptr(&bar));

    fmt::println("The value of bar is {}, the address of bar:{}",bar, fmt::ptr(&bar));
    changeValueByParameter(bar);
    fmt::println("After the call to changeValueByParameter");
    fmt::println("The value of bar is {}, the address of bar:{}",bar, fmt::ptr(&bar));

    fmt::println("The value pD is pointing to: {}, the address of pD:{}",*pD, fmt::ptr(pD));
    changeValueByPointer(pD);
    fmt::println("After the call to changeValueByPointer");
    fmt::println("The value pD is pointing to: {}, the address of pD:{}",*pD, fmt::ptr(pD));
    

    delete pD;
    return 0; /* exit gracefully*/
}
