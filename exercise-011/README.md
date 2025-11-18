# Aufgabenstellung  `std::vector` JSON‑getriebene Tests mit Catch2 & *nlohmann::json*

## Notwendige git Kommandos

```sh
git fetch --all
git status
git branch -a
git switch main
# create a new local branch based on the upstream main
git switch -c exercise-011 upstream/exercise-011
# prepare the target branch for the pull request
git push origin exercise-011:exercise-011
# create a solution branch locally
git switch -c solution-011 upstream/exercise-011

# make changes
git add exercise-011
git commit -m "feat: add exercise number ten"

# push the changes to the cloud
git push -u origin solution-011

# Show the git graph
git log --graph --oneline --decorate --all
```

---

## JSON in C++ – Grundlagen, Verwendung mit *nlohmann::json*, Raw String Literals & CMake

Bevor wir JSON-getriebene Tests schreiben, müssen wir verstehen, **was JSON überhaupt ist**, wie der Aufbau funktioniert und wie JSON **in C++ verarbeitet** wird. Anschließend wird gezeigt, wie wir JSON-Dateien robust über CMake einbinden, bevor es in die eigentliche Aufgabe mit `std::vector` und JSON-getriebenen Catch2-Tests geht.

---

### 1. Was ist JSON?

**JSON (JavaScript Object Notation)** ist ein leichtgewichtiges, textbasiertes Format zur Darstellung strukturierter Daten.

Typische Anwendungsfälle:

- Konfigurationsdateien
- Testfall-Definitionen
- Datenaustausch zwischen Programmen (APIs, Microservices, etc.)
- Speicherung von Objekten, Einstellungen und Metadaten

Vorteile:

- gut lesbar (auch für Menschen)
- sprachunabhängig
- sehr weit verbreitet
- klar und einfach aufgebaut

---

### 2. Grundlegende Konzepte von JSON

JSON besteht im Kern aus zwei Grundstrukturen: **Objekten** und **Arrays**.

#### 2.1 Objekt

Ein Objekt ist eine Sammlung von Schlüssel–Wert-Paaren:

```json
{
  "name": "Alice",
  "age": 25,
  "active": true
}
```

- Schlüssel (Keys) sind **immer Strings**.
- Werte können verschiedene Typen haben (String, Number, Boolean, Null, Object, Array).
- Die Reihenfolge der Schlüssel ist normalerweise nicht relevant.

---

#### 2.2 Array

Ein Array ist eine **geordnete Liste** von Werten:

```json
["rot", "grün", "blau"]
```

Die Elemente können wieder beliebige JSON-Werte sein (z. B. auch Objekte):

```json
[
  { "id": 1, "title": "First" },
  { "id": 2, "title": "Second" }
]
```

---

### 3. JSON-Datentypen

JSON kennt **genau sechs** Datentypen:

| Typ      | Beispiel        |
|----------|-----------------|
| String   | `"Hallo"`       |
| Number   | `42`, `3.14`    |
| Boolean  | `true`, `false` |
| Null     | `null`          |
| Object   | `{ "x": 1 }`    |
| Array    | `[1, 2, 3]`     |

Es gibt **keine** speziellen Typen für Date, Time, Enum, Char etc. – solche Dinge werden meist als String dargestellt.

---

### 4. JSON erlaubt **keine Kommentare**

Wichtig: JSON ist absichtlich minimalistisch.
Kommentare sind **nicht** Teil der Spezifikation.

Ungültig:

```json
{
  // Kommentar
  "x": 10
}
```

Ebenfalls ungültig:

```json
{
  "x": 10 /* Kommentar */
}
```

Wenn zusätzliche Erklärungen benötigt werden, nutzt man oft ein eigenes Feld:

```json
{
  "_comment": "Config-Datei für Entwicklungsmodus",
  "x": 10
}
```

---

### 5. Gültige und ungültige JSON-Beispiele

✔ **Gültig:**

```json
{
  "user": "Chris",
  "roles": ["editor", "admin"]
}
```

❌ **Ungültig – fehlende Anführungszeichen um den Key:**

```json
{
  user: "Chris"
}
```

❌ **Ungültig – trailing comma:**

```json
{
  "x": 10,
}
```

---

### 6. JSON in C++ mit *nlohmann::json*

Im Projekt ist die Bibliothek **nlohmann::json** bereits eingebunden.
Typalias:

```cpp
#include <nlohmann/json.hpp>
#include <fmt/core.h>

using json = nlohmann::json;
```

#### 6.1 JSON-Objekt in C++ erzeugen

```cpp
json person = {
    {"name", "Anna"},
    {"age", 30},
    {"languages", {"C++", "Python"}},
    {"active", true}
};
```

---

