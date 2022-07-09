#include "types.h"
#include "utils.h"
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>



char *returnGiorno(int giorno) {
  char *s = (char *)calloc(15,sizeof(char)); // alloca dinamicamente la memoria per contenere 10 caratteri

  if (giorno == NONE){
	  strcpy(s, "NULL");

  }else if (giorno == LUN){
      strcpy(s, "LUNEDI'   ");

  }else if (giorno == MAR){
    strcpy(s, "MARTEDI'  ");

  }else if (giorno ==  MER){
	  strcpy(s, "MERCOLEDI'");

  }else if (giorno == GIO){
		strcpy(s, "GIOVEDI'  ");

  }else if ( giorno == VEN){
	  strcpy(s,"VENERDI'  ");

  }else if( giorno == SAB){
	  strcpy(s,"SABATO    ");

  }else if( giorno == DOM){
	  strcpy(s,"DOMENICA  ");
  }

  return s;
}

// RESTITUISCE L'UNITA' DI MISURA(stringa) CORRISPONDENTE ALL'UNITA' DI MISURA
// PASSATA
char *returnUnita(unita_misura unita) {
  char *s = (char *)calloc(
      10,
      sizeof(
          char)); // alloca dinamicamente la memoria per contenere 10 caratteri

  // assegna a s l'unità di misura corrispondente
  if (unita == N_UNIT)
    strcpy(s, "");
  else {
    if (unita == PESO_GR)
      strcpy(s, "g");
    else {
      if (unita == PESO_KG)
        strcpy(s, "kg");
      else {
        if (unita == PESO_ML)
          strcpy(s, "ml");
        else {
          if (unita == PESO_L)
            strcpy(s, "lt");
          else
            strcpy(s, "ERROR");
        }
      }
    }
  }

  return s;
}

// RESTITUISCE L'UNITA' DI MISURA(unita_misura) CORRISPONDENTE ALLA STRINGA
// PASSATA
unita_misura getUnita(char *str) {
  unita_misura unita;

  if (strEqual(str, "G")) {
    unita = PESO_GR;
  } else if (strEqual(str, "KG")) {
    unita = PESO_KG;
  } else if (strEqual(str, "ML")) {
    unita = PESO_ML;
  } else if (strEqual(str, "L")) {
    unita = PESO_L;
  } else if (strEqual(str, "N")) {
    unita = N_UNIT;
  } else {
    unita = NONE_UNIT;
  }
  return unita;
}


//da una stringa resitituisce l'enum corrispondente
//TODO: "carne","pesce" ecc.. come costanti dichiarate da qualche parte
categorie getCategoria(char* str){
	categorie cat;
	strToUpper(str);

	if( strEqual(str,"CARNE") ){
		cat = CARNE;
	}else if( strEqual(str,"PESCE") ){
		cat = PESCE;
	}else if( strEqual(str,"VERDURE") ){
		cat = VERDURA;
	}else if( strEqual(str,"PASTA") ){
		cat = PASTA;
	}else{
		cat = NONE_CAT;
	}

	return cat;
}


char *returnCategoria(categorie categoria) {
  char *s = (char *)calloc(10,sizeof(char)); // alloca dinamicamente la memoria per contenere 10 caratteri
  //NONE_CAT, CARNE, PESCE, VERDURA, PASTA

  if (categoria == NONE_CAT)
    strcpy(s, "NULL");
  else {
    if (categoria == CARNE)
      strcpy(s, "CARNE");
    else {
      if (categoria == PESCE)
        strcpy(s, "PESCE");
      else {
        if (categoria == VERDURA)
          strcpy(s, "VERDURA");
        else {
          if (categoria == PASTA)
            strcpy(s, "PASTA");
          else
            strcpy(s, "ERROR");
        }
      }
    }
  }

  return s;
}
