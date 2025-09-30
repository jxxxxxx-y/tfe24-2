# Aufgabenstellung (erweitert): `myvector` + JSON‑getriebene Tests mit Catch2 & *nlohmann::json*

## Notwendige git Kommandos

```sh
git status
git branch -a
git switch main
# create a new local branch based on the origin main
git switch -c solution-011 origin/main
# perform changes
# ....
git add exercise-011
git commit -m "feat: add exercise number two"
# push the changes to the cloud
git push -u origin solution-011
....
```


---

## Einfache `myvector`-Implementierung in C++

### Kontext & Lernziele

Ziel dieser Aufgabe ist es, eine vereinfachte Variante von `std::vector`
zu entwickeln, um die Grundlagen von **dynamischer Speicherverwaltung**
in C++ zu verstehen **und** diese über **JSON‑getriebene Tests mit Catch2**
automatisiert zu verifizieren:

- Dynamischen Speicher mit `new[]` anfordern und mit `delete[]` freigeben.  
- Speicherwachstum (Capacity, Reallocation) und Besitzverhältnisse nachvollziehen.  
- **Rule of Three** (Destruktor, Copy‑Konstruktor, Copy‑Zuweisung) sicher anwenden.  
- Grenzenprüfung und einfache Ausnahme‑Sicherheit umsetzen.  
- JSON‑basierte Testvektoren mit *nlohmann::json* einlesen und in **Catch2** als dynamische Testfälle ausführen.

> **Hinweis:** Das JSON‑Parsing und Catch2 sind bereits im Projekt eingebunden.

---

## Aufgabenbeschreibung

