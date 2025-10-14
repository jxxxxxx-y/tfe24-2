# Übungsaufgabe: Referenzen in C++ mit `fmt`

## Details

Datum: 14.10.2025
Link zu [Rapla](https://rapla-ravensburg.dhbw.de/rapla?page=calendar&user=Regulski&file=TFE24-2&day=7&month=10&year=2025&next=%3E%3E)

## Notwendige git Kommandos

```sh
git status
git branch -a
git switch main
# create a new local branch based on the origin main
git switch -c solution-001 origin/main
# perform changes
# ....
git add exercise-001
git commit -m "feat: add exercise number two"
# push the changes to the cloud
git push -u origin solution-001
....
```

**Lernziel:** Verständnis des Unterschieds zwischen Übergabe von Variablen als Parameter, Übergabe per Zeiger und Übergabe per Referenz.  
Alle Ausgaben erfolgen mit der [`fmt`](https://fmt.dev/)-Bibliothek.

---

## Teil 1: Grundlagen Referenzen

1. Legen Sie eine `int`-Variable `x` mit dem Wert `10` an.
2. Deklarieren Sie eine Referenz `r`, die auf `x` zeigt (`int& r = x;`).
3. Geben Sie den Wert von `x` und den Wert von `r` mit `fmt::print` aus.
4. Ändern Sie den Wert von `x` über die Referenz `r` (z. B. `r = 42;`).
5. Geben Sie erneut den Wert von `x` und `r` aus.

---

## Teil 2: Funktionen mit Referenzen

Definieren Sie zwei Funktionen:

1. `void changeValueByParameter(int value)`  
   - Nimmt eine `int`-Variable als Parameter entgegen.  
   - Ändert den Wert innerhalb der Funktion (z. B. `value = 99;`).  
   - Geben Sie innerhalb der Funktion den neuen Wert aus.  
   - Beobachten Sie, ob sich die ursprüngliche Variable im Hauptprogramm verändert.

2. `void changeValueByReference(int& ref)`  
   - Nimmt eine Referenz auf `int` als Parameter entgegen.  
   - Ändert den Wert innerhalb der Funktion (z. B. `ref = 77;`).  
   - Geben Sie innerhalb der Funktion den neuen Wert aus.  
   - Beobachten Sie die Auswirkungen auf die ursprüngliche Variable.

---

## Teil 3: Vergleich

1. Deklarieren Sie eine `int`-Variable `y = 5;`.
2. Rufen Sie `changeValueByParameter(y);` auf und geben Sie **vor und nach dem Funktionsaufruf** den Wert von `y` aus.
3. Rufen Sie `changeValueByReference(y);` auf und geben Sie **vor und nach dem Funktionsaufruf** den Wert von `y` aus.

---

## Zusatzaufgabe

- Vergleichen Sie die Referenz mit dem Zeiger, was sind die Unterschiede?
- Erstellen Sie Eine Klasse und deklarieren Sie eine Membervariable vom Typ Referenz, wie kann die Klasse nun erzeugt werden, warum ist das so?


> **Hinweis:**  
> - Bei der Übergabe einer Variable als **Parameter** wird eine Kopie übergeben – die Originalvariable bleibt unverändert.  
> - Bei der Übergabe als **Referenz** arbeiten Sie direkt auf der Originalvariable – Änderungen wirken sich sofort aus.  
