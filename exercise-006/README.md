# Übungsaufgabe: Generische `Point<T>`-Klasse mit Templates (C++20)

**Lernziel:** Überführen der bisherigen `Point`-Klasse in eine **generische** Template-Klasse `Point<T>` für unterschiedliche Zahlentypen (`int`, `double`, …). Einsatz von **Templates**, **Concepts** (oder `std::enable_if`), **`std::common_type_t`** und Anbindung an **fmt**.

---

## Anforderungen

1. **Klassen-Template**
   - Definieren Sie `template <typename T> class Point`.
   - Member: `T x; T y;`
   - Konstruktoren:
     - Standardkonstruktor: `x = T{}` und `y = T{}`
     - Wertekonstruktor: `Point(T x, T y)`
   - Methode: `void move(T dx, T dy)`

2. **Typ-Einschränkung**
   - Beschränken Sie `T` auf **arithmetische Typen**.
   - **Variante A (C++20 Concepts):**
     ```cpp
     #include <concepts>
     template <std::arithmetic T>
     class Point { /* ... */ };
     ```
   - **Variante B (ohne Concepts):**
     ```cpp
     static_assert(std::is_arithmetic_v<T>, "Point<T>: T must be arithmetic");
     ```

3. **Distance-Funktion**
   - Signatur (als `const` Memberfunktion):
     ```cpp
     auto distance_to(const Point& other) const -> /* geeigneter Typ */;
     ```
   - Rückgabetyp per **`std::common_type_t<T, double>`** oder direkt `double`, damit Ergebnisse bei `int` nicht abgeschnitten werden.
   - Nutzen Sie `std::hypot` für numerisch stabile Distanzberechnung.
   - **Hinweis:** Achten Sie auf Casts (`static_cast`) vor dem Quadrieren.

4. **Vergleichsoperatoren**
   - Implementieren Sie `operator==` und `operator!=` für exakte Vergleiche.
   - (Optional) Für `floating point` zusätzlich eine **annähernde** Vergleichsfunktion:
     ```cpp
     template <typename T>
     bool almost_equal(T a, T b, T eps);
     ```

5. **fmt-Anbindung**
   - Schreiben Sie eine `fmt`-Formatter-Spezialisierung für `Point<T>`, damit `fmt::print("{}", p)` `"(x, y)"` ausgibt.
   - Gerüst (nicht vollständig):
     ```cpp
     template <typename T>
     struct fmt::formatter<Point<T>> : fmt::formatter<std::string_view> {
       template <typename FormatContext>
       auto format(const Point<T>& p, FormatContext& ctx) const {
         return fmt::format_to(ctx.out(), "({}, {})", p.x, p.y);
       }
     };
     ```

6. **Operatoren (optional, aber empfohlen)**
   - `Point<T> operator+(const Point<T>& rhs) const;`
   - `Point<T> operator-(const Point<T>& rhs) const;`
   - Skalar-Multiplikation: `Point<common_type_t<T,U>> operator*(U s) const;`

---

## Tests (mit Catch2)

Erstellen Sie eine neue Testdatei `tests/test_point_template.cpp`. Orientieren Sie sich an Ihrer bestehenden Test-Struktur und ergänzen Sie folgende Fälle:

1. **Instanziierung mit verschiedenen Typen**
   - `Point<int> pi{2, 3};`
   - `Point<double> pd{2.5, -3.75};`
   - Prüfen Sie Konstruktoren, `move`, `operator==/!=`.

2. **`distance_to` – Ganzzahl vs. Gleitkomma**
   - `Point<int> a{0,0}, b{3,4};` → `distance == 5.0` (mit `Approx`)
   - `Point<double> c{0.5, 0.5}, d{2.5, 4.5};` → Erwartungswert berechnen und mit `Approx` prüfen.
   - **Rückgabetyp**: verifizieren Sie, dass `decltype(a.distance_to(b))` **nicht** `int` ist (z. B. `std::is_same_v` in einem `STATIC_REQUIRE`).

3. **Operatoren (falls implementiert)**
   - `(pi + Point<int>{1,1}) == Point<int>{3,4}`
   - `(pd * 2) == Point<double>{5.0, -7.5}` (Toleranztest mit `Approx`)

4. **fmt-Formatter**
   - `fmt::format("{}", Point<int>{1,2}) == "(1, 2)"`
   - Ausgabe in Tests nicht nötig, aber ein Format-Check erhöht die Abdeckung.

5. **Edge Cases**
   - Große Werte (potenzielle Überläufe bei `int` → stellen Sie sicher, dass in `distance_to` in breiteren Typ gecastet wird).
   - Negative Koordinaten.
   - `distance_to` von einem Punkt zu sich selbst ist `0`.

---

## Beispiel-Schnipsel (unvollständig, zur Orientierung)

```cpp
#include <type_traits>
#include <cmath>
#include <concepts>

template <std::arithmetic T>
class Point {
public:
  T x{};
  T y{};

  Point() = default;
  Point(T x_, T y_) : x{x_}, y{y_} {}

  void move(T dx, T dy) {
    x += dx; y += dy;
  }

  using dist_t = std::common_type_t<T, double>;

  auto distance_to(const Point& other) const -> dist_t {
    auto dx = static_cast<dist_t>(x) - static_cast<dist_t>(other.x);
    auto dy = static_cast<dist_t>(y) - static_cast<dist_t>(other.y);
    return std::hypot(dx, dy);
  }

  bool operator==(const Point&) const = default;
};
```

> **Achtung:** Oben ist bewusst **nicht** alles enthalten (z. B. fmt-Formatter, zusätzliche Operatoren), damit Sie die Aufgabe selbstständig ausarbeiten.


## Erweiterungen (freiwillig)

- **`Point` als `constexpr` nutzbar** (wo sinnvoll)  
- `std::hash<Point<T>>` für den Einsatz in `std::unordered_set/map`  
- Konvertierender Konstruktor `template <typename U> Point(const Point<U>&)` mit `std::is_convertible_v<U,T>`  
- Interoperable Operatoren zwischen `Point<T>` und `Point<U>` mit `std::common_type_t<T,U>`