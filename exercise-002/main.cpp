#include <fmt/chrono.h>
#include <fmt/format.h>

#include "CLI/CLI.hpp"
#include "config.h"

// global variables in the various segments

int bss;
int bss1 = 0;

int data = 23;
int data1 = 29;

const int rodata = 4711;
const int rodata1 = 4712;

void foo() { 
    fmt::print("Hello from foo!\\n"); 
}

auto main(int argc, char **argv) -> int
{

    int localVar = 2;
    int localVar1;

    /**
     * CLI11 is a command line parser to add command line options
     * More info at https://github.com/CLIUtils/CLI11#usage
     */
    CLI::App app{PROJECT_NAME};
    try
    {
        app.set_version_flag("-V,--version", fmt::format("{} {}", PROJECT_VER, PROJECT_BUILD_DATE));
        app.parse(argc, argv);
    }
    catch (const CLI::ParseError &e)
    {
        return app.exit(e);
    }

    /**
     * The {fmt} lib is a cross platform library for printing and formatting text
     * it is much more convenient than std::cout and printf
     * More info at https://fmt.dev/latest/api.html
     */
    fmt::print("Hello, {}!\n", app.get_name());

    
    fmt::println("The value of the variable bss: {} and its address {}", bss, fmt::ptr(&bss));
    fmt::println("The value of the variable bss: {} and its address {}", bss1, fmt::ptr(&bss1));

    fmt::println("The value of the variable data: {} and its address {}", data, fmt::ptr(&data));
    fmt::println("The value of the variable data: {} and its address {}", data1, fmt::ptr(&data1));

    fmt::println("The value of the variable rodata: {} and its address {}", rodata, fmt::ptr(&rodata));
    fmt::println("The value of the variable rodata: {} and its address {}", rodata1, fmt::ptr(&rodata1));

    fmt::println("------------------------------------------------------------------------------------------------");
    fmt::println("The value of the variable localVar: {} and its address {}", localVar, fmt::ptr(&localVar));
    fmt::println("The value of the variable localVar1: {} and its address {}", localVar1, fmt::ptr(&localVar1));

    fmt::println("------------------------------------------------------------------------------------------------");
    fmt::print("Adresse von foo: {}\\n", fmt::ptr(&foo));

    return 0; /* exit gracefully*/
}
