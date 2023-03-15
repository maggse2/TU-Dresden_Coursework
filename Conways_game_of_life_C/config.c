/*
 * Praktikumsversuch: Einführung in die Sprache C
 * Konfigurationsdatei-Modul
 */

#include "config.h"

// für fopen, getline, fscanf, fclose:
#include <stdio.h>

// für strncmp und memset:
#include <string.h>

// für malloc, calloc und atoi:
#include <stdlib.h>
//für time()
#include <time.h>
	 
int readConfig()
{
    FILE* file = fopen("settings-1.txt", "r"); //opens read only file

    char line[256];
    char first[50];
    int number1 = 0;
    Zeilen = 100;
    Spalten = 100;
    step = 0;
    steps = 15;
    pauseTime = 0.1;



    //error message for when the file cannot be found
    if(file == NULL){
    perror("Failed: ");
             return -1;

    }

    //go thorugh the file line by line
    while (fgets(line, sizeof(line), file)) {


        printf("%s", line); //values read from file

        //copy strings by line and store to first
        memcpy(first, line, strlen(line)+1);
        sscanf(first, "%s %d", &first[0],&number1);

        //look for Zeilen
        if(!strcmp(first, "Zeilen:"))
        {
            memcpy(first, line, strlen(line)+1);

            char  *number1 = first;



            //look though the line character by character and give back only the numbers
            while (*number1) { // While there are more characters to process...

                //when it contains number
                if ( isdigit(*number1) ) {

                    // Found a number
                    int val = (int)strtol(number1,&number1, 10); // Read number

                    //store it
                    Zeilen= val-0;

                } else {
                // Otherwise, move on to the next character.
                    number1++;

                }
            }
        }

        //look for Schritte
        if(!strcmp(first, "Schritte:"))
        {
            memcpy(first, line, strlen(line)+1);
            char  *number1 = first;

            while (*number1) {

                if ( isdigit(*number1) ) {

                    int val = (int)strtol(number1,&number1, 10);
                    steps= val-0;

                } else {

                    number1++;
                }
            }
        }

        //look for Spalten
        if(!strcmp(first, "Spalten:"))
        {
            memcpy(first, line, strlen(line)+1);
            char  *number1 = first;

            while (*number1) {

                if ( isdigit(*number1) ) {

                    int val = (int)strtol(number1,&number1, 10);
                    Spalten= val-0;

                } else {

                    number1++;
                }
            }
        }

        //look for Schritt
        if(!strcmp(first, "Schritt:"))
        {
            memcpy(first, line, strlen(line)+1);
            char  *number1 = first;

            while (*number1) {

                if ( isdigit(*number1) ) {

                    int val = (int)strtol(number1,&number1, 10);
                    step = val-0;

                } else {

                    number1++;
                }
            }
        }

        //look for Pause
        if(!strcmp(first, "Pause:"))
        {
            memcpy(first, line, strlen(line)+1);
            char  *number1 = first;

            while (*number1) {

                if ( isdigit(*number1) ) {

                    double val = (double)strtod(number1,&number1);
                    pauseTime= val-0;

                } else {

                    number1++;
                }
            }
        }

        if(!strcmp(first,"Animations-Puffer:"))
        {
        	readBuffer(file);
        }


    }//while




    fclose(file);
    if(mainBuffer==NULL){ //if the Command Animations-Puffer was not found, the buffer is currently empty. We must fill it randomly then.
    	randBuffer();
    }
    return 0;

}



int *initBuffer(void){
	//size fits engine, easily portable
	int* bufferPtr= malloc(((abs(Zeilen)+2)*(abs(Spalten)+2)*sizeof(int)));


	if (bufferPtr==NULL){	//fuer diese OutOfMemory-Guard-implementierung Credit:Kris Jordan
		fprintf(stderr, "Kein Speicherplatz mehr verfügbar!");
		exit(EXIT_FAILURE);
	}

	for (int i=0; i<((abs(Zeilen)+2)*(abs(Spalten)+2)); i++){
		bufferPtr[i]=0;	//emulates calloc
	}

	return bufferPtr;
}




void initAllBuffers(void){
	if(mainBuffer==NULL) mainBuffer=initBuffer();

	if(preBuffer==NULL) preBuffer=initBuffer();

	bufferRows=0;
}



void readBuffer(FILE *fPointer){
	initAllBuffers();	//Puffer initialisieren

	int*prePtr=preBuffer;
	printf("Config: Reading Buffer from File");
	int counter;
	char x[1]={"x"};
	char dot[1]={"."};
	int nullFound; //WhileSchleife beenden, sobald das nullzeichen gefunden wurde.
	while(!nullFound){

		if (bufferRows==Zeilen){	//Schutz vor zu langem Buffer in der Datei
				fprintf(stderr, "Config: Buffer too long!");
				exit(EXIT_FAILURE);
		}
		counter=0; 		//Zählt die Zeichen in einer Reihe
		char* buffLine=calloc(abs(Spalten),abs(Spalten)*sizeof(char));
		if (buffLine==NULL){	//fuer diese OutOfMemory-Guard-implementierung Credit:Kris Jordan
				fprintf(stderr, "Kein Speicherplatz mehr verfügbar!");
				exit(EXIT_FAILURE);
		}
		fgets(buffLine, Spalten, fPointer);
		puts(buffLine);
		if(buffLine[0]==NULL)nullFound=1;
		char *buffLine2;
		//Valide inputs werden fürs ausmitteln gezählt
		for(int i=0;i<Spalten;i++){
			if(!strcmp(buffLine2,x))counter++;
			if(!strcmp(buffLine2,dot))counter++;
			buffLine2++;
		}
		printf("Erste forschleife geschafft!");
		buffLine2=buffLine;
		prePtr=prePtr+((Spalten+2)-counter)/2+1;//Ausmitteln innerhalb der Zeile; +1 für Randreihe
		for(int i=0;i<Spalten;i++){
			if(!strcmp(buffLine2,x)){
				*prePtr=1;
				prePtr++;
			}
			if(!strcmp(buffLine2,dot))prePtr++;
			//Die Schliefe ist geschützt gegen Fremdzeichen, arbeitet aber dennoch nur so viele
			//Zeichen ab, wie in eine Zeile stehen dürfen.
			buffLine2++;
		}
		printf("Zweite FForschleife geschafft!");
		bufferRows++;		//Zählen der insgesamt eingelesenen Reihen
		prePtr=preBuffer+((Spalten+2)*bufferRows);	//Shiften um die bereits eingelesenen Reihen
		free(buffLine);
		printf("iteration complete");
	}
	printf("While-Schleife fertig");
	//Nach fertigem einlesen muss noch vertikal ausgemittelt werden
	prePtr=preBuffer;
	int*mainPtr=mainBuffer;
	mainPtr=mainPtr+((Zeilen+2)-bufferRows)/2+1;//Analog zur Ausmittel-Rechenoperation innerhalb der Zeile
	for(int i=0;i<(bufferRows*(Spalten+2));i++){
		*mainPtr=*prePtr;
	}
	//Das Ausmitteln ist abgeschlossen und das Array kann ausgegeben werden!
}

void randBuffer(void){

	printf("Config: Filling the Buffer with randomly generated numbers.");

	srand(time(NULL));

	//buffers get initialized at function start
	initAllBuffers();

	int*mainPtr=mainBuffer;

	for(int i=0; i<(Zeilen+2)*(Spalten+2);i++){//also fills the frame
		if(rand()%10>6){*mainPtr=1;};//3in10 chance to spawn live cell

			mainPtr++;
	}
}
