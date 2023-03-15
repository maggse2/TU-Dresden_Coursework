/*
 * Praktikumsversuch: Einführung in die Sprache C
 * Grafikausgabe-Modul
 */

#include "gfx.h" 

// für vorgegebene Grafik Funktionen grafik_paint_point() und andere:
#include "graphic.h"
#include "engine.h"

// Funktionen zur Grafikausgabe (Leinwanderstellng)
void initCanvas(void){
//Initialisierung der Textur zur Bemalung (aus "gfx.h")
//rowlen: Spalten; rowcount: Zeilen
//Casting auf "double" Typ, da...
//die Spalten und Zeile um 2 dekrementiert, was aus dem benötigten Platz des zweidimensinalen C-Arrays resultiert (s. Aufgabe 3.1)
//Casting auf "unsigned" Typ, da...
	grafik_create_paint_area(0,((double) rowlen-2), 0,((double) rowcount-2),((unsigned) (rowlen-2)),((unsigned) (rowcount-2)));
//			     x_min, x_max,       y_min, y_max,	       x_points, y_pints
}
//vorgegebene Funktion aus "gfx.h" (Sperren der Zeichenfläche, Auszeichnen des aktuellen Mainfelds) 
void gfx_drawField(void){
//hierzu dürfen keine Änderungen an der Grafik mehr möglich sein
	grafik_lock_for_painting();
//Der Pointer von Cell zeigt auf die Adresse des Hauptfeldes
	Cell *mainfieldPtr=mainfield;
//Ermitteln der Größe des gesamten Arrays; alle ungewollten Positionen werden nicht gezeichnet.
	int arraySize=(rowlen*rowcount);
	for (int i=0;i<arraySize;i++){
//Die x-/y-Elemente^, auf welche gepointed wird, müssen größer Null und zugleich kleiner sein als die um eins dekrementierte Spalten- und Zeilenlänge 
		if((mainfieldPtr->x>0)&&(mainfieldPtr->y>0)&&((mainfieldPtr->x)<(rowlen-1))&&(mainfieldPtr->y<(rowcount-1))){
//Wenn ungewollte Positionen ausgeschlossen sind sowie der Pointer auf a gerichtet ist, soll schwarz gezeichnet werden (gem. x-/y-Wert)
			if(mainfieldPtr->a){grafik_paint_point(mainfieldPtr->x-1, mainfieldPtr->y-1, Black);}
//ansonsten soll weiß gezeichnet werden
			else{grafik_paint_point(mainfieldPtr->x-1, mainfieldPtr->y-1, White);}
		}
//Der Pointer soll auf die Adresse des nächsten Hauptfeldes zeigen
		mainfieldPtr++;
	}
//Abschluss des Vorgangs; Änderungen an der Grafik sind wieder möglich (aus "grafic.c") 
	grafik_unlock_and_show();
}
