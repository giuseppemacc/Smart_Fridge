#include "types.h"
#include <stdio.h>
#include "gestione_ricette.h"
#include "gestione_alimenti.h"
#include "utils.h"
#include "file_names.h"
#include "menu_utente.h"
#include "check_input.h"





void default_piano_settimanale(){
  FILE* file_pianosettimanale;
  categorie cat;
  giorni giorno;

  if( apriFile(&file_pianosettimanale, FILENAME_PIANO_SETTIMANALE, "wb+") ){

	// il primo elemento del file indica il giorno corrente
	giorno = MER;
	fwrite(&giorno, sizeof(giorni), 1, file_pianosettimanale);

	// tutti gli altri indicano il piano settimanale
    cat = CARNE;
    fwrite(&cat, sizeof(categorie), 1, file_pianosettimanale);

    cat = VERDURA;
    fwrite(&cat, sizeof(categorie), 1, file_pianosettimanale);

    cat = PESCE;
    fwrite(&cat, sizeof(categorie), 1, file_pianosettimanale);

    cat = PASTA;
    fwrite(&cat, sizeof(categorie), 1, file_pianosettimanale);

    cat = CARNE;
    fwrite(&cat, sizeof(categorie), 1, file_pianosettimanale);

    cat = VERDURA;
    fwrite(&cat, sizeof(categorie), 1, file_pianosettimanale);

    cat = PESCE;
    fwrite(&cat, sizeof(categorie), 1, file_pianosettimanale);

    fclose(file_pianosettimanale);
  }

}


void print_piano_settimanale(){

  FILE* file_pianosettimanale;
  categorie categoria_corrente;
  int giorno=1;

  if(apriFile(&file_pianosettimanale, FILENAME_PIANO_SETTIMANALE, "rb+")){

    fseek(file_pianosettimanale,sizeof(giorni), SEEK_SET);	//posizioniamo il puntatore dopo il giorno

    fread(&categoria_corrente, sizeof(categorie), 1, file_pianosettimanale);
    while (!feof(file_pianosettimanale)) {

    	printf("%s:\t%s\n", returnGiorno(giorno),returnCategoria(categoria_corrente));
    	giorno++;

        fread(&categoria_corrente, sizeof(categorie), 1, file_pianosettimanale);
    }

    fclose(file_pianosettimanale);
  }
}



giorni get_giorno_attuale(){
	FILE* file_pianosettimanale;
	giorni giorno;

	if(apriFile(&file_pianosettimanale, FILENAME_PIANO_SETTIMANALE, "rb+")){

		rewind(file_pianosettimanale);
		fread(&giorno, sizeof(giorni), 1, file_pianosettimanale);

		fclose(file_pianosettimanale);
	}

	return giorno;
}




categorie return_categoria_giorno_attuale(){
	FILE* file_pianosettimanale;
	categorie cat;
	giorni giorno;

	if(apriFile(&file_pianosettimanale, FILENAME_PIANO_SETTIMANALE, "rb+")){

		rewind(file_pianosettimanale);
		fread(&giorno, sizeof(giorni), 1, file_pianosettimanale);

		fseek(file_pianosettimanale, giorno*sizeof(categorie), SEEK_SET);	//posizioniamo il puntatore dopo il giorno
		fread(&cat, sizeof(categorie), 1, file_pianosettimanale);


		fclose(file_pianosettimanale);
	}

	return cat;
}



void shift_arrRicette_4cat(t_ricetta ricette[], int n_ricette, categorie cat){
	int i=0;
	int j;
	int cat_found=1;
	int i_cat;
	t_ricetta ric_cat;

	while( (i<n_ricette) && (cat_found==1)){

		cat_found = 0;
		j=i;

		while((j<n_ricette) && (cat_found==0)){

			if(ricette[j].categoria == cat){
				i_cat = j;
				cat_found = 1;
			}

			j++;
		}

		if( cat_found && (i_cat != i) ){
			ric_cat = ricette[i_cat];

			for(int z = (i_cat-1); z >=i ; z--){
				ricette[z+1] = ricette[z];
			}
			ricette[i] = ric_cat;
		}
		i++;

	}
}

void ordina_arrRicette_4giorni(t_ricetta ricette[], int n_ricette){

	int i;
	int j;
	int i_max;
	t_ricetta temp_ricetta;

	i=0;
	while( (i < (n_ricette-1)) ){

		i_max = i;
		j = i+1;

		while(j<n_ricette){

			if( ricette[j].counter_giorni > ricette[i_max].counter_giorni ){
				i_max = j;
			}

			j++;
		}

		//scambia ricette[i] con ricette[i_min]
		temp_ricetta = ricette[i];
		ricette[i] = ricette[i_max];
		ricette[i_max] = temp_ricetta;

		i++;

	}
}


void prioritarizza_ricette( t_ricetta ricette[], int n_ricette ){

	// ottiene la categoria dal giorno
	categorie cat_giorno = return_categoria_giorno_attuale();

	// ordina ricette in ordine decrescente in base a ricette.counter_giorni
	ordina_arrRicette_4giorni(ricette, n_ricette);

	// ordina ricette in base alla categoria del giorno
	shift_arrRicette_4cat(ricette, n_ricette, cat_giorno);


}






giorni input_giorno(int* flag_home){
	char str[20];
	giorni giorno;
	int flag_errore;

	do{
		flag_errore = 0;

		do{
			printf("giorno >> ");
			inputStr(str, 20, &flag_errore, &(*flag_home));
		}while(flag_errore && (!*(flag_home)));


		if(!(*flag_home)){
			strToUpper(str);

			if ( strEqual(str,"LUN") )
				giorno = LUN;
			else if( strEqual(str,"MAR") )
				giorno = MAR;
			else if( strEqual(str,"MER") )
				giorno = MER;
			else if( strEqual(str,"GIO") )
				giorno = GIO;
			else if( strEqual(str,"VEN") )
				giorno = VEN;
			else if( strEqual(str,"SAB"))
				giorno = SAB;
			else if( strEqual(str,"DOM") )
				giorno = DOM;
			else{
				flag_errore=1;
				printf("ERRORE: inserire un giorno corretto\n");
			}
		}

	}while(flag_errore && !(*flag_home));

	return giorno;
}




void modificaPiano_settimanale(){

	FILE* file_pianosettimanale;
	giorni giorno;
	categorie categoria;

	int flag_home;
	int flag_errore;
	int input=0;

	flag_home = 0;

	puts("piano settimanale");
	print_piano_settimanale();

	do{

		printf("inserisci il giorno da modificare ( LUN, MAR, MER, GIO, VEN, SAB, DOM )\n\t");

		giorno = input_giorno(&flag_home);


		if(!flag_home){

			do{
				printf("inserisici la categoria ( CARNE, PESCE, VERDURA, PASTA ) >> ");
				categoria = inputCategoria(&flag_errore, &flag_home);
			}while(flag_errore && !(flag_home));

			if(!flag_home){

				if(apriFile(&file_pianosettimanale, FILENAME_PIANO_SETTIMANALE, "rb+")){

					fseek(file_pianosettimanale, (giorno) * sizeof(categorie), SEEK_SET);
					fwrite(&categoria, sizeof(categorie), 1, file_pianosettimanale);

					fclose(file_pianosettimanale);
				}

				puts("piano settimanale aggiornato!");
				print_piano_settimanale();

				do{
					printf("vuoi modificare un' altro giorno? ");
					input = inputBool(&flag_errore, &flag_home);
				}while(flag_errore && !(flag_home));
			}
		}



	}while((input==1) && !flag_home);

}

