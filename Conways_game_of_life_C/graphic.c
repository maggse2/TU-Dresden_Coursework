/* BOF GRAPHIC_C
 * Praktikumsversuch: Einführung in die Sprache C
 * Programm-Modul "Grafische Darstellung"
 *
 * vorgegebene Funktionalität zur Erleichterung der Grafikausgabe.
 *
 */

#include "graphic.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>

/** interne Definitionen.
 * static ⇒ alle Variablen nur in diesem Modul sichbar
 */

// Fenstergröße
static const int WIN_WIDTH=800;
static const int WIN_HEIGHT=600;

// Grafikausgabe SDL-Ressourcen
static SDL_Window *win = NULL;
static SDL_Renderer *renderer = NULL;
static SDL_Texture *texture = NULL;

// Anzahl vorgegebener Farbwerte
#define NUM_COLORS 32

/** Zuordnungstabelle Farb-Namen ⇒ RGB-Wert.
 Quelle der Namen und Farbwerte:
 http://pixeljoint.com/forum/forum_posts.asp?TID=16247 
 */
static const unsigned char rgb_vals[NUM_COLORS][3] = {
        { /*Black*/                0,       0,       0 },
        { /*Valhalla*/            34,      32,      52 },
        { /*Loulou*/              69,      40,      60 },
        { /*Oiled Cedar*/        102,      57,      49 },
        { /*Rope*/               143,      86,      59 },
        { /*Tahiti Gold*/        223,     113,      38 },
        { /*Twine*/              217,     160,     102 },
        { /*Pancho*/             238,     195,     154 },
        { /*Golden Fizz*/        251,     242,      54 },
        { /*Atlantis*/           153,     229,      80 },
        { /*Christi*/            106,     190,      48 },
        { /*Elf Green*/           55,     148,     110 },
        { /*Dell*/                75,     105,      47 },
        { /*Verdigris*/           82,      75,      36 },
        { /*Opal*/                50,      60,      57 },
        { /*Deep Koamaru*/        63,      63,     116 },
        { /*Venice Blue*/         48,      96,     130 },
        { /*Royal Blue*/          91,     110,     225 },
        { /*Cornflower*/          99,     155,     255 },
        { /*Viking*/              95,     205,     228 },
        { /*Light Steel Blue*/   203,     219,     252 },
        { /*White*/              255,     255,     255 },
        { /*Heather*/            155,     173,     183 },
        { /*Topaz*/              132,     126,     135 },
        { /*Dim Gray*/           105,     106,     106 },
        { /*Smokey Ash*/          89,      86,      82 },
        { /*Clairvoyant*/        118,      66,     138 },
        { /*Brown*/              172,      50,      50 },
        { /*Mandy*/              217,      87,      99 },
        { /*Plum*/               215,     123,     186 },
        { /*Rainforest*/         143,     151,      74 },
        { /*Stinger*/            138,     111,      48 }
};

static double xmin, ymin, deltax, deltay;
static double xres, yres;

/** Grafikausgabe initialisieren.
*/
void grafik_init_window(void)
{
        if(SDL_Init(SDL_INIT_VIDEO) < 0){
                fprintf(stderr, "%s: SDL_Init failed: %s\n",
                        __FUNCTION__,
                        SDL_GetError());
                exit(-1);
        }
        
        if(atexit(grafik_close_window)){
                fprintf(stderr,
                        "%s: Fehler bei Registrierung der Exitfunktion\n",
                        __FUNCTION__);
                exit(-1);
        }
        
        win = SDL_CreateWindow("MRT1-V3-Grafik",
                               SDL_WINDOWPOS_UNDEFINED,
                               SDL_WINDOWPOS_UNDEFINED,
                               WIN_WIDTH,
                               WIN_HEIGHT,
                               0);
        if(!win){
                fprintf(stderr, "%s: SDL_CreateWindow failed: %s",
                        __FUNCTION__,
                        SDL_GetError());
                exit(-1);
        }
        
        renderer = SDL_CreateRenderer(win, -1, SDL_RENDERER_TARGETTEXTURE);
        if(!renderer){
                fprintf(stderr, "%s: SDL_CreateRenderer failed: %s",
                        __FUNCTION__,
                        SDL_GetError());
                exit(-1);
        }

}

