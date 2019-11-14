/*Napisati program koji pomoæu vezanih listi simulira rad:
a) stoga,
b) reda.
Napomena: Funkcija "push" sprema cijeli broj, sluèajno generirani u opsegu od 10 -100.*/

#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include <time.h>



typedef struct list *pos;
typedef struct list {
	int el;
	pos next;
}LIST;

int pushRed(pos p);
int pushStog(pos p);
int pop(pos p);
int print(pos p);
int deleteAll(pos p);
pos createNew();

int main(void)
{
	LIST red, stog;
	char c;
	red.next = stog.next = NULL;
	srand(time(NULL));
	do {
		printf("Unesite:\n1 - dodaj na stog\n2 - popaj sa stoga\n3 - ispis stoga\n4 - dodaj na red\n5 - popaj s reda\n6 - ispisi red"
			"\n0 - kraj\n");
		scanf(" %c", &c);
		switch (c) {
		case '1':
			pushStog(&stog);
			break;
		case '2':
			pop(&stog);
			break;
		case '3':
			print(stog.next);
			printf("\n");
			break;
		case '4':
			pushRed(&red);
			break;
		case '5':
			pop(&red);
			break;
		case '6':
			print(red.next);
			printf("\n");
			break;
		case '0':
			break;
		default:
			printf("Pogresan unos!\n");
			break;

		}
	} while (c != '0');
	deleteAll(&stog);
	deleteAll(&red);
	system("pause");
	return 0;
}
pos createNew()
{
	pos q = (pos)malloc(sizeof(LIST));

	if (q == NULL)
		return NULL;

	q->next = NULL;
	return q;
}

int pop(pos p)
{
	if (p->next == NULL)  //znaci da se nisu povezale dvi liste
		return 1;
	pos tmp = p->next;
	p->next = tmp->next;
	free(tmp);
	return 0;
}

int pushStog(pos p)
{
	pos q = createNew();
	
	q->el = rand() % 91 + 10;
	q->next = p->next;
	p->next = q;
	return 0;
}

int pushRed(pos p)
{
	static pos last = NULL;

	if (p->next == NULL)
		last = p;
	pos q = createNew();
	q->el = rand() % 91 + 10;
	q->next = last->next;
	last->next = q;
	last = q;
	return 0;
}

int print(pos p)
{
	if (p == NULL)
		return 0;
	printf("%d ", p->el);
	print(p->next);
	return 0;
}

int deleteAll(pos p)
{
	pos tmp = NULL;
	while (p->next != NULL) {
		tmp = p->next;
		p->next = tmp->next;
		free(tmp);
	}
	return 0;
}