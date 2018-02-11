#ifndef SIMULATION_H
#define SIMULATION_H
#include <stdio.h>

typedef struct _Node
{
	char type; //d = departure, a = arrival
	int data[3]; //contains, raw arrival time, priority, and service time respectively
	int event_time; //contains raw event time, for arrivals, this is equivalent to data[0], for departures its the time they enter the node + system_time
	struct _Node *next;
	//int subtasks;
	//int isBusy //specific for server_nodes only

} Node;

//FUNCTION SIGNATURES FOR BOTH MODE 1 AND MODE 2
void mode_1(double lamb_0, double lamb_1, double mu, int total_tasks);
void mode_2(char* file_name);
void simulate(Node* future_event_list, int num_zero_tasks, int num_one_tasks, int num_of_arrivals); 

//SIMULATE HELPER FUNCTIONS
void _arrival_event(Node** server_node, Node* next_event, Node** future_event_list, Node** service_queue, int system_time, int* queue_size, int* cum_queue_size);
void _departure_event(Node** server_node, Node* next_event, Node** future_event_list, Node** service_queue, int system_time, int* queue_size, int* CPU_busy_time, int* wait_time_0, int* wait_time_1);


//FUNCTION SIGNATURES FOR PRIORITY QUEUE (pq)
void pq_enqueue(Node** pq, int data[], char type, int event_time);
void _pq_enqueue_helper(Node** list_head, Node** new_node);

//FUNCTION SIGNATURES FOR FUTURE EVENT LIST QUEUE (fel)
void fel_enqueue(Node** pq, int data[], char type, int event_time); 
void _fel_enqueue_helper(Node** list_head, Node** new_node); 


//MODE_1 HELPER FUNCTIONS
int _generate_time(double rate); //will create a random number based on the input rate
void _interleave(Node** combined_list, Node* queue_0, Node* queue_1);
int _create_new_arrival(Node** queue, double lambda, double mu, int data[], int system_time); /* will create and enqueue a new arrival event */


//MISC UTILITY FUNCTIONS
int get_queue_size(Node* list);
Node* stack_pop(Node **stack);
void destroy_node(Node *root);
void print_data(Node* data);
void print_everything(int i, int system_time, int queue_size, int cum_queue_size, int wait_time_0, int wait_time_1, int CPU_busy_time, Node* server_node, Node* service_queue, Node* next_event, Node* future_event_list);

#endif
