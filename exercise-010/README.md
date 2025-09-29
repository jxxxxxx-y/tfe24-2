# Aufgabenstellung

## Notwendige git Kommandos

```sh
git status
git branch -a
git fetch --all
# create a new local branch based on the upstream (graugans)
git switch -c solution-002 upstream/main
# copy the folder exercise-001 to exercise-002
cp exercise-001/ exercise-002 -r
# modify the CMakeLists.txt and main.cpp in the directory exercise-002
# modify the top-level CMakeLists.txt
# commit the changes
git add exercise-002
git commit -m "feat: add exercise number two"
# push the changes to the cloud
git push -u origin solution-002
....
```

## Einfache `myvector`-Implementierung in C++

### Kontext & Lernziele

Ziel dieser Aufgabe ist es, eine vereinfachte Variante von `std::vector`
zu entwickeln, um die Grundlagen von **dynamischer Speicherverwaltung**
in C++ zu verstehen:

-   Dynamischen Speicher mit `new[]` anfordern und mit `delete[]`
    freigeben.\
-   Speicherwachstum (Capacity, Reallocation) und Besitzverhältnisse
    nachvollziehen.\
-   **Rule of Three** (Destruktor, Copy-Konstruktor, Copy-Zuweisung)
    sicher anwenden.\
-   Grenzenprüfung und einfache Ausnahme-Sicherheit umsetzen.

------------------------------------------------------------------------

## Aufgabenbeschreibung

Implementieren Sie eine generische Klasse `myvector<T>`, angelehnt an
die Standardbibliothek:\
[cppreference:
`std::vector`](https://en.cppreference.com/w/cpp/container/vector)

### Minimal geforderte öffentliche Schnittstelle

-   `void push_back(const T& value);`
-   `T& at(size_t index);` und `const T& at(size_t index) const;`
-   `size_t size() const noexcept;`
-   `void resize(size_t new_size);`
-   `void clear() noexcept;`

### Zusätzlich **verbindlich**

-   **Konstruktoren**
    -   `myvector() noexcept;`
    -   `explicit myvector(size_t count);`
-   **Destruktor**
-   **Rule of Three**
    -   Copy-Konstruktor
    -   Copy-Zuweisungsoperator
-   **Capacity-Basics**
    -   `size_t capacity() const noexcept;`
    -   `void reserve(size_t new_cap);`
-   **`operator[]`**

------------------------------------------------------------------------

## Vorgaben & Einschränkungen

-   **Nicht erlaubt:** `std::vector`, `std::unique_ptr<T[]>`,
    `std::allocator`, `malloc/free`, externe Bibliotheken.\
-   **Erlaubt:** `<stdexcept>`, `<algorithm>`, `<utility>`,
    `<initializer_list>`, `<cstddef>`, `<new>`, `<string>` in Tests.\
-   **Namensraum:** Packen Sie alles in den Namespace `mystd`.\
-   **Dateistruktur:**
    -   `myvector.hpp` -- Implementierung\
    -   `main.cpp` -- einfache Tests / Demo

------------------------------------------------------------------------

## Beispieltests (Skizze)

``` cpp
#include "myvector.hpp"
#include <cassert>
#include <string>

int main() {
    using mystd::myvector;

    myvector<int> v;
    v.push_back(1);
    v.push_back(2);
    v.push_back(3);

    assert(v.size() == 3);
    assert(v.at(0) == 1);
    assert(v[1] == 2);

    v.resize(10);
    v.clear();

    return 0;
}
```
