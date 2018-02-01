#include <stdio.h>
#include <stdlib.h>
#include "simulation.h"


//TODO: insert function 1 here:



void mode_2(char* file_name){
	
	//Open File for reading
	FILE* fp = fopen(file_name, "r");

	int data[3];
	//data[0] = arrival_time;
	//data[1] = priority;
	//data[2] = service_time;

	Node* head = NULL;

	//loop through every line to ensure data and linked list can be formed properly
	while(1){		
		
		fscanf(fp, "%d %d %d", &data[0], &data[1], &data[2]);

		if(feof(fp)){
			break;
		}

		pq_enqueue(&head, data);


		}

	print_data(head);

	destroy_node(head);
	fclose(fp);

}

void print_data(Node* data){
	
	for(Node* curr = data; curr != NULL; curr = curr -> next){
		printf("NEXT NODE:\n");
		printf("arrival_time = %d\npriority= %d\nservice_time = %d\n", curr -> arrival_time, curr -> priority, curr -> service_time);
	}

}



//this function finds the correct location in linked list
void _enqueue_helper(Node** list_head, Node** tree_head){ 

	Node* temp = *list_head;	
	Node* new_node = *tree_head;
	
	
		if(temp != NULL && new_node -> priority - temp -> priority < 0){
			new_node -> next = temp;
			*list_head = new_node;
			return;
		}
		
		while(temp -> next != NULL && new_node -> priority - temp -> next -> priority >= 0){
			temp = temp -> next;
		}

		new_node -> next = temp -> next;
		temp -> next = new_node;

}


//will create and assign variables for new node...then calls enqueue helper
//to find where to place the new node in list
void pq_enqueue(Node **pq, int data[]){

	Node* temp;
	Node* new_node;
	

	temp = *pq;
	new_node = malloc(sizeof(*new_node));

	//assign fields
	new_node -> arrival_time = data[0];
	new_node -> priority = data[1];
	new_node -> service_time = data[2];
	
	if(temp == NULL){
		new_node -> next = temp;
		*pq = new_node;
	}

	else{
		_enqueue_helper(pq, &new_node);
	}

}



//returns the node to be deleted/popped
Node* stack_pop(Node **stack){

	Node* temp = *stack;
	Node* delete = *stack;
	if(temp == NULL){
		return NULL;
	}
		
	temp = temp -> next;
	*stack = temp;

	delete -> next = NULL;

	return delete;
}

void destroy_node(Node *root){ //this function will destroy the linked list of chars

	while(root != NULL){
		Node* hold = root;
		root = root -> next;
		free(hold);
	}

}
