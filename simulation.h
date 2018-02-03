#ifndef SIMULATION_H
#define SIMULATION_H
#include <stdio.h>

typedef struct _Node
{


	//char type is used for popping the FEL, how do we determine if the node we're popping is an 
	//arrival or deparutre? a = arrival
	char type;
	int data[3];
	struct _Node *next;

	//Node* (*stack_pop)(Node **stack); //this may not even need to be here...

} Node;


//TODO: INSERT fxn definition for mode 1
void mode_2(char* file_name);


void arrival_event(Node* arrival_node,  Node* server_node, Node* service_queue, int system_time);


void print_data(Node* data);
void _pq_enqueue_helper(Node** list_head, Node** tree_head);
void pq_enqueue(Node **pq, int data[]);


void fel_enqueue(Node **pq, int data[], char type);
void _fel_arrival_enqueue_helper(Node** list_head, Node** tree_head);
void _fel_departure_enqueue_helper(Node** list_head, Node** tree_head); 

void destroy_node(Node *root);
Node* stack_pop(Node **stack);


#endif
