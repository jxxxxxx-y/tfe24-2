# Übungsaufgabe: `Point` mit Catch2 testen (Template-kompatibel)

**Lernziel:** Schreiben aussagekräftiger Unit-Tests für die Klasse `Point` mit Catch2 – kompatibel zur bereitgestellten Template-Struktur aus `templates/catch2` im TFE23-2-Repository.

> **Hinweis zur Einbindung:** Nutzen Sie die Catch2-Integration **gemäß Ihrem Template**.  
> - Falls Ihr CMake bereits `Catch2WithMain` linkt (üblich bei Catch2 v3): `#include <catch2/catch_test_macros.hpp>` **ohne** `CATCH_CONFIG_MAIN`.  
> - Falls Ihr Template den **amalgamierten Header** verwendet: `#define CATCH_CONFIG_MAIN` und `#include "catch_amalgamated.hpp"`.

---

## Aufgabenstellung

Erstellen Sie eine Testdatei `tests/test_point.cpp` und implementieren Sie folgende Testbereiche. Wählen Sie passende **`TEST_CASE`**- und **`SECTION`**-Namen, die klar machen, **was** geprüft wird.

### A) Konstruktoren
- `Point(int x, int y)` setzt beide Koordinaten korrekt.
- Standardkonstruktor setzt `(0, 0)`.

### B) `move(int dx, int dy)`
- Positive und negative Verschiebungen ändern `x`/`y` relativ.
- Mehrere aufeinanderfolgende Moves verhalten sich wie die Summe der Verschiebungen (assoziativ).

### C) `distance_to(const Point& other) const`
- Euklidische Distanz zwischen `(0,0)` und `(3,4)` ist `5.0`.
- Distanz ist **symmetrisch**: `a→b == b→a`.
- Distanz zu sich selbst ist `0.0`.
- **Floating-Point-Vergleiche:** verwenden Sie `Approx(…).margin(1e-12)` oder `.epsilon(1e-12)`.

### D) Edge Cases (mindestens zwei selbst wählen)
- Große/negative Koordinaten (denken Sie an mögliche Überläufe bei Differenzen; ggf. Cast auf `double` in der Distanzberechnung).
- Dreiecksungleichung (optional): `dist(a,c) ≤ dist(a,b) + dist(b,c)`.
- Stabilität bei vielen aufeinanderfolgenden `move`-Aufrufen.

---

## Beispielgerüst (bitte an Ihr Template anpassen)

> **Variante 1 (Catch2 v3, mit `Catch2WithMain`)** – bevorzugt, wenn CMake das Main bereitstellt:

```cpp
#include <catch2/catch_test_macros.hpp>
#include "point.hpp"

TEST_CASE("Point: Konstruktoren") {
    SECTION("Init mit Werten") {
        Point p{2, 3};
        REQUIRE(p.x == 2);
        REQUIRE(p.y == 3);
    }
    SECTION("Default-Konstruktor") {
        Point p;
        REQUIRE(p.x == 0);
        REQUIRE(p.y == 0);
    }
}

TEST_CASE("Point: move verschiebt relativ") {
    Point p{1, 1};
    p.move(2, -3);
    REQUIRE(p.x == 3);
    REQUIRE(p.y == -2);
}

TEST_CASE("Point: distance_to – euklidisch & robust") {
    Point a{0, 0};
    Point b{3, 4};
    REQUIRE( a.distance_to(b) == Approx(5.0).margin(1e-12) );
    REQUIRE( b.distance_to(a) == Approx(5.0).margin(1e-12) );
    REQUIRE( a.distance_to(a) == Approx(0.0).margin(1e-12) );
}
```

> **Variante 2 (amalgamierter Header in `tests/`)** – falls Ihr Template so arbeitet:

```cpp
#define CATCH_CONFIG_MAIN
#include "catch_amalgamated.hpp"
#include "point.hpp"

TEST_CASE("Point: Konstruktoren setzen Koordinaten korrekt") {
    Point p1{2, 3};
    REQUIRE(p1.x == 2);
    REQUIRE(p1.y == 3);

    Point p2;
    REQUIRE(p2.x == 0);
    REQUIRE(p2.y == 0);
}
```

---

## Tipps

- Für Distanz: Verwenden Sie `double` für Zwischenergebnisse (z. B. `dx`, `dy`) bevor Sie quadrieren/summieren.  
- Testen Sie **Vorher/Nachher-Zustände** bei `move` und nutzen Sie mehrere `SECTION`s in einem `TEST_CASE`.  
- Halten Sie Tests **deterministisch** und **unabhängig**: Jeder Test richtet seinen Zustand selbst ein.

---