#### 6.2 Werte auslesen

```cpp
fmt::print("Name: {}
", person["name"].get<std::string>());
fmt::print("Age:  {}
", person["age"].get<int>());
fmt::print("First language: {}
", person["languages"][0].get<std::string>());
```

Mit `contains` kann geprüft werden, ob ein Key existiert:

```cpp
if (person.contains("age")) {
    fmt::print("Age is present: {}
", person["age"].get<int>());
}
```

---

#### 6.3 JSON formatiert ausgeben

```cpp
fmt::print("{}
", person.dump(4));
```

`dump(4)` pretty-printet mit 4 Leerzeichen Einrückung.

---

#### 6.4 JSON aus einer Datei einlesen

```cpp
std::ifstream in("tests/test_vectors.json");
json doc;
in >> doc;
```

Danach kann man wie gewohnt auf `doc["cases"]`, `doc["cases"][0]` usw. zugreifen.

---

### 7. Raw String Literals in C++ (sehr hilfreich für JSON)

Normale String-Literale in C++ brauchen Escape-Sequenzen:

```cpp
std::string s = "{ "x": 10, "y": 20 }";
```

Das ist unübersichtlich.
Stattdessen kann man **Raw String Literals** verwenden:

```cpp
std::string s = R"({ "x": 10, "y": 20 })";
```

Vorteile:

- keine Escape-Sequenzen
- JSON bleibt optisch JSON
- mehrzeilig möglich

#### 7.1 Mehrzeiliges Beispiel

```cpp
json cfg = json::parse(R"(
{
  "port": 8080,
  "enabled": true,
  "mode": "debug"
}
)");
```

#### 7.2 Eigene Delimiter

Falls im Inhalt `)"` vorkommt, kann man einen eigenen Delimiter nutzen:

```cpp
std::string tricky = R"###(
Text mit )" im Inhalt
)###";
```

---

### 8. **Trick 17: Dateipfade robust handhaben mit CMake + `configure_file()` + `constexpr auto`**

Dateipfade sind immer fehleranfällig, weil Working Directories variieren.
Die robusteste Lösung (wie im Beispielprojekt `version_info`) ist:

### 8.1 `config.h.in` erstellen

```cpp
#pragma once

namespace config {
    constexpr auto data_dir = "@CMAKE_CURRENT_SOURCE_DIR@/tests";
    constexpr auto json_tests = "@CMAKE_CURRENT_SOURCE_DIR@/tests/test_vectors.json";
}
```

### 8.2 `CMakeLists.txt`

```cmake
configure_file(
    ${CMAKE_CURRENT_SOURCE_DIR}/config.hpp.in
    ${CMAKE_CURRENT_BINARY_DIR}/config.hpp
    @ONLY
)
```

### 8.3 Nutzung im Code

```cpp
#include "config.h"

#include <fstream>
#include <string>
#include <iterator>
#include <filesystem>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

namespace fs = std::filesystem;

const auto path = fs::path{json_config::json_test_file};

std::ifstream in(path);
if (!in.is_open()) {
    fmt::print("Fehler: konnte JSON-Datei nicht öffnen: {}\n", path.string());
    return;
}

// gesamte Datei in einen String laden
std::string text(std::istreambuf_iterator<char>{in},
                 std::istreambuf_iterator<char>{});

// JSON parsen
json doc = json::parse(text);
```

Damit sind Pfade:

- reproduzierbar
- unabhängig vom Working Directory
- portable und build-system-gesteuert

---

### 9. Übergang zur Aufgabe

Mit diesem Wissen können wir nun:

- JSON-Dateien als **Testfall-Beschreibung** verwenden.
- Diese JSON-Daten in C++ mit *nlohmann::json* einlesen.
- Aus den JSON-Daten dynamisch **Catch2-Testfälle** erzeugen.
- Dateipfade zur JSON-Datei über CMake zuverlässig bereitstellen.

Im folgenden Abschnitt geht es genau darum:
Wir verwenden **`std::vector<int>`** als getestete Datenstruktur und konzentrieren uns vollständig auf:

- das Verständnis von JSON,
- das Einlesen mit *nlohmann::json*,
- und die Erstellung JSON-getriebener Tests mit Catch2.

---

## Aufgabe: JSON-getriebene Tests mit `std::vector<int>`

Anstatt eine eigene `myvector<T>`-Klasse zu implementieren, verwenden wir in dieser Übung bewusst den vorhandenen `std::vector<int>`.
Der Schwerpunkt liegt darauf, **Testfälle in JSON zu beschreiben** und diese **automatisiert in Catch2** auszuführen.

### Lernziele

