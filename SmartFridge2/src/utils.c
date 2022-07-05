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


// ??TODO?? apri il file se non � gi� aperto
int apriFile(FILE **file, char *file_name, char *mode) {
  int flag_open = 0;

  *file = fopen(file_name, mode);

  if ((*file) == NULL) {
    puts("file non trovato");
  } else {
    puts("."); // TODO: da togliere poi serve solo per capire che e andato tutto
               // bene
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


// TODO: capire come funziona perche ho copiato e incollato
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

