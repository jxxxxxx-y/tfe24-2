# Übungsaufgabe: `Point` mit Catch2 testen (Template-kompatibel)

## Notwendige git Kommandos

```sh
git status
git branch -a
git switch main
# create a new local branch based on the origin main
git switch -c solution-005 origin/main
# perform changes
# ....
git add exercise-005
git commit -m "feat: add exercise number two"
# push the changes to the cloud
git push -u origin solution-005
....
```

**Lernziel:** Schreiben aussagekräftiger Unit-Tests für die Klasse `Point` mit Catch2 – kompatibel zur bereitgestellten Template-Struktur aus `templates/catch2` im tfe24-2-Repository.

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

## Beispielgerüst

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

---

## Tipps

- Für Distanz: Verwenden Sie `double` für Zwischenergebnisse (z. B. `dx`, `dy`) bevor Sie quadrieren/summieren.  
- Testen Sie **Vorher/Nachher-Zustände** bei `move` und nutzen Sie mehrere `SECTION`s in einem `TEST_CASE`.  
- Halten Sie Tests **deterministisch** und **unabhängig**: Jeder Test richtet seinen Zustand selbst ein.

---
