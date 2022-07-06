#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "file_names.h"
#include "gestione_alimenti.h"
#include "gestione_ricette.h"
#include "piano_settimanale.h"
#include "types.h"
#include "utils.h"
#include "check_input.h"


// ?TODO: dichiarare un nuovo tipo bool come enum {false, true}  (false=0,
// true=1)

//#ifndef HOME_VALUE
#define HOME_VALUE -1
//#endif






void preparaRicetta(t_ricetta ricetta){

	// file giorni ++

	// deve scalare la quantità dal frigo


	// counter_giorni = 0
	// preparata = true

	// per ogni ricetta eccetto quella preparata:

	//	counter_giorni++
	//  if (prepara==true) AND (counter_giorni > 7):
	//		preparata = false



}



t_ricetta richiediRicetta(int* flag_home){

	t_ricetta ricetta_trovata;
	t_ricetta ricette_trovate[50];
	int n_ricette_trovate;

	int flag_continue;
	int flag_errore;

	char nome[20];
	int input;

	FILE* file_ricette;

	*flag_home = 0;
	do{
		flag_continue = 0;

		do{
			printf("Inserisci il nome della ricetta >> ");
			inputStr(nome, 20, &flag_errore, &(*flag_home));

		}while(flag_errore && ((*flag_home)==0));


		if(!(*flag_home)){

			if(apriFile(&file_ricette, FILENAME_RICETTE, "rb+")){

				if( !ricerca_ricetta(nome, &ricetta_trovata, file_ricette) ){

					ricerca_ricettaSottstr(nome, ricette_trovate, &n_ricette_trovate, file_ricette);

					if( n_ricette_trovate > 0){
						// printa gli alimenti

						puts("forse cercavi ...");

						for( int i = 0; i < n_ricette_trovate; i++){
							printf("%d) %s\n", i+1, ricette_trovate[i].nome );
						}
						printf("0) cerca un'altra ricetta\n");

						do{
							printf("seleziona opzione >> ");
							input = inputInt(&flag_errore, &(*flag_home));

							if(!(*flag_home) && !flag_errore){

								if( input == 0 ){
									flag_continue = 1;
								}else if ( input > n_ricette_trovate ){
									flag_errore = 1;
								}else{
									ricetta_trovata = ricette_trovate[input-1];
								}
							}

						}while(flag_errore && ((*flag_home)==0));


					}else{
						printf("ricetta non trovata\n");
						flag_continue = 1;
					}

				}

				fclose(file_ricette);
			}
		}

	}while(flag_continue && ((*flag_home)==0) );

	return ricetta_trovata;
}



t_alimento richiediAlimento(int* flag_home){

	t_alimento alimento_trovato;
	t_alimento alimenti_trovati[50];
	int n_alimenti_trovati;

	int flag_continue;
	int flag_errore;

	char nome[20];
	int input;

	FILE* file_alimenti;

	*flag_home = 0;
	do{
		flag_continue = 0;

		do{
			printf("Inserisci il nome dell'alimento >> ");
			inputStr(nome, 20, &flag_errore, &(*flag_home));

		}while(flag_errore && ((*flag_home)==0));


		if(!(*flag_home)){

			if(apriFile(&file_alimenti, FILENAME_ALIMENTI, "rb+")){

				if( !ricerca_alimento(nome, &alimento_trovato, file_alimenti) ){

					ricerca_alimentoSottstr(nome, alimenti_trovati, &n_alimenti_trovati, file_alimenti);

					if( n_alimenti_trovati > 0){
						// printa gli alimenti

						puts("forse cercavi ...");

						for( int i = 0; i < n_alimenti_trovati; i++){
							printf("%d) %s\n", i+1, alimenti_trovati[i].nome );
						}
						printf("0) cerca un altro alimento\n");

						do{
							printf("seleziona opzione >> ");
							input = inputInt(&flag_errore, &(*flag_home));

							if(!(*flag_home) && !flag_errore){

								if( input == 0 ){
									flag_continue = 1;
								}else if ( input > n_alimenti_trovati ){
									flag_errore = 1;
								}else{
									alimento_trovato = alimenti_trovati[input-1];
								}
							}

						}while(flag_errore && ((*flag_home)==0));


					}else{
						printf("alimento non trovato\n");
						flag_continue = 1;
					}

				}

				fclose(file_alimenti);
			}
		}

	}while(flag_continue && ((*flag_home)==0) );

	return alimento_trovato;
}



void printRic_Preparabili(){
	t_ricetta ricette_preparabili[50]; // deve essere il numero di ricette presenti
	int n_ricette_preparabili;

	ricettePreparabili(ricette_preparabili, &n_ricette_preparabili,FILENAME_RICETTE);
	if(n_ricette_preparabili>0){
		print_arr_ricette(ricette_preparabili, n_ricette_preparabili);
	}else{
		puts("Nessuna ricetta preparabile :(");
	}

}


