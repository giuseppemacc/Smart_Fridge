#include "types.h"
#include <stdio.h>
#include "gestione_ricette.h"
#include "gestione_alimenti.h"
#include "utils.h"
#include "file_names.h"
#include "menu_utente.h"



void default_piano_settimanale(){
  FILE* file_pianosettimanale;
  categorie cat;

  if( apriFile(&file_pianosettimanale, FILENAME_PIANO_SETTIMANALE, "wb+") ){

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
  int i_giorno=0;

  if(apriFile(&file_pianosettimanale, FILENAME_PIANO_SETTIMANALE, "rb+")){

    rewind(file_pianosettimanale);
    fread(&categoria_corrente, sizeof(categorie), 1, file_pianosettimanale);

    while (!feof(file_pianosettimanale)) {

      printf("GIORNO %d -> %s\n",i_giorno+1, returnCategoria(categoria_corrente) );

      i_giorno++;

      fread(&categoria_corrente, sizeof(categorie), 1, file_pianosettimanale);

    }

    fclose(file_pianosettimanale);
  }

}

void prioritarizza_ricette( t_ricetta ricette[], int n_ricette ){

  FILE* file_cronologia;
  FILE* file_piano_settimanale;

  int n_cronologia[7];
  int n_pianosettimanale[7];

  categorie tipo_cronologia;
  categorie tipo_pianosettimanale;

  if( apriFile(&file_cronologia, FILENAME_CRONOLOGIA_RICETTE, "rb+")  ){

    if( apriFile(&file_piano_settimanale, FILENAME_PIANO_SETTIMANALE, "rb+")  ){







      fclose(file_piano_settimanale);
    }


    fclose(file_cronologia);
  }


}