// initialisiere die Textur zum bemalen
void grafik_create_paint_area(const double x_min, const double x_max,
                     const double y_min, const double y_max,
                     const unsigned x_points, const unsigned y_points)
{
        if(!renderer){
                fprintf(stderr, "%s: Renderer not initialized",
                        __FUNCTION__);
                return;
        }
        
        if(texture)
                SDL_DestroyTexture(texture);
        
        texture = SDL_CreateTexture(renderer,
                                    SDL_PIXELFORMAT_RGB888,
                                    SDL_TEXTUREACCESS_TARGET,
                                    x_points,
                                    y_points);
        if(!texture){
                fprintf(stderr, "%s: SDL_CreateTexture failed: %s",
                        __FUNCTION__,
                        SDL_GetError());
                exit(-1);
        }

        SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");
        SDL_RenderSetLogicalSize(renderer, WIN_WIDTH, WIN_HEIGHT);
        
        SDL_SetRenderTarget(renderer, texture);
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
        SDL_RenderClear(renderer);
        SDL_SetRenderTarget(renderer, NULL);
        SDL_RenderCopy(renderer, texture, NULL, NULL);
        SDL_RenderPresent(renderer);
        
        xmin = x_min;
        ymin = y_min;
        xres = x_points;
        yres = y_points;
        deltax = x_max - x_min;
        deltay = y_max - y_min;
}



/** einzelnen Farbpunkt setzen.
 */
int grafik_paint_point(double x, double y,
                       color_name_t colorname)
{
        Uint32 xp;
        Uint32 yp;
        xp = round(((x - xmin) / deltax) * xres);
        yp = round(((y - ymin) / deltay) * yres);
        
        if ((colorname < 0) || (colorname >= NUM_COLORS)){
                printf("color reset");
                colorname = 6;
        }        

        if(!texture){
                fprintf(stderr, "%s: Texture not initialized.",
                        __FUNCTION__);
                return 0;
        }

        SDL_SetRenderDrawColor(renderer,
                               rgb_vals[colorname][0],
                               rgb_vals[colorname][1],
                               rgb_vals[colorname][2],
                               255 /*opaque*/);
        SDL_RenderDrawPoint(renderer, xp, yp);
        
        return 1;
}


/** Ausgabefenster sperren um zu zeichnen.
*/
void grafik_lock_for_painting(void)
{
        if(!renderer || !texture){
                fprintf(stderr, "%s: Grafik not initialized.",
                        __FUNCTION__);
                return;
        }
        SDL_SetRenderTarget(renderer, texture);
}


/** Ausgabefenster entsperren und gepufferte Daten ausgeben.
*/
void grafik_unlock_and_show(void)
{
        if(!renderer || !texture){
                fprintf(stderr, "%s: Grafik not initialized.",
                        __FUNCTION__);
                return;
        }
        
        SDL_SetRenderTarget(renderer, NULL);
        SDL_RenderCopy(renderer, texture, NULL, NULL);
        SDL_RenderPresent(renderer);
}


/** Grafikfenster schließen und aufräumen.
*/
void grafik_close_window(void) {
        if(texture)
                SDL_DestroyTexture(texture);
        texture=NULL;
        
        if(renderer)
                SDL_DestroyRenderer(renderer);
        renderer=NULL;
        if(win)
                SDL_DestroyWindow(win);
        win=NULL;
        SDL_Quit();
}

/** warte eine definierte Zeit auf gewünschte Nutzereingaben.
 * https://wiki.libsdl.org/SDL_Event
 * https://wiki.libsdl.org/SDL_WindowEvent
 * https://www.libsdl.org/release/SDL-1.2.15/docs/html/sdlkey.html
*/
user_input_t grafik_user_input(int timeout)
{
	struct timespec start, current;
	SDL_Event event;
	clock_gettime(CLOCK_MONOTONIC_RAW, &start);
	SDL_ClearError();
	
	while(timeout >= 0){
		
		if(SDL_WaitEventTimeout(&event, timeout)){
			switch(event.type){
			case SDL_QUIT:
				return Beenden;
			case SDL_KEYDOWN:
				switch(event.key.keysym.sym){
				case SDLK_SPACE:
					return Pause;
				case SDLK_PERIOD:
					return Schritt;
				case SDLK_q:
					return Beenden;
				}
			default: //alle anderen Envents ignorieren
				#ifdef DEBUG
				fprintf(stderr, "%s: Ignorierter Event Typ %i\n",
					__FUNCTION__, event.type);
				#endif //DEBUG
				break;
			}
		} else {
			const char * const error = SDL_GetError();
			if(strlen(error)){
				fprintf(stderr, "%s: SDL_WaitEvent Fehler: %s\n",
					__FUNCTION__, error);
				return Fehler;
			}
		}

		if(timeout != 0){ //Spezialfall: "unendlich warten" beachten
			// kein Spezialfall, wir müssen dafür sorgen, dass
			// wir (ziemlich) genau die geforderte Zeit warten,
			// wenn kein erwünschter Event eingeht
			clock_gettime(CLOCK_MONOTONIC_RAW, &current);
			timeout = timeout - ((current.tv_sec - start.tv_sec) * 1000 +
					     ((current.tv_nsec - start.tv_nsec) / (1000 * 1000)));
			start = current;
			if(timeout == 0) // Spezialfall darf nicht auftreten
				break;
		}
	}
		
	return Nichts;
}

/* EOF GRAFIC_C */
