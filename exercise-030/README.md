# Übung: Strategy Pattern – Logger mit JSON- und fmt-Ausgabe

## Lernziele

- **Strategy Pattern** verstehen und anwenden (Austausch von Algorithmen zur Laufzeit).
- **Interface-basierte Programmierung** und **Dependency Injection** nutzen.
- Saubere **Trennung von Anliegen** (Kontext vs. konkrete Strategie).
- Optional: Konfiguration über **JSON** und Logging-Formatierung mit **fmt**.

> Annahmen: *nlohmann::json* und *fmt* stehen im Projekt bereit (oder alternativ mit kleinen Anpassungen ersetzbar).

---

## Aufgabenbeschreibung

Implementieren Sie einen Logger, der zur Laufzeit zwischen zwei Strategien wechseln kann:

1. `JsonLogger` – schreibt strukturierte Einträge als **JSON-Zeilen** (line-delimited JSON) in eine Datei.
2. `FmtConsoleLogger` – schreibt formattierte **Kommandozeilen-Ausgabe** mittels *fmt*.

Die Auswahl der Strategie erfolgt **nicht** per `if/else` im Anwendungscode, sondern über das **Strategy Pattern**: der Anwendungskontext kennt nur das `ILogger`-Interface. Die konkrete Strategie wird via **Konstruktor-Injektion** (oder Setter) bereitgestellt und kann zur Laufzeit gewechselt werden.

---

## Anforderungen

### Fachliche Anforderungen

- Jeder Logeintrag enthält mindestens:
  - `timestamp` (ISO-8601, z. B. `2025-09-30T12:34:56Z`),
  - `level` (z. B. `"info" | "warn" | "error"`),
  - `message` (Freitext),
  - optional `context` (Key-Value-Objekt, z. B. `{ "module": "auth", "user": "alice" }`).

- **JsonLogger**
  - schreibt **eine JSON-Zeile pro Eintrag** (LDJSON/NDJSON) in eine angegebene Datei.
  - Datei wird im Konstruktor geöffnet; im Destruktor geschlossen.
  - Robust gegen fehlende Felder (setzt sinnvolle Defaults).

- **FmtConsoleLogger**
  - verwendet *fmt* für formattierte Ausgabe, z. B.:

    ```text
    [2025-09-30T12:34:56Z] (INFO) user=alice module=auth :: login ok
    ```

  - `context` wird als `key=value` Paare angehängt.

### Technische Anforderungen

- `ILogger` Interface definiert die **einheitliche** API.
- `Logger`-Kontext kapselt die Strategie und bietet komfortable Methoden (`info`, `warn`, `error`).
- **Keine** `if (json) ... else (fmt) ...`-Verzweigung im Kontext: nur Polymorphie!
- Exception-sicherer Umgang mit Dateiressourcen.
- Zeitzone: UTC oder lokal – aber konsistent (Dokumentation in README).

---

## UML (Mermaid)

```mermaid
classDiagram
    class ILogger {
        <<interface>>
        + log(string level, string message, map<string,string> context) void
    }

    class JsonLogger {
        - ofstream out_
        - string path_
        + JsonLogger(string path)
        + log(string level, string message, map<string,string> context) void
    }

    class FmtConsoleLogger {
        + FmtConsoleLogger()
        + log(string level, string message, map<string,string> context) void
    }

    class Logger {
        - unique_ptr<ILogger> strategy_
        + Logger(unique_ptr<ILogger>)
        + set_strategy(unique_ptr<ILogger>) void
        + info(string msg, map<string,string> ctx = {} ) void
        + warn(string msg, map<string,string> ctx = {} ) void
        + error(string msg, map<string,string> ctx = {} ) void
    }

    ILogger <|.. JsonLogger
    ILogger <|.. FmtConsoleLogger
    Logger *-- ILogger
```

---

## Starter-Skeleton

### `ilogger.hpp`

```cpp
#pragma once
#include <string>
#include <map>

struct ILogger {
    virtual ~ILogger() = default;
    virtual void log(const std::string& level,
                     const std::string& message,
                     const std::map<std::string, std::string>& context = {}) = 0;
};
```

### `json_logger.hpp` / `json_logger.cpp`

```cpp
// json_logger.hpp
#pragma once
#include "ilogger.hpp"
#include <fstream>
#include <string>

class JsonLogger : public ILogger {
public:
    explicit JsonLogger(std::string path);
    ~JsonLogger() override;
    void log(const std::string& level,
             const std::string& message,
             const std::map<std::string, std::string>& context = {}) override;
private:
    std::ofstream out_;
};
```

```cpp
// json_logger.cpp
#include "json_logger.hpp"
#include "nlohmann/json.hpp"
#include <chrono>
#include <iomanip>
#include <sstream>

using json = nlohmann::json;

static std::string iso8601_now_utc() {
    using namespace std::chrono;
    auto now = system_clock::now();
    std::time_t t = system_clock::to_time_t(now);
    std::tm tm{};
#ifdef _WIN32
    gmtime_s(&tm, &t);
#else
    gmtime_r(&t, &tm);
#endif
    std::ostringstream oss;
    oss << std::put_time(&tm, "%FT%TZ");
    return oss.str();
}

JsonLogger::JsonLogger(std::string path) : out_(std::move(path), std::ios::app) {}

JsonLogger::~JsonLogger() = default;

void JsonLogger::log(const std::string& level,
                     const std::string& message,
                     const std::map<std::string, std::string>& context) {
    json j;
    j["timestamp"] = iso8601_now_utc();
    j["level"] = level;
    j["message"] = message;
    if (!context.empty()) j["context"] = context;
    out_ << j.dump() << '\n';
    out_.flush();
}
```

