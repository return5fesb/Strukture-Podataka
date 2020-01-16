#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define HASH_SIZE 11

struct _student;
typedef struct _student* pos;
typedef struct _student {
	int matBr;
	char name[16];
	char surname[16];
	pos next;
}_STUDENT;

pos createNew();
int readFromFile(char fileName[], pos hash[]);
int calculateHash(char surname[], int* hasVal);
int insertToHash(pos newNode, pos hash[]);
int compare(pos node1, pos node2);
int printHash(pos hash[]);
int printMBrOfStudent(char name[], char surname[], pos hash[]);

int main(int argc, char* argv[])
{
	pos hash[HASH_SIZE];

	int i = 0;
	for (i = 0; i < HASH_SIZE; i++) {
		hash[i] = NULL;
	}

	readFromFile("studenti.txt", hash);
	printHash(hash);

	char c;
	char ime[16], prezime[16];
	while (1) {
		printf("Zelite li ispisati maticni broj odredenog studenta? (y/n)\n");
		scanf(" %c", &c);
		if (c == 'y') {
			printf("Unesite ime i prezime:\n");
			scanf(" %s %s", ime, prezime);
			printMBrOfStudent(ime, prezime, hash);
		}
		else
			break;
	}

	return 0;
}

pos createNew()
{
	pos q = (pos)malloc(sizeof(_STUDENT));
	if (q == NULL) {
		printf("Unable to allocate memory!\n");
		return NULL;
	}
	q->next = NULL;
	q->name[0] = '\0';
	q->surname[0] = '\0';
	q->matBr = -1;
	return q;
}

int calculateHash(char surname[], int* hashIndex)
{
	int i = 0;
	int sum = 0;
	while (i < 5 && surname[i] != '\0') {
		sum += surname[i];
		++i;
	}
	//printf("%d ", sum);
	*hashIndex = sum % HASH_SIZE;
	return 0;
}

int compare(pos node1, pos node2)
{
	int result = 0;
	result = strcmp(node1->surname, node2->surname);
	if (result == 0) {
		result = strcmp(node1->name, node2->name);
	}
	if (result == 0) {
		if (node1->matBr > node2->matBr) {
			result = 1;
		}
		else if (node1->matBr < node2->matBr) {
			result = -1;
		}
	}
	//printf("%d\n", result);
	return result;
}

int insertToHash(pos newNode, pos hash[])
{
	int hashIndex = -1;

	calculateHash(newNode->surname, &hashIndex);

	if (hash[hashIndex] == NULL) {
		hash[hashIndex] = newNode;
	}
	else if (compare(hash[hashIndex], newNode) > 0) {
		newNode->next = hash[hashIndex];
		hash[hashIndex] = newNode;
	}
	else {
		pos it = hash[hashIndex];
		while (it->next != NULL && compare(it->next, newNode) < 0) {
			it = it->next;
		}
		newNode->next = it->next;
		it->next = newNode;
	}
}

int readFromFile(char fileName[], pos hash[])
{
	pos newNode = NULL;
	FILE *f = fopen(fileName, "r");
	if (f == NULL) {
		printf("Unable to open file!\n");
		return 1;
	}

	while (!feof(f)) {
		newNode = createNew();
		if (newNode == NULL) {
			return 1;
		}
		fscanf(f, " %s %s %d\n", newNode->name, newNode->surname, &newNode->matBr);
		insertToHash(newNode, hash);
	}
	fclose(f);
	return 0;
}

int printHash(pos hash[])
{
	int i = 0;
	pos it = NULL;
	printf("PREZIME    IME\t      MBR\n");
	for (i = 0; i < HASH_SIZE; i++) {
		it = hash[i];
		while (it != NULL) {
			printf("%-10s %-10s %-5d\thash: %d\n", it->surname, it->name, it->matBr, i);
			it = it->next;
		}
	}
}

int printMBrOfStudent(char name[], char surname[], pos hash[])
{
	int hashIndex = -1;
	calculateHash(surname, &hashIndex);
	pos it = hash[hashIndex];
	while (it != NULL && (strcmp(name, it->name) != 0 || strcmp(surname, it->surname) != 0)) {
		it = it->next;
	}
	if (it == NULL)
		printf("Ne postoji!\n");
	else
		printf("Maticni broj je: %d\n", it->matBr);
	return 0;
}
