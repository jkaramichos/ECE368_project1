#include <stdio.h>
#include <stdlib.h>
#include "simulation.h"

int main(int argc, char** argv){

	if(!(argc == 2 || argc == 5)) { 
		return EXIT_FAILURE;
	}

	if(argc == 5) { //mode 1
		
		double lamb_0 = atof(argv[1]);
		double lamb_1 = atof(argv[2]);
		double mu = atof(argv[3]);
		int total_tasks = atoi(argv[4]);

		if (!(lamb_0 + lamb_1 < mu)){
			printf("Error!: lamb_0 + lamb_1 must be less than mu\n");
			return EXIT_FAILURE;
		}

		mode_1(lamb_0, lamb_1, mu, total_tasks);
	}
	
	else { //mode 2
		char* file_name = argv[1]; 
		mode_2(file_name);
	}
	

	return EXIT_SUCCESS;
}
