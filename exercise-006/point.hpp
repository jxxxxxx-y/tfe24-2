#pragma once
#include <type_traits>
#include <fmt/core.h>
#include <cmath>


template <typename T> class Point {
  static_assert(std::is_arithmetic<T>::value, "Point<T>: T must be arithmetic");
  public: 
    T x_m;
    T y_m;

    Point() = default;

    Point(T x, T y) : x_m(x), y_m(y) {};
    void move(T dx, T dy) {
        x_m += dx;
        y_m += dy;
    }

    using dist_t = std::common_type_t<T, double>;
    auto distance_to(const Point& other) const -> dist_t {
    const auto dx = static_cast<dist_t>(x_m) - static_cast<dist_t>(other.x_m);
    const auto dy = static_cast<dist_t>(y_m) - static_cast<dist_t>(other.y_m);
    return std::hypot(dx, dy);
    }
     
    bool operator==(const Point& rhs) const { return x_m == rhs.x_m && y_m == rhs.y_m; }
    bool operator!=(const Point& rhs) const { return !(*this == rhs); }
};

template <typename T> struct fmt::formatter<Point<T>> : fmt::formatter<std::string_view> {
  template <typename FormatContext>
  auto format(const Point<T>& p, FormatContext& ctx) const {
    return fmt::format_to(ctx.out(), "({}, {})", p.x_m, p.y_m);
  }
};
