/*
 * Praktikumsversuch: Einführung in die Sprache C
 * Nutzerinteraktions-Modul
 */

#include "ui.h"

// für vorgegebene UI Funktionen: grafik_user_input()
# include "graphic.h"

// für die Funktion `exit`
#include <stdlib.h>
int UserInput(void)
{
    char eingabe[2];                           		// Variablen werden deklariert
    char pausieren[2];
    char str1[2]= "q";
    char str2[2]= ".";
    char str3[2]= " ";
    int ret[5];

    fgets(eingabe,2,stdin); // Eingabe wird eingelesen
    ret[0] = strcmp(eingabe, str1);          		// Eingabe wird verglichen
    ret[1] = strcmp(eingabe, str2);
    ret[2] = strcmp(eingabe, str3);

    if (ret[0] == 0)                                          // prüfen ob q für beenden eingegeben wurde
     {
         printf("q wurde eingegeben: %s", eingabe);
         exit(0);                                       	 // Programm beenden
     }

    if(ret[1]== 0)                                            // prüfen ob ein Punkt eingegeben wurde
    {
        printf(". wurde eingegeben: %s", eingabe);
    }

    if(ret[2]== 0)                                            // prüfen ob ein Leerzeichen eingegeben wurde
    {
        printf("Leerzeichen wurde eingegeben: %s", eingabe);
        do                                                     // do-while Schleife zum Pausieren des Programms
               {                                                      //erst nach eingabe eines Leerzeichen wird das Programm fortgesetzt
                   fgets(pausieren,2,stdin);
                   ret[3] = strcmp(pausieren, str3);
                   ret[4] = strcmp(pausieren, str1);

                   if(ret[4]==0) {
                       exit(0);
                   }
               }
               while (ret[3]!= 0);
           }
           return 0;
       }

// Funktionen um Nutzerinteraktionen zu behandeln
