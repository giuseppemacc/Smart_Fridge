#include "inputs.h"

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "file_names.h"
#include "gestione_alimenti.h"
#include "gestione_ricette.h"
#include "types.h"
#include "utils.h"
#include "piano_settimanale.h"
#include "menu_utente.h"


#ifndef HOME_VALUE
	#define BACK_HOME "home" // BACK_HOME
#endif






void inputAlimento_unita(t_alimento* alimento, int* flag_home){
	int flag_errore;

	do {
	  printf("\tunita di misura>> ");

	  alimento->unita = inputUnitaMisura(&flag_errore, &(*flag_home));

	  if(flag_errore){
		printf("\tunit� di misura non trovata (disponibili:g,kg,ml,l,n)\n");
	  }

	} while ((flag_errore == 1) && ((*flag_home) == 0));
}

void inputAlimento_quantita(t_alimento* alimento, int* flag_home){
	float f_quantita;
	int flag_errore;

	do {
	  printf("\tquantità>> ");

	  f_quantita = inputFloat(&flag_errore, &(*flag_home));


	  if( ! (*flag_home) ){ // se non � stato detto di tornare alla home

				  // controlla se sono avvenuti errori
		//NULL
		if( ! flag_errore ){

		  // altri controlli cio� i vari check
		  isPositive(f_quantita,  &flag_errore  ); // controlla che sia > 0

		  if( ! flag_errore ){
			if ((alimento->unita == PESO_KG) || (alimento->unita == PESO_L)) { // se kg/lt si convertono in g/ml

			  alimento->quantita = (int)(f_quantita * 1000);
			  alimento->unita = alimento->unita - 1;
			} else {
			  //Ci troviamo nei casi in cui alimento.unita=g/ml/n_elementii
			  checkFloat( f_quantita, &flag_errore);

			  if( flag_errore ){
				printf("\tERRORE! Le unit� di misura g  ml  n_elementi non possono avere numeri decimali\n");
			  }
			  else{
				alimento->quantita = (int)f_quantita;
			  }

			}
		  }

		}

	  }

	} while ((flag_errore == 1) && ((*flag_home) == 0));
}

void inputAlimento_nome(t_alimento* alimento, int* flag_home){

	int flag_errore;

	  do{
		printf("\tnome >> ");
		inputStr(alimento->nome, 50, &flag_errore, &(*flag_home) );


		if( ! (*flag_home) ){ // se non � stato detto di tornare alla home

		  // controlla se sono avvenuti errori
		  if( ! flag_errore ){
			strToUpper(alimento->nome);
		  }

		}

	  }while( (flag_errore == 1) && ((*flag_home) == 0) );
}

void inputAlimento_dispensa(t_alimento* alimento, int* flag_home){
	int flag_errore;
	do{
		printf("\tquest'alimento si trova in dispensa? >> ");

		alimento->dispensa = inputBool(&flag_errore, &(*flag_home));

	  }while( (flag_errore == 1) && ((*flag_home) == 0) );
}

t_alimento inputAlimento(int input_dispensa, int *flag_home) {
  t_alimento alimento;

  *flag_home = 0;

  strcpy(alimento.nome, "");
  alimento.quantita = 0;
  alimento.unita = NONE_UNIT;
  alimento.dispensa = 0;

  //---NOME---

  inputAlimento_nome(&alimento, &(*flag_home));


  //---UNITA DI MISURA---

  if (!(*flag_home)) { // se non � stato detto di tornare alla home
    // input unit� misura
    inputAlimento_unita(&alimento, &(*flag_home));
  }


  //---QUANTITA'---

  if (!(*flag_home)) { // se non � stato detto di tornare alla home
    // input quantit�
    inputAlimento_quantita(&alimento, &(*flag_home));
  }

  if(!(*flag_home)){
	  if(input_dispensa){
		  inputAlimento_dispensa(&alimento, &(*flag_home));
	  }
  }

  return alimento;
}








void inputRicetta_procedimento(t_ricetta* ricetta, int* flag_home){
	int flag_errore;
	do{
		printf("\tprocedimento >> ");
		inputStr(ricetta->procedimento, 200, &flag_errore, &(*flag_home) );

	  }while( (flag_errore == 1) && ((*flag_home) == 0) );
}

void inputRicetta_categoria(t_ricetta* ricetta, int* flag_home){
	// input categoria
	int flag_errore;
	do {
	  printf("\tcategoria ricetta>> ");

	  ricetta->categoria = inputCategoria(&flag_errore, &(*flag_home));

	  if(flag_errore){
		printf("\tcategorria non trovata (disponibili:CARNE,PESCE,VERDURA,PASTA)\n");
	  }

	} while ((flag_errore == 1) && ((*flag_home) == 0));

}

void inputRicetta_nome(t_ricetta* ricetta, int* flag_home){

	int flag_errore;

	  do{
		printf("\tnome >> ");
		inputStr(ricetta->nome, 50, &flag_errore, &(*flag_home) );


		if( ! (*flag_home) ){ // se non � stato detto di tornare alla home

		  // controlla se sono avvenuti errori
		  if( ! flag_errore ){
			strToUpper(ricetta->nome);
		  }

		}

	  }while( (flag_errore == 1) && ((*flag_home) == 0) );
}

