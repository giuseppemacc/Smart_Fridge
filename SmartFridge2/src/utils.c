#include "file_names.h"
#include "types.h"
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// ritorna 1 str1 == str2
int strEqual(char *str1, char *str2) {
  int flag_equal;
  if (strcmp(str1, str2) == 0) {
    flag_equal = 1;
  } else {
    flag_equal = 0;
  }
  return flag_equal;
}

// str1 stringa in cui cercare
// str2 stringa da cercare
int sottostrEqual(char * str1, char* str2){

	int flag_equal;

	flag_equal = 0;

	char* str = strstr(str1,str2);

	if( str != NULL){
		flag_equal = 1;
	}

	return flag_equal;
}

// ritorna 1 se str1 < str2 (dal punto di vista alfabetico)
int strMin(char *str1, char *str2) {
  int str1_len = strlen(str1);
  int str2_len = strlen(str2);
  int str_min = (str1_len <= str2_len) ? str1_len : str2_len;

  int i = 0;
  int flag_min = -1;

  while (i < str_min && (flag_min == -1)) {
    // printf("str1:%c  str2:%c\n", str1[i], str2[i]);
    if (str1[i] > str2[i]) {
      flag_min = 0;
    } else if (str1[i] < str2[i]) {
      flag_min = 1;
    }
    i++;
  }
  // flag_min == 0 ==> str1>str2
  // flag_min == 1 ==> str1<str2
  // flag_min ==-1 ==> str1==str2 (per i primi str_min caratteri)

  // se sottostringa uguale e str1_len > str2_len  ==> 0
  // se sottostringa uguale e str1_len == str2_len  ==> 0
  if (flag_min == -1) {
    if (str1_len > str2_len) {
      flag_min = 0;

    } else if (str1_len == str2_len) {
      flag_min = 0;
    } else {
      flag_min = 1;
    }
  }

  return flag_min;
}


int apriFile(FILE **file, char *file_name, char *mode) {
  int flag_open = 0;

  *file = fopen(file_name, mode);

  if ((*file) == NULL) {
    puts("file non trovato");
  } else {

    flag_open = 1;
  }
  return flag_open;
}

void clearFile(char *file_name) {
  // ------ resetta il file ---------------
  FILE *f;
  if (apriFile(&f, file_name, "wb+")) {
    printf("%s pulito\n", file_name);
    fclose(f);
  }
}



void strToUpper(char *str) {
  char *name;
  name = strtok(str, ":");

  // Convert to upper case
  char *s = name;
  while (*s) {
    *s = toupper((unsigned char)*s);
    s++;
  }
}




/*RESTITUISCE:  1 = quantita < 0
                0 = quantita > 0*/
void isPositive(float quantita,int* flag_errore){
  *flag_errore = 0;

  if (quantita <= 0){
    *flag_errore = 1;
    printf("ERRORE! La quantit� deve essere positiva\n");
  }
}


// ritorna 1 se è float
void checkFloat(float quantita_float, int *flag_errore) {
  int quantita_int;
  *flag_errore = 0;


  quantita_int = (int)quantita_float; // viene fatto il cast(int), quindi se
                                      // quantita_float=2.30, quantita_int=2

  if (quantita_float > quantita_int) {
    *flag_errore = 1;
  }
}


/*RESTITUISCE 1 = la stringa passata non � composta da soli numeri
              0 = la stringa passata � composta da soli numeri */
void isNum(char *str, int *flag_errore) {
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