- JSON-Strukturen lesen und verstehen.
- JSON-Dateien mit *nlohmann::json* in C++ einlesen.
- Testfälle aus einer JSON-Datei dynamisch in Catch2 erzeugen.
- Pfade zur JSON-Datei über eine generierte `config.hpp` (CMake `configure_file`) robust handhaben.
- Verhalten von `std::vector<int>` über Operationen wie `push_back`, `resize`, `clear` nachvollziehen.

---

## JSON-getriebene Tests

Schreiben Sie **einen** Catch2-Test, der **alle** Testfälle aus einer JSON-Datei lädt und dynamisch ausführt.
Pfad der Datei: `tests/test_vectors.json` (idealerweise über `config.hpp` eingebunden, z. B. `config::json_tests`).

### Eingabe-JSON

Hierbei handelt es sich lediglich um einen nicht getesteten Vorschlag, versuchen Sie eigene Ideen und Vorschläge einzubringen. Das Beispiel ist AI generiert und kann Fehler enthalten, es dient lediglich als Lösungsskizze!

```jsonc
{
  "cases": [
    {
      "name": "push_and_resize",
      "initial_values": [1, 2],
      "operations": [
        { "op": "push_back", "value": 3 },
        { "op": "resize", "new_size": 4 }
      ],
      "expect": {
        "final_size": 4,
        "final_values": [1, 2, 3, 0]
      }
    }
  ]
}
```

---

## Beispiel-Testvektoren `tests/test_vectors.json`

```json
{
  "cases": [
    {
      "name": "push_and_resize",
      "initial_values": [1, 2],
      "operations": [
        { "op": "push_back", "value": 3 },
        { "op": "resize", "new_size": 4 }
      ],
      "expect": {
        "final_size": 4,
        "final_values": [1, 2, 3, 0]
      }
    },
    {
      "name": "resize_down",
      "initial_values": [10, 20, 30, 40],
      "operations": [
        { "op": "resize", "new_size": 2 }
      ],
      "expect": {
        "final_size": 2,
        "final_values": [10, 20]
      }
    },
    {
      "name": "clear_vector",
      "initial_values": [7, 8, 9],
      "operations": [
        { "op": "clear" }
      ],
      "expect": {
        "final_size": 0,
        "final_values": []
      }
    }
  ]
}
```

---

## Catch2-Test (Skeleton)

```cpp
#include <catch2/catch_all.hpp>
#include <nlohmann/json.hpp>
#include "config.hpp"

#include <vector>
#include <filesystem>
#include <fstream>
#include <iterator>
#include <string>

using json = nlohmann::json;
namespace fs = std::filesystem;

TEST_CASE("JSON-driven test cases for std::vector<int>", "[json][vector]") {
    const auto path = fs::path{config::json_tests};
    std::ifstream in(path);
    REQUIRE(in.is_open());

    std::string text(
        std::istreambuf_iterator<char>{in},
        std::istreambuf_iterator<char>{}
    );

    json doc = json::parse(text);
    REQUIRE(doc.contains("cases"));

    for (const auto& tc : doc["cases"]) {
        DYNAMIC_SECTION(tc.value("name","<unnamed>")) {
            std::vector<int> v;

            if (tc.contains("initial_values")) {
                auto arr = tc["initial_values"];
                v.resize(arr.size());
                for (size_t i=0; i<arr.size(); ++i)
                    v[i] = arr[i].get<int>();
            }

            if (tc.contains("operations")) {
                for (const auto& op : tc["operations"]) {
                    auto name = op.value("op","");
                    if (name=="push_back")
                        v.push_back(op["value"].get<int>());
                    else if (name=="resize")
                        v.resize(op["new_size"].get<size_t>());
                    else if (name=="clear")
                        v.clear();
                }
            }

            auto& expect = tc["expect"];
            CHECK(v.size() == expect["final_size"].get<size_t>());

            if (expect.contains("final_values")) {
                auto arr = expect["final_values"];
                REQUIRE(arr.size() == v.size());
                for (size_t i=0; i<arr.size(); ++i)
                    CHECK(v[i] == arr[i].get<int>());
            }
        }
    }
}
```

---

### Lösungsweg

Zerlegen Sie die Aufgabe in kleine, gut beherrschbare Schritte. Vorgehensweise und kontinuierliches Arbeiten sind hier wichtiger als sofort die gesamte Lösung vor Augen zu haben.

### 1. Einstieg: JSON-Datei einlesen
Beginnen Sie mit dem fundamentalen Teil: **dem Einlesen einer JSON-Datei**.
Legen Sie in Ihrem Projekt einen Ordner wie `testdata/` oder `tests/data/` an und platzieren Sie dort eine erste einfache JSON-Datei.

Passen Sie Ihr Projekt so an, dass diese Datei eingelesen werden kann.
Testen Sie dies zunächst **in einer einfachen `main.cpp`**, in der Sie:

