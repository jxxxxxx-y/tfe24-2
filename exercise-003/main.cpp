#include <fmt/chrono.h>
#include <fmt/format.h>

#include "CLI/CLI.hpp"
#include "config.h"

#include <algorithm> /* needed for the std::sort */
#include <random>

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
        app.add_option("-c,--count", counter, "An counter option")->default_val("3");
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
    fmt::print("The counter value is: {}!\n", counter);

        // Seed with a real random value, if available
    std::random_device r;

    // Choose a random mean between 1 and 100
    // https://en.cppreference.com/w/cpp/numeric/random.html
    std::default_random_engine e1(r());
    std::uniform_int_distribution<int> uniform_dist(1, 100);
    int rand_value = uniform_dist(e1);

    std::vector<unsigned int> numbers;
    auto start = std::chrono::system_clock::now();
    for (int i = 0; i < counter; i++)
    {
        numbers.push_back(uniform_dist(e1));
    }
    auto end = std::chrono::system_clock::now();

    const auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
    fmt::println("The inserting took: {}", elapsed);
    fmt::println("The random vector: [ {} ]", fmt::join(numbers, ", "));

    fmt::println("Let's sort the numbers vector");
    fmt::println("--------------------------------------------------------------------------");

    start = std::chrono::system_clock::now();
    std::sort(numbers.begin(), numbers.end(), std::less<int>());
    end = std::chrono::system_clock::now();

    fmt::println("The sorted numbers vector");
    fmt::println("--------------------------------------------------------------------------");
    fmt::println("The sorted vector: [ {} ]", fmt::join(numbers, ", "));
    const auto elapsed_sort = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
    fmt::println("The sorting took: {}", elapsed_sort);

    return 0; /* exit gracefully*/
}
