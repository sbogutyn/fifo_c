#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>

#include <linux/stat.h>

#define PLIK_FIFO	"serverfifo"

int main(void)
{
	int plik;
	int plik_klienta;

	int x = 0;
	int rozmiar = 0;
	char* sciezka;

	/* Tworzymy FIFO jeżeli nie istnieje */
	umask(0);
	mknod(PLIK_FIFO , S_IFIFO|0666, 0);
	
	int i;	
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
	while(1)
	{
		plik = open(PLIK_FIFO, O_RDONLY);
		if (read(plik, &rozmiar, sizeof(int))) {
			read(plik, &x, sizeof(int));
			int dlugosc_napisu = (rozmiar - sizeof(int))/sizeof(char); 
			sciezka = malloc(sizeof(char) * dlugosc_napisu);
			read(plik, sciezka, sizeof(char) * dlugosc_napisu);
			close(plik);
			printf("Otrzymane dane: %d %d %s\n", dlugosc_napisu, x, sciezka);

			umask(0);
			mknod(sciezka , S_IFIFO|0666, 0);
	
			typedef struct {
				int dlugosc;
				char wiadomosc[0];
			} komunikat;

			plik_klienta = open(sciezka, O_WRONLY);
			if ((x > 19) || (x < 0)) {
				char* tekst = "Nie ma";
				komunikat* k = malloc(sizeof(komunikat) + strlen(tekst));
				k->dlugosc = strlen(tekst);
				strcpy(k->wiadomosc, tekst);
				write(plik_klienta, k, sizeof(komunikat) + strlen(tekst));
			} else {
				komunikat* k = malloc(sizeof(komunikat) + strlen(nazwiska[x]));
				k->dlugosc = strlen(nazwiska[x]);
				strcpy(k->wiadomosc, nazwiska[x]);
				write(plik_klienta, k, sizeof(komunikat) + strlen(nazwiska[x]));
			}
			close(plik_klienta);
			free(sciezka);
		}

		sleep(1);
	}
	return(0);
}







