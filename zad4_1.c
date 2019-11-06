#include <stdio.h>
#include <stdlib.h>

struct _polinom;
typedef struct _polinom *pozicija;
typedef struct _polinom {
	int koef;
	int exp;
	pozicija next;
}_POLINOM;

int readFromFile(pozicija p, char *name);
pozicija createNew();
int ispis(pozicija p);
int suma(pozicija suma, pozicija p, pozicija q);
int pomnozi(pozicija pomnozi, pozicija p, pozicija q);
int ubaci(pozicija p, pozicija q);
int kopiraj(pozicija p, pozicija q);
int obrisiSve(pozicija p);

int main()
{
	FILE *f;
	_POLINOM head1, head2, headSuma, headPomnozi;
	head1.next = head2.next = headSuma.next = headPomnozi.next = NULL;
	
	readFromFile(&head1, "poli1.txt");
	readFromFile(&head2, "poli2.txt");

	suma(&headSuma, head1.next, head2.next);
	pomnozi(&headPomnozi, head1.next, head2.next);
	printf("MNOZENJE:\n");
	ispis(headPomnozi.next);
	printf("\nZBRAJANJE:\n");
	ispis(headSuma.next);
	//printf("\n----------------\n");
	//ispis(head1.next);
	obrisiSve(&head1);
	obrisiSve(&head2);
	obrisiSve(&headSuma);
	obrisiSve(&headPomnozi);
	printf ("%p", head1.next);

	system("pause");
	return 0;
}

pozicija createNew()
{
	pozicija q = (pozicija)malloc(sizeof(_POLINOM));
	if (q == NULL) {
		printf("Greska pri alociranju memorije!\n");
		return NULL;
	}
	q->next = NULL;
	return q;
}

int kopiraj(pozicija p, pozicija q)
{
	p->exp = q->exp;
	p->koef = q->koef;
	return 0;
}

int ubaci(pozicija p, pozicija q)
{
	q->next = p->next;
	p->next = q;
}

int ispis(pozicija p)
{
	while (p != NULL) {
		printf("%d %d\n", p->koef, p->exp);
		p = p->next;
	}
}

int readFromFile(pozicija p, char *name)
{

	pozicija q = NULL, tmp = NULL;
	FILE *f = fopen(name, "r");
	if (f == NULL) {
		printf("Greska pri otvaranju filea!\n");
		return 1;
	}
	while (!feof(f)) {
		tmp = p;
		q = createNew();
		if (q == NULL)
			return 1;
		fscanf(f, " %d %d", &q->koef, &q->exp);
		if (q->koef == 0) {
			free(q);
			continue;
		}
		while (tmp->next != NULL && tmp->next->exp > q->exp)
			tmp = tmp->next;
		if (tmp->next != NULL && tmp->next->exp == q->exp) {
			tmp->next->koef += q->koef;
			free(q);
			if (tmp->next->koef == 0) {
				q = tmp->next;
				tmp->next = q->next;
				free(q);
			}
		}
		else
			ubaci(tmp, q);

	}
	fclose(f);
	return 0;
}

int suma(pozicija suma, pozicija p, pozicija q)
{
	pozicija novi = NULL, tmp = NULL;
	while (p != NULL && q != NULL) {
		novi = createNew();
		if (novi == NULL)
			return 1;
		if (p->exp > q->exp) {
			kopiraj(novi, p);
			p = p->next;
		}
		else if (q->exp > p->exp) {
			kopiraj(novi, q);
			q = q->next;
		}
		else {
			novi->exp = p->exp;
			novi->koef = p->koef + q->koef;
			p = p->next;
			q = q->next;
		}
		ubaci(suma, novi);
		suma = novi;
	}
	if (p == NULL) 
		tmp = q;		
	else 
		tmp = p;

	while (tmp != NULL) {
		novi = createNew();
		if (novi == NULL)
			return 1;
		kopiraj(novi, tmp);
		ubaci(suma, novi);
		suma = novi;
		tmp = tmp->next;
	}
	
	return 0;
}

int pomnozi(pozicija rez, pozicija p, pozicija q)
{
	pozicija novi = NULL, tmp = NULL, qHead = q;
	while (p != NULL) {
		while (q != NULL) {
			tmp = rez;
			novi = createNew();
			if (novi == NULL)
				return 1;
			novi->exp = q->exp + p->exp;
			novi->koef = q->koef * p->koef;
			while (tmp->next != NULL && tmp->next->exp > novi->exp)
				tmp = tmp->next;
			if (novi->exp == tmp->exp) {
				tmp->koef += novi->koef;
				free(novi);
				if (tmp->next->koef == 0) {
					novi = tmp->next;
					tmp->next = novi->next;
					free(novi);
				}
			}
			else 
				ubaci(tmp, novi);		
			q = q->next;
		}
		p = p->next;
		q = qHead;
	}
}

int obrisiSve(pozicija p)
{
	pozicija tmp = NULL;
	while (p->next != NULL) {
		tmp = p->next;
		p->next = tmp->next;
		free(tmp);
	}
}