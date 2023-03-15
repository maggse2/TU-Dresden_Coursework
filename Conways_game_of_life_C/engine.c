/*
 * Praktikumsversuch: Einführung in die Sprache C
 * Berechnungs-Modul
 */

#include "engine.h"

// Engine Quellcode

void engine_loadConfig(void){
	rowlen=abs(Spalten)+2;
	rowcount=abs(Zeilen)+2;
	engine_initMainField();
	getConfigBuffer(mainBuffer);
}


Cell *cellGridMalloc(void){
	int cellCount=rowlen*rowcount;	//Datentyp size_t verwenden, vor negativen eingaben schützen
	Cell *cellGrid = malloc((cellCount*sizeof(Cell)));
	Cell *gridPtr = cellGrid;
	if (cellGrid==NULL){	//fuer diese OutOfMemory-Guard-implementierung Credit:Kris Jordan
		fprintf(stderr, "Kein Speicherplatz mehr verfügbar!");
		exit(EXIT_FAILURE);
	}
	//Jede Zelle erhält ihre Koordinaten
	for(int iy=0; iy<rowlen;iy++){
		for (int ix=0;ix<rowcount;ix++){
			gridPtr->x=ix;
			gridPtr->y=iy;
			gridPtr->a=0;
			gridPtr++;
		}
	}//Der nächste Schritt wäre, die Erstellung des structs auszulagern
	return cellGrid;
}


void engine_initMainField(void){
	if (mainfield==NULL){			//entwurfsmuster singleton
	mainfield=cellGridMalloc();
	printf("Engine: Mainfield initialisiert.\n");
	}
}

void getConfigBuffer(int *bufferLocation){
	Cell *cellPtr=mainfield;
	printf("Beginne Buffer-Reading \n");
	for (int i=0; i<rowlen*rowcount;i++){
		cellPtr->a=*bufferLocation;
		cellPtr++;
		bufferLocation++;
	}
	printf("Engine: Buffer-reading done. \n");
}



int countNeighbors(Cell *pointedCell){	//Zählen aller lebenden Zellen um p und anschließend subtrahieren von *p
	int c=0;
	Cell *p;
	/*Das Nachbarnzählen an sich ist leicht umzusetzen, indem man zwischen den Zeileniterationen
		 * dreimal die Spalte iteriert. (jeweils von -1 bis 1)
		 * Schwieriger wird es am Rand, da wir hier die weit äußeren zellen nicht betrachten wollen.
		 * Daher werden die variablen o, u, l, r eingeführt um die iteration in diesem fall zu begrenzen.
		 */
	int o,u,l,r;
	//Fall 1: oben; Pointerposition kleiner als Zeilenlänge
	if (pointedCell->y==0) o=0; else o=(-1);

	//Fall 2: unten; Wenn sich der pointer nach y+1 nicht mehr im Array befindet, ist er unten
	//(Pointer um 1 nach unten geshiftet)>(letzter im Array befindlicher Punkt)
	if ((pointedCell->y)==rowcount-1) u=1; else u=2;

	//Fall 3: links - a mod rowlen = 1
	if (pointedCell->x==0) l=0; else l=(-1);

	//Fall 4: rechts
	if(pointedCell->x==rowlen-1) r=1; else r=2;

	//Hier die eigentliche Nachbarnberechnung. Da pointedCell auf Cell gecastet ist, sind arithmetikbefehle ohne probleme möglich.
	for (int j=o; j<u; j++){
		for (int i=l; i<r; i++){
			p=pointedCell+(i+j*rowlen);
			c=c+(p->a);
		}
	}
	c=c-pointedCell->a; //Zelle selbst abziehen, da nur die nachbarn betrachtet werden.
	return c;
}


//Updaten der gerade gepointeten Zelle in Feld 2
void updateCell(Cell *oldCell, Cell *newCell){		//Geupdatete Zellen werden direkt in Feld 2 geladen.
	int a = countNeighbors(oldCell);
	if(oldCell->x==newCell->x){
		if(oldCell->y==newCell->y){
			switch(a){
				case 2: {newCell->a=oldCell->a;printf("0"); break;}	//Zelle bleibt im vorherigen Zustand
				case 3: {newCell->a=1; printf("x");break;} 	//Zelle wird belegt
				default: {newCell->a=0;printf(".");break;}			//Zelle stirbt
			}
		}
		else{fprintf(stderr, "Felder main und out sind nicht deckungsgleich!");
		exit(EXIT_FAILURE);
		}
	}
	else{fprintf(stderr, "Felder main und out sind nicht deckungsgleich!");
			exit(EXIT_FAILURE);
	}
}

//Jede Zelle in Feld 2 wird aus Feld 1 errechnet, danach wird Feld 1 überschrieben
Cell *engine_updateField(void){
	printf("Engine: Computing next iteration \n");
	free(outfield);
	outfield=cellGridMalloc();
	if(sizeof(outfield)!=sizeof(mainfield)){
		fprintf(stderr, "Felder main und out sind nicht gleichgroß!!");
		exit(EXIT_FAILURE);
	}
	Cell *pMain=mainfield;
	Cell *pOut=outfield;
	for (int i=0; i<(rowlen*rowcount);i++){
		if(i%rowlen==0)printf("\n");
		updateCell(pMain, pOut);

		pMain++;
		pOut++;
	}
	memcpy(mainfield, outfield, sizeof(Cell)*rowlen*rowcount);
	printf("\n Engine: Next iteration complete and saved. \n");
	return outfield;
}
void freeMemory(void){
	free(outfield);
	free(mainfield);
	free(preBuffer);
	free(mainBuffer);
}
/*
void mainFieldToTerminal(void){
	Cell *mfPtr=mainfield;
	for(int j=0;j<rowcount;j++){
		for(int i=0;i<rowlen;i++){
			int x=mfPtr->x;
			int y=mfPtr->y;
			int a=mfPtr->a;
			printf("Zelle %d \n",(j*rowlen+i));
			printf("X: %d ;",x);
			printf("Y: %d ;",y);
			printf("A: %d \n",a);
			mfPtr++;
		}
	}
}
*/
void mainFieldToTerminal2(void){
	printf("\nDas gespeicherte Feld ist:\n");
	Cell *mfPtr=mainfield;
	for(int j=0;j<rowcount;j++){
		for(int i=0;i<rowlen;i++){
			int a=mfPtr->a;
			if(1==a){
				printf("X");
			}
			else printf("O");
			mfPtr++;
		}
		printf("\n");
	}
}
