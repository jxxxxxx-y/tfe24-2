#include <fmt/chrono.h>
#include <fmt/format.h>
#include <random>

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
    fmt::print("Hello {}\n", app.get_name());
    fmt::print("counter value = {}\n", counter);

    std::random_device r;
    std::default_random_engine e1(r());
    std::uniform_int_distribution<int> uniform_dist(1, 100);
    
    //fmt::print("value for mean = {}\n", mean);

    std::vector<int> rand_vector;
    for (int i = 0; i < counter; i++)
    {
    int mean = uniform_dist(e1);
    rand_vector.push_back(mean);
    }

    fmt::print("values:");
    fmt::print("[");
    for (int value : rand_vector){
        fmt::print(" {}", value);
    }
    fmt::print("]");

    std::sort(rand_vector.begin(), rand_vector.end());

    fmt::print("\n");
    fmt::print("values:");
    fmt::print("[");
    for (int value : rand_vector){
        fmt::print(" {}", value);
    }
    fmt::print("]");

    std::vector<int> speed_vec;
    auto start = std::chrono::system_clock::now();
    for (int i = 0; i < counter; i++)
    {
        speed_vec.push_back(uniform_dist(e1));
    }
    std::sort(speed_vec.begin(), speed_vec.end());
    auto end = std::chrono::system_clock::now();
    auto elapsed = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start);

    fmt::print("\n");
    fmt::print("Time taken for exercise: {}\n", elapsed);

    fmt::print("values:");
    fmt::print("[");
    for (int value : speed_vec){
        fmt::print(" {}", value);
    }
    fmt::print("]");

    return 0; /* exit gracefully*/
}
