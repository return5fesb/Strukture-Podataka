/*Prethodnom zadatku dodati funkcije :
a) dinamièki dodaje novi element iza odreðenog elementa,
b) dinamièki dodaje novi element ispred odreðenog elementa,
c) sortira listu po prezimenima osoba,
d) upisuje listu u datoteku,
e) èita listu iz datoteke.*/

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>

#define MAX 50

typedef struct Osoba* Pozicija;
typedef struct Osoba {
	char ime[MAX];
	char prezime[MAX];
	int god;
	Pozicija next;
} Osoba;

int UnosP(Pozicija);
int UnosK(Pozicija);
Pozicija Trazi(Pozicija);
int Ispis(Pozicija);
int Brisi(Pozicija);
Pozicija TraziPret(char*, Pozicija);
int UnosIza(Pozicija);
int UnosIspred(Pozicija);
int Sortiraj(Pozicija);
int UpisUDat(Pozicija);
int CitajIzDat(Pozicija);
int Ubaci(Pozicija, char*, char*, int);

int main(void)
{
	Osoba Head;
	Head.next = NULL;
	Osoba* P = NULL;

	int br = 1;
	int unosKorisnika = 0;

	while (br)
	{
		printf("Postovani korisnice, izaberite opciju:\n\n");
		printf("1 - dodaj osobu na pocetak liste\n");
		printf("2 - ispisi listu osoba\n");
		printf("3 - dodaj osobu na kraj liste\n");
		printf("4 - pronadi osobu po prezimenu u listi\n");
		printf("5 - brisi osobu iz liste\n");
		printf("6 - dodaj osobu iza odredene osobe\n");
		printf("7 - dodaj osobu ispred odredene osobe\n");
		printf("8 - sortiraj listu po prezimenima\n");
		printf("9 - ispisi listu osoba u file\n");
		printf("10 - procitaj listu iz datoteke\n");
		printf("0 - gotov sam s radnjama\n");
		scanf("%d", &unosKorisnika);
		switch (unosKorisnika)
		{
		case 1:
			UnosP(&Head);
			break;
		case 2:
			Ispis(Head.next);
			break;
		case 3:
			UnosK(&Head);
			break;
		case 4:
			P = Trazi(Head.next); //u njega spremam onog kojeg nadem
			printf("%s %s %d", P->ime, P->prezime, P->god);
			break;
		case 5:
			Brisi(&Head);
			break;
		case 6:
			UnosIza(&Head);
			break;
		case 7:
			UnosIspred(&Head);
			break;
		case 8:
			Sortiraj(&Head);
			break;
		case 9:
			UpisUDat(&Head);
			break;
		case 10:
			CitajIzDat(&Head);
			break;
		case 0:
			br = 0;
			break;
		default:
			printf("Nisi unio dobar broj\n");
			continue;
		}
	}
	return 0;

}


int UnosP(Pozicija p)
{
	Pozicija q;
	q = (Pozicija)malloc(sizeof(struct Osoba));

	printf("Unesi ime: ");
	scanf("%s", q->ime);
	printf("Unesi prezime: ");
	scanf("%s", q->prezime);
	printf("Unesi godinu rodenja: ");
	scanf("%d", &(q->god));

	q->next = p->next;
	p->next = q;

	return 0;
}

int UnosK(Pozicija p)
{
	Pozicija q;
	q = (Pozicija)malloc(sizeof(Osoba));

	printf("Unesi ime: ");
	scanf("%s", q->ime);
	printf("Unesi prezime: ");
	scanf("%s", q->prezime);
	printf("Unesi godinu rodenja: ");
	scanf("%d", &(q->god));

	while (p->next != NULL)
		p = p->next;

	q->next = p->next;
	p->next = q;

	return 0;
}

Pozicija Trazi(Pozicija p)
{
	char prezime[MAX];
	printf("Unesi prezime osobe koju zelis pronaci: ");
	scanf("%s", prezime);
	while (p != NULL && strcmp(p->prezime, prezime))
	{
		p = p->next;
	}

	return p;
}

int Ispis(Pozicija p)
{
	while (p != NULL)
	{
		printf("%s %s %d\n", p->ime, p->prezime, p->god);
		p = p->next;
	}
	return 0;
}

int Brisi(Pozicija p)
{
	char prezime[MAX];
	printf("Unesi prezime osobe koju zelis izbrisati: ");
	scanf("%s", prezime);

	Pozicija temp;
	Pozicija s = TraziPret(prezime, p);

	if (s == NULL)
		printf("\nOsoba ne postoji");
	else
	{
		temp = s->next;
		s->next = s->next->next;
		free(temp);
	}
	return 0;
}

