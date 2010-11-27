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
	int plik;
	int plik_klienta;
	klient* nowy;
	if ( argc != 3 ) {
		printf("UŻYCIE: klient [id] [nazwisko]\n");
		exit(1);
	}
	if  ((plik = open(FIFO_FILE, O_WRONLY)) == -1) {
		perror("fopen");
		exit(1);
	}
	
	int id = atoi(argv[1]);
	int pozostala = sizeof(id) + strlen(argv[2]) * sizeof(char);
	
	nowy = malloc(sizeof(klient) + strlen(argv[2]));
	nowy->id = id;
	nowy->pozostala = pozostala;
	strcpy(nowy->home, argv[2]);	//argv[2];

	write(plik, nowy, sizeof(klient) + strlen(argv[2]));
	
	close(plik);


	while ((plik_klienta = open(argv[2], O_RDONLY)) == -1) {
		perror("fopen");
		//exit(1);
	}
	int dlugosc_odpowiedzi;
	read(plik_klienta, &dlugosc_odpowiedzi, sizeof(int));
	char* nazwisko = malloc(dlugosc_odpowiedzi * sizeof(char));
	read(plik_klienta, nazwisko, sizeof(char) * dlugosc_odpowiedzi);
	close(plik_klienta);
	printf("Otrzymana odpowiedz: %s\n", nazwisko);
	return(0);
}



