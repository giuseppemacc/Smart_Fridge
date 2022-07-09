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










void valutaRicetta(char* nome_ricetta, int* flag_home){
	int valutazione;
	int flag_errore;
	FILE* file_ricette;
	t_ricetta ricetta_trovata; // che saraà uguale a ricetta


	do{
		printf("inserisci una valutazione da 1 a 5 per [%s] >> ", nome_ricetta);
		valutazione = inputInt(&flag_errore, &(*flag_home));

		if(!(*flag_home) && !(flag_errore)){
			flag_errore = !((valutazione>=1) && (valutazione<=5));
		}

	}while(flag_errore && (*flag_home==0));

	if(!(*flag_home)){

		if(apriFile(&file_ricette, FILENAME_RICETTE, "rb+")){

			if( ricerca_ricetta(nome_ricetta, &ricetta_trovata, file_ricette) ){

				ricetta_trovata.valutazione = valutazione;

				fwrite(&ricetta_trovata, sizeof(t_ricetta), 1, file_ricette);

			}

			fclose(file_ricette);
			puts("file chiuso ao");

		}
	}
}




void preparaRicetta(t_ricetta ricetta){
	FILE* file_pianosettimanale;
	FILE* file_alimenti;
	FILE* file_ricette;
	FILE* file_cronologiaricette;

	giorni giorno;
	t_alimento alimento;
	t_ricetta ricetta_corrente;

	//aggiungi la ricetta alla cronologia

	// file giorni ++
	if (apriFile(&file_pianosettimanale, FILENAME_PIANO_SETTIMANALE, "rb+")){

		fread( &giorno, sizeof(giorni), 1, file_pianosettimanale);
		fseek(file_pianosettimanale, -sizeof(giorni), SEEK_CUR); // sposta di uno indietro

		if(giorno == DOM){
			giorno = LUN;
		}else{
			giorno++;
		}

		fwrite(&giorno, sizeof(giorni), 1, file_pianosettimanale);

		fclose(file_pianosettimanale);
	}


	// deve scalare la quantità dal frigo
	if (apriFile(&file_alimenti, FILENAME_ALIMENTI, "rb+")){

		for(int i=0; i<ricetta.n_ingredienti; i++){

			if( ricetta.ingredienti[i].dispensa == 0 ){ // se l alimento non è da dispensa
				if( ricerca_alimento(ricetta.ingredienti[i].nome, &alimento, file_alimenti  ) ){
					alimento.quantita -= ricetta.ingredienti[i].quantita;

					if(alimento.quantita<=0){
						strcpy(alimento.nome,""); // se la quantita==0 elimina l'alimento dal frigo
					}

					fwrite(&alimento, sizeof(t_alimento), 1, file_alimenti);
				}else{
					printf("GRAAAAAAAANDE BUUUUUG\n");
				}
			}

		}

		fclose(file_alimenti);
	}


	// counter_giorni = 0
	// preparata = true

	// per ogni ricetta eccetto quella preparata:

	//	counter_giorni++
	//  if (prepara==true) AND (counter_giorni > 7):
	//		preparata = false

	if( apriFile( &file_ricette, FILENAME_RICETTE, "rb+") ){

		t_ricetta ric_corrente;
		int i=0;

		rewind(file_ricette);
		fread(&ric_corrente, sizeof(t_ricetta), 1, file_ricette);

		while( !(feof(file_ricette)) ){


			ric_corrente.counter_giorni += 1;
			//print_ricetta(ric_corrente);
			fseek(file_ricette, -sizeof(t_ricetta), SEEK_CUR);
			fwrite(&ric_corrente, sizeof(t_ricetta), 1, file_ricette);
			i++;



			fseek(file_ricette, i*sizeof(t_ricetta), SEEK_SET);
			fread(&ric_corrente, sizeof(t_ricetta), 1, file_ricette);
		}


		if(ricerca_ricetta(ricetta.nome, &ricetta_corrente, file_ricette)){

			ricetta_corrente.counter_giorni = 0;
			ricetta_corrente.preparata = 1;
			fwrite(&ricetta_corrente, sizeof(t_ricetta), 1, file_ricette);

		}else{
			printf("ANCORA PIU GRAAAAAAAANDE BUUUUUG\n");
		}


		fclose(file_ricette);
	}





	// aggiugni ricetta alla cronologia ricette
	if( apriFile(&file_cronologiaricette, FILENAME_CRONOLOGIA_RICETTE, "rb+")){
		fseek( file_cronologiaricette, 0, SEEK_END ); // posiziona alla fine

		fwrite(&ricetta, sizeof(t_ricetta), 1, file_cronologiaricette);

		fclose(file_cronologiaricette);

	}

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
	int input_valutazione;
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

				prioritarizza_ricette(ricette_selezionate, n_ricette_selezionate);

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
								do{
									printf("vuoi aggiungere una valutazione per la ricetta? ");
									input_valutazione = inputBool(&flag_errore, &flag_home);
								}while(flag_errore && (flag_home==0));

								if(!flag_home){

									if(input_valutazione){
										valutaRicetta(ricette_selezionate[i].nome, &flag_home);
									}

								}

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



// --------------------------------------------------------------------------------------------



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

						print_ricette(FILENAME_RICETTE);

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

						printRic_Preparabili();

					}else if(strEqual(input, "2")){

						menu_preparaRicetta();

					}else if(strEqual(input, "3")){

						fattiConsigliare();

					}


				}else if( menu_selezionato == 3 ){ // menu piano settimanale

					if(strEqual(input, "1")){

						print_piano_settimanale();

					}else if(strEqual(input, "2")){

						modificaPiano_settimanale();

					}else if(strEqual(input, "3")){

						puts("Cronologia pasti, dalla meno recente alla più recente");
						print_ricette(FILENAME_CRONOLOGIA_RICETTE);

					}
				}
			}
		}

	}while(flag_continue || flag_errore || flag_home);

}
























