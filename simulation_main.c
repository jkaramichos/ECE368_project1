#include <stdio.h>
#include <stdlib.h>
#include "simulation.h"


//output_file = proj1-a_output


int main(int argc, char** argv){

	if(!(argc == 2 || argc == 5)) { 
		return EXIT_FAILURE;
	}

	if(argc == 5) { //mode 1
		
		double lamb_0 = atoi(argv[1]);
		double lamb_1 = atoi(argv[2]);
		double mu = atoi(argv[3]);
		int total_tasks = atoi(argv[4]);
	
		printf("lamb_0 = %f\nlamb_1 = %f\nmu = %f\ntotal_tasks = %d\n", lamb_0, lamb_1, mu, total_tasks);

		//call mode1();
	}
	
	else { //mode 2
		char* file_name = argv[1]; 
		mode_2(file_name);
	}
	

	return EXIT_SUCCESS;
}
