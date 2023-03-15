#ifndef CONFIG_HH
#define CONFIG_HH
#include<stdio.h>
#include<string.h>
#include<ctype.h>
#include<stdlib.h>
#include<stdio.h>
#include<string.h>
// Config Schnittstelle
int readConfig(void);
/*
 * Liest die Config-Datei ein und speichert alle vorgefundenen Definitionen in die passenden, globalen Variablen,
 * damit alle anderen module auf sie zugreifen können.
 * Die variablen sind standartmäßig auf die settings1 Datei initialisiert. Kommt ein Keyword nicht vor, behält seine variable diesen Wert.
 * Kommt das Wort animationspuffer nicht vor, wird dieser zufällig gefüllt.
 */
int Zeilen;
int Spalten;
int step;
int steps;
double pauseTime;
int *initBuffer(void);

/*
 * Initialisiert ein Buffer Array in der Größe des in der settings Datei definierten Spielfeldes.
 * Es besteht nur aus den intigern 0 und 1 für tot und lebendig.
 */
void initMainBuffer(void);
/*
 * Initialisiert einen main Buffer und einen preBuffer mit der initBuffer Methode
 * und speichert seinen Pointer auf
 * Modulebene, um von anderen functions verwendet werden zu können.
 * Die variable bufferRows zählt die eingelesenen Zeilen um den Buffer vertikal mittig
 * platzieren zu können.
 */
int*mainBuffer;
int*preBuffer;
int bufferRows;

void readBuffer(FILE *fPointer);
/*
 * Benötigt einen File-Pointer, welcher genau auf das buffer-Stück zeigt.
 * Das Herzstück des Buffer Einlesens. Die Zeile wird in ein array von char eingelesen,
 * in diesem werden zunächst die Validen Zeichen gezählt, um den pointer im preBuffer innerhalb
 * der Zeile auszumitteln. Mit jeder Zeileniteration wird bufferRows inkrementiert um Vertikal
 * auszumitteln. Das fertige Array ist im mainBuffer gespeichert und kann weiterverwendet werden.
 */
void randBuffer(void);
/*
 * Die randBuffer function wird immer dann ausgeführt, wenn die readBuffer function nicht
 * ausgeführt wurde.(erkennbar an den nicht initialisierten Buffer Arrays) Es wird immer der gesamte
 * Puffer gefüllt. Die chance auf eine lebende Zelle beträgt immer 30%
 * #################IF-ANWEISUNG NOCH IN NINAS ZEILEN SCHREIBEN!!!!!!###########
 */
#endif //CONFIG_HH
