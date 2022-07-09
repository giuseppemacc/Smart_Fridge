/*
gestione_ricette.h:

	ricerca_ricetta
	ricerca_ricettaSottstr
	richiediRicetta

	ordinaFileRicette_AZ
	print_ricette
	caricaRicette

	modificaRicetta
	sovrascrivi_ricetta

	isAlimento_compatibile
	isPreparabile
	isContained
	ricettePreparabili
	ricetteCompatibili

	shift_arrRicette_4cat
	ordina_arrRicette_4giorni
	prioritarizza_ricette

	fattiConsigliare   // consigliaRicette
	preparaRicetta

	valutaRicetta
	printStatistica_voti

*/




#ifndef GESTIONE_RICETTE_H_
#define GESTIONE_RICETTE_H_

#include "types.h"
#include <stdio.h>


int ricerca_ricetta(char* nome, t_ricetta* ricetta, FILE* file_ricette);

void ricerca_ricettaSottstr(char *nome, t_ricetta ricette[], int* n_ricette, FILE *file_ricette);

t_ricetta richiediRicetta(int* flag_home);



void print_ricette(int ordina_file, char* filename_ricette);

void ordinaFileRicette_AZ(char *file_name);

void caricaRicette();




t_ricetta modificaRicetta(t_ricetta ricetta, int* flag_home);

void sovrascrivi_ricetta(char* nome_ricetta, t_ricetta ricetta_modificata);




int isAlimento_compatibile(t_alimento alimento1, t_alimento alimento2, int ignora_quantita);

int isPreparabile(t_ricetta ricetta, char* filename_alimenti );

int isContained(t_alimento alimenti1[], t_alimento alimenti2[], int n_alimenti1, int n_alimenti2);

void ricettePreparabili( t_ricetta ricette_preparabili[], int* n_ricette_preparabili, char* filename_ricette);

void ricetteCompatibili( t_alimento alimenti[], int n_alimenti, t_ricetta ricette_compatibili[], int* n_ricette_compatibili, char* filename_ricette);




void ordina_arrRicette_4giorni(t_ricetta ricette[], int n_ricette);

void shift_arrRicette_4cat(t_ricetta ricette[], int n_ricette, t_categoria cat);

void prioritarizza_ricette( t_ricetta ricette[], int n_ricette );


void consigliaRicette();

void preparaRicetta(t_ricetta ricetta);




void valutaRicetta(char* nome_ricetta, int* flag_home);

void printStatistica_voti();





#endif /* GESTIONE_RICETTE_H_ */
