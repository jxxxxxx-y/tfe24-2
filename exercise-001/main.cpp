#include <fmt/chrono.h>
#include <fmt/format.h>

#include "config.h"

void changeValueByParameter (int value);
void changeValueByReference (int& ref);

auto main(int argc, char **argv) -> int
{

    /**
     * The {fmt} lib is a cross platform library for printing and formatting text
     * it is much more convenient than std::cout and printf
     * More info at https://fmt.dev/latest/api.html
     */
    //fmt::print("Hello, {}!\n", tfe24::PROJECT_NAME);

    // Part 1: References basics
    int x = 10;
    int& r = x; 
    fmt::print("x = {}\n r = {}\n", x, r);
    r = 42;
    fmt::print("x = {}\n r = {}\n", x, r);

    // Part 2: functions with references
    int y = 5;
    changeValueByParameter(y);
    fmt::print("y after function: {}\n", y);
    changeValueByReference(y);
    fmt::print("y after function: {}\n", y);

    return 0; /* exit gracefully*/
}
void changeValueByParameter (int value){
    value = 99;
    fmt::print("y inside function: {}\n", value);
}
void changeValueByReference (int& ref){
    ref = 77;
    fmt::print("y inside function: {}\n", ref);
}