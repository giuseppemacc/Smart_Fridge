#include "gestione_ricette.h"
#include "gestione_alimenti.h"
#include "menu_utente.h"
#include "utils.h"
#include "piano_settimanale.h"
#include "check_input.h"
#include "file_names.h"
#include "types.h"

#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>



//todo: isNotNum

//todo: ricerca binaria per i file
//todo: rimuovere preparata ultimi 7 giorni

//todo: capire come funziona strUpper perche ho copiato e incollato
//todo: capire le ifdef


//todo: tipo t_bool, t_unita ...
//todo: commenti
//todo: doxygen
//todo: messaggi all utente
//todo: riempire i file



int main(void) {
	setvbuf(stdout, NULL, _IONBF, 0);


	//clearFile(FILENAME_CRONOLOGIA_RICETTE);

	menuu();








	//print_alimenti(FILENAME_ALIMENTI);

	//print_alimento(al);



	//menu();

	//clearFile(FILENAME_CRONOLOGIA_RICETTE);

	//FILE* file;
	/*
	if(apriFile(&file, FILENAME_RICETTE, "wb+")){

		rewind(file);


		t_ricetta ric = {"ok_1",1, {}, CARNE, "sooooooos", 0, 0, 10 };
		fwrite(&ric, sizeof(t_ricetta), 1, file);

		t_ricetta ric1 = {"ok_2",1, {}, CARNE, "sografoos", 0, 0, 10 };
		fwrite(&ric1, sizeof(t_ricetta), 1, file);

		t_ricetta ric2 = {"ok_3",1, {}, CARNE, "sooooooos", 0, 0, 10 };
		fwrite(&ric2, sizeof(t_ricetta), 1, file);

		t_ricetta ric3 = {"ok_4",1, {}, CARNE, "sooasdooos", 0, 0, 10 };
		fwrite(&ric3, sizeof(t_ricetta), 1, file);

		t_ricetta ric4 = {"ok_5",1, {}, CARNE, "sooooooos", 0, 0, 10 };
		fwrite(&ric4, sizeof(t_ricetta), 1, file);

		t_ricetta ric5 = {"ok_6",1, {}, CARNE, "sooooooos", 0, 0, 10 };
		fwrite(&ric5, sizeof(t_ricetta), 1, file);

		fclose(file);
	}*/





	//print_ricette(FILENAME_RICETTE);



	/*
	int flag_errore;
	int flag_home;

	do{
		char str[20];

		//inputStr(str, 20, &flag_errore, &flag_home);
		//int num = inputInt(&flag_errore, &flag_home);//(int)atoi(str);
		int num = inputBool(&flag_errore, &flag_home);

		if(num==10){
			puts("aoooo");
		}

		//isNotNum(str, &flag_errore);

		printf("num: %d, str: %s,  errore: %d,   home: %d\n", num, str, flag_errore, flag_home);

	}while(1);*/






	//menu();

	return 0;
}





/*  ALTRA GRANDE SALVEZZA
 *
 *
if(apriFile(&file, FILENAME_RICETTE, "rb+")){
		rewind(file);

		t_ricetta ric_corrente;
		int i=0;

		rewind(file);
		fread(&ric_corrente, sizeof(t_ricetta), 1, file);

		while( !(feof(file)) ){


			ric_corrente.counter_giorni += 1;
			//print_ricetta(ric_corrente);
			fseek(file, -sizeof(t_ricetta), SEEK_CUR);
			fwrite(&ric_corrente, sizeof(t_ricetta), 1, file);
			i++;



			fseek(file, i*sizeof(t_ricetta), SEEK_SET);
			fread(&ric_corrente, sizeof(t_ricetta), 1, file);
		}

		fclose(file);
	}


*/




/* LA SALVEZZA

t_ricetta ric_corrente;
int i=0;

fread(&ric_corrente, sizeof(t_ricetta), 1, file);
ric_corrente.counter_giorni += 1;
//print_ricetta(ric_corrente);
fseek(file, -sizeof(t_ricetta), SEEK_CUR);
fwrite(&ric_corrente, sizeof(t_ricetta), 1, file);
i++;


fseek(file, i*sizeof(t_ricetta), SEEK_SET);


fread(&ric_corrente, sizeof(t_ricetta), 1, file);
ric_corrente.counter_giorni += 1;
//print_ricetta(ric_corrente);
fseek(file, -sizeof(t_ricetta), SEEK_CUR);
fwrite(&ric_corrente, sizeof(t_ricetta), 1, file);
i++;


fseek(file, i*sizeof(t_ricetta), SEEK_SET);


fread(&ric_corrente, sizeof(t_ricetta), 1, file);
ric_corrente.counter_giorni += 1;
//print_ricetta(ric_corrente);
fseek(file, -sizeof(t_ricetta), SEEK_CUR);
fwrite(&ric_corrente, sizeof(t_ricetta), 1, file);
i++;


fseek(file, i*sizeof(t_ricetta), SEEK_SET);


fread(&ric_corrente, sizeof(t_ricetta), 1, file);
ric_corrente.counter_giorni += 1;
//print_ricetta(ric_corrente);
fseek(file, -sizeof(t_ricetta), SEEK_CUR);
fwrite(&ric_corrente, sizeof(t_ricetta), 1, file);
i++;


fseek(file, i*sizeof(t_ricetta), SEEK_SET);


fread(&ric_corrente, sizeof(t_ricetta), 1, file);
ric_corrente.counter_giorni += 1;
//print_ricetta(ric_corrente);
fseek(file, -sizeof(t_ricetta), SEEK_CUR);
fwrite(&ric_corrente, sizeof(t_ricetta), 1, file);
i++;


fseek(file, i*sizeof(t_ricetta), SEEK_SET);


fread(&ric_corrente, sizeof(t_ricetta), 1, file);
ric_corrente.counter_giorni += 1;
//print_ricetta(ric_corrente);
fseek(file, -sizeof(t_ricetta), SEEK_CUR);
fwrite(&ric_corrente, sizeof(t_ricetta), 1, file);
i++;



fseek(file, i*sizeof(t_ricetta), SEEK_SET);
fread(&ric_corrente, sizeof(t_ricetta), 1, file);

printf("feof:%d\n", feof(file));

		*/













