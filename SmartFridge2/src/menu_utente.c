#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "file_names.h"
#include "gestione_alimenti.h"
#include "gestione_ricette.h"
#include "types.h"
#include "utils.h"
#include "check_input.h"


// ?TODO: dichiarare un nuovo tipo bool come enum {false, true}  (false=0,
// true=1)

//#ifndef HOME_VALUE
#define HOME_VALUE -1
//#endif










void menuu() {
  char opzioni[] = "1) visualizza alimenti\n"
		           "2) carica alimenti\n"
		           "3) visualizza ricette\n"
		           "4) carica ricette\n"
		  	  	   "5) resetta file alimenti\n"
		  	  	   "6) resetta file ricette\n"
		  	  	   "0) uscire\n";

  int input;
  int flag_continue; // sarebbe il flag_home
  int flag_errore;

  do {
    flag_continue = 1;
    flag_errore = 0;
    printf("\n\n%s\n\t>> ", opzioni);
    input = inputInt(&flag_errore, &flag_continue); // se viene inserito HOME_VAL
                                      // flag_continue=true e flag_errore=false

    if (!flag_errore && !flag_continue) { // se non sono avvenuti errori e non �
                                          // inserito HOME_VAL
      flag_continue = 1;

      if (input == 0) {
    	 puts("exit ... ");
        flag_continue = 0;

      } else if (input == 1) {
    	print_alimenti();

      } else if (input == 2) {
    	  caricaAlimenti();

      } else if (input == 3) {
    	  print_ricette();

      }else if (input == 4) {
    	  caricaRicette();

      }else if (input == 5) {
    	  clearFile(FILENAME_ALIMENTI);

      }else if (input == 6) {
    	  clearFile(FILENAME_RICETTE);

      } else {
        flag_errore = 1;
      }
    }

    if (flag_errore) {
    	flag_continue = 1;
      puts("comando non trovato");
    }

  } while (flag_continue);
}

// --------------------------------------------------------------------------------------------

void menu() {
  // TODO fare un menu a pi� pagine

  int input;
  int flag_exit;
  do {
    flag_exit = 0;
    puts("\n\n");
    printf("1) aggiungi alimenti\n");
    printf("2) aggiungi ricette\n");
    printf("3) visualizza file alimenti\n");
    printf("4) visualizza file ricette\n");
    printf("5) visualizza ricette preparabili\n");
    printf("6) prepara ricetta\n");
    printf("7) modifica alimenti\n");
    printf("8) modifica ricette\n");
    printf("0) exit\n");
    printf("\t>> ");
    scanf("%d", &input);

    if (input == 0) {
      flag_exit = 1;
    } else if (input == 1) {
      //input_alimenti();
    } else if (input == 2) {
      aggiungi_ricette();
    } else if (input == 3) {
      print_alimenti();
    } else if (input == 4) {
      print_ricette();
    } else if (input == 5) {

      t_ricetta ricette_preparabili[20];
      int n_ricette_preparabili;

      ricettePreparabili(ricette_preparabili, &n_ricette_preparabili,
                         FILENAME_RICETTE);
      print_arr_ricette(ricette_preparabili, n_ricette_preparabili);

    } else if (input == 6) {

      t_alimento alimenti[2];
      t_ricetta ricette_compatibili[20];
      int n_ricette_compatibili;
      /*
      alimenti[0] = input_alimento();
      puts("--");
      alimenti[1] = input_alimento();
      puts("--");*/

      // inserisci i nomi degli alimenti
      // cerca questi alimenti in frigo
      // se presenti:
      //   ricetteCompatibili(alimenti_trovati)
      // altrimenti:
      //   chiedi al negro di inserire alimenti presenti in frigo

      ricetteCompatibili(alimenti, 2, ricette_compatibili,
                         &n_ricette_compatibili, FILENAME_RICETTE);
      print_arr_ricette(ricette_compatibili, n_ricette_compatibili);

    } else if (input == 7) {
      modifica_alimenti();
    } else if (input == 8) {
      modifica_ricette();
    } else {
      puts("\ncomando non trovato\n");
    }

  } while (flag_exit == 0);
}
