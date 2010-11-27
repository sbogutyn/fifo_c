CC=gcc
KLIENT=klient
SERWER=serwer


all: klient serwer

klient: ${KLIENT}.c
	$(CC) ${KLIENT}.c -o ${KLIENT}.o

serwer: serwer.c
	$(CC) ${SERWER}.c -o ${SERWER}.o

clean:
	rm -f ${KLIENT}.o ${SERWER}.o serverfifo
