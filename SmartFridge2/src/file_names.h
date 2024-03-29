/**
 * @def FILE_NAMES_H_
 * @brief modulo contenente tutti i nomi dei files utilizzati nel programma
 */

#ifndef FILE_NAMES_H_
#define FILE_NAMES_H_

/**
 * @def FILENAME_ALIMENTI
 * @brief file binario di tipo t_alimento
 * � il file in cui vengono memorizzati ed aggiornati gli alimenti presenti in frigo
 */
#ifndef FILENAME_ALIMENTI
	#define FILENAME_ALIMENTI "alimenti.dat"
#endif

/**
 * @def FILENAME_RICETTE
 * @brief file binario di tipo t_ricetta
 * � il file in cui vengono memorizzate ed aggiornate le ricette presenti nel ricettario
 */
#ifndef FILENAME_RICETTE
	#define FILENAME_RICETTE "ricette.dat"
#endif

/**
 * @def FILENAME_CRONOLOGIA_RICETTE
 * @brief file binario di tipo t_ricetta
 * � il file in cui vengono memorizzate le ricette preparate in ordine cronologico
 */
#ifndef FILENAME_CRONOLOGIA_RICETTE
	#define FILENAME_CRONOLOGIA_RICETTE "cronologia_ricette.dat"
#endif

/**
 * @def FILENAME_PIANO_SETTIMANALE
 * @brief file binario misto di tipo t_giorno e t_categoria (entrambi enum)
 * @warning il primo elemento indica il giorno corrente ed � di tipo t_giorno
 * - gli altri 7 elementi sono di tipo t_categoria ed indicano la categoria associata al gioro della settimana corrispondente
 */
#ifndef FILENAME_PIANO_SETTIMANALE
	#define FILENAME_PIANO_SETTIMANALE "piano_settimanale.dat"
#endif


#endif /* FILE_NAMES_H_ */
