#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "file_names.h"
#include "gestione_alimenti.h"
#include "gestione_ricette.h"
#include "inputs.h"
#include "piano_settimanale.h"
#include "types.h"
#include "utils.h"





void menu_modificaAlimento(){
	int flag_home;
	t_alimento alimento;
	t_alimento alimento_modificato;

	alimento = richiediAlimento(&flag_home);

	if(!flag_home){

		alimento_modificato = modificaAlimento(alimento, 0, &flag_home);

		if(!flag_home){
			sovrascrivi_alimento(alimento.nome, alimento_modificato);
		}
	}
}

void menu_modificaRicetta(){
	int flag_home;
	t_ricetta ricetta;
	t_ricetta ricetta_modificata;

	ricetta = richiediRicetta(&flag_home);

	if(!flag_home){

		ricetta_modificata = modificaRicetta(ricetta, &flag_home);

		if(!flag_home){
			sovrascrivi_ricetta(ricetta.nome, ricetta_modificata);
		}
	}
}

void menu_printRic_Preparabili(){
	t_ricetta ricette_preparabili[50]; // deve essere il numero di ricette presenti
	int n_ricette_preparabili;

	ricettePreparabili(ricette_preparabili, &n_ricette_preparabili,FILENAME_RICETTE);
	if(n_ricette_preparabili>0){

		for(int i=0; i<n_ricette_preparabili; i++){
			print_ricetta(ricette_preparabili[i]);

		}
		puts("");
	}else{
		puts("Nessuna ricetta preparabile :(");
	}

}

void menu_cercaAlimento(){
	int flag_home;
	t_alimento alimento = richiediAlimento(&flag_home);

	  if(!flag_home){
		  print_alimento(alimento);
	  }
}

void menu_cercaRicetta(){
	int flag_home;
	t_ricetta ricetta = richiediRicetta(&flag_home);

	  if(!flag_home){
		  print_ricetta(ricetta);
	  }
}

void menu_valutaRicetta(){

	int flag_home;

	t_ricetta ricetta_da_valutare = richiediRicetta(&flag_home);

	  if(!flag_home){
		  valutaRicetta(ricetta_da_valutare.nome, &flag_home);
	  }
}

void menu_preparaRicetta(){
	int flag_home;

	t_ricetta ricetta_da_preparare = richiediRicetta(&flag_home);

	if(!flag_home ){

		if(isPreparabile(ricetta_da_preparare, FILENAME_ALIMENTI)){
			preparaRicetta(ricetta_da_preparare);
			puts("ricetta preparata!");
		}else{
			puts("ingredienti non sufficienti per preparare la ricetta selezionata");
		}

	}
}



void menuu(){


	char opzioni_menu[][300] = {
			"[1] visualizza gli alimenti del frigo\n[2] aggiungi alimenti in frigo\n[3] cerca alimento nel frigo\n[4] modifica/rimuovi alimento dal frigo\n---------------- FRIGO (1/4) --------\n",
			"[1] visualizza ricettario\n[2] aggiungi ricetta al ricettario\n[3] cerca ricetta nel ricettario\n[4] modifica/rimuovi ricetta dal ricettario\n[5] valuta una ricetta\n[6] visualizza statistica valutazione ricette\n---------------- RICETTARIO (2/4) --------\n",
			"[1] visualizza ricette preparabili\n[2] prepara ricetta\n[3] fatti consigliare cosa prepare!\n---------------- PREPARA RICETTE (3/4) --------\n",
			"[1] visualizza il tuo piano settimanale\n[2] personalizza piano settimanale\n[3] visualizza cronologia pasti\n---------------- PIANO SETTIMANALE (4/4) --------\n"
	};


	int menu_selezionato = 0;
	int flag_continue = 1;
	int flag_errore;
	int flag_home;

	char input[20];


	do{
		printf("\n\n------------- OGGI E' %s ------------\n", returnGiorno( get_giorno_attuale()));
		printf("%s", opzioni_menu[menu_selezionato]);
		printf("[help] per visualizzare comandi aggiuntivi\n");
		printf("\n\t\t\tV\n");
		printf("\t\t\t");

		inputStr(input, 20, &flag_errore, &flag_home);

		if(!flag_errore && !flag_home){

			if( strEqual(input, "help") ){

				printf("[exit] per terminare il programma\n");
				printf("[home] per tornare al menu da qualsiasi punto del programma\n");
				printf("[<] per spostarsi di una pagina a sinistra nel menu\n");
				printf("[>] per spostarsi di una pagina a destra nel menu\n");

			}else if( strEqual(input, "exit") ){

				printf("exit ...");
				flag_continue = 0;

			}else if( strEqual(input, ">") ){

				if(menu_selezionato < 3 ){
					menu_selezionato++;
				}

			}else if( strEqual(input, "<") ){

				if(menu_selezionato > 0 ){
					menu_selezionato--;
				}

			}else{

				if( menu_selezionato == 0 ){ // menu frigo

					if(strEqual(input, "1")){

						print_alimenti(FILENAME_ALIMENTI);

					}else if(strEqual(input, "2")){

						caricaAlimenti();

					}else if(strEqual(input, "3")){

						menu_cercaAlimento();

					}else if(strEqual(input, "4")){

						menu_modificaAlimento();

					}

				}else if( menu_selezionato == 1 ){ // menu ricette

					if(strEqual(input, "1")){

						print_ricette(1, FILENAME_RICETTE);

					}else if(strEqual(input, "2")){

						caricaRicette();

					}else if(strEqual(input, "3")){

						menu_cercaRicetta();

					}else if(strEqual(input, "4")){

						menu_modificaRicetta();

					}else if(strEqual(input, "5")){

						menu_valutaRicetta();

					}else if(strEqual(input, "6")){

						printStatistica_voti();

					}


				}else if( menu_selezionato == 2 ){ // menu prepara ricette

					if(strEqual(input, "1")){

						menu_printRic_Preparabili();

					}else if(strEqual(input, "2")){

						menu_preparaRicetta();

					}else if(strEqual(input, "3")){

						consigliaRicette();

					}


				}else if( menu_selezionato == 3 ){ // menu piano settimanale

					if(strEqual(input, "1")){

						print_piano_settimanale();

					}else if(strEqual(input, "2")){

						modificaPiano_settimanale();

					}else if(strEqual(input, "3")){

						puts("Cronologia pasti, dalla meno recente alla più recente");
						print_ricette(0, FILENAME_CRONOLOGIA_RICETTE);

					}
				}
			}
		}

	}while(flag_continue || flag_errore || flag_home);

}
























