#pragma once
#include <type_traits>
#include <cmath>
#include <utility> // std::move (falls benötigt)

template <typename T> class Point {
  static_assert(std::is_arithmetic<T>::value, "Point<T>: T must be arithmetic");
public:
  T x{};
  T y{};

  Point() = default;
  Point(T x_, T y_) : x{x_}, y{y_} {}

  void move(T dx, T dy) { x += dx; y += dy; }

  using dist_t = std::common_type_t<T, double>;
  auto distance_to(const Point& other) const -> dist_t {
    const auto dx = static_cast<dist_t>(x) - static_cast<dist_t>(other.x);
    const auto dy = static_cast<dist_t>(y) - static_cast<dist_t>(other.y);
    return std::hypot(dx, dy);
  }

  bool operator==(const Point& rhs) const { return x == rhs.x && y == rhs.y; }
  bool operator!=(const Point& rhs) const { return !(*this == rhs); }
};
