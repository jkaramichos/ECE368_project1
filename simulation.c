#include <stdio.h>
#include <stdlib.h>
#include "simulation.h"


//TODO: insert function 1 here:



void mode_2(char* file_name){
	
	//Open File for reading
	FILE* fp = fopen(file_name, "r");

	int data[3];
	//data[0] = arrival_time; (column 1)
	//data[1] = priority; (column 2)
	//data[2] = service_time; (column 3)

	Node* future_event_list = NULL;
	Node* service_queue = NULL;
	Node* server_item = NULL;


	int system_time = 0; 
	char type = 'a'; //needed for enqueuing all of FEL with arrivals from txt file


	//STEP 1: create a future event list based solely on arrival times
	while(1){		

		fscanf(fp, "%d %d %d", &data[0], &data[1], &data[2]);	
		
		if(feof(fp)){
			break;
		}
		
		fel_enqueue(&future_event_list, data, type);

	} //after this completes you'll never have to enqueue arrival events to FEL again

	print_data(future_event_list);
	
	
	//STEP 2: start popping FEL and actually run the simulation
	Node* next_event = stack_pop(&future_event_list);
	
	while(next_event != NULL){

		if (next_event -> type == 'a'){
			system_time = next_event -> data[0];
			arrival_event(next_event, server_item, service_queue); //call arrival fxn
		}
		else{
			
			system_time = next_event -> data[0] + next_event -> data[2];
			//call departure fxn
		}
		next_event = stack_pop(&future_event_list); //get next event
	}

	destroy_node(future_event_list); 
	fclose(fp);

}


//arrival event function
//input: node that is arriving, the server node, the service queue
//return: void..it'll take in pointers so everything will change in the calling fxn  as well
void arrival_event(Node* arrival_node,  Node* server_node, Node* service_queue, int system_time){


	//this is left side of flow chart: (i.e server is not busy)
	if (server_node == NULL) {
		
		pq_enqueue(&server_node, arrival_node -> data); //enqueue server node so it can be busy
		
		
		Node* new_departure = NULL;
		fel_enqueue(&new_departure, arrival_node -> data, 'd');//enqueue FEL with departure event

	}

	//this is right side of flow chart: (i.e server is busy)
	else {
		pq_enqueue(&service_queue, arrival_node -> data); //enqueue the service queue with the node that is arriving
	}

	//NOTE: if this was mode_1 you would have to generate the next arrival event here..(or you could do something similiar
	//like mode_2 and generate all arrivals first)


	//COLLECT STATS

}



//this function will simply print a linked list
void print_data(Node* data){
	
	for(Node* curr = data; curr != NULL; curr = curr -> next){
		//printf("\n\nNEXT NODE:\n");
		//printf("arrival_time = %d\npriority= %d\nservice_time = %d\n", curr -> data[0], curr -> data[1], curr -> data[2]);
		printf("%d %d %d\n", curr -> data[0], curr -> data[1], curr -> data[2]);
	}

}


//this function finds the correct location in linked list
void _pq_enqueue_helper(Node** list_head, Node** tree_head){ 

	Node* temp = *list_head;	
	Node* new_node = *tree_head;
	
	
		//data[1] = priority i.e lamb_0 or lamb_1
		if(temp != NULL && new_node -> data[1] - temp -> data[1] < 0){
			new_node -> next = temp;
			*list_head = new_node;
			return;
		}
		
		while(temp -> next != NULL && new_node -> data[1] - temp -> next -> data[1] >= 0){
			temp = temp -> next;
		}

		new_node -> next = temp -> next;
		temp -> next = new_node;

}


//will create and assign variables for new node...then calls enqueue helper
//to find where to place the new node in list
void pq_enqueue(Node **pq, int data[]){

	Node* temp = *pq;
	Node* new_node = malloc(sizeof(*new_node));

	//assign fields
	new_node -> data[0] = data[0];
	new_node -> data[1] = data[1];
	new_node -> data[2] = data[2];
	
	if(temp == NULL){
		new_node -> next = temp;
		*pq = new_node;
	}

	else{
		_pq_enqueue_helper(pq, &new_node);
	}

}

void _fel_arrival_enqueue_helper(Node** list_head, Node** tree_head){ 

	Node* temp = *list_head;	
	Node* new_node = *tree_head;
	
	
		//data[0] = arrival_time
		if(temp != NULL && new_node -> data[0] - temp -> data[0] < 0){
			new_node -> next = temp;
			*list_head = new_node;
			return;
		}
		
		while(temp -> next != NULL && new_node -> data[0] - temp -> next -> data[0] >= 0){
			temp = temp -> next;
		}

		new_node -> next = temp -> next;
		temp -> next = new_node;

}

void _fel_departure_enqueue_helper(Node** list_head, Node** tree_head){ 

	Node* temp = *list_head;	
	Node* new_node = *tree_head;
	

		//data[0] + data[2]  = departure_time
		if(temp != NULL && (new_node -> data[0] + new_node -> data[2]) - (temp -> data[0] + temp -> data[2]) < 0){
			new_node -> next = temp;
			*list_head = new_node;
			return;
		}
		
		while(temp -> next != NULL && (new_node -> data[0] + new_node -> data[2]) - (temp -> next -> data[0] + temp -> next -> data[2]) >= 0){
			temp = temp -> next;
		}

		new_node -> next = temp -> next;
		temp -> next = new_node;

}


//will create and assign variables for new node...then calls enqueue helper
//to find where to place the new node in list
//char type = departure vs arrival node
//departure_time is used for enqueuing departure nodes
void fel_enqueue(Node **pq, int data[], char type){

	Node* temp = *pq;
	Node* new_node = malloc(sizeof(*new_node));


	
	//assign fields
	new_node -> data[0] = data[0];
	new_node -> data[1] = data[1];
	new_node -> data[2] = data[2];




	if(temp == NULL){
		new_node -> next = temp;
		*pq = new_node;
	}

	else{
		
		if (type == 'a'){
			_fel_arrival_enqueue_helper(pq, &new_node);//when called from here, enqueue will always be based on arrival time
		}
		else{
			_fel_departure_enqueue_helper(pq, &new_node);
		}
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
