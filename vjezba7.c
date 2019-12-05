#include <stdio.h>
#include <stdlib.h>
#define BUFFSIZE 16

struct stack;
typedef struct stack *pos;
typedef struct stack {
	int el;
	pos next;
}STACK;

pos createNew();
int push(pos p, int x);
int pop(pos p, int *num);
int readFromFile(pos p, char *fileName);
int calculate(char *operacija, int a, int b, int *result);
int deleteStack(pos p);

int main(void)
{
	int bul = 0;
	STACK head;
	head.next = NULL;

	bul = readFromFile(&head, "postfiks.txt");
	if (!bul)
		printf("%d\n", head.next->el);
	else
		printf("Pogreska!\n");
	deleteStack(&head);
	system("pause");
	return 0;
}

pos createNew()
{
	pos q = (pos)malloc(sizeof(STACK));
	if (q == NULL) {
		printf("Greska u alokaciji memorije!\n");
		return NULL;
	}
	q->next = NULL;
	return q;
}

int push(pos p, int x)
{
	pos q = createNew();
	if (q == NULL || p == NULL)
		return 1;
	q->el = x;
	q->next = p->next;
	p->next = q;
	return 0;
}

int pop(pos p, int *num)
{
	if (p == NULL || p->next == NULL)
		return 1;
	pos tmp = p->next;
	*num = tmp->el;
	p->next = tmp->next;
	free(tmp);
	return 0;
}

int calculate(char *operation, int a, int b, int *result)
{
	if (operation == NULL || strlen(operation) != 1)
		return 1;
	switch (*operation) {
	case '+':
		*result = a + b;
		break;
	case '-':
		*result = a - b;
		break;
	case '*':
		*result = a * b;
		break;
	case '/':
		if (b == 0) {
			printf("Deviding with zero!\n");
			return 1;
		}
		*result = a / b;
		break;
	case '%':
		*result = a % b;
		break;
	default:
		printf("Operacija: %s\n", operation);
		return 1;
	}
	return 0;
}

int readFromFile(pos head, char *fileName)
{
	char buffer[BUFFSIZE];
	int  number = 0, bul = 0, a = 0, b = 0;
	int result = 0;
	memset(buffer, '\0', BUFFSIZE);  //cili buffer ima vrijednost \0
	FILE *f = fopen(fileName, "r");
	if (f == NULL) {
		printf("Neuspjesna datoteka!\n");
		return 1;
	}
	while (!feof(f)) {
		fscanf(f, " %s", buffer);
		if (strlen(buffer) == 0)  //priskace razmake
			continue;
		if (sscanf(buffer, " %d", &number) > 0)    //vraća 1 ako je vrijednost broj ili 0 ako to nije
			push(head, number);
		else {
			bul = pop(head, &b);
			if (bul)
				break;
			bul = pop(head, &a);
			if (bul)
				break;
			bul = calculate(buffer, a, b, &result);
			if (bul)
				break;
			push(head, result);
		}
	}
	fclose(f);
	if (head->next->next != NULL || bul)
		return 1;
	return 0;
}

int deleteStack(pos p)
{
	pos tmp = NULL;
	while (p->next != NULL) {
		tmp = p->next;
		p->next = tmp->next;
		free(tmp);
	}
}
