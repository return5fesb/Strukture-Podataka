#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

struct _list;
typedef struct _list * pos;
typedef struct _list {
	int el;
	pos next;
}_LIST;

int read(pos p, char *fileName);
int print(pos p);
int Union(pos l1, pos l2, pos uni);
int Intersection(pos l1, pos l2, pos inte);
pos createNew();

int main(int argc, char *argv[])
{
	_LIST l1, l2, uni, inte;
	l1.next = l2.next = uni.next = inte.next = NULL;

	read(&l1, "lista1.txt");
	read(&l2, "lista2.txt");
	printf("lista 1: ");
	print(l1.next);
	printf("lista 2: ");
	print(l2.next);
	Union(l1.next, l2.next, &uni);
	printf("Unija: ");
	print(uni.next);
	Intersection(l1.next, l2.next, &inte);
	printf("Presjek: ");
	print(inte.next);

	system("pause");
	return 0;
}

pos createNew()
{
	pos p = (pos)malloc(sizeof(_LIST));
	if (p == NULL) {
		printf("Greska u alokaciji!\n");
		return NULL;
	}
	p->next = NULL;
	return p;

}

int read(pos p, char *fileName)
{
	pos newNode = NULL, tmp = NULL;
	FILE *f = fopen(fileName, "r");
	while (!feof(f)) {
		newNode = createNew();
		
		fscanf(f, " %d,", &newNode->el);
		tmp = p;
		while (tmp->next != NULL && tmp->next->el > newNode->el)
			tmp = tmp->next;
		if (tmp->next != NULL && tmp->next->el == newNode->el) {
			free(newNode);
		}
		else {
			newNode->next = tmp->next;
			tmp->next = newNode;
		}
	}
	return 0;
}

int print(pos p)
{
	while (p != NULL) {
		printf("%d ", p->el);
		p = p->next;
	}
	printf("\n");
	return 0;
}

int Union(pos l1, pos l2, pos uni)
{
	pos newNode = NULL, tmp = NULL;
	while (l1 != NULL && l2 != NULL) {
		newNode = createNew();
		
		if (l1->el > l2->el) {
			newNode->el = l1->el;
			l1 = l1->next;
		}
		else if (l2->el > l1->el) {
			newNode->el = l2->el;
			l2 = l2->next;
		}
		else {
			newNode->el = l1->el;
			l1 = l1->next;
			l2 = l2->next;
		}

		newNode->next = uni->next;
		uni->next = newNode;
		uni = newNode;
	}
	if (l1 == NULL)
		tmp = l2;
	else
		tmp = l1;
	while (tmp != NULL) {
		newNode = createNew();
		
		newNode->el = tmp->el;
		newNode->next = uni->next;
		uni->next = newNode;
		uni = newNode;
		tmp = tmp->next;
	}
	return 0;
}

int Intersection(pos l1, pos l2, pos inte)
{
	pos newNode = NULL;
	while (l1 != NULL && l2 != NULL) {
		if (l1->el > l2->el) {
			l1 = l1->next;
		}
		else if (l2->el > l1->el) {
			l2 = l2->next;
		}
		else if (l1->el == l2->el) {
			newNode = createNew();
			
			newNode->el = l1->el;
			l1 = l1->next;
			l2 = l2->next;
			newNode->next = inte->next;
			inte->next = newNode;
			inte = newNode;
		}
	}

	return 0;
}