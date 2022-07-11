/**
 * @def TYPES_H_
 * @brief modulo contenente nuovi tipi di dato, e relative funzioni di conversione/visualizzazione, utilizzati nel programma
 */

#ifndef TYPES_H_
#define TYPES_H_

/**
 * @enum t_giorno
 * @brief definisce i giorni della settimana
 * 		  NONE indica un giorno della settimana non valido
 */
typedef enum{
	NONE, LUN, MAR, MER, GIO, VEN, SAB, DOM
} t_giorno;


/**
 * @enum t_categoria
 * @brief definisce le categorie delle ricette
 * 		  NONE_CAT indica una categoria non valida
 */
typedef enum{
	NONE_CAT, CARNE, PESCE, VERDURA, PASTA
} t_categoria;


/**
 * @enum t_unita_misura
 * @brief definisce le unita di misura
 * 		  (N_UNIT significa numero elementi)
 * 		  NONE_UNIT indica un unita di misura non valida
 */
typedef enum{
  NONE_UNIT, N_UNIT, PESO_GR, PESO_KG, PESO_ML, PESO_L,
} t_unita_misura;



/**
 * @struct t_alimento
 * @brief definisce le informazione relative ad un alimento
 * dispensa:
 *   se è 1 indica che l'alimento è presente in dispensa
 *   se è 0 indica che l'alimento va cercato in frigo
 *   tutti gli alimenti presenti nel file_alimenti avranno sempre dispensa = 0
 * 	 possono esserci alimenti in ricetta.ingredienti[] che possono avere dispensa = 1
 * unita:
 * 	 l'unità di misura di ogni alimento valido può essere espressa solo in N_UNIT, PESO_GR, PESO_ML
 * 	 nei casi in cui si faccia inserire un alimento in KG o L l'unità di misura e la quantita verrano convertite in GR o ML
 */
typedef struct {
	char nome[50];
  int quantita;
  t_unita_misura unita;
	int dispensa;
} t_alimento;


/***
 * @struct t_ricetta
 * @brief definisce le informazione relative ad una ricetta
 * valutazione:
 *   se è 0 indica che la ricetta non è stata valutata
 * 	 da 1 a 5 compresi indica la valutazione della ricetta
 * 	 valori minori di 0 e maggiori di 5 non sono validi
 * counter_giorni:
 * 	 indica i giorni passati dall'utlima volta che la ricetta è stata valutata
 */
typedef struct {
	char nome[50];
	int n_ingredienti;
	t_alimento ingredienti[50];
	t_categoria categoria;
	char procedimento[200];
	int valutazione;

	int counter_giorni;

} t_ricetta;


/**
 * @fn char returnGiorno*(t_giorno)
 * @brief converte da t_giorno a stringa
 * @param giorno
 * @return ritorna la stringa corrispondente al giorno inserito come argomento
 */
char *returnGiorno(t_giorno giorno);

/**
 * @fn t_unita_misura getUnita(char*)
 * @brief converte da stringa a t_giorno
 * @param str
 * @return ritorna l'unità di misura corrispondente alla stringa passata come argomento
 */
t_unita_misura getUnita(char *str);


/**
 * @fn char returnUnita*(t_unita_misura)
 * @brief converte da t_unita a stringa
 * @param unita
 * @return ritorna la stringa corrispondente all'unita di misura passata come argomento
 */
char *returnUnita(t_unita_misura unita);

/**
 * @fn t_categoria getCategoria(char*)
 * @brief converte da stringa a t_categoria
 * @param str
 * @return ritorna la categoria corrispondente alla stringa passata come argomento
 */
t_categoria getCategoria(char* str);

/**
 * @fn char returnCategoria*(t_categoria)
 * @brief converte da t_categoria a stringa
 * @param categoria
 * @return ritorna la stringa corrispondente alla categoria passata come argomento
 */
char *returnCategoria(t_categoria categoria);

/**
 * @fn void print_alimento(t_alimento)
 * @brief stampa a schermo i campi dell'alimento passato come parametro
 * @param alimento
 */
void print_alimento(t_alimento alimento);

/**
 * @fn void print_ricetta(t_ricetta)
 * @brief stampa a schermo i campi della ricetta passata come parametro
 * @param ricetta
 */
void print_ricetta(t_ricetta ricetta);


#endif /* TYPES_H_ */
