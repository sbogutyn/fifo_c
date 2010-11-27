/*****************************************************************************
  Zaczerpnięto z "Linux Programmer's Guide - Rozdział 6"
  (C)opyright 1994-1995, Scott Burkett
 ***************************************************************************** 
 MODUŁ: fifoclient.c
 *****************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <string.h>
#define FIFO_FILE       "serverfifo"

typedef struct {
	int pozostala;
	int id;
	char home[0];
} klient;


int main(int argc, char *argv[])
{
	FILE* plik;
	klient* nowy;
	if ( argc != 3 ) {
		printf("UŻYCIE: klient [id] [nazwisko]\n");
		exit(1);
	}

	if((plik = fopen(FIFO_FILE, "w")) == NULL) {
		perror("fopen");
		exit(1);
	}
	
	int id = atoi(argv[1]);
	int pozostala = sizeof(id) + strlen(argv[2]) * sizeof(char);
	//	fwrite(&pozostala, sizeof(int), 1, plik);
	//fwrite(&id, sizeof(int), 1, plik);
	//fwrite(argv[2], sizeof(char), strlen(argv[2]), plik);
	
	nowy = malloc(sizeof(klient) + strlen(argv[2]));
	nowy->id = id;
	nowy->pozostala = pozostala;
	//nowyhome = malloc(sizeof(char)*strlen(argv[2]));
	strcpy(nowy->home, argv[2]);	//argv[2];

	fwrite(nowy, sizeof(klient) + strlen(argv[2]), 1, plik);
	
	//fputs(argv[1], fp);
	//fputs(argv[2] ,fp);
	//fclose(fp);
	fclose(plik);
	return(0);
}


