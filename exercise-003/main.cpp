#include <fmt/chrono.h>
#include <fmt/format.h>

#include "CLI/CLI.hpp"
#include "config.h"


auto main(int argc, char **argv) -> int
{
    auto counter = 5;
    /**
     * CLI11 is a command line parser to add command line options
     * More info at https://github.com/CLIUtils/CLI11#usage
     */
    CLI::App app{"Strava for std::vectors"};
    try
    {
        app.set_version_flag("-V,--version", fmt::format("{} {}", PROJECT_VER, PROJECT_BUILD_DATE));

        app.add_option("-c,--count", counter, "An counter option")->default_val("20");
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
    
    // Parameterraum
    /*fmt::print("Hello {}\n", app.get_name());
    fmt::print("counter value = {}\n", counter);*/

    



    return 0; /* exit gracefully*/
}
