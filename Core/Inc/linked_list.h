/*
 * linked_list.h
 *
 *  Created on: Nov 4, 2021
 *      Author: Steven
 */

#ifndef INC_LINKED_LIST_H_
#define INC_LINKED_LIST_H_

typedef struct Node Node;

struct Node{
	char data;
	Node *prev;
	Node *next;
};

Node* create_node(char data);

void delete_node(Node *point);
void delete_all(Node *head);

void copy_all(char data[]);


#endif /* INC_LINKED_LIST_H_ */
