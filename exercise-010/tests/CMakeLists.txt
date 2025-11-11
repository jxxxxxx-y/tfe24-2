cmake_minimum_required (VERSION 3.10.2)

message( STATUS "Catch2 Tests included" )

# Some one-offs first:
# 1) Tests and main in one file
add_executable( ${PROJECT_NAME}-tests
  000-Main.cpp
  001-TestCase.cpp
  ../myvector.cpp
)

# Add libraries
target_link_libraries(${PROJECT_NAME}-tests PRIVATE
                                        fmt::fmt
                                        nlohmann_json::nlohmann_json
                                        Catch2::Catch2WithMain)

# Provide include path to find myvector.hpp
target_include_directories(${PROJECT_NAME}-tests PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/..)

add_catch2_test(
  TARGET ${PROJECT_NAME}-tests
)