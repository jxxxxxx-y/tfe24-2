#include <fmt/chrono.h>
#include <fmt/format.h>

#include <nlohmann/json.hpp>
#include "point.hpp"
#include "CLI/CLI.hpp"
#include "config.h"

// for convenience
using json = nlohmann::json;

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

    Point<int> p(0,0);
    fmt::print("Initial Point position: ({}, {})\n", p.x_m, p.y_m);
    
    p.move(5,7);
    fmt::print("Point position after move: ({}, {})\n", p.x_m, p.y_m);

    Point<int> b(3,4);
    fmt::print("Distance to b: {}\n", p.distance_to(b));


    return 0; /* exit gracefully*/
}
