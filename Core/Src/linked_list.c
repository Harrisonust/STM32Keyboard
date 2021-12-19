#include "linked_list.h"
#include <stdlib.h>

Node* create_node(char data){
	Node *link = (Node*) malloc(sizeof(Node));
	link->data = data;
	link->next = NULL;
	link->prev = NULL;
	return link;
}

void delete_node(Node *point){
	if(point == NULL) return;
	free(point);
}

void delete_all(Node *head){
	if(head == NULL) return;
	Node *current = head->next;
	while(current != NULL){
		Node *temp = current;
		current = current->next;
		free(temp);
	}
	free(head);
}
