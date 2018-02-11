#include <stdio.h>
#include <stdlib.h>
#include "simulation.h"
#include <math.h>


void mode_1(double lamb_0, double lamb_1, double mu, int total_tasks){

	Node* queue_0 = NULL; //queue with only lamb_0 arrivals
	Node* queue_1 = NULL;
	Node* future_event_list = NULL; //queue with interleaved queue_0 and queue_1...this will get freed by simulation fxn
		
	int lcv = 0;
	int system_time = 0;
	int num_zero_tasks = 0;
	int num_one_tasks = 0;
	int data[3];
	data[1] = 0; //initialize priortiy
	
	if (lamb_0 != 0)
	{
		while(lcv < total_tasks){ //generate all lamb_0 events	
			system_time = _create_new_arrival(&queue_0, lamb_0, mu, data, system_time);
			num_zero_tasks++;
			lcv++;
		}
	}

	lcv = 0;
	data[1] = 1; //set priority to 1 for priority 1 events
	system_time = 0;
	
	if (lamb_1 != 0)
	{	
		while(lcv < total_tasks){ //generate all lamb_1 events
			system_time = _create_new_arrival(&queue_1, lamb_1, mu, data, system_time);
			num_one_tasks++;
			lcv++;
		}
	}
	
	_interleave(&future_event_list, queue_0, queue_1);

	simulate(future_event_list, num_zero_tasks, num_one_tasks, 2 * total_tasks); //this will also take care of freeing memory
	
	destroy_node(queue_0);
	destroy_node(queue_1);
}




void mode_2(char* file_name){

	//Open File for reading
	FILE* fp = fopen(file_name, "r");
	int num_zero_tasks = 0; 
	int num_one_tasks = 0;
	int num_of_arrivals = 0; //total numberr of arrivals (mode_1 would be in the input parameter
	char type = 'a'; //needed for determining if the event is an arrival or departure	
	int data[3]; /* data[0] = arrival_time; data[1] = priority; data[2] = service_time; */

	Node* future_event_list = NULL;
	
	//STEP 1: create a future event list based solely on arrival times
	while(1)
	{		

		fscanf(fp, "%d %d %d", &data[0], &data[1], &data[2]);	
		
		//stop attempting to scan file if we're at the end of the file
		if(feof(fp)){
			break;
		}
		
		if(data[1] == 0){
			num_zero_tasks++;
		}
		else{
			num_one_tasks++;
		}

		//call helper function to generate num subtasks
		fel_enqueue(&future_event_list, data, type, data[0]);
		num_of_arrivals++;

	} /* after this completes you'll never have to enqueue arrival events to FEL again */
	
	simulate(future_event_list, num_zero_tasks, num_one_tasks, num_of_arrivals);
	
	fclose(fp);
} /*END OF MODE_2 */



void simulate(Node* future_event_list, int num_zero_tasks, int num_one_tasks, int num_of_arrivals){	

	Node* service_queue = NULL;
	Node* server_node = NULL; //add while loop to initialize 64 nodes to isBusy -> false or 0 whatever
	Node* next_event = NULL;
	
	int system_time = 0; //i.e "real time" if this wasn't a simulation
	int cum_queue_size = 0; //cumulative sum of the size of the queue - used for calculting its average size
	int wait_time_0 = 0; //cumulative sum of the wait time of priority 0 event
	int wait_time_1 = 0; //cumulative sum of the wait time of priority 1 event
	int CPU_busy_time = 0; //cumulative sum of time that the cpu is serving
	int queue_size = 0; //length of the service queue

	int i = 0; //just used for counting the iteration in print everything
	
	while(future_event_list != NULL)
	{
		
		next_event = stack_pop(&future_event_list);

		print_everything(i, system_time, queue_size, cum_queue_size, wait_time_0, wait_time_1, CPU_busy_time, server_node, service_queue, next_event, future_event_list);

		system_time = next_event -> event_time;
		
		//arrival event goes here:
		if (next_event -> type == 'a'){
			_arrival_event(&server_node, next_event, &future_event_list, &service_queue, system_time, &queue_size, &cum_queue_size); 
		}

		else{ //departure event goes here: 
			_departure_event(&server_node, next_event, &future_event_list, &service_queue, system_time, &queue_size, &CPU_busy_time, &wait_time_0, &wait_time_1);
		}
	
		i++;
		destroy_node(next_event);
	}
			
	double average_wait_0 = (double)wait_time_0/num_zero_tasks;
	double average_wait_1 = (double)wait_time_1/num_one_tasks;
	double average_queue_length = (double)cum_queue_size/num_of_arrivals;
	double average_cpu_utilization = (double)CPU_busy_time/system_time;
	
	FILE* write_file = fopen("proj1-a_output", "w");
	fprintf(write_file, "average_wait_0 = %f\n", average_wait_0);
	fprintf(write_file, "average_wait_1 = %f\n", average_wait_1);
	fprintf(write_file, "average_queue_length = %f\n", average_queue_length);
	fprintf(write_file, "average_CPU_utilization = %f\n", average_cpu_utilization);

	destroy_node(future_event_list); 
	destroy_node(service_queue);
	destroy_node(server_node);
	fclose(write_file);

}

