#include <stdio.h>
#include <stdlib.h>
#include "simulation.h"


//output_file = proj1-a_output


int main(int argc, char** argv){

	if(!(argc == 2 || argc == 5)) { 
		return EXIT_FAILURE;
	}

	if(argc == 5) { //mode 1
		
		int lamb_0 = atoi(argv[1]);
		int lamb_1 = atoi(argv[2]);
		int mu = atoi(argv[3]);
		int total_tasks = atoi(argv[4]);
	
		printf("lamb_0 = %d\nlamb_1 = %d\nmu = %d\ntotal_tasks = %d\n", lamb_0, lamb_1, mu, total_tasks);

		//call mode1();
	}
	
	else { //mode 2
		
		char* file_name = argv[1]; 
		

		printf("file_name = %s\n", file_name);
	

		mode_2(file_name);
	}
	

	return EXIT_SUCCESS;
}
