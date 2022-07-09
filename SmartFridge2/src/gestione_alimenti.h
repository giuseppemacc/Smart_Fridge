/*
gestione_alimenti.h:

	ricerca_alimento
	ricerca_alimentoSottstr
	richiediAlimento

	ordinaFileAlimenti_AZ
	print_alimenti
	caricaAlimenti

	modificaAlimento
	sovrascrivi_alimento


*/

#ifndef GESTIONE_ALIMENTI_H_
#define GESTIONE_ALIMENTI_H_

#include "types.h"
#include <stdio.h>



void ricerca_alimentoSottstr(char *nome, t_alimento alimenti[], int* n_alimenti, FILE *file_alimenti);

int ricerca_alimento(char* nome, t_alimento* alimento, FILE* file_alimenti);

t_alimento richiediAlimento(int* flag_home);



//ORDINAMENTO FILE ALIMENTI IN ORDINE ALFABETICO(A-Z)
void ordinaFileAlimenti_AZ(char *file_name);

//STAMPA ALIMENTI
void print_alimenti(char* filename_alimenti);

void caricaAlimenti();




t_alimento modificaAlimento(t_alimento alimento, int modifica_dispensa, int* flag_home);

void sovrascrivi_alimento(char* nome_alimento, t_alimento alimento_modificato);


#endif /*GESTIONE_ALIMENTI_H*/

