# Slush-YV-fikation
HF Seminarweek for die machine "Tech-tonic Tab"

## Hardwarekomponenten
This project needs:
- Lego Mindstorm Ev3 Education kit
- PET-Bottles
- Silicon tube
- a cup or a glass

## Getting Started

- down
- Laden Sie die Datei Main.cpp from repository herunter.
- Verbinden Sie Ihren Microbit mit ihrem Computer (Bluetooth oder Kabel möglich)
- Laden Sie den heruntergeladenen Code auf Ihren Microbit.

## Auslesen des 5x5 Pixelfeldes
auf dem 5x5 Pixelfeld des Microbits werden die zahlen wie folgt angezeigt.
- in der obersten Reihe werden die Zehnerstunden angezeigt.
- in der zweit obersten Reihe werden die Einerstunden angezeigt.
- die Mittlere Reihe ist die abtrennung von Stunden und Minuten.
- in der zweit untersten Reihe werden die Zehnerminuten angezeigt.
- in der untersten Reihe werden die Einerminuten angezeigt.

## Menüauswahl
Um zur Menüauswahl zu gelangen drücke beide Knöpfe (Knopf A und Knopf B), bis der Text "Menu" auf dem 5x5 LED Feld erscheint.
Mit dem ersten Menü wählt man zwischen Uhrzeit einstellen (Menu "0") oder Wecker einstellen (Menu "1").
Anschliessend wird auf dem 5x5 LED Feld angezeigt, was eingestellt wird (z.B. H = Stunden oder M = Minuten). Wenn man die Zeit (Uhrzeit oder Weckzeit) fertig eingestellt hat, wird automatisch wieder zur Zeitanzeige gewechselt.

## Navigantion durch das Menü
Die Navigation durch alle Menüs sind einheitlich. drücke Knopf B um den aktuellen Menüpunkt zu bestätigen und drücke Knopf A um Aktion auszuführen (wechsel zu einem anderen Menüpunkt oder eine Zahl um 1 zu erhöhen). 

### Der Wecker 
Der Wecker ertönt eine Minute lang zur gewählten Uhrzeit.

### Anzeige der Zahlen beim einstellen
Man muss nicht zwingend jedes Mal warten bis die Zahl verschwunden ist, um die Zeit weiter einstellen zu können. Die letzte gesehene Zahl ist die aktuelle Wert.

# Beispiel

Man möchte die Uhrzeit neu einstellen.
- Knopf A und B gleichzeitig drücken bis auf dem 5x5 Feld das Wort "Menu" erscheint.
- Menüpunkt "0" auswählen und mit Knopf B bestätigen.
- Den Kopf A soviel mal drücken bis gewünschte Zahl (in diesem Fall Stunden) anzeigt und mit Knopf B bestätigen => Stunden sind nun eingstellt.
- Den Kopf A soviel mal drücken bis gewünschte Zahl (in diesem Fall Minuten) anzeigt und mit Knopf B bestätigen => Minuten sind nun eingstellt.
Nun wird die eingestellte Uhrzeit auf dem Display und auf dem 5x5 Feld angezeigt.
