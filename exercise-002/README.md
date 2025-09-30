# Aufgabenstellung

## Notwendige git Kommandos

```sh
git status
git branch -a
git switch main
# create a new local branch based on the origin main
git switch -c solution-002 origin/main
# perform changes
# ....
git add exercise-002
git commit -m "feat: add exercise number two"
# push the changes to the cloud
git push -u origin solution-002
....
```

## Übungsaufgabe: Speichersegmente in C++

**Lernziel:** Verständnis der verschiedenen Speichersegmente (Stack, Heap, Data, Code) in einem C++-Programm.

---

### Teil 1: Globale Variablen (Data-Segment)

1. Deklarieren Sie eine **globale Variable** `int globalVar = 1;`.
2. Geben Sie im `main` den Wert und die Adresse von `globalVar` mit `fmt::print` aus.
3. Beobachten Sie: Globale Variablen liegen im **Data-Segment**.

---

### Teil 2: Lokale Variablen (Stack)

1. Deklarieren Sie im `main` eine lokale Variable `int localVar = 2;`.
2. Geben Sie den Wert und die Adresse von `localVar` mit `fmt::print` aus.
3. Beobachten Sie: Lokale Variablen werden auf dem **Stack** angelegt.

---

### Teil 3: Dynamisch allozierte Variablen (Heap)

1. Reservieren Sie mit `new` Speicher für eine einzelne `int`-Variable (`int* heapVar = new int(3);`).
2. Geben Sie den Wert und die Adresse von `heapVar` mit `fmt::print` aus.
3. Geben Sie den Speicher mit `delete` wieder frei.
4. Beobachten Sie: Dynamisch allozierte Variablen liegen im **Heap**.

---

### Teil 4: Funktionen (Code-Segment)

1. Definieren Sie eine Funktion `void foo() { fmt::print("Hello from foo!\\n"); }`.
2. Geben Sie im `main` mit `fmt::print("Adresse von foo: {}\\n", fmt::ptr(&foo));` die Adresse der Funktion aus.
3. Beobachten Sie: Funktionen liegen im **Code-Segment**.

---

### Zusatz

Schreiben Sie ein kurzes Fazit, in dem Sie erklären:

- Welche Art von Variablen wo gespeichert wird.
- Warum es wichtig ist, zwischen Stack und Heap zu unterscheiden.
- Welche Rolle Referenzen und Zeiger in diesem Zusammenhang spielen.
