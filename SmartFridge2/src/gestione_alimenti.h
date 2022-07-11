/**
 * @def GESTIONE_ALIMENTI_H_
 * @brief contiene i sottoprogrammi che operano sul file alimenti e la relativa interazione con l'utente
 */
#ifndef GESTIONE_ALIMENTI_H_
#define GESTIONE_ALIMENTI_H_

#include "types.h"
#include <stdio.h>

/**
 * @fn void ordinaFileAlimenti_AZ(char*)
 * @brief ordina fil_name di alimenti in ordine alfabetico
 * @param file_name
 */
void ordinaFileAlimenti_AZ(char *file_name);


/**
 * @fn int ricerca_alimento_binaria(char*, t_alimento*, FILE*)
 * @brief ricerca un'alimento tramite il nome in file_alimenti
 * @warning usa la ricerca binaria quindi necessita che file_alimento sia ordinato!
 * @param nome
 * @param alimento con valore dell'alimento se trovato
 * @param file_alimenti
 * @return 0 se non è stata trovata l'alimento
 *         1 se è stato trovato e viene memorizzato in *alimento
 */
int ricerca_alimento_binaria(char *nome, t_alimento *alimento, FILE *file_alimenti);


/**
 * @fn void ricerca_alimentoSottstr(char*, t_alimento[], int*, FILE*)
 * @brief cerca e restituisce tutte gli alimenti che contengono *nome per sottostringa nel loro nome
 * @param nome
 * @param alimenti
 * @param n_alimenti
 * @param file_alimenti
 */
void ricerca_alimentoSottstr(char *nome, t_alimento alimenti[], int* n_alimenti, FILE *file_alimenti);


/**
 * @fn t_alimento richiediAlimento(int*)
 * @brief chiede all'utente di inserire un nome di alimento e resituisce l'alimento voluto trovato nel file alimenti
 * @param flag_home
 * @return
 */
t_alimento richiediAlimento(int* flag_home);



/**
 * @fn void print_alimenti(char*)
 * @brief visualizza a schermo tutte gli alimenti (in ordine alfabetico se ordina_file=1) presenti in filename_alimenti
 * @param filename_alimenti
 */
void print_alimenti(char* filename_alimenti);

/**
 * @fn void caricaAlimenti()
 * @brief permette all'utente di aggiungere degli alimenti al file alimenti
 */
void caricaAlimenti();



/**
 * @fn t_alimento modificaAlimento(t_alimento, int, int*)
 * @brief permette all'utente di modificare i campi di un alimento passato come argomento
 * @param alimento
 * @param modifica_dispensa se uguale a 1 permette anche di modifcare la dispensa, altrimenti rimmarrà invariata
 * @param flag_home
 * @return alimento modificato
 */
t_alimento modificaAlimento(t_alimento alimento, int modifica_dispensa, int* flag_home);


/**
 * @fn void sovrascrivi_alimento(char*, t_alimento)
 * @brief sovrascrive nel file alimenti l'alimento con nome nome_alimento con alimento_modificato
 * @param nome_alimento
 * @param alimento_modificato
 */
void sovrascrivi_alimento(char* nome_alimento, t_alimento alimento_modificato);


#endif /*GESTIONE_ALIMENTI_H*/

