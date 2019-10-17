/*Definirati strukturu osoba(ime, prezime, godina roðenja) i napisati program koji :
a) dinamièki dodaje novi element na poèetak liste,
b) ispisuje listu,
c) dinamièki dodaje novi element na kraj liste,
d) pronalazi element u listi(po prezimenu),
e) briše odreðeni element iz liste,
U zadatku se ne smiju koristiti globalne varijable*/


#include <stdio.h>
#include <stdlib.h>

#define MAX 50

typedef struct Osoba* Pozicija;
struct Osoba {
	char ime[MAX];
	char prezime[MAX];
	int god;
	Pozicija next;
};

void UnosP(char*, char*, int, Pozicija);
void UnosK(char*, char*, int, Pozicija);
Pozicija Trazi(char*, Pozicija);
void IspisP(Pozicija);

int main(void)
{
	struct Osoba Head, *t;
	Head.next = NULL;



	UnosP("Ante", "Antic", 1998, &Head);
	UnosP("Ivan", "Ivic", 1999, &Head);
	UnosK("Petar", "Peric", 1995, &Head);
	t = Trazi("Ivic", Head.next);
	IspisP(Head.next);

	printf("\n%s\n", t);
}
void UnosP(char* ime, char* prezime, int god, Pozicija p)
{
	
	Pozicija q;
	q = (Pozicija)malloc(sizeof(struct Osoba));

	strcpy(q->ime, ime);
	strcpy(q->prezime, prezime);

	q->god = god;

	q->next = p->next;
	p->next = q;
}

void UnosK(char* ime, char* prezime, int gr, Pozicija p)
{
	Pozicija q;
	q = (Pozicija)malloc(sizeof(struct Osoba));

	strcpy(q->ime, ime);
	strcpy(q->prezime, prezime);

	q->god = gr;

	while (p->next != NULL)
		p = p->next;

	q->next = p->next;
	p->next = q;
}

Pozicija Trazi(char* prezime, Pozicija p)
{
	while (p != NULL && p->prezime != prezime)
	{
		p = p->next;
	}

	return p;
}

void IspisP(Pozicija p)
{
	while (p != NULL)
	{
		printf("%s %s %d\n", p->ime, p->prezime, p->god);
		p = p->next;
	}
}