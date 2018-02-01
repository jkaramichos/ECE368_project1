#ifndef CUSTOMER_H
#define CUSTOMER_H

#include <stdio.h>



typedef struct _Node
{

	int priority;
	int arrival_time;
	int service_time;

	struct _Node *next;

} Node;


//TODO: INSERT fxn definition for mode 1
void mode_2(char* file_name);

void print_data(Node* data);
void _enqueue_helper(Node** list_head, Node** tree_head);
void pq_enqueue(Node **pq, int data[]);

void destroy_node(Node *root);
Node* stack_pop(Node **stack);


#endif
