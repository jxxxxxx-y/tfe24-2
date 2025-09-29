# Übungsaufgabe: Generische `Point<T>`-Klasse (C++17-kompatibel)

**Ziel:** Überführen der bisherigen `Point`-Klasse in eine **generische** Template-Klasse `Point<T>` für unterschiedliche Zahlentypen – **ohne C++20 Concepts**, vollständig **C++17-kompatibel**.  
Schwerpunkte: Templates, `static_assert`/Type-Traits, sicherer Rückgabetyp für `distance_to`, `fmt`-Formatter, Catch2-Tests.

---

## Anforderungen

1. **Klassen-Template**
   - `template <typename T> class Point` mit Membern `T x; T y;`
   - Standardkonstruktor: `x = T{}`, `y = T{}`
   - Wertekonstruktor: `Point(T x, T y)`
   - Methode: `void move(T dx, T dy)`

2. **Typ-Constraint (ohne Concepts)**
   - Beschränken Sie `T` auf arithmetische Typen über Type-Traits:
     ```cpp
     #include <type_traits>
     static_assert(std::is_arithmetic<T>::value, "Point<T>: T must be arithmetic");
     ```
     > Hinweis: In C++17 ist `std::is_arithmetic_v<T>` via `<type_traits>` verfügbar. Sie können wahlweise `_v` verwenden.

3. **Distance-Funktion**
   - Signatur:
     ```cpp
     auto distance_to(const Point& other) const -> /* geeigneter Typ */;
     ```
   - Nutzen Sie als Rückgabetyp **`std::common_type_t<T, double>`** (oder `double`).  
   - Implementierung mit `std::hypot` (C++17 vorhanden). Vor dem Rechnen in den breiteren Typ casten:
     ```cpp
     using dist_t = std::common_type_t<T, double>;
     auto dx = static_cast<dist_t>(x) - static_cast<dist_t>(other.x);
     auto dy = static_cast<dist_t>(y) - static_cast<dist_t>(other.y);
     return std::hypot(dx, dy);
     ```

4. **Vergleichsoperatoren**
   - Implementieren Sie `operator==` und `operator!=` **explizit** (kein `= default` erforderlich, aber erlaubt):
     ```cpp
     bool operator==(const Point& rhs) const { return x == rhs.x && y == rhs.y; }
     bool operator!=(const Point& rhs) const { return !(*this == rhs); }
     ```

5. **fmt-Integration (C++17)**
   - Spezialisieren Sie einen Formatter für `Point<T>`, damit `fmt::print("{}", p)` die Form `"(x, y)"` ausgibt.
   - Beispielgerüst:
     ```cpp
     #include <fmt/core.h>

     template <typename T>
     struct fmt::formatter<Point<T>> : fmt::formatter<std::string_view> {
       template <typename FormatContext>
       auto format(const Point<T>& p, FormatContext& ctx) const {
         return fmt::format_to(ctx.out(), "({}, {})", p.x, p.y);
       }
     };
     ```
     > Achten Sie auf die Header-Reihenfolge: Der Formatter muss nach der Point-Deklaration sichtbar sein.

6. **(Optional) Operatoren**
   - `Point<T> operator+(const Point<T>& rhs) const;`
   - `Point<T> operator-(const Point<T>& rhs) const;`
   - Skalar-Multiplikation: `template <typename U> Point<std::common_type_t<T,U>> operator*(U s) const;`

---

## Beispiel-Skelett (unvollständig, zur Orientierung)

```cpp
// point.hpp
#pragma once
#include <type_traits>
#include <cmath>
#include <utility> // std::move (falls benötigt)

template <typename T>
class Point {
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
```

```cpp
// point_fmt.hpp (oder unter point.hpp, nach der Klasse)
#pragma once
#include <fmt/core.h>
template <typename T>
struct fmt::formatter<Point<T>> : fmt::formatter<std::string_view> {
  template <typename FormatContext>
  auto format(const Point<T>& p, FormatContext& ctx) const {
    return fmt::format_to(ctx.out(), "({}, {})", p.x, p.y);
  }
};
```

---

## Tests (Catch2, C++17)

Erstellen Sie `tests/test_point_template_cpp17.cpp` (Pfade/Includes an Ihr Template anpassen).  
Verwenden Sie `Approx` für Gleitkomma-Vergleiche.

```cpp
#include <catch2/catch_test_macros.hpp>
#include "point.hpp"
#include <type_traits>
#include <fmt/core.h>
#include "point_fmt.hpp" // falls der Formatter separat ist

TEST_CASE("Point<T>: Konstruktion & move (int)") {
  Point<int> p{2, 3};
  REQUIRE(p.x == 2);
  REQUIRE(p.y == 3);

  p.move(1, -4);
  REQUIRE(p.x == 3);
  REQUIRE(p.y == -1);
}

TEST_CASE("Point<T>: Konstruktion & move (double)") {
  Point<double> p{2.5, -3.75};
  p.move(0.5, 0.25);
  REQUIRE(p.x == Approx(3.0));
  REQUIRE(p.y == Approx(-3.5));
}

TEST_CASE("Point<T>: distance_to – Typ & Wert") {
  Point<int> a{0,0}, b{3,4};
  typedef decltype(a.distance_to(b)) dist_t;
  STATIC_REQUIRE(!std::is_same<dist_t, int>::value);
  REQUIRE(a.distance_to(b) == Approx(5.0).margin(1e-12));
  REQUIRE(b.distance_to(a) == Approx(5.0).margin(1e-12));
  REQUIRE(a.distance_to(a) == Approx(0.0).margin(1e-12));
}

TEST_CASE("Point<T>: fmt-Formatter") {
  Point<int> pi{1,2};
  REQUIRE(fmt::format("{}", pi) == "(1, 2)");
}
```

**Edge Cases:**  
- Sehr große/negative Werte (Achtung bei Differenzen: Cast auf `dist_t` wie gezeigt).  
- Viele aufeinanderfolgende `move`-Aufrufe (Stabilität).  
- Typmischung in optionalen Operatoren (z. B. `Point<int>{} * 2.5`).


## Hinweise

- `std::hypot` ist in C++17 verfügbar und robust für die euklidische Norm.  
- `STATIC_REQUIRE` ist ein Catch2-Makro (Compile-Time-Check). Alternativ: `REQUIRE(std::is_same<...>::value)` (Laufzeit).  
- Achten Sie darauf, dass der Formatter **nach** der Klassendefinition sichtbar ist (oder in separater Headerdatei, die nach `point.hpp` inkludiert wird).