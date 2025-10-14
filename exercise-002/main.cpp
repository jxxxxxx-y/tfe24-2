#include <fmt/chrono.h>
#include <fmt/format.h>

#include "CLI/CLI.hpp"
#include "config.h"

int globalVar = 1;

void foo();

auto main(int argc, char **argv) -> int
{
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
   

    // Part 1 - Global Variable 

    fmt::print("Global variable value: {}\n", globalVar);
    fmt::print("Adress of global variable is: {}\n", fmt::ptr(&globalVar));

    // Part 2 - Local Variable

    int localVar = 2;
    fmt::print("Local Variable value: {}\n", localVar);
    fmt::print("Adress of local variable is: {}\n", fmt::ptr(&localVar));

    // Part 3 - Dynamic Variable

    int* heapVar = new int(3);
    fmt::print("Dynamic Variable value: {}\n", *heapVar);
    fmt::print("Adress of dynamic variable is: {}\n", fmt::ptr(&heapVar));
    delete heapVar;

    // Part 4 - Funktions 

    fmt::print("Adress of Foo: {}\n", fmt::ptr(&foo));

    // Fazit
    /* 
    Globale Variablen werden im Data-Segment gespeichert, Lokale Variablen im Stack und dynamische Variablen im Heap. 
    Da der Heapspeicher begrenzt ist, und bei der Initialisierung von dynamisch allozierten Variablen viel Speicher 
    reserviert wird, sollte dieser am Ende des Programms freigegeben werden.
    Bei variabel allozierten Variablen zeigt der Variablenname als Pointer auf den reservierten Speicher,
    lokale Variablen sind feste Speicherzellen, in denen der Wert gespeichert wird.
    */

    return 0; /* exit gracefully*/
}

void foo()
    {
        fmt::print("Hello from foo!\n");

    };
