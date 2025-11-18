#include <fmt/chrono.h>
#include <fmt/format.h>

#include "CLI/CLI.hpp"
#include "config.h"
#include "myvector.hpp"



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
    fmt::print("Hello, {}!\n", app.get_name());

    myvector<int> vec(2);
    vec.status();
    vec.push_back(10);
    vec.status();
    for (int i = 0; i < 5; i++){
        vec.push_back(i);
    }
    vec.push_back(1);
    vec.status();
    vec.push_back(2);
    vec.status();
    vec.push_back(3);
    vec.status();
    vec.push_back(4);
    vec.status();
    vec.value_at(4);
    vec.push_back(5);
    vec.status();
    vec.resize(25);
    vec.status();
    vec.capacity();
    vec.size();
    vec.clear();
    vec.value_at(4);

    return 0;
}