/*1. Napisati program koji prvo proèita koliko redaka ima datoteka, tj.koliko ima studenata
zapisanih u datoteci.Nakon toga potrebno je dinamièki alocirati prostor za niz struktura
studenata(ime, prezime, bodovi) i uèitati iz datoteke sve zapise.Na ekran ispisati ime,
prezime, apsolutni i relativni broj bodova.
Napomena: Svaki redak datoteke sadrži ime i prezime studenta, te broj bodova na kolokviju.
relatvan_br_bodova = br_bodova / max_br_bodova * 100*/

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 100

typedef struct _studenti {
	char ime[MAX];
	char prezime[MAX];
	int bod;
}_studenti;

FILE* ucitaj_datoteku();
int broj_redaka(FILE*);
void punjenje(FILE*, _studenti*);
void ispis(_studenti*, int);

int main(void)
{
	int counter = 0;
	FILE* fp = NULL;
	fp = ucitaj_datoteku();
	counter = broj_redaka(fp);

	_studenti* ps;
	ps = malloc(counter * sizeof(_studenti));
	punjenje(fp, ps);
	ispis(ps, counter);

}

FILE* ucitaj_datoteku()
{
	return fopen("studenti.txt", "r");
}
int broj_redaka(FILE* fp)
{
	int br = 0;
	char ch;
	while (!feof(fp))
	{
		ch = fgetc(fp);
		if (ch == '\n')
			br++;
	}
	return br + 1;
}
void punjenje(FILE* fp, _studenti* ps)
{
	rewind(fp);
	_studenti* temp = ps;
	while (!feof(fp))
	{
		fscanf(fp, "%s", temp->ime);
		fscanf(fp, "%s", temp->prezime);
		fscanf(fp, "%d", &(temp->bod));
		temp++;
	}
}
void ispis(_studenti* ps, int br)
{
	for (int i = 0; i < br; i++)
	{
		printf("%s %s %d %f \n", ps->ime, ps->prezime, ps->bod, ps->bod / 100.0);
		ps++;
	}
}