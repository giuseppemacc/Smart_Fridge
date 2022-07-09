#ifndef TYPES_H_
#define TYPES_H_

typedef enum{
	NONE, LUN, MAR, MER, GIO, VEN, SAB, DOM
} giorni;

typedef enum{
	NONE_CAT, CARNE, PESCE, VERDURA, PASTA
} categorie; //TODO: cambiare in t_categoria



typedef enum{
  NONE_UNIT, N_UNIT, PESO_GR, PESO_KG, PESO_ML, PESO_L,
} unita_misura;


typedef struct {
	char nome[50];
  int quantita;
  unita_misura unita;
	int dispensa;  //0=alimento in frigo  1=alimento in dispensa
} t_alimento;



typedef struct {
	char nome[50];
	int n_ingredienti;
	t_alimento ingredienti[50];
	categorie categoria;
	char procedimento[200];
	int valutazione;

	int preparata; // V/F  dice se è stata preparata negli ultimi 7 giorni
	int counter_giorni; // giorni passati dall ultima volta che è stata preparata

} t_ricetta;



unita_misura getUnita(char *str);
char *returnUnita(unita_misura unita);


categorie getCategoria(char* str);
char *returnCategoria(categorie categoria);


char *returnGiorno(int giorno);

#endif /* TYPES_H_ */