t_ricetta inputRicetta(int *flag_home){

	int flag_errore;
  t_ricetta ricetta;


  flag_errore = 0;
  *flag_home = 0;


  	strcpy(ricetta.nome, "");
  	strcpy(ricetta.procedimento, "");
  	ricetta.n_ingredienti = 0;
  	ricetta.categoria = NONE_CAT;
	ricetta.valutazione = 0;
	ricetta.preparata = 0;
	ricetta.counter_giorni = 8;


  //---NOME---

  inputRicetta_nome(&ricetta, &(*flag_home));



  //--- CATEGORIA ---

  if (!(*flag_home)) { // se non � stato detto di tornare alla home
	// input unit� misura
	inputRicetta_categoria(&ricetta, &(*flag_home));
  }


  // ---- PROCEDIMENTO -----
  if(!(*flag_home)){
	  inputRicetta_procedimento(&ricetta, &(*flag_home));
  }


  //--- INGREDIENTI ---

  if (!(*flag_home)) { // se non � stato detto di tornare alla home
	// input quantit�
	int flag_continue;
	t_alimento ingrediente;
	do {
	  printf("  Inserisci ingredienti : \n");
	  ingrediente = inputAlimento( 1, &(*flag_home));


	  if( !(*flag_home) ){

		  ricetta.ingredienti[ ricetta.n_ingredienti ] = ingrediente;
		  ricetta.n_ingredienti++;

		  do{
			  printf("  inserire altri ingredienti? >> ");
			  flag_continue = inputBool(&flag_errore, &(*flag_home));

		  }while( (flag_errore == 1) && (*flag_home == 0) );

	  }


	} while ( (flag_continue==1) && ((*flag_home) == 0));
  }

  return ricetta;

}







void inputStr(char *str,int l_max, int *flag_errore, int *flag_home) {

	// la fgets ne legge -1 da quello che gli passi dentro
	// " " = 32
	// alla fine di ogni stringa sta 10
	// tranne nei casi in cui vengono inseriti l_max-1 caratteri

  *flag_errore = 0; // false
  *flag_home = 0;   // false
  int len;


  strcpy(str, "");

  //scanf("%s", str);

  fgets(str, l_max-1, stdin);
  fflush(stdin);

  len = strlen(str);

  if(len >= (l_max-2)){
	  *flag_errore = 1;
	  printf("la stringa inserita e' troppo grande\n");
  }else{

	 if( str[len-1]=='\n' ){
		 str[len-1] = 0;
	 }

	if (strEqual(str, BACK_HOME)) {
	  *flag_home = 1;
	}else if( strEqual(str, "") ){
		 *flag_errore = 1;
	 }
  }



  // fai inserire al tizio la stringa

  // se quello che viene inseriro � == HOME_VALUE :
  //    flag_home = true
  //
  // altrimenti se quello che viene inserito non va bene:
  //    flag_errore = true
  //
  // altrimenti se va tutto bene:
  //    str = quello che ha inserito
}


int inputInt(int *flag_errore, int *flag_home) {
  int num;
  char str[20];


  num=0;
  inputStr( str, 20, &(*flag_errore), &(*flag_home) );


  if(!(*flag_errore) &&  !(*flag_home)){
	  isNum(str, flag_errore); // isNum

	  if( !(*flag_errore) ){
		  num = (int)atoi(str);
	  }

  }

  return num;
}


int inputBool(int *flag_errore, int *flag_home) {
  int flag;
  char str[20];

  *flag_errore = 0;
  *flag_home = 0;
  flag = 0;

  inputStr(str, 20, &(*flag_errore), &(*flag_home));

  if( !(*flag_home) && !(*flag_errore) ){

	  if(strEqual(str,"si")||strEqual(str,"sì")||strEqual(str,"1")||strEqual(str,"y")||strEqual(str,"yes")||strEqual(str,"ok")){
	  	  flag = 1;

	  }else if(strEqual(str, "no")||strEqual(str, "n")||strEqual(str, "0")){
		  flag = 0;

	  }else{
		  *flag_errore = 1;

	  }
  }
  return flag;
}


float inputFloat(int *flag_errore, int *flag_home) {
  *flag_home=0;
  *flag_errore=0;
  float num=0;
  char str[20];


  inputStr( str, 20, &(*flag_errore), &(*flag_home) );


  if (! (*flag_home) ){

    isNum(str, &(*flag_errore));

    if(! (*flag_errore)){
     num = (float)atof(str);
    }

  }

  return num;
}




t_giorno input_giorno(int* flag_home){
	char str[20];
	t_giorno giorno;
	int flag_errore;

	do{
		flag_errore = 0;

		do{
			printf("giorno >> ");
			inputStr(str, 20, &flag_errore, &(*flag_home));
		}while(flag_errore && (!*flag_home));


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


t_unita_misura inputUnitaMisura(int *flag_errore, int *flag_home) {
  char str[20];
  t_unita_misura unita;

  *flag_errore=0;
  *flag_home=0;
  unita = NONE_UNIT;

  inputStr( str, 20, &(*flag_errore), &(*flag_home) );



  if ( !(*flag_home)  && !(*flag_errore) ){

    strToUpper(str);
    unita = getUnita(str);

    if (unita == NONE_UNIT){
      *flag_errore = 1;
    }
  }

  return unita;
}


t_categoria inputCategoria(int *flag_errore, int *flag_home) {
	char str[20];
  t_categoria cat;

  *flag_errore=0;
  *flag_home=0;
  cat = NONE_CAT;

  inputStr( str, 20, &(*flag_errore), &(*flag_home) );



  if ( !(*flag_home)  && !(*flag_errore) ){

	strToUpper(str);
	cat = getCategoria(str);

	if (cat == NONE_CAT){
	  *flag_errore = 1;
	}
  }

  return cat;
}