void fattiConsigliare(){
	int input;
	int input_ins_al;
	int flag_errore;
	int flag_home;
	int flag_continue;

	t_alimento alimenti_scelti[50];
	int n_alimenti_scelti;

	t_ricetta ricette_selezionate[50];
	int n_ricette_selezionate;

	do{
		printf("vuoi mangiare qualche alimento in particolare? ");
		input_ins_al = inputBool(&flag_errore, &flag_home);
	}while( flag_errore && (flag_home==0)  );

	if( !flag_home ){

		do{
			n_alimenti_scelti = 0;
			n_ricette_selezionate = 0;

			if(input_ins_al){ // se è stato detto di inserire gli alimenti

				do{
					alimenti_scelti[n_alimenti_scelti] = richiediAlimento(&flag_home);
					if (!flag_home){
						n_alimenti_scelti++;
						do{
							printf("sceliere un altro alimento? ");
							input = inputBool(&flag_errore, &flag_home);
						}while(flag_errore && (flag_home==0));
					}

				}while(input && (flag_home==0));

				if(!flag_home){
					ricetteCompatibili(alimenti_scelti, n_alimenti_scelti, ricette_selezionate, &n_ricette_selezionate, FILENAME_RICETTE);

				}

			}else{ // se non è stato detto di inserire gli alimenti
				ricettePreparabili(ricette_selezionate, &n_ricette_selezionate, FILENAME_RICETTE);
			}

			if(!flag_home){

				//prioritarizza_ricette(ricette_selezionate, &n_ricette_selezionate);

				if( n_ricette_selezionate > 0){ // se sono state trovate ricette possibili

					input = 0;
					int i = 0;

					while( (i<n_ricette_selezionate) && (flag_home == 0) && (input==0) ){

						print_ricetta( ricette_selezionate[i] );

						do{
							printf("prepare questa ricetta? ");
							input = inputBool(&flag_errore, &flag_home);
						}while(flag_errore && (flag_home==0));

						if(!flag_home){
							if(input){ // se è stato detto di preparare la ricetta
								// prepara ricetta
								puts("ricetta preparata\n\n");
								flag_continue = 0;
								preparaRicetta( ricette_selezionate[i]  );
							}else{
								if(i == (n_ricette_selezionate-1)){
									printf("non sono presenti altre ricette preparabili\n");

									if(input_ins_al){
										do{
											printf("cambiare gli alimenti? ");
											flag_continue = inputBool(&flag_errore, &flag_home);
										}while(flag_errore && (flag_home==0));
									}else{
										flag_continue = 0;
									}

								}
								i++;
							}
						}
					}
				}else{ // se non sono state trovate ricette possibili
					if(input_ins_al){
						printf("nessuna ricetta preparabile con gli alimenti scelti!\n");
						do{
							printf("cambiare gli alimenti ?");
							flag_continue = inputBool(&flag_errore, &flag_home);
						}while(flag_errore && (flag_home==0));

					}else{
						printf("nessuna ricetta è preparabile con gli alimenti presenti in frigo\n");
						flag_continue = 0;
					}
				}
			}
		}while( flag_continue && (flag_home==0) );


	}

}







void menuu() {
  char opzioni[] = "1) visualizza alimenti\n"
		           "2) carica alimenti\n"
		           "3) visualizza ricette\n"
		           "4) carica ricette\n"
		  	  	   "5) resetta file alimenti\n"
		  	  	   "6) resetta file ricette\n"
		  	  	   "7) visualizza ricette preparabili\n"
		  	  	   "8) ricerca alimento\n"
		  	  	   "9) ricerca ricetta\n"
		  	  	   "10) visualizza cronologia pasti\n"
		  	  	   "11) visualizza statistica valutazioni ricette\n"
		  	  	   "12) fatti consigliare\n"
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
    	  print_ricette(FILENAME_RICETTE);

      }else if (input == 4) {
    	  caricaRicette();

      }else if (input == 5) {
    	  clearFile(FILENAME_ALIMENTI);

      }else if (input == 6) {
    	  clearFile(FILENAME_RICETTE);

      }else if (input == 7) {
    	  printRic_Preparabili();

      }else if (input == 8) {
    	  t_alimento alimento = richiediAlimento(&flag_continue);

    	  if(!flag_continue){
    		  print_alimento(alimento);
    		  flag_continue = 1;
    	  }
      }else if (input == 9) {
    	  t_ricetta ricetta = richiediRicetta(&flag_continue);

		  if(!flag_continue){
			  print_ricetta(ricetta);
			  flag_continue = 1;
		  }

      }else if (input == 10) {
    	  print_ricette(FILENAME_CRONOLOGIA_RICETTE);

      }else if (input == 11) {
    	  printStatistica_voti();

      }else if (input == 12) {
    	  fattiConsigliare();

      }else {
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
    } else if (input == 3) {
      print_alimenti();
    } else if (input == 4) {
      //print_ricette();
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
