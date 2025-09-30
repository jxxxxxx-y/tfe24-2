# Übung: Fahrzeuge, Vererbung & Aggregation

## Lernziele
- Klassenhierarchie mit **abstrakten Basisklassen** und **überschriebenen** Methoden entwerfen.  
- **Vererbung** (is-a) sinnvoll einsetzen (z. B. `Car` ist ein `Vehicle`).  
- **Aggregation/Komposition** (has-a) für Teilsysteme nutzen (z. B. `Vehicle` hat einen `Motor`).  
- Späte Bindung via **virtual** / **override** verstehen.  
- Sauberer Umgang mit Ressourcen (z. B. `std::unique_ptr` für Besitzverhältnisse).  

## Fachlicher Kontext
Im Studiengang Fahrzeugelektronik betrachten wir ein Fahrzeug als System mit unterschiedlichen Antrieben.  
Die **Fahrzeugklasse** bildet die gemeinsamen Eigenschaften und das Verhalten ab, während **spezialisierte Fahrzeugtypen** Feinheiten überschreiben.  
Der **Motor/Antrieb** ist als austauschbares Modul (Aggregation/Komposition) modelliert — so lassen sich Verbrenner, E-Motor oder Hybrid kombinieren.

---

## Aufgabenbeschreibung

### 1) Klassen- & Schnittstellendesign

**Fahrzeuge (Vererbung)**
- `class Vehicle` (abstrakt)
- Spezialisierungen: `Car`, `Truck`, `Motorcycle`

**Antriebe (Aggregation/Komposition)**
- `class IMotor` (abstrakt)
- Implementierungen: `CombustionEngine`, `ElectricMotor`, optional `HybridMotor`

**Aggregation/Komposition**
- `Vehicle` besitzt genau einen `std::unique_ptr<IMotor> motor_`.

---

## UML-Klassendiagramm

```mermaid
classDiagram
    class Vehicle {
        - string vin
        - double mass_kg
        - unique_ptr<IMotor> motor_
        + range_km() double
        + drive(double km) void
        + type() string
    }
    class Car {
        + range_km() double
        + drive(double km) void
        + type() string
    }
    class Truck {
        + range_km() double
        + drive(double km) void
        + type() string
    }
    class Motorcycle {
        + range_km() double
        + drive(double km) void
        + type() string
    }

    Vehicle <|-- Car
    Vehicle <|-- Truck
    Vehicle <|-- Motorcycle
    Vehicle *-- IMotor

    class IMotor {
        <<interface>>
        + available_energy_kWh() double
        + consume_for_distance(double km, double mass_kg) double
        + label() string
    }
    class CombustionEngine {
        - double fuel_l
        - double l_per_100km
    }
    class ElectricMotor {
        - double battery_kWh
        - double kWh_per_100km
        - double recuperation_factor
    }

    IMotor <|-- CombustionEngine
    IMotor <|-- ElectricMotor
```

---

## C++-Skeleton (Auszug)

*(siehe motor.hpp, vehicle.hpp, main.cpp im Unterrichtsbeispiel)*

---

## Abgabe

- `motor.hpp`, `vehicle.hpp`, `main.cpp`  
- Kurze **README.md** mit Build‑Anleitung (`g++ -std=c++20 -Wall -Wextra main.cpp -o app`).  
- Ergänzen Sie mindestens einen weiteren Fahrzeugtyp (z. B. `Motorcycle`) **oder** einen weiteren Motortyp (z. B. `HybridMotor`).  

---

Viel Erfolg 🚗⚡️🚚