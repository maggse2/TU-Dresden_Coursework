#ifndef ENGINE_HH
#define ENGINE_HH

// Engine Schnittstelle
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "config.h"

typedef struct Cell{
	int x;	//x-Wert der Zelle (Im +2 Raster)
	int y;	//y-Wert der Zelle (Im +2 Raster)
	int a;	//Lebensstatus der Zelle, a enthält [0;1]
} Cell;


Cell *cellGridMalloc(void);
/*
 * Erzeugt ein dynamisches Array von integern im Heap via malloc()
 * Das Array wird initialisiert auf ein Spielfeld mit ausschließlich toten Zellen
 * Dabei wird durch die integer 1 und 0 der Datentyp boolean emuliert.
 * Sowohl schutz gegen negative int, als auch OutOfMemory
 */

void engine_loadConfig(void);
/*
 * Holt die geforderte Zeilen- und Spaltenlänge aus der Config, diese werden um 2 inkrementiert und im header deklariert,
 * da mehrere Methode auf diese zugriff benötigen. Das mainfield wird initialisiert.
 * Danach wird der Buffer aus der Config-Datei gelesen und in das Zellensystem konvertiert.
 *
 */
int rowlen;	//Zeilenlänge incl. Rand
int rowcount;	//Zeilenanzahl incl. Rand

void getConfigBuffer(int *bufferAdress);
/*
 * Konvertiert den Buffer aus integern in das Zellensystem und Speichert alles ins mainfield.
 */

void engine_initMainField(void);
/*
 * Erstellt das Hauptspielfeld, wenn nicht vorhanden und speichert seinen Startpointer.
 * Das Hauptspielfeld hat eine feste Adresse und wird nur durch memcpy() manipuliert.
 * vgl. Entwurfsmuster Singleton in Java
 */
Cell *mainfield;//Adresse des Hauptfeldes


int countNeighbors(Cell *pointedCell);
/*
 * Zählt die Nachbarn um eine Zelle, wobei bei Randzellen alles außerhalb des Arrays als tot angesehen wird.
 */

void updateCell(Cell *oldCell, Cell *newCell);
/*
 * Überprüft, ob die Zellen deckungsgleich in den Koordinatensystemen ihrer Felder liegen.
 * Im alten feld werden die nachbarn überprüft und die nächste iteration berechnet.
 * Danach wird die neue Zelle in ihrem Feld geupdatet.
 */

Cell *engine_updateField(void);
/*
 * Löscht zunächst das letzte outputfield
 * Errechnet den nächsten Iterationsschritt des mainfield und speichert ihn ins outfield,
 * überschreibt danach das mainfield mit dem outfield
 */
Cell *outfield;

void freeMemory(void);
/*
 * Ausführen vor Programmende. Gibt den Speicher der Felder wieder frei.
 */
//Debugging-Methoden
//void mainFieldToTerminal(void);
void mainFieldToTerminal2(void);
#endif //ENGINE_HH
