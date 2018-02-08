#ifndef SIMULATION_H
#define SIMULATION_H
#include <stdio.h>

typedef struct _Node
{

	//char type is used for popping the FEL, how do we determine if the node we're popping is an 
	//arrival or deparutre? a = arrival
	char type; //d = departure
	int data[3];
	struct _Node *next;
	int event_time; //raw time that the node entered the server
	int raw_arrival_time; //kinda over lapping but whatevs


} Node;

void mode_1(double lamb_0, double lamb_1, double mu, int total_tasks);
void mode_2(char* file_name);

//this is the driver program that runs the simulation. NOTE: for this function to work, the FEL must have all arrivals already enqueued into it. it will not generate any arrivals
void simulate(Node* future_event_list, int num_zero_tasks, int num_one_tasks, int num_of_arrivals); 

//FUNCTION SIGNATURE FOR MODE_1 HELPER FUNCTION
int _generate_time(double rate); //will create a random number based on the input rate
void _interleave(Node** combined_list, Node* queue_0, Node* queue_1);

//FUNCTION SIGNATURES FOR PRIORITY QUEUE (pq)
void _pq_enqueue_helper(Node** list_head, Node** new_node);
void pq_enqueue(Node **pq, int data[], char type, int event_time, int raw_arrival_time);


//FUNCTION SIGNATURES FOR FUTURE EVENT LIST QUEUE (fel)
void fel_enqueue(Node **pq, int data[], char type, int event_time, int raw_arrival_time); 
void _fel_enqueue_helper(Node** list_head, Node** new_node); 



//FUNCTION SIGNATURE TO GET THE SIZE OF LINKED LIST
int get_queue_size(Node* list);


//MISC HELPER FUNCTIONS
void print_data(Node* data);
void destroy_node(Node *root);
Node* stack_pop(Node **stack);

#endif