1. die Datei öffnen,
2. den Inhalt vollständig einlesen,
3. und mit `nlohmann::json` parsen.

Ziel dieses Schrittes:
✔ Die Datei wird gefunden
✔ Sie können JSON fehlerfrei einlesen
✔ Sie verstehen die grundlegende Verarbeitung

Erst wenn dies zuverlässig funktioniert, übertragen Sie dieses Wissen in Ihren Catch2-Testfall.

> **Tipp:** Arbeiten Sie hier bewusst explorativ. Machen Sie sich mit JSON-Strukturen vertraut und probieren Sie Zugriffsmöglichkeiten (`contains()`, `get<T>()`, `dump()`) direkt in der `main.cpp` aus.

Erstellen Sie anschließend einen **Commit**, der diesen Stand sauber dokumentiert.

---

### 2. Minimale JSON-Struktur für den Testfall entwerfen
Im nächsten Schritt entwickeln Sie eine **minimale JSON-Datei**, die einen sehr einfachen Testfall beschreibt.
Beispiel:

```json
{
  "cases": [
    {
      "name": "simple_init",
      "initial_values": [1, 2],
      "operations": [],
      "expect": {
        "final_size": 2
      }
    }
  ]
}
```

Damit schaffen Sie die Basis für den späteren dynamischen Test.

Speichern Sie diese Datei unter `tests/test_vectors.json` oder einem ähnlich sinnvollen Pfad.

Erstellen Sie danach wieder einen Commit, um diesen Fortschritt festzuhalten.

---

### 3. Konzepte schrittweise in den Catch2-Test übertragen

Übernehmen Sie nun die zuvor erarbeitete Logik aus Ihrer `main.cpp` in den eigentlichen Catch2-Testfall:

- JSON-Datei laden
- Inhalt parsen
- Prüfen, ob `cases` existiert
- Ersten Testfall auslesen und einfache Assertions schreiben

Führen Sie zuerst nur **eine minimale Prüfung** durch, etwa:

```cpp
CHECK(v.size() == expect["final_size"].get<size_t>());
```

Wenn dieser kleinste Testfall erfolgreich ist, haben Sie die Grundlage geschaffen.

Wieder committen.

---

### 4. Iterativ erweitern

Nun steigern Sie Schritt für Schritt die Komplexität:

1. **Unterstützung für `push_back`**
2. **Unterstützung für `resize`**
3. **Unterstützung für `clear`**
4. **Überprüfen der `final_values`**
5. Optional: Fehlerfälle wie Out-of-Range-Zugriffe

Nach jedem Schritt gilt:

✔ Funktion testen
✔ JSON-Datei anpassen oder erweitern
✔ Commit erstellen

---

### 5. Denken Sie in kleinen Schritten

Das Entscheidende:
Sie müssen **nicht sofort das gesamte System** implementieren.

Arbeiten Sie inkrementell:

- kleine Änderungen
- häufiges Testen
- regelmäßige Commits
- dokumentierte Zwischenschritte

So entsteht eine stabile, nachvollziehbare Lösung, in der jeder Schritt begründet und überprüfbar ist.

---

### 6. Erzählen Sie eine Geschichte

Ihre Git-Historie sollte zeigen, **wie Sie die Lösung erarbeitet haben**:

- Welche Herausforderungen gab es?
- Warum haben Sie eine bestimmte Struktur gewählt?
- Welche Fehler traten auf – und wie wurden sie behoben?

Diese Art der Dokumentation ist ein wichtiger Teil des Lernprozesses. Sie macht Ihre Gedanken sichtbar und zeigt, wie Sie Probleme verstehen, analysieren und lösen.

## Abgabemodalitäten

Zur Abgabe dieser Übung gehen Sie wie folgt vor:

> Kurze Zusammenfassung Ihrer Erkenntnisse in Markdown in dieser Datei (exercise-011/README.md).

Erstellen Sie einen Pull Request auf GitHub von Ihrem Branch (z. B. solution-011) gegen den Zweig `excercise-011`.
Tragen Sie den Benutzer `graugans` als Reviewer/Approver ein.
Stellen Sie sicher, dass alle Catch2-Tests erfolgreich sind (ctest) und die README sauber formatiert ist.
Geben Sie Ihrem PR einen aussagekräftigen Titel (z. B. „exercise-011: tfe24::vector mit JSON Test input“) und eine kurze Beschreibung Ihrer Umsetzung.

Hinweis: PRs werden nach Review und erfolgreichem Testlauf gemerged. Unvollständige PRs bitte als Draft markieren.

Viel Erfolg beim test‑getriebenen „Selbst‑Vectorn“! 🚀
