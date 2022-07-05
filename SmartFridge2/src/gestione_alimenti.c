#include "file_names.h"
#include "types.h"
#include "check_input.h"
#include "utils.h"
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>



int ricerca_alimento(char *nome, t_alimento *alimento, FILE *file_alimenti) {
  int flag_alimento_trovato = 0;
  t_alimento alimento_corrente;

  strToUpper(nome);

  // cerca nel file alimenti e ritorna 1/0 se lo trova e lo setta in *alimento
  rewind(file_alimenti);
  fread(&alimento_corrente, sizeof(t_alimento), 1, file_alimenti);

  while (!feof(file_alimenti) && (flag_alimento_trovato == 0)) {
    if (strcmp(alimento_corrente.nome, nome) == 0) {
      flag_alimento_trovato = 1;
      *alimento = alimento_corrente;
      fseek(file_alimenti, -1 * sizeof(t_alimento),
            SEEK_CUR); // sposta di uno indietro
    } else {
      fread(&alimento_corrente, sizeof(t_alimento), 1, file_alimenti);
    }
  }
  return flag_alimento_trovato;
}

t_alimento inputAlimento(int *flag_home) {
  int flag_errore;
  t_alimento alimento;
  float f_quantita=0;

  flag_errore = 0;
  *flag_home = 0;


  //---NOME---

  do{
    printf("\tnome >> ");
    inputStr(alimento.nome, 50, &flag_errore, &(*flag_home) );


    if( ! (*flag_home) ){ // se non � stato detto di tornare alla home

      // controlla se sono avvenuti errori
      if( ! flag_errore ){
        strToUpper(alimento.nome);
      }

    }

  }while( (flag_errore == 1) && ((*flag_home) == 0) );



  //---UNITA DI MISURA---

  if (!(*flag_home)) { // se non � stato detto di tornare alla home
    // input unit� misura
    do {
      printf("\tunita di misura>> ");

      alimento.unita = inputUnitaMisura(&flag_errore, &(*flag_home));

      if(flag_errore){
        printf("\tunit� di misura non trovata (disponibili:g,kg,ml,l,n)\n");
      }

    } while ((flag_errore == 1) && ((*flag_home) == 0));
  }


  //---QUANTITA'---

  if (!(*flag_home)) { // se non � stato detto di tornare alla home
    // input quantit�
    do {
      printf("\tquantità>> ");

      f_quantita = inputFloat(&flag_errore, &(*flag_home));


      if( ! (*flag_home) ){ // se non � stato detto di tornare alla home

                  // controlla se sono avvenuti errori
        //NULL
        if( ! flag_errore ){

          // altri controlli cio� i vari check
          checkQuantita(f_quantita,  &flag_errore  ); // controlla che sia > 0

          if( ! flag_errore ){
            if ((alimento.unita == PESO_KG) || (alimento.unita == PESO_L)) { // se kg/lt si convertono in g/ml

              alimento.quantita = (int)(f_quantita * 1000);
              alimento.unita = alimento.unita - 1;
            } else {
              //Ci troviamo nei casi in cui alimento.unita=g/ml/n_elementii
              checkFloat( f_quantita, &flag_errore);

              if( flag_errore ){
                printf("\tERRORE! Le unit� di misura g  ml  n_elementi non possono avere numeri decimali\n");
              }
              else{
                alimento.quantita = (int)f_quantita;
              }

            }
          }

        }

      }

    } while ((flag_errore == 1) && ((*flag_home) == 0));
  }

  return alimento;
}

void ordinaFileAlimenti_AZ(char *file_name) {

  FILE *file;

  t_alimento j_alimento;
  t_alimento i_alimento;
  t_alimento min_alimento;


  int i = 0;
  int i_min;
  int j;

  if (apriFile(&file, file_name, "rb+")) {
    rewind(file);

    //-----
    fread(&i_alimento, sizeof(t_alimento), 1, file);
    min_alimento = i_alimento;
    //-----

    while (!feof(file)) {
      // TODO: levare//printf("->%s  i:%d\n", i_alimento.nome, i);

      fread(&j_alimento, sizeof(t_alimento), 1, file);
      j = i + 1;
      min_alimento = i_alimento;
      i_min = i;

      while (!feof(file)) {

        // TODO: levare//printf("\t%s  j:%d\n", j_alimento.nome, j);

        if (strMin(j_alimento.nome, min_alimento.nome)) {
          min_alimento = j_alimento;
          i_min = j;
        }

        fread(&j_alimento, sizeof(t_alimento), 1, file);
        j++;
      }

      // TODO: levare//printf("\tmin_al:%s  i_min:%d\n", min_alimento.nome,
      // i_min);

      // file[i_min] = i_alimento
      fseek(file, i_min * sizeof(t_alimento), SEEK_SET);
      fwrite(&i_alimento, sizeof(t_alimento), 1, file);

      // file[i] = min_alimento
      fseek(file, (i) * sizeof(t_alimento), SEEK_SET);
      fwrite(&min_alimento, sizeof(t_alimento), 1, file);

      //----

      i++;
      fseek(file, i * sizeof(t_alimento), SEEK_SET);
      fread(&i_alimento, sizeof(t_alimento), 1, file);
      min_alimento = i_alimento;
      //-----
    }

    fclose(file);
  }
}

