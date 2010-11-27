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
	
	nowy = malloc(sizeof(klient) + strlen(argv[2]));
	nowy->id = id;
	nowy->pozostala = pozostala;
	strcpy(nowy->home, argv[2]);	//argv[2];

	fwrite(nowy, sizeof(klient) + strlen(argv[2]), 1, plik);
	
	fclose(plik);
	return(0);
}


