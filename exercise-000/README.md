# Übungsaufgabe: Zeiger in C++ mit `fmt`


## Notwendige git Kommandos

```sh
git status
git branch -a
git switch main
# create a new local branch based on the origin main
git switch -c solution-000 origin/main
# perform changes
git add exercise-000
git commit -m "feat: add exercise number two"
# push the changes to the cloud
git push -u origin solution-000
....
```


**Lernziel:** Wiederholung und Festigung des Verständnisses von Zeigern in C++ sowie Einführung in die Verwendung der [`fmt`](https://fmt.dev/)-Bibliothek zur Ausgabe.

---

## Teil 1: Zeiger-Grundlagen

1. Legen Sie eine `int`-Variable `x` mit dem Wert `10` an.
2. Deklarieren Sie einen Zeiger `p`, der auf `x` zeigt.
3. Geben Sie mit `fmt::print` den Wert von `x` und die Adresse von `x` aus.  
   → Tipp: Mit `fmt::ptr(&x)` können Sie eine Adresse im Pointer-Format ausgeben.
4. Geben Sie den Wert aus, auf den der Zeiger `p` zeigt, sowie die Adresse, die in `p` gespeichert ist.
5. Ändern Sie den Wert von `x` über den Zeiger `p` auf `42`.
6. Geben Sie erneut den Wert von `x` und den Wert aus, auf den `p` zeigt.

---

## Teil 2: Dynamische Speicherverwaltung

1. Deklarieren Sie einen Zeiger auf `double`.
2. Reservieren Sie mit `new` Speicher für genau einen `double`-Wert und initialisieren Sie ihn mit `3.1415`.
3. Geben Sie Wert und Adresse mit `fmt::print` aus.
4. Geben Sie den Speicher anschließend wieder mit `delete` frei.

> **Merke:** Jeder mit `new` reservierte Speicher muss mit `delete` wieder freigegeben werden, sonst entsteht ein **Memory Leak**.

### Beispiel (Ausschnitt)

```cpp
double* d = new double(3.1415);   // Speicher im Heap reservieren
fmt::print("Wert: {}\n", *d);     // Zugriff über Dereferenzierung
fmt::print("Adresse: {}\n", fmt::ptr(d));

delete d;                         // Speicher wieder freigeben
```

---

## Teil 3: Funktionen mit Zeigern

Definieren Sie zwei Funktionen:

1. `void changeValueByParameter(int value)`  
   - Nimmt eine `int`-Variable als **Parameter** entgegen.  
   - Ändert den Wert innerhalb der Funktion (z. B. `value = 99;`).  
   - Geben Sie innerhalb der Funktion den neuen Wert aus.  
   - Beobachten Sie, ob sich die ursprüngliche Variable im Hauptprogramm verändert.

2. `void changeValueByPointer(int* ptr)`  
   - Nimmt einen Zeiger auf `int` als Parameter entgegen.  
   - Ändert den Wert, auf den der Zeiger zeigt (z. B. `*ptr = 77;`).  
   - Geben Sie innerhalb der Funktion den neuen Wert aus.  
   - Beobachten Sie die Auswirkungen auf die ursprüngliche Variable.

### Aufgabe

1. Deklarieren Sie eine `int`-Variable `y = 5;`.
2. Rufen Sie `changeValueByParameter(y);` auf und geben Sie **vor und nach dem Funktionsaufruf** den Wert von `y` aus.
3. Rufen Sie `changeValueByPointer(&y);` auf und geben Sie **vor und nach dem Funktionsaufruf** den Wert von `y` aus.

> **Hinweis:** So erkennen Sie den Unterschied zwischen Übergabe einer Variable als Parameter (keine Änderung der Originalvariable) und Übergabe eines Zeigers (die Originalvariable wird verändert).