void print_alimento(t_alimento alimento) {
  printf("\t%s:", alimento.nome);
  // se g/ml>=1000 si stampa convertito in kg/lt
  if ((alimento.unita == PESO_GR) || (alimento.unita == PESO_ML)) {
    if (alimento.quantita >= 1000) {
      printf("  %.3f %s\n", (float)(((float)alimento.quantita) / 1000.0),
             returnUnita(alimento.unita + 1));
    } else
      printf("  %d %s\n", alimento.quantita, returnUnita(alimento.unita));
  } else
    printf("  %d %s\n", alimento.quantita, returnUnita(alimento.unita));
}

void print_alimenti() {
  t_alimento alimento_corrente;
  FILE *file_alimenti;

  if (apriFile(&file_alimenti, FILENAME_ALIMENTI, "rb+")) {
    rewind(file_alimenti);
    fread(&alimento_corrente, sizeof(t_alimento), 1, file_alimenti);

    while (!feof(file_alimenti)) {
      if (strcmp(alimento_corrente.nome, "") != 0) {
        print_alimento(alimento_corrente);
      }
      fread(&alimento_corrente, sizeof(t_alimento), 1, file_alimenti);
    }

    fclose(file_alimenti);
  }
}

// TODO: chiedere all utente di modificare l'alimento e modificarlo
void modifica_alimenti() {
  int input;
  char str[50];
  t_alimento alimento;
  FILE *file_alimenti; // frigo

  do {

    printf("Inserisci il nome dell'alimento da modificare/rimuovere >> ");
    scanf("%s", str);

    if (apriFile(&file_alimenti, FILENAME_ALIMENTI, "r+")) {

      if (ricerca_alimento(str, &alimento, file_alimenti)) {

        print_alimento(alimento);
        puts("[1] elimina alimento");
        puts("[2] modifica alimento");
        scanf("%d", &input);

        // elimina alimento
        if (input == 1) {
          strcpy(alimento.nome, "");
        }

        // modifica alimento
        if (input == 2) {
          // TODO: chiedere qui all utente cosa e di quanto modificare
          alimento.quantita += 100;
        }

        fwrite(&alimento, sizeof(t_alimento), 1, file_alimenti);

      } else {
        puts("alimento non trovato");
      }

      fclose(file_alimenti);
    }

    print_alimenti();

    printf("Modificare/Eliminare un altro alimento? [si:1, no:0] >> ");
    scanf("%d", &input);

  } while (input == 1);
}


void caricaAlimenti() {
  int flag_home;
  int flag_continue;
  int flag_errore;
  t_alimento alimento;
  t_alimento alimento_trovato;
  FILE* file_alimenti;

  do {
    flag_home = 0;
    flag_continue = 0;
    flag_errore = 0;

    printf("inserisci alimento:\n");
    alimento = inputAlimento(&flag_home);

    if (!flag_home) {
    	if( apriFile(&file_alimenti, FILENAME_ALIMENTI, "rb+") ){

    		if( ricerca_alimento(alimento.nome, &alimento_trovato, file_alimenti) ){
				if( alimento.unita == alimento_trovato.unita ){
					alimento.quantita += alimento_trovato.quantita;
				}else{
					flag_errore = 1;
					flag_continue = 1; // cioè che glielo fa rinserire
					 printf("ERRORE! %s gia'  esistente espresso in unita'  di misura differente\n",alimento.nome);
				}
			}else{
				fseek(file_alimenti, 0, SEEK_END); // posiziona alla fine
			}

		   if (!flag_errore ) {

				fwrite(&alimento, sizeof(t_alimento), 1, file_alimenti);

				do{
				  printf("  inserire altri alimenti? >> ");
				  flag_continue = inputBool(&flag_errore, &flag_home);

			  }while( (flag_errore == 1) && (flag_home == 0) );

			}

    		fclose(file_alimenti);
    	}

    }

  } while ((flag_continue == 1) && (flag_home == 0));
}


// TODO: aggiungere ricerca su sottostringa (?? e forse cercavi ... ??)
/*dato che dobbiamo visualizzare gli alimenti in ordine alfabetico possiamo
 * pensare di ordinare direttamente il file_alimenti e usare qui la ricerca
 * binaria*/


