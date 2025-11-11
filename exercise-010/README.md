# Aufgabenstellung

## Notwendige git Kommandos

```sh
git fetch --all
git status
git branch -a
git switch main
# create a new local branch based on the upstream main
git switch -c solution-010 upstream/main
# perform changes
# ....
git add exercise-010
git commit -m "feat: add exercise number two"
# push the changes to the cloud
git push -u origin solution-010
....
```

## Einfache `myvector`-Implementierung in C++

### Kontext & Lernziele

Ziel dieser Aufgabe ist es, eine vereinfachte Variante von `std::vector`
zu entwickeln, um die Grundlagen von **dynamischer Speicherverwaltung**
in C++ zu verstehen:

- Dynamischen Speicher mit `new[]` anfordern und mit `delete[]`
    freigeben.
- Speicherwachstum (Capacity, Reallocation) und Besitzverhältnisse
    nachvollziehen.
- **Rule of Three** (Destruktor, Copy-Konstruktor, Copy-Zuweisung)
    sicher anwenden.
- Grenzenprüfung und einfache Ausnahme-Sicherheit umsetzen.

- Deep-Copy bei Zuweisung/Kopie: eigener Speicherbereich, keine geteilten Zeiger.
- Reallocation richtig durchführen: Beim Wachstum vorhandene Elemente umkopieren.
- Amortisierte Kosten verstehen: `push_back` darf nicht bei jedem Aufruf neu allokieren (Wachstumsstrategie).
- Zeitmessung mit `std::chrono`: einfache Performance-Experimente durchführen und bewerten.

------------------------------------------------------------------------

## Aufgabenbeschreibung

