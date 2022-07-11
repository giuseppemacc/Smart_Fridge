/*
inputs.h:

	inputAlimento
	inputAlimento_unita
	inputAlimento_quantita
	inputAlimento_nome
	inputAlimento_dispensa

	inputRicetta
	inputRicetta_procedimento
	inputRicetta_categoria
	inputRicetta_nome

	inputStr
	inputInt
	inputBool
	inputFloat

	input_giorno
	inputUnitaMisura
	inputCategoria


*/
#ifndef INPUTS_H_
#define INPUTS_H_



#include "types.h"



void inputAlimento_unita(t_alimento* alimento, int* flag_home);

void inputAlimento_quantita(t_alimento* alimento, int* flag_home);

void inputAlimento_nome(t_alimento* alimento, int* flag_home);

void inputAlimento_dispensa(t_alimento* alimento, int* flag_home);

t_alimento inputAlimento(int input_dispensa, int *flag_home);




void inputRicetta_procedimento(t_ricetta* ricetta, int* flag_home);

void inputRicetta_categoria(t_ricetta* ricetta, int* flag_home);

void inputRicetta_nome(t_ricetta* ricetta, int* flag_home);

t_ricetta inputRicetta(int *flag_home);



float inputFloat(int *flag_errore, int *flag_home);

int inputInt(int *flag_errore, int *flag_home);

int inputBool(int *flag_errore, int *flag_home);

void inputStr(char *str,int l_max, int *flag_errore, int *flag_home);




t_unita_misura inputUnitaMisura(int *flag_errore, int *flag_home);

t_categoria inputCategoria(int *flag_errore, int *flag_home);

t_giorno input_giorno(int* flag_home);




#endif /* INPUTS_H_ */
