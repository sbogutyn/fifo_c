#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>

#include <linux/stat.h>

#define PLIK_FIFO	"serverfifo"
typedef struct Element {
	int ID;
	char nazwisko[20]; // max dlugosc 20 wraz z \0
} element;

int main(void)
{
	FILE* plik;
	FILE* plik_klienta;

	int x = 0;
	int rozmiar = 0;
	char* sciezka;

	/* Tworzymy FIFO jeżeli nie istnieje */
	umask(0);
	mknod(PLIK_FIFO , S_IFIFO|0666, 0);
	
	int i;	
	element tablica[20];
	char* nazwiska[] = {
	"Kowalski",
	"Korzeniowski",
	"Małysz",
	"Bogutyn",
	"Austen",
	"Defo",
	"Nowak",
	"Majda",
	"Skrzypczak",
	"Theis",
	"Michalski",
	"Markowski",
	"Konieczny",
	"Farbotko",
	"Nowicki",
	"Kuszlewicz",
	"Cichocki",
	"Bartyzel",
	"Kwoczek",
	"Biernat"
	};

	for (i=0; i<20;i++) {
		tablica[i].ID = i;
		strcpy(tablica[i].nazwisko, nazwiska[i]);
	}
	/*for (i=0; i<20;i++) {*/
		/*printf("%d. %s\n", tablica[i].ID, tablica[i].nazwisko);*/
	/*}*/

	while(1)
	{
		plik = fopen(PLIK_FIFO, "r");
		if (fread(&rozmiar, sizeof(int), 1, plik) == 1) {
			fread(&x, sizeof(int), 1, plik);
			int dlugosc_napisu = (rozmiar - sizeof(int))/sizeof(char); 
			sciezka = malloc(sizeof(char) * dlugosc_napisu);
			fread(sciezka, sizeof(char), dlugosc_napisu, plik);
			fclose(plik);
			printf("Otrzymany łańcuch: %d %d %s\n", dlugosc_napisu, x, sciezka);

			umask(0);
			mknod(sciezka , S_IFIFO|0666, 0);
			plik_klienta = fopen(sciezka, "w");
			if ((x > 19) || (x < 0)) {
				char* komunikat = "Nie ma";
				fwrite(komunikat, sizeof(char), strlen(komunikat), plik_klienta);
			} else {
				fwrite(nazwiska[x], sizeof(char), strlen(nazwiska[x]), plik_klienta);
			}
			fclose(plik_klienta);
			free(sciezka);
		}

		sleep(1);
	}
	return(0);
}






