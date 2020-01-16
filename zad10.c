#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct _tree;
typedef struct _tree *posTree;
typedef struct _tree {
	char op[10];
	posTree left;
	posTree right;
}_TREE;

struct _stack;
typedef struct _stack *posStack;
typedef struct _stack {
	posTree el;
	posStack next;
}_STACK;

posTree createTreeNode();
posStack createStackNode();
int pushToStack(posStack head, posTree x);
int popFromStack(posStack head, posTree *returnValue);
int readFromFile(char *fileName, posStack head);
int printToFile(char *fileName, posTree head);
int printToConsole(posTree root);

int main(int argc, char *argv[])
{
	int result = 0;
	_STACK head;
	head.next = NULL;
	result = readFromFile("postfiks.txt", &head);
	if (result) {
		system("pause");
		return result;
	}
	FILE *f = fopen("infiks.txt", "w");
	fclose(f);
	printToFile("infiks.txt", head.next->el);
	printToConsole(head.next->el);
	system("pause");
	return 0;
}

posTree createTreeNode()
{
	posTree q = (posTree)malloc(sizeof(_TREE));
	if (q == NULL) return NULL;
	q->left = q->right = NULL;
	return q;
}

posStack createStackNode()
{
	posStack q = (posStack)malloc(sizeof(_STACK));
	if (q == NULL) return NULL;
	q->next = q->el = NULL;
	return q;
}

int popFromStack(posStack head, posTree *returnValue)
{
	if (head == NULL || head->next == NULL || returnValue == NULL) return 1;
	posStack tmp = head->next;
	*returnValue = tmp->el;
	head->next = tmp->next;
	free(tmp);
	
	return 0;
}

int pushToStack(posStack head, posTree x)
{
	if (head == NULL || x == NULL) return 1;
	posStack newStackNode = createStackNode();
	if (newStackNode == NULL) return 1;
	newStackNode->el = x;
	newStackNode->next = head->next;
	head->next = newStackNode;
	return 0;
}

int readFromFile(char *fileName, posStack head)
{
	if (head == NULL) return 1;
	char buff[10];
	int result;
	FILE *f = fopen(fileName, "r");
	if (f == NULL) return 1;

	while (!feof(f)) {
		posTree newTreeNode = createTreeNode();
		if (createTreeNode == NULL) return 1;
		fscanf(f, " %s", newTreeNode->op);
		if (!strcmp(newTreeNode->op, "+") || !strcmp(newTreeNode->op, "-") ||
			!strcmp(newTreeNode->op, "*") || !strcmp(newTreeNode->op, "%")) 
		{
			result = popFromStack(head, &(newTreeNode->right));
			if (result) {
				printf("Can't pop!\n");
				return 1;
			}
			result = popFromStack(head, &(newTreeNode->left));
			if (result) {
				printf("Can't pop!\n");
				return 1;
			}
			pushToStack(head, newTreeNode);
		}
		else {
			pushToStack(head, newTreeNode);
		}
	}
	fclose(f);

	if (head->next == NULL || head->next->next != NULL) {
		printf("Invalid postfiks!\n");
		return 1;
	}
	return 0;
}

int printToFile(char *fileName, posTree q)
{
	if (q == NULL) return 0;

	printToFile(fileName, q->left);	
	FILE *f = fopen(fileName, "a");
	if (f == NULL) return NULL;
	fprintf(f, "%s ", q->op);
	fclose(f);
	printToFile(fileName, q->right);
	
	return 0;
}

int printToConsole(posTree p)
{
	if (p != NULL) {

		if (p->left != NULL) 
			printf("(");
		printToConsole(p->left);
		
		printf("%s", p->op);

		printToConsole(p->right);
		if (p->right != NULL)
			printf(")");
	}
	return 0;
}