Implementieren Sie eine generische Klasse `myvector<T>` im Namespace `tfe24`, angelehnt an
die Standardbibliothek:
[cppreference:
`std::vector`](https://en.cppreference.com/w/cpp/container/vector)

### Minimal geforderte öffentliche Schnittstelle

- `void push_back(const T& value);`
- `T& at(size_t index);` und `const T& at(size_t index) const;`
- `size_t size() const noexcept;`
- `void resize(size_t new_size);`
- `void clear() noexcept;`

### Zusätzlich **verbindlich**

- **Konstruktoren**
  - `myvector() noexcept;`
  - `explicit myvector(size_t count);`
- **Destruktor**
- **Rule of Three**
  - Copy-Konstruktor
  - Copy-Zuweisungsoperator
  - Deep-Copy: Zuweisung muss eigenen Speicher allozieren und Inhalte vollständig kopieren.
- **Capacity-Basics**
  - `size_t capacity() const noexcept;`
  - `void reserve(size_t new_cap);`
- **`operator[]`**

------------------------------------------------------------------------

## Kernanforderungen: Wachstum, Umkopieren, Amortisierung

Diese Punkte sind zentral für die Bewertung dieser Übung:

- Wachstumsstrategie: Bei fehlender Kapazität wächst der Speicher in Blöcken (z. B. Verdopplung). Ein „lineares“ Wachstum mit Allokation bei jedem `push_back` ist NICHT zulässig.
- Umkopieren bei Reallocation: Beim Vergrößern des internen Speichers werden die vorhandenen Elemente korrekt in den neuen Speicherbereich kopiert und der alte Speicher wird freigegeben.
- Deep-Copy bei Copy-Zuweisung/-Konstruktor: Ziel erhält einen eigenen Speicher, Änderungen an Quelle und Ziel sind unabhängig.
- Komplexität: `push_back` ist amortisiert O(1); `at()` ist O(1); `resize(n)` ist O(n) in der Größe des Ziels.

Akzeptanzkriterien (Auszug):

- Mehrere `push_back`-Aufrufe führen nicht zu einer Allokation pro Aufruf (Capacities steigen in Sprüngen).
- Nach `b = a;` sind `a` und `b` unabhängig (Änderungen an `a` ändern `b` nicht).
- Keine Speicherlecks (z. B. mittels Sichtprüfung, RAII korrekt umgesetzt).

------------------------------------------------------------------------

## Vorgaben & Einschränkungen

- **Nicht erlaubt:** `std::vector`, `std::unique_ptr<T[]>`,
    `std::allocator`, `malloc/free`, externe Bibliotheken.
- **Erlaubt:** `<stdexcept>`, `<algorithm>`, `<utility>`,
    `<initializer_list>`, `<cstddef>`, `<new>`, `<string>` in Tests.
- **Namensraum:** Packen Sie alles in den Namespace `tfe24`.
- **Dateistruktur:**
  - `myvector.hpp` -- Implementierung
  - `main.cpp` -- einfache Tests / Demo

------------------------------------------------------------------------

## Tests mit Catch2

Testen Sie Ihre Implementierung mit **Catch2**. Catch2 ist bereits ins Projekt integriert (siehe andere Übungen). Passen Sie die Tests unter `exercise-010/tests/001-TestCase.cpp` entsprechend an.

### Ziele der Tests

- Konstruktoren und Grundzustand prüfen (`size()==0`, `capacity()==0` oder Startwert je nach Implementierung).
- `push_back` Wachstumsverhalten (Size erhöht sich, Capacity wächst mindestens geometrisch oder per Ihrer Strategie).
- `at()` wirft bei Out-of-Range einen `std::out_of_range`.
- `resize()` größer: neue Elemente sind per Default-Konstruktion erzeugt (für `int` i.d.R. `0`).
- `resize()` kleiner: Größe reduziert, keine Zugriffe jenseits der neuen Größe möglich.
- `clear()` setzt Größe auf `0`, Capacity bleibt erhalten (nicht zwingend freigeben).
- Copy-Konstruktor und Copy-Zuweisung erzeugen unabhängige Kopien (Änderung am Original beeinflusst Kopie nicht).

### Beispiel: Minimaler Catch2-Test

Die Verwendung des Namensraum `tfe24` ist optional siehe Zusatzaufgaben.

```cpp
#include <catch2/catch_all.hpp>
#include "myvector.hpp"

TEST_CASE("basic operations on tfe24::myvector<int>", "[myvector][basic]") {
  tfe24::myvector<int> v;
  REQUIRE(v.size() == 0);

  SECTION("push_back grows size") {
    v.push_back(42);
    v.push_back(7);
    REQUIRE(v.size() == 2);
    REQUIRE(v[0] == 42);
    REQUIRE(v.at(1) == 7);
  }

  SECTION("resize larger fills with default values") {
    v.resize(5);
    REQUIRE(v.size() == 5);
    for (size_t i = 0; i < v.size(); ++i) {
      REQUIRE(v[i] == int{}); // erwartet 0 für int
    }
  }

  SECTION("at throws on out of range") {
    v.push_back(1);
    REQUIRE_THROWS_AS(v.at(5), std::out_of_range);
  }
}

TEST_CASE("copy semantics (Rule of Three)", "[myvector][copy]") {
  tfe24::myvector<int> a;
  for (int i = 0; i < 3; ++i) a.push_back(i + 10);
  tfe24::myvector<int> b = a;          // Copy-Konstruktor
  tfe24::myvector<int> c; c = a;       // Copy-Zuweisung

  REQUIRE(b.size() == a.size());
  REQUIRE(c.size() == a.size());

  a[0] = 99; // Änderungen dürfen Kopien nicht beeinflussen
  REQUIRE(b[0] != a[0]);
  REQUIRE(c[0] != a[0]);
}
```

### Erweiterungsideen (optional)

- Test für `reserve()`: Kapazitätsänderung ohne Größenänderung.
- Wachstumsstrategie: Prüfen, dass `capacity()` nach mehreren `push_back` nicht linear bleibt (heuristische Checks).
- Ausnahme-Sicherheit: Erzeugen eines künstlichen Fehlers (bei komplexeren Typen) – hier für `int` nicht nötig.
- Template-Fähigkeit: Zusätzlicher Test mit `myvector<std::string>` (Copy, Resize, Default-Werte = leere Strings).
- Kurzer TDD-Impuls: Gehen Sie in sehr kleinen Schritten vor: (1) **Red** – schreiben Sie zuerst einen präzisen Test, der aktuell fehlschlägt und eine neue Verhaltensanforderung ausdrückt. (2) **Green** – implementieren Sie nur den minimal nötigen Code, damit alle Tests bestehen. (3) **Refactor** – verbessern Sie Struktur, Lesbarkeit und entfernen Duplikate, ohne dass die Tests rot werden. Halten Sie Ihre Tests aussagekräftig (klarer Arrange/Act/Assert), vermeiden Sie übermäßige Logik in Tests und nutzen Sie sie als lebende Spezifikation für die API Ihres `myvector`.

Viel Erfolg beim Test-getriebenen Entwickeln! 🚀

------------------------------------------------------------------------

## Performance-Experimente mit `std::chrono`

Führen Sie einfache Messungen durch, um die Wirkung der Wachstumsstrategie sichtbar zu machen. Nutzen Sie dafür die API aus Ihrer Implementierung (z. B. `push_back`, `reserve`, `clear`).

Messaufgaben:

1) Push-Sequenz ohne Vorab-Reserve: Fügen Sie N Elemente nacheinander ein und messen Sie die verstrichene Zeit mit `std::chrono::steady_clock`. Wiederholen Sie den Versuch mehrfach und mitteln Sie die Ergebnisse.
2) Push-Sequenz mit `reserve(N)`: Wiederholen Sie 1) nach einem einmaligen `reserve(N)` und vergleichen Sie die Zeitwerte.
3) Wachstumsstrategie-Vergleich: Variieren Sie den Wachstumsfaktor (z. B. ×1.5 vs. ×2) und beobachten Sie den Einfluss auf Zeit und Anzahl Reallocations.