void _arrival_event(Node** server_node, Node* next_event, Node** future_event_list, Node** service_queue, int system_time, int* queue_size, int* cum_queue_size){  
			
			if(*server_node == NULL){ //server is not busy, put something in the server node and create departure event 
				//TODO: call unpack fxn
				pq_enqueue(server_node, next_event -> data, next_event -> type, system_time); //enqueue server node so it can be busy
				fel_enqueue(future_event_list, next_event -> data, 'd', system_time + next_event -> data[2]);//enqueue FEL with new departure event
			}
			else{ //server is busy, so enqueue the priority queue
				pq_enqueue(service_queue, next_event -> data, next_event -> type, 69); //enqueue the wait queue with the arrival_node
			}

			*cum_queue_size += *queue_size;	
			*queue_size = get_queue_size(*service_queue);

} /* END OF ARRIVAL EVENT */


void _departure_event(Node** server_node, Node* next_event, Node** future_event_list, Node** service_queue, int system_time, int* queue_size, int* CPU_busy_time, int* wait_time_0, int* wait_time_1){
			
			*CPU_busy_time += (*server_node) -> data[2]; //CPU Busy time is the time the CPU is serving an item
			destroy_node(*server_node); //get rid of whats in the server currently
			
			//if an item is in the queue then pop it and put it in the server
			if (*queue_size >= 1) 
			{ 

				//if get_num_availble >= (*service_queue) -> subtasks)
				*server_node = stack_pop(service_queue);
				(*server_node) -> event_time = system_time + (*server_node) -> data[2];
				*queue_size = get_queue_size(*service_queue);		
				/* else {
					while loop through service queue until service_queue -> subtasks <= availble server
				}	*/

				if((*server_node) -> data[1] == 0){
					*wait_time_0 += system_time - (*server_node) -> data[0]; //system_time minus raw arrival time = time waiting
				}
				else{
					*wait_time_1 += system_time - (*server_node) -> data[0];
				}
			
				fel_enqueue(future_event_list, (*server_node) -> data, 'd', (*server_node) -> event_time); //enqueue the new server_nodes departure

			}
		
			//nothing to replace the server node with, set server to not busy
			else{ 
				*server_node = NULL;	
			}
	
} /* END OF DEPARTURE EVENT */



/*this function will enqueue a brand new node with the given data */
void pq_enqueue(Node **pq, int data[], char type, int event_time/*add subtasks parameter*/)
{

	Node* temp = *pq;
	Node* new_node = malloc(sizeof(*new_node));

	//assign fields
	new_node -> data[0] = data[0];
	new_node -> data[1] = data[1];
	new_node -> data[2] = data[2];
	new_node -> type = type;
	new_node -> event_time = event_time;
	//new_node -> subtasks = subtasks


	if(temp == NULL){
		new_node -> next = temp;
		*pq = new_node;
	}

	else{
		_pq_enqueue_helper(pq, &new_node);
	}

}

