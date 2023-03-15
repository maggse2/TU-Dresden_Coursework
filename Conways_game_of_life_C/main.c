/* BOF MAIN_C
 Praktikumsversuch: Einführung in die Sprache C
 Haupt-Programm
 */

#include "graphic.h"
#include "config.h"
#include "engine.h"
#include "gfx.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

// Forwarddeklaration der später definierten Hilfsfunktionen:
void goodbye_msg(void);
static void init_exit(void);


/* Demonstration zur Nutzung der vorgegebenen Grafikfunktionen */
void farb_demonstration(void)
{
	int dialog_showed =0;
	
	// Erzeuge eine virtuelle Leinwand.
	// (Anmerkung: willkürliche Dimmensionen zum Zweck der Demonstration)
	// auf der X-Achse von 0 bis 100 (rationaler Zahlenbereich)
	// auf der Y-Achse von 0 bis 64  (rationaler Zahlenbereich)
	// skaliere alle diese Koordinaten auf eine Fläche von 75 x 32 Pixel
        grafik_create_paint_area(0, 100, 0, 64, 75, 32);
	//
	// Sinnvoll für den Animations Praktikumsversuch:
	// grafik_create_paint_area(0, x_max, 0, y_max, x_max, y_max);
	
	while (1){
		
		// Der Bildschirm muss zum Setzen von Pixeln gesperrt sein.
		grafik_lock_for_painting();

		// Zeichne jeweils eine Linie in einer eigenen Farbe.
		int cn=0;
		for(int j=0; j < 64; j=j+2){                    // Zeile (y)
			cn= (j / 2) % 32;                       // Farbe auswählen
			for(int i=0; i < 100 ; i=i+1){          // Spalte (x)
				grafik_paint_point(i, j, cn);   // Pixel zeichnen
			}
		}

		// Alle Änderungen auf dem Bildschirm ausgeben.
		grafik_unlock_and_show();

		
		// Blockierender Dialog, einmalig anzeigen.
		// Solange der Dialog angezeigt wird, wird die Grafik nicht neu gezeichnet.
		if(dialog_showed == 0) {
			SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_INFORMATION,
						 "MRT 1 - V3 - Information",
						 "MRT 1 - V3 - Farbdemonstration\n\n"
						 "Nach dem Schließen dieses Dialogs,\n"
						 "kann die Taste 'q' verwendet werden "
						 "um das Programm zu beenden.\n",
						 NULL);
			dialog_showed = 1;

			// Alle bisherigen Tastatureingaben verwerfen.
			while (grafik_user_input(10) > Fehler);
		}

		
		// Getätigte Nutzereingaben verarbeiten.
		// 100 Millisekunden auf Nutzereingabe warten,
		// dann mit Programmablauf fortfahren.
		switch( grafik_user_input(100) ){
		case Beenden:
			// Auf die Taste `q` und "Fenster schließen" reagieren.
			return;
		case Pause:
		case Schritt:
		default:
			// Alle anderen Nutzeraktionen ignorieren.
			continue;
		}
	} // Ende while(1)
}


/* Hauptprogramm, Einstiegspunkt für eigene Programmierlösung.
 * Kommentarzeichen vor Funktionsaufrufen entfernen und
 * Programmrahmen ausfüllen.
 */
int main (void)
{
	/* registireren einer Hilfsfunktion, welche bei jedem Programmende einen Text ausgibt. */
        init_exit();
	
        /* Initialisierung des Grafikausgabefensters
	 Hinweis: das Fenster ist immer 800x600 Pixel groß */
     grafik_init_window();


	readConfig();		//Config lesen im configmodul
	engine_loadConfig();
	engine_initMainField();
	initCanvas();
	printf("Initialisierung Komplett");
	
	for(int i=step;i<steps;i++){
		engine_updateField();
		gfx_drawField();
		mainFieldToTerminal2();
		sleep((pauseTime/1000));
		

switch (grafik_user_input(100))
    {
        case Beenden:
            UserInput1();
            break;
        case Pause:
            UserInput2() ;
            break;
        case Schritt:
		
	engine_updateField();
	gfx_drawField();
	mainFieldToTerminal2();
	UserInput3();
            
	    break;
        default:
            break;

    }

	}

         /* Aufräumen und Freigeben der benutzten Grafikressourcen */
        grafik_close_window();
        
        return 0;
}


// -- Hilfsfunktionen ---
static void init_exit(void)
{
        if(atexit(goodbye_msg)){
                fprintf(stderr, "Fehler bei Registrierung der Exitfunktion\n");
                exit(-1);
        }
}

void goodbye_msg(void)
{
        printf("MRT1, V3, Programm beendet.\n");
}

/* EOF MAIN_C */