Implementieren Sie eine generische Klasse `myvector<T>` im Namespace `mystd`, angelehnt an die Standardbibliothek:  
[cppreference: `std::vector`](https://en.cppreference.com/w/cpp/container/vector)

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
- **Rule of Three**: Copy‑Konstruktor, Copy‑Zuweisungsoperator
- **Capacity‑Basics**
  - `size_t capacity() const noexcept;`
  - `void reserve(size_t new_cap);`
- **`operator[]`** (ohne Bounds‑Check)

---

## Vorgaben & Einschränkungen

- **Nicht erlaubt:** `std::vector`, `std::unique_ptr<T[]>`, `std::allocator`, `malloc/free`, externe Bibliotheken.  
- **Erlaubt:** `<stdexcept>`, `<algorithm>`, `<utility>`, `<initializer_list>`, `<cstddef>`, `<new>`, `<string>`.  
- **Namensraum:** `namespace mystd`.  
- **Dateistruktur (Vorschlag):**
  - `include/myvector.hpp` — Implementierung  
  - `tests/test_myvector_json.cpp` — JSON‑getriebene Catch2‑Tests  
  - `tests/test_vectors.json` — Testvektoren

---

## JSON‑getriebene Tests (Pflichtteil)

Schreiben Sie **einen** Catch2‑Test, der **alle** Testfälle aus einer JSON‑Datei lädt und dynamisch ausführt.  
Pfad der Datei: `tests/test_vectors.json` (kann in CMake/CTest als Arbeitsverzeichnis konfiguriert werden).

### Eingabe‑JSON: Schemastruktur

```jsonc
{
  "cases": [
    {
      "name": "push_resize_read",
      "initial_capacity": 0,           // optional
      "initial_size": 0,               // optional
      "initial_values": [1, 2, 3],     // optional (überschreibt initial_size)
      "operations": [
        { "op": "push_back", "value": 5 },
        { "op": "resize", "new_size": 6 },
        { "op": "at", "index": 1 },
        { "op": "clear" },
        { "op": "reserve", "new_cap": 32 }
      ],
      "expect": {
        "final_size": 0,               // Pflicht
        "min_capacity": 32,            // optional (anstelle exakter capacity‑Prüfung)
        "reads": [ { "index": 1, "value": 2 } ],     // optional
        "errors": [                                   // optional
          // z. B. { "op": "at", "index": 99, "error": "out_of_range" }
        ],
        "final_values": [ ]            // optional: Inhalt ab Index 0..size-1 prüfen
      }
    }
  ]
}
```

**Regeln & Bewertungshinweise:**  
- `initial_capacity` → via `reserve()` anwenden.  
- `initial_values` füllt den Vektor; falls vorhanden, **ignoriert** `initial_size`.  
- `operations` werden sequenziell ausgeführt.  
- Bei `at`‑Zugriffen sollen gelesene Werte in eine Ergebnisliste `reads` protokolliert werden.  
- Fehler/Exceptions (z. B. Out‑of‑Range) **beenden** den Testfall nicht, sondern werden als Einträge in `errors` gesammelt.  
- In den Erwartungen gilt:
  - **Pflicht:** `final_size` muss exakt stimmen.  
  - **Kapazität:** Prüfen Sie **entweder** `min_capacity` (≥) **oder** verzichten Sie auf eine Kapazitätsprüfung, um Wachstumsstrategien nicht zu erzwingen.  
  - **`reads`/`errors`:** vergleichen Sie **in Reihenfolge** der Ausführung.  
  - **`final_values`:** falls angegeben, prüfen Sie Inhalte über `operator[]`.

---

## Beispiel‑Testvektoren `tests/test_vectors.json`

> Dies ist ein **Beispiel**. Sie dürfen/solllen weitere Fälle ergänzen (Out‑of‑Range, mehrfaches Reallocate, leerer Vektor, nur `reserve`, …).

```json
{
  "cases": [
    {
      "name": "push_and_read",
      "initial_values": [1, 2, 3],
      "operations": [
        { "op": "push_back", "value": 5 },
        { "op": "at", "index": 1 }
      ],
      "expect": {
        "final_size": 4,
        "reads": [ { "index": 1, "value": 2 } ],
        "final_values": [1, 2, 3, 5]
      }
    },
    {
      "name": "resize_up_and_down",
      "initial_capacity": 0,
      "initial_size": 2,
      "operations": [
        { "op": "resize", "new_size": 10 },
        { "op": "resize", "new_size": 3 }
      ],
      "expect": {
        "final_size": 3,
        "min_capacity": 10
      }
    },
    {
      "name": "out_of_range_read_is_error",
      "initial_values": [7],
      "operations": [
        { "op": "at", "index": 5 }
      ],
      "expect": {
        "final_size": 1,
        "errors": [ { "op": "at", "index": 5, "error": "out_of_range" } ]
      }
    }
  ]
}
```

---

## Catch2‑Test (Skeleton)

> Catch2 ist bereits eingebunden. Verwenden Sie **einen** Test, der alle Cases aus `tests/test_vectors.json` lädt und mit `DYNAMIC_SECTION`/`INFO` aussagekräftige Fehlermeldungen erzeugt.

```cpp
// tests/test_myvector_json.cpp
#include <catch2/catch_all.hpp>
#include "myvector.hpp"
#include "nlohmann/json.hpp"
#include <fstream>
#include <string>

using json = nlohmann::json;

TEST_CASE("JSON-driven test cases for mystd::myvector<int>", "[json][myvector]") {
    // Pfad ggf. in CTest via WORKING_DIRECTORY setzen
    std::ifstream in("tests/test_vectors.json");
    REQUIRE(in && "tests/test_vectors.json not found");
    json doc;
    in >> doc;
    REQUIRE(doc.contains("cases"));
    for (const auto& tc : doc["cases"]) {
        const std::string name = tc.value("name", "<unnamed>");
        DYNAMIC_SECTION(name) {
            mystd::myvector<int> v;

            if (tc.contains("initial_capacity"))
                v.reserve(tc["initial_capacity"].get<size_t>());

            if (tc.contains("initial_values")) {
                const auto& arr = tc["initial_values"];
                v.resize(arr.size());
                for (size_t i = 0; i < arr.size(); ++i) v[i] = arr[i].get<int>();
            } else if (tc.contains("initial_size")) {
                v.resize(tc["initial_size"].get<size_t>());
            }

            json reads = json::array();
            json errors = json::array();

            if (tc.contains("operations")) {
                for (const auto& op : tc["operations"]) {
                    try {
                        const std::string op_name = op.value("op", "");
                        if (op_name == "push_back") {
                            v.push_back(op.at("value").get<int>());
                        } else if (op_name == "resize") {
                            v.resize(op.at("new_size").get<size_t>());
                        } else if (op_name == "at") {
                            size_t idx = op.at("index").get<size_t>();
                            int value = v.at(idx);
                            reads.push_back({{"index", idx}, {"value", value}});
                        } else if (op_name == "clear") {
                            v.clear();
                        } else if (op_name == "reserve") {
                            v.reserve(op.at("new_cap").get<size_t>());
                        } else {
                            errors.push_back({{"op", op_name}, {"error", "unknown_operation"}});
                        }
                    } catch (const std::out_of_range&) {
                        json e = op;
                        e["error"] = "out_of_range";
                        errors.push_back(e);
                    } catch (const std::exception& e) {
                        json eobj = op;
                        eobj["error"] = std::string("exception: ") + e.what();
                        errors.push_back(eobj);
                    }
                }
            }

            REQUIRE(tc.contains("expect"));
            const auto& expect = tc["expect"];

            // final_size (exakt)
            REQUIRE(v.size() == expect.at("final_size").get<size_t>());

            // capacity (nur prüfen, wenn min_capacity angegeben)
            if (expect.contains("min_capacity")) {
                CHECK(v.capacity() >= expect["min_capacity"].get<size_t>());
            }

            // reads (optional, Reihenfolge muss stimmen)
            if (expect.contains("reads")) {
                CHECK(reads == expect["reads"]);
            }

            // errors (optional, Reihenfolge entspricht Ausführung)
            if (expect.contains("errors")) {
                CHECK(errors == expect["errors"]);
            }

            // final_values (optional)
            if (expect.contains("final_values")) {
                const auto& vals = expect["final_values"];
                REQUIRE(vals.size() == v.size());
                for (size_t i = 0; i < vals.size(); ++i) {
                    INFO("Mismatch at index " << i);
                    CHECK(v[i] == vals[i].get<int>());
                }
            }
        }
    }
}
```

---

## CMake‑Hinweis (Tests)

Falls nötig, fügen Sie ein Testtarget hinzu (Catch2 ist bereits vorhanden):

```cmake
add_executable(test_myvector_json tests/test_myvector_json.cpp)
target_include_directories(test_myvector_json PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include)
# Catch2 und nlohmann::json sind eingebunden; ansonsten:
# target_link_libraries(test_myvector_json PRIVATE Catch2::Catch2WithMain)
add_test(NAME myvector_json_tests COMMAND test_myvector_json WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})
```

---

## Abgabe

- `include/myvector.hpp`
- `tests/test_myvector_json.cpp`
- `tests/test_vectors.json` (mit mindestens 5 sinnvollen Fällen inkl. Fehlerfall)
- Kurze `README.md` mit Build‑ und Test‑Anleitung:
  ```sh
  cmake -S . -B build
  cmake --build build -j
  ctest --test-dir build --output-on-failure
  ```

Viel Erfolg beim Test‑getriebenen „Selbst‑Vectorn“! 🚀