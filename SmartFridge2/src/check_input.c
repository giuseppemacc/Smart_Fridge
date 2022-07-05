#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "file_names.h"
#include "gestione_alimenti.h"
#include "gestione_ricette.h"
#include "types.h"
#include "utils.h"

// ------ INPUT qualcosa ----------
// tipo inputTipo(int *flag_errore, int *flag_home)

// fai inserire al tizio la stringa

// se quello che viene inseriro � == HOME_VALUE :
//    flag_home = true
//
// altrimenti se quello che viene inserito non va bene:
//    flag_errore = true
//
// altrimenti se va tutto bene:
//    flag = quello che ha inserito


void checkLenght(int *flag_errore, char *str, int L_MAX) {
  *flag_errore = 0;

  if (strlen(str) > L_MAX) {
    *flag_errore = 1;
    printf("ERRORE!La stringa inserita � troppo lunga (L_MAX = %d)",L_MAX);
  }
}

void inputStr(char *str,int l_max, int *flag_errore, int *flag_home) {

  *flag_errore = 0; // false
  *flag_home = 0;   // false

  strcpy(str, "");

  scanf("%s", str);

  if (strEqual(str, "-1")) {
    *flag_home = 1;

  }else{
    checkLenght( &(*flag_errore), str, l_max);
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

/*RESTITUISCE 1 = la stringa passata non � composta da soli numeri
              0 = la stringa passata � composta da soli numeri */
void isNotNum(char *str, int *flag_errore) {
  // L = { 2., .2, asd, .asd, asd., as.d, .2.2 }

  // non ci devono essere lettere
  // ci deve essere solo un punto

  // 22.2 .22 222. 2.33
  // il punto non pu� essere n� all inizio n� alla fine
  //
  *flag_errore = 0;
  int i = 0;
  int dot_counter = 0;

  int len = strlen(str);

  // dal [48,57]

  if (str[0] == '.' || str[strlen(str) - 1] == '.') {
    *flag_errore = 1;
    printf("\tERRORE! Il punto (.) non pu� stare ne all'inizio ne alla fine\n");
  } else {
    while ((i < len) && (*flag_errore == 0)) {
      if ((((str[i] >= '0') && (str[i] <= '9')) || str[i] == '.' ||str[0] == '-') && dot_counter <= 1) {

        if (str[i] == '.') {
          dot_counter++;
          if (dot_counter > 1) {
            *flag_errore = 1;
            printf("\tERRORE !Non puoi inserire più di un punto (.)\n");
          }
        }
      } else {
        *flag_errore = 1;
        printf("\tERRORE! non puoi inserire caratteri non numerici\n");
      }
      i++;
    }
  }
}





int inputInt(int *flag_errore, int *flag_home) {
  int num;
  char str[20];


  num=0;
  inputStr( str, 20, &(*flag_errore), &(*flag_home) );


  if(!(*flag_errore) &&  !(*flag_home)){
	  isNotNum(str, flag_errore); // isNum

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













int checkUnita(t_alimento *alimento, t_alimento *alimento_trovato) {
  int check = 1; // 1=somma effettuata	0=somma non effettuat� perch� diverse
                 // unit� di misura

  // CASO:g+g,ml+ml,n_elementi+n_elementi;
  if (alimento->unita == alimento_trovato->unita)
    alimento->quantita = alimento->quantita + alimento_trovato->quantita;
  else
    check = 0;

  return check;
}



/*RESTITUISCE:  1 = quantita < 0
                0 = quantita > 0*/
void checkQuantita(float quantita,int* flag_errore){
  *flag_errore = 0;

  if (quantita <= 0){
    *flag_errore = 1;
    printf("ERRORE! La quantit� deve essere positiva\n");
  }
}



void checkFloat(float quantita_float, int *flag_errore) {
  int quantita_int;
  *flag_errore = 0;


  quantita_int = (int)quantita_float; // viene fatto il cast(int), quindi se
                                      // quantita_float=2.30, quantita_int=2

  if (quantita_float > quantita_int) {
    *flag_errore = 1;
  }
}



unita_misura inputUnitaMisura(int *flag_errore, int *flag_home) {
  char str[20];
  unita_misura unita;

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



categorie inputCategoria(int *flag_errore, int *flag_home) {
	char str[20];
  categorie cat;

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



float inputFloat(int *flag_errore, int *flag_home) {
  *flag_home=0;
  *flag_errore=0;
  float num=0;
  char str[20];


  inputStr( str, 20, &(*flag_errore), &(*flag_home) );


  if (! (*flag_home) ){

    isNotNum(str, &(*flag_errore));

    if(! (*flag_errore)){
     num = (float)atof(str);
    }

  }

  return num;
}
