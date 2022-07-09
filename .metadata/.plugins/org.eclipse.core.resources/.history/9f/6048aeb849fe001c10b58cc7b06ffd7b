#ifndef GESTIONE_ALIMENTI_H_
#define GESTIONE_ALIMENTI_H_

#include <stdio.h>

#include "types.h"


t_alimento inputAlimento(int *flag_home);

void caricaAlimenti();


void ricerca_alimentoSottstr(char *nome, t_alimento alimenti[], int* n_alimenti, FILE *file_alimenti);

/*RESTITUISCE: 1 = ALIMENTO TROVATO
               0 = ALIMENTO NON TROVATO */
int ricerca_alimento(char* nome, t_alimento* alimento, FILE* file_alimenti);


/*RESTITUISCE: 1 = SOMMA EFFETTUATA PERCHE' alimento E alimento_trovato HANNO LA STESSA UNITA' DI MISURA
               0 = SOMMA NON EFFETTUATA PERCHE' alimento E alimento_trovato HANNO UNITA' DI MISURA DIFFERENTI */
//int checkUnita(t_alimento* alimento,t_alimento* alimento_trovato);


//ORDINAMENTO FILE ALIMENTI IN ORDINE ALFABETICO(A-Z)
void ordinaFileAlimenti_AZ(char *file_name);


//MODIFICA ALIMENTI
void modifica_alimenti();


//STAMPA ALIMENTI
void print_alimenti();


//STAMPA ALIMENTO
void print_alimento(t_alimento alimento);


#endif /*GESTIONE_ALIMENTI_H*/

