# Übungsaufgabe: Klassen in C++ – `Point`

## Notwendige git Kommandos

```sh
git status
git branch -a
git switch main
# create a new local branch based on the origin main
git switch -c solution-004 origin/main
# perform changes
# ....
git add exercise-004
git commit -m "feat: add exercise number two"
# push the changes to the cloud
git push -u origin solution-004
....
```


**Lernziel:** Verständnis der Grundlagen von Klassen in C++:

- Attribute (Membervariablen)  
- Methoden (Memberfunktionen)  
- Konstruktoren  
- Nutzung der `fmt`-Bibliothek für Ausgaben  

---

## Aufgabe

Erstellen Sie eine Klasse `Point`, die einen Punkt im zweidimensionalen Raum beschreibt.

### Anforderungen

1. **Attribute:**
   - `int x`
   - `int y`

2. **Konstruktoren:**
   - Ein Konstruktor, der `x` und `y` initialisiert.
   - Ein Standardkonstruktor, der `x = 0` und `y = 0` setzt.

3. **Methoden:**
   - `void move(int dx, int dy)`  
     Verschiebt den Punkt um `dx` in x-Richtung und `dy` in y-Richtung.
   - `void print() const`  
     Gibt die Koordinaten mit `fmt::print` in der Form `(x, y)` aus.

---

## Beispiel

### Beispielnutzung im `main`

```cpp
int main() {
    Point p1(2, 3);     // Erzeugen eines Punktes (2, 3)
    p1.print();         // Ausgabe: (2, 3)

    p1.move(1, -1);     // Verschiebe um (1, -1)
    p1.print();         // Ausgabe: (3, 2)

    Point p2;           // Standardkonstruktor -> (0, 0)
    p2.print();         // Ausgabe: (0, 0)
}
```

---

## Zusatzaufgabe

Erweitern Sie die Klasse um eine Methode:

- `double distance_to(const Point& other) const`  
  Berechnet den euklidischen Abstand zwischen dem aktuellen Punkt und `other`.  

Formel:  

\[
\text{Abstand} = \sqrt{(x - other.x)^2 + (y - other.y)^2}
\]

Weitere Informationen finden Sie hier:  
[Wikipedia – Abstand zwischen zwei Punkten](https://de.wikipedia.org/wiki/Abstand_(Mathematik)#Abstand_zwischen_zwei_Punkten)