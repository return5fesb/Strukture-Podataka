/*Definirati strukturu osoba(ime, prezime, godina roðenja) i napisati program koji :
a) dinamièki dodaje novi element na poèetak liste,
b) ispisuje listu,
c) dinamièki dodaje novi element na kraj liste,
d) pronalazi element u listi(po prezimenu),
e) briše odreðeni element iz liste,
U zadatku se ne smiju koristiti globalne varijable*/

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>

#define MAX 50

typedef struct Osoba* Pozicija;
typedef struct Osoba {
	char ime[MAX];
	char prezime[MAX];
	int god;
	Pozicija next;
} Osoba;

void UnosP(Pozicija);
void UnosK(Pozicija);
Pozicija Trazi(Pozicija);
void Ispis(Pozicija);
void Brisi(Pozicija);
Pozicija TraziPret(char*, Pozicija);

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
		case 0:
			br = 0;
			break;
		default:
			printf("Nisi unio dobar broj\n");
			continue;
		}
	}


}


void UnosP(Pozicija p)
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
}

void UnosK(Pozicija p)
{
	Pozicija q;
	q = (Pozicija)malloc(sizeof(struct Osoba));

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

void Ispis(Pozicija p)
{
	while (p != NULL)
	{
		printf("%s %s %d\n", p->ime, p->prezime, p->god);
		p = p->next;
	}
}

void Brisi(Pozicija p)
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