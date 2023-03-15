/* BOF GRAPHIC_H
 Praktikumsversuch: Einführung in die Sprache C
 Programm-Modul "Grafische Darstellung"
 */

#ifndef GRAFIK__H
#define GRAFIK__H

/** dieses Programmmodul benutzt die Grafikbibliothek `libSDL2`
 * Homepage: https://www.libsdl.org
 *
 * zum Installieren der benötigten Dateien innerhalb der MRT-VM,
 * folgenden Kommandozeilenbefehl nutzen:
  sudo apt-get install libsdl2-dev
 */
#include <SDL2/SDL.h>

/** limits.h definiert Eigenschaften verschiedener Datentypen
*/
#include <limits.h>

/*--- Typdefinitionen ------------------------------------------------------*/

/** Farbnamen der 32 vorgegebenen Farben
 */
typedef enum { Black = 0,
               Valhalla,
               Loulou,
               Oiled_Cedar,
               Rope,
               Tahiti_Gold,
               Twine,
               Pancho,
               Golden_Fizz,
               Atlantis,
               Christi,
               Elf_Green,
               Dell,
               Verdigris,
               Opal,
               Deep_Koamaru,
               Venice_Blue,
               Royal_Blue,
               Cornflower,
               Viking,
               Light_Steel_Blu,
               White,
               Heather,
               Topaz,
               Dim_Gray,
               Smokey_Ash,
               Clairvoyant,
               Brown,
               Mandy,
               Plum,
               Rainforest,
               Stinger
} color_name_t;

typedef enum {
	Nichts = 0, // keine relevante Nutzereingabe
	Fehler,     // SDL-Problem
	Beenden,    // Fenster schließen oder Taste `q`
	Pause,      // Leertaste
	Schritt,    // Punkt-Taste `.`
} user_input_t;
	
	
/*--------------------------------------------------------------------------*/
/*    Funktionen                                                            */
/*--------------------------------------------------------------------------*/

/*--- Grafik initialisieren und schließen ----------------------------------*/

/** Initialisiere das Grafikfenster zum Start des Programms.
 */
void grafik_init_window(void);

/** Schließe das Grafikfenster und beende SDL.
 * wird auch im Fehlerfall ausgeführt.
 */
void grafik_close_window(void);

/** erzeugt neuen Speicherbereich zum Zeichnen.
 * entfernt den alten Speicherbereich aus dem RAM vor dem Neuanlegen
 * Benutze diese Funktion um die Auflösung oder die Bereichsgrenzen zu ändern
 * skaliert automatisch delta(x_max-x_min) auf die Pixelanzahl x_points und
 * skaliert automatisch delta(y_max-y_min) auf die Pixelanzahl y_points
 * Dieses komplexe Interface ist nützlich um die `cosinus`-Funktion zu zeichnen.
 */
void grafik_create_paint_area(const double x_min, const double x_max,
			      const double y_min, const double y_max,
			      const unsigned x_points, const unsigned y_points);


/*--- Ausgabefenster sperren und entsperren --------------------------------*/

/** Ausgabefenster sperren um zu zeichnen.
*/
void grafik_lock_for_painting();

/** Ausgabefenster entsperren und gepufferte Daten ausgeben.
*/
void grafik_unlock_and_show();

/*--- Zeichenfunktionen ----------------------------------------------------*/

/** setze einen einzelnen Grafikpunkt.
 * an den Koordinaten der Berechnung, 
 * die Umrechnung in Bildschirmpixel erfolgt automatisch.
 * Angebe des Farbwertes mittels der oben definierten Farbnamen.
 */
int grafik_paint_point(double x, double y,
                       color_name_t colorname);


/*--- Hilfsfunktionen ------------------------------------------------------*/
/** Wartet auf eine Nutzereingabe für `timeout` Millisekunden.
 * Wartet auf Nutzereingaben, wie Fenster schließen und Tasten: `q`, `Leertaste`und `.`.
 * Liefert die Art der erkannten Nutzereingabe zurück, sobald der Nutzer diese eingegeben hat
 * wenn keine, oder keine der gewünschten Nutzereingaben erfolgen, wird gewartet bis timeout Millisekunden verstrichen sind
 * Nutzereingaben, und System-Ereignisse welche nicht gebraucht werden, werden entfernt und ignoriert
 * ein timeout-Wert von `0` wartet unendlich, bis einer der gewünschter Nutzereingaben eintrifft
*/
user_input_t grafik_user_input(int timeout);

/*--- Demonstration für den Einstieg in die Praktikumsaufgabe --------------*/

// Demonstrationsfunktion, bitte nicht im eigenen Projekt verwenden.
void farb_demonstration(void);

#endif /* GRAFIK__H */
/* EOF GRAFIK__H */
