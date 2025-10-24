#include <fmt/chrono.h>
#include <fmt/format.h>

#include "config.h"

void changeValueByParameter(int value);
void changeValueByReference(int& ref);

auto main(int argc, char **argv) -> int
{

    class Foo {
    public:
        Foo(int& value) :x_(value){
            //x_ = value;
        }
        ~Foo() = default;
        void print() {
            fmt::println("The value of x_ = {} in Class Foo", x_);
        }
    private:
        int& x_;
    };

    /**
     * The {fmt} lib is a cross platform library for printing and formatting text
     * it is much more convenient than std::cout and printf
     * More info at https://fmt.dev/latest/api.html
     */
    fmt::print("Hello, {}!\n", tfe24::PROJECT_NAME);

    int x = 10;
    int y = 4711;

    int& ref = x; // ref is a reference to x
    ref = y;

    fmt::print("x = {}, ref = {}\n", x, ref);
    ref = 20; // changing ref changes x
    fmt::print("x = {}, ref = {}\n", x, ref);

    changeValueByParameter(x);
    fmt::println("After changeValueByParameter(x): x = {}, ref = {}", x, ref);

    changeValueByReference(x);
    fmt::println("After changeValueByReference(x): x = {}, ref = {}", x, ref);
    
    Foo foo(ref);
    foo.print();

    return 0; /* exit gracefully*/
}

void changeValueByParameter(int value) {
    value = 99; // changing value does not change x
}

void changeValueByReference(int& ref) {
    ref = 77; // changing ref changes x
}