//t_ricetta ricette[13] = {
//			{"ok",1, {}, CARNE, "sooooooos", 0, 0, 10 },
//			{"lol",1, {}, PESCE, "1", 0, 0, 1 },
//			{"lol",1, {}, VERDURA, "2", 0, 0, 2 },
//			{"ok",1, {}, CARNE, "sooooooos", 0, 0, 40 },
//			{"ok",1, {}, CARNE, "sooooooos", 0, 0, 30 },
//			{"ok",1, {}, CARNE, "sooooooos", 0, 0, 20 },
//			{"lol",1, {}, PASTA, "3", 0, 0, 3 },
//			{"lol",1, {}, PASTA, "4", 0, 0, 4 },
//			{"ok",1, {}, CARNE, "sooooooos", 0, 0, 60 },
//			{"ok",1, {}, CARNE, "sooooooos", 0, 0, 50 },
//			{"lol",1, {}, PESCE, "5", 0, 0, 2 },
//			{"lol",1, {}, VERDURA, "6", 0, 0, 3 },
//			{"ok",1, {}, CARNE, "sooooooos", 0, 0, 1 }
//	};
//
//	default_piano_settimanale();
//
//	ordina_arrRicette_4giorni(ricette, 13);
//
//	shift_arrRicette_4cat(ricette, 13, return_categoria_giorno_attuale());
//
//	//print_arr_ricette(ricette, 13);






//menuu();

//	char str1[] = "PallealSugo";
//    char str2[] = "sos";
//
//    int a = sottostrEqual(str1, str2);
//
//
//
//    printf("%d\n", a);






//menuu();

/*
int flag_home=0;
int flag_errore=0;
do{
	flag_home=0;
	flag_errore=0;

	char str[6];
	inputStr(str, 6, &flag_errore, &flag_home);
	printf("%s  errore:%d   home:%d  equal:%d\n", str ,flag_errore, flag_home, strEqual(str, "-1"));
	for(int i=0; i < strlen(str); i++){
		printf("%d\t",str[i]);
	}
	puts("");
}while(1);*/

//menuu();

//TODO: funzione che controlla l esistenza dei file e li crea altrimenti

//print_alimenti();

//caricaAlimenti();

//print_alimenti();
/*
do{
	char str[6];
	int len;

	fgets(str, 5, stdin);
	len = strlen(str);
	printf("len: %d  %s\n", len ,str);

	fflush(stdin);


	fgets(str, 5, stdin);
	len = strlen(str);
	printf("len: %d  %s\n", len ,str);
	*/

//}while(1);


//menuu();

/*
int flag_home=0;
int flag_errore=0;

do{
	flag_home = 0;
	//int n = inputInt(&flag_errore, &flag_home);
	t_ricetta ric = inputRicetta(&flag_home);
	print_ricetta(ric);
	//char str[20];

	//inputStr(str, 20, &flag_errore, &flag_home);
	//isNotNum(str, &flag_errore);

	printf("\n  errore:%d   home:%d\n",  flag_errore, flag_home);

}while( 1 );*/



//menu();

	/*
  int flag_home=0;
  int flag_errore=0;
  char str[20];

  do{
	  caricaAlimenti();
  }while(1);
	*/

  /*
  do{
    flag_home = 0;
    flag_errore = 0;
    char str[20];
    scanf("%s", str);
    isNotNum(str, &flag_errore);
    printf("!!errore: %d\n", flag_errore);
  }while(1);*/

  //unita_misura unit  = inputUnitaMisura(&flag_errore, &flag_home);
  //printf("\n%d  errore:%d   home:%d\n", unit, flag_errore, flag_home);
  /*
  do{
    float qua  = inputFloat(&flag_errore, &flag_home);
    printf("\n%f  errore:%d   home:%d\n\n", qua, flag_errore, flag_home);
  }while(1);*/
  /*
  do{
    flag_home = 0;
    flag_errore = 0;
    t_alimento al = inputAlimento(&flag_home);
    //t_alimento al = inputAlimento(&flag_home);
    //inputStr(str,50, &flag_errore, &flag_home);

    puts("----alimento---");
    print_alimento(al);
    puts("---------------");
    printf("errore:%d   home:%d\n\n\n", flag_errore, flag_home);
  }while(1);*/
