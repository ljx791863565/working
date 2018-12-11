#include <stdio.h>
#include <stdlib.h>

typedef int typeElement ;
typedef struct Node
{
	typeElement data;
	struct Node *next;
}Node;

Node* push_back(Node *head, typeElement data)
{
	Node *p = (Node *)malloc(sizeof(Node));
	if (p == NULL){
		perror("malloc");
		return NULL;
	}
	p->data = data;
	if (head == NULL){
		head = p;
		p->next = NULL;
		return head;
	}

	Node *t = head;
	while (t->next != NULL){
		t = t->next;
	}
	t->next = p;
	p->next = NULL;
	return head;
}

Node *push_front(Node *head, typeElement data)
{
	Node *p = (Node *)malloc(sizeof(Node));
	if (p == NULL){
		perror("malloc");
		return NULL;
	}
	p->data = data;
	p->next = head;
	head = p;
	return head;
}

void display(Node *head)
{
	if (head == NULL){
		printf("linkedList is empty...\n");
		return ;
	}

	Node *t = head;
	while (t != NULL){
		printf("%d ", t->data);
		t = t->next;
	}
	printf("\n");
}

void Free(Node *head)
{
	Node *t = head;
	if (head != NULL){
		head = head->next;
		free(t);
		t = head;
	}
}


int main()
{
	Node *head = NULL;
	head = push_back(head, 2);
	head = push_back(head, 3);
	head = push_back(head, 5);
	head = push_back(head, 7);
	head = push_back(head, 11);
	head = push_back(head, 13);
	head = push_back(head, 17);
	head = push_front(head, 19);
	head = push_front(head, 23);
	head = push_front(head, 29);
	head = push_front(head, 31);
	head = push_front(head, 37);
	head = push_front(head, 41);
	head = push_front(head, 43);
	display(head);
	Free(head);

	return 0;
}
