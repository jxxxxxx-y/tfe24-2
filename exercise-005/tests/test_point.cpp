#include <catch2/catch_test_macros.hpp>
#include "point.hpp"
#include <catch2/catch_approx.hpp>

TEST_CASE("Point: Konstruktoren") {
    SECTION("Init mit Werten") {
        Point p{2, 3};
        REQUIRE(p.m_x == 2);
        REQUIRE(p.m_y == 3);
    }
    SECTION("Default-Konstruktor") {
        Point p;
        REQUIRE(p.m_x == 0);
        REQUIRE(p.m_y == 0);
    }
}

TEST_CASE("Point: move verschiebt relativ") {
    SECTION("einmal verschieben") {
        Point p{0, 0};
        p.move(2, 3);
        REQUIRE(p.m_x == 2);
        REQUIRE(p.m_y == 3);
    }
    SECTION("mehrfach verschieben") {
        Point p{1, 1};
        p.move(1,4);
        p.move(2,3);
        REQUIRE(p.m_x == 4);
        REQUIRE(p.m_y == 8);
    }
}

TEST_CASE("Point: distance_to – euklidisch & robust") {
    Point a{0, 0};
    Point b{3, 4};
    REQUIRE( a.distance(b) == Catch::Approx(5.0).margin(1e-12) );
    REQUIRE( b.distance(a) == Catch::Approx(5.0).margin(1e-12) );
    REQUIRE( a.distance(a) == Catch::Approx(0.0).margin(1e-12) );
}

TEST_CASE("Negative Koordinaten"){
    Point p{-2, -3};
    REQUIRE(p.m_x == -2);
    REQUIRE(p.m_y == -3);
}
TEST_CASE("Viele Move-Aufrufe"){
    Point p{0,0};
    for(int i=0; i<100; ++i){
        p.move(1,1);
    }
    REQUIRE(p.m_x == 100);
    REQUIRE(p.m_y == 100);
}
    