Hinweise:

- Messen Sie in einem „Release“-Build und führen Sie die Messungen mehrmals aus, um Ausreißer zu glätten.
- Optional: Zählen Sie Reallocations mit (ein interner Zähler in der Demo oder Debug-Ausgaben helfen bei der Sichtbarkeit) und geben Sie am Ende „N Inserts -> R Reallocations“ aus.
- Dokumentieren Sie Ihre Beobachtungen kurz: Warum ist `reserve` oft deutlich schneller? Wie beeinflusst der Wachstumsfaktor die Anzahl der Umkopiervorgänge?

------------------------------------------------------------------------

## Bonus / Zusatzaufgaben für die Schnellen

Dieser Abschnitt ist optional und gibt Ihnen zusätzliche Übung sowie Bonuspunkte. Ziel ist es, Ihre Implementierung zu professionalisieren und gute Entwicklungspraktiken einzuführen.

### 1. Eigener Namespace `tfe24`

Zur besseren Kapselung legen Sie Ihre finale Implementierung in den Namespace `tfe24`:

```cpp
namespace tfe24 {
  template <class T>
  class myvector { /* ... */ };
} // namespace tfe24
```

Beachten Sie dabei:

- Öffentliche API bleibt analog der Basisaufgabe.
- Tests als `tfe24::myvector` verwenden.

### 2. Erstellung einer eigenen Bibliothek

Extrahieren Sie Ihre Implementierung in eine statische oder Shared Library:

Empfohlene Struktur:

```text
exercise-010/
  include/
    tfe24/myvector.hpp
  src/
    myvector.cpp
  CMakeLists.txt (Bibliothek + Demo + Tests)
```

In `CMakeLists.txt` (vereinfacht):

```cmake
add_library(tfe24_myvector
    src/myvector.cpp
)
target_include_directories(tfe24_myvector PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_compile_features(tfe24_myvector PUBLIC cxx_std_17)

add_executable(${PROJECT_NAME} main.cpp)
target_link_libraries(${PROJECT_NAME} PRIVATE tfe24_myvector fmt::fmt CLI11::CLI11)
```