Pozicija TraziPret(char* prezime, Pozicija p)
{
	Pozicija pret = p;
	p = p->next;
	while (p != NULL && strcmp(p->prezime, prezime))
	{
		pret = p;
		p = p->next;
	}
	if (p == NULL)
		return NULL;
	else
		return pret;
}

int UnosIza(Pozicija p)
{
	Pozicija q;
	q = (Pozicija)malloc(sizeof(Osoba));
	char prezime[MAX];

	p = p->next;

	printf("Unesite prezime iza kojeg zelite upisati novu osobu: ");
	scanf("%s", prezime);

	while (p != NULL && strcmp(p->prezime, prezime))
		p = p->next;
	if (p == NULL)
		printf("Prezime ne postoji u listi! (Greska)");
	else
	{
		q = (Pozicija)malloc(sizeof(Osoba));
		strcpy(q->prezime, prezime);

		printf("Unesi ime: ");
		scanf("%s", q->ime);
		printf("Unesi prezime: ");
		scanf("%s", q->prezime);
		printf("Unesi godinu rodenja: ");
		scanf("%d", &(q->god));

		q->next = p->next;
		p->next = q;
	}

	return 0;
}

int UnosIspred(Pozicija p)
{
	Pozicija q;
	q = (Pozicija)malloc(sizeof(Osoba));
	char prezime[MAX];

	printf("Unesite prezime ispred kojeg zelite upisati novu osobu: ");
	scanf("%s", prezime);

	Pozicija s = TraziPret(prezime, p);

	if (s == NULL)
		printf("Prezime ne postoji (greska)");
	else
		UnosP(s);

	return 0;
}

int Sortiraj(Pozicija p)
{
	Pozicija temp = p;
	Pozicija i = NULL;
	Pozicija prev = NULL;
	Pozicija kraj = NULL;

	while (temp->next != kraj)
	{
		prev = temp;
		i = prev->next;
		while (i->next != kraj)
		{
			if (strcmp(i->prezime, i->next->prezime) > 0)
			{
				prev->next = i->next;
				i->next = i->next->next;
				prev->next->next = i;
				i = prev->next;
			}
			prev = i;
			i = i->next;
		}
		kraj = i;
	}
	return 0;
}

int UpisUDat(Pozicija p)
{
	char* imedat = NULL;
	FILE* fp;

	imedat = (char*)malloc(20 * sizeof(char));
	if (imedat == NULL)
		return 1;

	printf("Ime datoteke u koju zelite upisati listu: ");
	scanf(" %s", imedat);

	fp = fopen(imedat, "w+");
	if (fp == NULL)
		return 1;

	while (p->next != NULL)
	{
		fprintf(fp, "%s %s %d\n", p->next->ime, p->next->prezime, p->next->god);

		p = p->next;
	}

	fclose(fp);
	free(imedat);

	return 0;
}

int CitajIzDat(Pozicija p)
{
	FILE* fp;
	char* ime = NULL;
	char* prezime = NULL;
	int god = 0;
	char* imedat = NULL;

	imedat = (char*)malloc(20 * sizeof(char));
	if (imedat == NULL)
		return 1;
	ime = (char*)malloc(20 * sizeof(char));
	if (ime == NULL)
		return 1;
	prezime = (char*)malloc(20 * sizeof(char));
	if (prezime == NULL)
		return 1;

	printf("Upisite ime datoteke: ");
	scanf(" %s", imedat);

	fp = fopen(imedat, "r");
	if (fp == NULL)
	{
		printf("Greska");
		return 1;
	}

	while (!feof(fp))
	{
		fscanf(fp, "%s %s %d\n", ime, prezime, &god);
		Ubaci(p, ime, prezime, god);
	}
	fclose(fp);
	free(imedat);

	return 0;

}
int Ubaci(Pozicija p, char* buffime, char* buffprezime, int god)
{
	Pozicija q = NULL;

	q = (Pozicija)malloc(sizeof(Osoba));
	q->ime = (char*)malloc(20 * sizeof(char*));
	q->prezime = (char*)malloc(20 * sizeof(char*));

	q->next = NULL;

	strcpy(q->ime, buffime);
	strcpy(q->prezime, buffprezime);
	q->god = god;

	q->next = p->next;
	p->next = q;

	return 0;
}