/* insert any node into a list based on its priority */
void _pq_enqueue_helper(Node** list_head, Node** tree_head)
{ 

	Node* temp = *list_head;	
	Node* new_node = *tree_head;
	
	
		/* data[1] = priority i.e lamb_0 or lamb_1 */
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



/*will create and assign variables for new node...then calls enqueue helper
to find where to place the new node in list
char type = departure vs arrival node
departure_time is used for enqueuing departure nodes */
void fel_enqueue(Node **pq, int data[], char type, int event_time)
{

	Node* temp = *pq;
	Node* new_node = malloc(sizeof(*new_node));
	
	//assign fields
	new_node -> data[0] = data[0];
	new_node -> data[1] = data[1];
	new_node -> data[2] = data[2];
	new_node -> type = type;
	new_node -> event_time = event_time;


	if(temp == NULL){
		new_node -> next = temp;
		*pq = new_node;
	}

	else{
		_fel_enqueue_helper(pq, &new_node);
	}

}

//this function finds the correct location in linked list
void _fel_enqueue_helper(Node** list_head, Node** tree_head)
{ 

	Node* temp = *list_head;	
	Node* new_node = *tree_head;
	
	
		//data[1] = priority i.e lamb_0 or lamb_1
		if(temp != NULL && new_node -> event_time - temp -> event_time < 0){
			new_node -> next = temp;
			*list_head = new_node;
			return;
		}
		
		while(temp -> next != NULL && new_node -> event_time - temp -> next -> event_time >= 0){
			temp = temp -> next;
		}

		new_node -> next = temp -> next;
		temp -> next = new_node;

}

int _generate_time(double rate)
{
	
	int rand_value = rand();
	float unit_rand = rand_value / (double)RAND_MAX;
	return ceil((-1 / rate) * log(1-unit_rand));

} /*END OF _generate_time FUNCTION*/


//this function will "return" a combined list of queue_0 and queu_1 while keepign queue_0 and queue_1 completely in tact
void _interleave(Node** combined_list, Node* queue_0, Node* queue_1){


	//first step is to initialize the combined list with all of queue_0...this can be done simply by calling FEL_enqueue
	if(queue_0 != NULL){
		for(Node* curr = queue_0; curr != NULL; curr = curr -> next){
			fel_enqueue(combined_list, curr -> data, curr -> type, curr -> event_time);
		}
	}
	
	if (queue_1 != NULL){
		//next step is to do the interleaving:
		for(Node* curr = queue_1; curr != NULL; curr = curr -> next){
			fel_enqueue(combined_list, curr -> data, curr -> type, curr -> event_time);
		}
	}


} /*END OF _interleave*/

//this function will create a new arrival and enqueue it
int _create_new_arrival(Node** queue, double lambda, double mu, int data[], int system_time){
		int interarrival = _generate_time(lambda);
		data[0] = system_time + interarrival; //create interarrival times
		data[2]= _generate_time(mu); //create service times
		

		//(*queue) -> subtasks = _generate_subtasks()		

		fel_enqueue(queue, data, 'a', data[0]); //put new event into queue_0;
		return system_time += interarrival; //update system time
}

// returns the size of the linked list
int get_queue_size(Node* list)
{
	
	int size = 0;
	for(Node* curr = list; curr != NULL; curr = curr -> next){
		size += 1;
	}
	
	return size;
}


//returns the node to be deleted/popped
Node* stack_pop(Node **stack)
{

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


//this function will destroy the linked list of chars
void destroy_node(Node *root)
{ 

	while(root != NULL){
		Node* hold = root;
		root = root -> next;
		free(hold);
	}

}


/* prints the first ten elements of linked list */
void print_data(Node* data)
{
	
	int i = 0;
	for(Node* curr = data; curr != NULL; curr = curr -> next){
		printf("%d %d %d %c %d,\t", curr -> data[0], curr -> data[1], curr -> data[2], curr -> type, curr -> event_time);
		if (i >= 10){
			break;
		}
		i++;
	}
	printf("\n");
}

void print_everything(int i, int system_time, int queue_size, int cum_queue_size, int wait_time_0, int wait_time_1, int CPU_busy_time, Node* server_node, Node* service_queue, Node* next_event, Node* future_event_list){
		/*PRINT INFORMATION*/	
		printf("\n\nIteration: %d\n", i);
		printf("System_time: %d\n", system_time);
		printf("Queue Size: %d\n", queue_size);
		printf("cum_queue_size: %d\n", cum_queue_size);
		printf("wait_time_0: %d\n", wait_time_0);
		printf("wait_time_1: %d\n", wait_time_1);
		printf("CPU_busy_time: %d\n", CPU_busy_time);
		printf("SERVER NODE: \t");
		print_data(server_node);
		printf("SERVICE QUEUE: \t");
		print_data(service_queue);		
		printf("NEXT EVENT:      ");
		print_data(next_event);
		printf("FEL:          \t");
		print_data(future_event_list);
}