Tests dann gegen `tfe24_myvector` linken:

```cmake
target_link_libraries(${PROJECT_NAME}-tests PRIVATE tfe24_myvector Catch2::Catch2WithMain)
```

### 3. Doxygen-Dokumentation

Dokumentieren Sie Ihre Klasse mit aussagekräftigen Kommentaren. Beispiel:

```cpp
/// \brief Ein einfacher dynamischer Vektor ähnlich std::vector.
/// \\tparam T Elementtyp.
/// \\invariant 0 <= size() <= capacity()
/// \\exception std::out_of_range bei ungültigem Index für at().
template <class T>
class myvector { /* ... */ };
```

Ergänzen Sie für jede öffentliche Methode:

- Kurzbeschreibung
- Parameter (`\\param`)
- Rückgabewert (`\\return`)
- Ausnahmehinweise (`\\throws`)
- Komplexität (z.B. amortisiert O(1) für `push_back`)

### 4. Erweiterte Rule-of-Five (optional)

Ergänzen Sie Move-Konstruktor und Move-Zuweisung für effizienteres Verschieben großer Vektoren. Schreiben Sie dazu Tests, die sicherstellen, dass nach einem Move der Quellvektor in einem validen, leeren Zustand ist (`size()==0`, keine Dangling Pointer).

### 5. Iterator-Schnittstelle (Stretch Goal)

Implementieren Sie rudimentäre Iteratoren (`begin()`, `end()`) und fügen Sie einfache Range-basierte for-Schleifen Tests hinzu. Dokumentieren Sie Gültigkeitsregeln bei Reallocation.

### 6. Wachstumspolitik variieren

Stellen Sie eine Strategie bereit (z.B. Faktor 1.5 vs. Verdopplung) und testen Sie beide per Konfiguration / Policy-Klasse.

### 7. Messung & Beobachtung

Instrumentieren Sie Reallocation-Ereignisse (Counter). Geben Sie in Tests oder Demo-Programm aus, wie viele Reallocations für N Inserts gebraucht wurden. Nutzen Sie dies zur Diskussion von Wachstumspolitiken.

------------------------------------------------------------------------

Nutzen Sie diese Zusatzaufgaben, um grundlegende Konzepte Richtung Produktionsreife zu vertiefen. Wählen Sie 2–3 Aspekte und setzen Sie diese sauber um, statt alles nur halb anzureißen.

Viel Erfolg beim Vertiefen! 🧠

------------------------------------------------------------------------

## Abgabemodalitäten

Zur Abgabe dieser Übung gehen Sie wie folgt vor:

1. Kurze Zusammenfassung Ihrer Erkenntnisse in Markdown in dieser Datei (`exercise-010/README.md`).

Empfohlene Punkte:

- Wachstumspolitik und amortisierte Kosten
- Korrektes Umkopieren/Deep-Copy
- Ergebnisse der `std::chrono`-Messungen (mit kurzer Interpretation)
- Besondere Randfälle/Fehlerbehandlung

1. Erstellen Sie einen Pull Request auf GitHub von Ihrem Branch (z. B. `solution-010`) gegen den Hauptzweig.
1. Tragen Sie den Benutzer `graugans` als Reviewer/Approver ein.
1. Stellen Sie sicher, dass alle Catch2-Tests erfolgreich sind (CI/`ctest`) und die README sauber formatiert ist.
1. Geben Sie Ihrem PR einen aussagekräftigen Titel (z. B. „exercise-010: tfe24::myvector mit Wachstum & chrono-Messungen“) und eine kurze Beschreibung Ihrer Umsetzung.

Hinweis: PRs werden nach Review und erfolgreichem Testlauf gemerged. Unvollständige PRs bitte als Draft markieren.

------------------------------------------------------------------------
