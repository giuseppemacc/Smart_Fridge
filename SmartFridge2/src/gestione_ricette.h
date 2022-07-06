#ifndef GESTIONE_RICETTE_H_
#define GESTIONE_RICETTE_H_

#include "types.h"
#include <stdio.h>


void preparaRicetta(t_ricetta ricetta);

void ricerca_ricettaSottstr(char *nome, t_ricetta ricette[], int* n_ricette, FILE *file_ricette);

t_ricetta inputRicetta(int *flag_home);

void caricaRicette();


void print_ricetta(t_ricetta ricetta);
void print_ricette(char* filename_ricette);

void print_arr_ricette(t_ricetta ricette[], int n_ricette);


void ordinaFileRicette_AZ(char *file_name);

int ricerca_ricetta(char* nome, t_ricetta* ricetta, FILE* file_ricette);


void modifica_ricette();


int isAlimento_compatibile(t_alimento alimento1, t_alimento alimento2, int ignora_quantita);

int isPreparabile(t_ricetta ricetta, char* filename_alimenti );

int isContained(t_alimento alimenti1[], t_alimento alimenti2[], int n_alimenti1, int n_alimenti2);

void ricettePreparabili( t_ricetta ricette_preparabili[], int* n_ricette_preparabili, char* filename_ricette);

void ricetteCompatibili( t_alimento alimenti[], int n_alimenti, t_ricetta ricette_compatibili[], int* n_ricette_compatibili, char* filename_ricette);


void printStatistica_voti();

void valuta_ricette();

#endif /* GESTIONE_RICETTE_H_ */
