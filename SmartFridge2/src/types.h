/*
types.h:
	returnGiorno
	returnUnita
	getUnita
	getCategoria
	returnCategoria

	print_alimento
	print_ricetta

*/

#ifndef TYPES_H_
#define TYPES_H_

typedef enum{
	NONE, LUN, MAR, MER, GIO, VEN, SAB, DOM
} t_giorno;

typedef enum{
	NONE_CAT, CARNE, PESCE, VERDURA, PASTA
} t_categoria;



typedef enum{
  NONE_UNIT, N_UNIT, PESO_GR, PESO_KG, PESO_ML, PESO_L,
} t_unita_misura;


typedef struct {
	char nome[50];
  int quantita;
  t_unita_misura unita;
	int dispensa;  //0=alimento in frigo  1=alimento in dispensa
} t_alimento;



typedef struct {
	char nome[50];
	int n_ingredienti;
	t_alimento ingredienti[50];
	t_categoria categoria;
	char procedimento[200];
	int valutazione;

	int preparata; // V/F  dice se � stata preparata negli ultimi 7 giorni
	int counter_giorni; // giorni passati dall ultima volta che � stata preparata

} t_ricetta;



char *returnGiorno(t_giorno giorno);
t_unita_misura getUnita(char *str);
char *returnUnita(t_unita_misura unita);
t_categoria getCategoria(char* str);
char *returnCategoria(t_categoria categoria);


void print_alimento(t_alimento alimento);
void print_ricetta(t_ricetta ricetta);


#endif /* TYPES_H_ */