### `fmt_console_logger.hpp` / `fmt_console_logger.cpp`

```cpp
// fmt_console_logger.hpp
#pragma once
#include "ilogger.hpp"

class FmtConsoleLogger : public ILogger {
public:
    void log(const std::string& level,
             const std::string& message,
             const std::map<std::string, std::string>& context = {}) override;
};
```

```cpp
// fmt_console_logger.cpp
#include "fmt_console_logger.hpp"
#include <fmt/core.h>
#include <chrono>
#include <iomanip>
#include <sstream>

static std::string iso8601_now_local() {
    using namespace std::chrono;
    auto now = system_clock::now();
    std::time_t t = system_clock::to_time_t(now);
    std::tm tm{};
#ifdef _WIN32
    localtime_s(&tm, &t);
#else
    localtime_r(&t, &tm);
#endif
    std::ostringstream oss;
    oss << std::put_time(&tm, "%FT%T");
    return oss.str();
}

void FmtConsoleLogger::log(const std::string& level,
                           const std::string& message,
                           const std::map<std::string, std::string>& context) {
    std::string ctx_str;
    for (const auto& [k, v] : context) {
        if (!ctx_str.empty()) ctx_str += ' ';
        ctx_str += k + '=' + v;
    }
    if (!ctx_str.empty()) ctx_str = " " + ctx_str;

    fmt::print("[{}] ({}){} :: {}\n", iso8601_now_local(), level, ctx_str, message);
}
```

### `logger.hpp`

```cpp
#pragma once
#include "ilogger.hpp"
#include <memory>
#include <utility>

class Logger {
public:
    explicit Logger(std::unique_ptr<ILogger> strat) : strategy_(std::move(strat)) {}
    void set_strategy(std::unique_ptr<ILogger> strat) { strategy_ = std::move(strat); }

    void info(const std::string& msg, const std::map<std::string, std::string>& ctx = {}) {
        if (strategy_) strategy_->log("info", msg, ctx);
    }
    void warn(const std::string& msg, const std::map<std::string, std::string>& ctx = {}) {
        if (strategy_) strategy_->log("warn", msg, ctx);
    }
    void error(const std::string& msg, const std::map<std::string, std::string>& ctx = {}) {
        if (strategy_) strategy_->log("error", msg, ctx);
    }
private:
    std::unique_ptr<ILogger> strategy_;
};
```

### `main.cpp` (Demo)

```cpp
#include "logger.hpp"
#include "json_logger.hpp"
#include "fmt_console_logger.hpp"
#include <memory>

int main() {
    Logger log{std::make_unique<FmtConsoleLogger>()};
    log.info("Application started", {{"module","core"}});
    log.warn("Low battery", {{"soc","12%"}});

    log.set_strategy(std::make_unique<JsonLogger>("app.log.jsonl"));
    log.info("Switch to JSON logger", {{"module","core"}});
    log.error("Fatal error", {{"code","E42"}, {"action","shutdown"}});
    return 0;
}
```

---

## CMake (Beispiel)

```cmake
cmake_minimum_required(VERSION 3.16)
project(strategy_logger CXX)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(app
    src/main.cpp
    src/logger.hpp
    src/ilogger.hpp
    src/json_logger.hpp src/json_logger.cpp
    src/fmt_console_logger.hpp src/fmt_console_logger.cpp
)

# Include-Pfade (passen Sie an Ihr Layout an)
target_include_directories(app PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src)

# Abhängig von Ihrer Umgebung:
# target_link_libraries(app PRIVATE fmt::fmt)  # wenn fmt als Package verfügbar
# Bei nlohmann::json als Header-only reicht der Include-Pfad.
```

---

## Abnahmekriterien

- Austausch der Log-Strategie **zur Laufzeit** ohne Codeänderung im Anwendungskern (`Logger` nutzt nur `ILogger`).
- Korrekte Ausgabeformate (JSON pro Zeile; fmt-Ausgabe auf STDOUT).
- Ressourcen- und Ausnahme-sicherer Datei-Umgang im `JsonLogger`.
- Sinnvolle Timestamps & Levels.

---

## Bonus-Ideen

- **Konfiguration via JSON** (z. B. `{"logger":"json","path":"app.log.jsonl"}`) statt festem Wechsel in `main`.
- **Asynchrones Logging**: Queue + Worker-Thread (Achtung: Thread-Sicherheit, Flush).
- **Rotating File Logger** (Max-Größe in MB, Keep-Count).
- **Context-Adapter**: automatische Felder (Hostname, PID, Thread-ID).

Viel Spaß beim Strategien‑Tauschen! 🧩