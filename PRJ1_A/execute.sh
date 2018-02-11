#! /bin/bash

#Modes of operation:
# 1.) if you would like to run only one test case. The first argument is the mode, the second argument is which test case
# 2.) if you would like to run all test cases both modes. type in "-a" as your argument
# 3.) if you would like to run all of one mode type. use one argument either 1 or 2 for either mode

clear

lamb_0=0.9
lamb_1=0
mu=1
total_tasks=10000

#MODE 1 TEST 1 ######################################################
if [[ $1 == "1" && $2 == "1" || $1 == "-a" || ($# == 1 && $1 == "1") ]]
then
	printf "==========================================================================================\n"	
	echo "Running mode_1 with lamb_0 = $lamb_0, lamb_1 =  $lamb_1, mu = $mu, total_tasks = $total_tasks"
	gcc -g -std=c99 -lm  -Wall -Wshadow --pedantic -Wvla -Werror simulation.c simulation_main.c -o simulation
	./simulation $lamb_0 $lamb_1 $mu $total_tasks > debugging_info.txt
	cat proj1-a_output
fi


#MODE 1 TEST 2 ######################################################
if [[ $1 == "1" && $2 == "2" || $1 == "-a" || ($# == 1 && $1 == "1") ]]
then	
	lamb_0=0
	lamb_1=0.2
	mu=0.9
	total_tasks=10000
	printf "==========================================================================================\n"	

	echo "Running mode_1 with lamb_0 = $lamb_0, lamb_1 =  $lamb_1, mu = $mu, total_tasks = $total_tasks"
	gcc -g -std=c99 -lm  -Wall -Wshadow --pedantic -Wvla -Werror simulation.c simulation_main.c -o simulation
	./simulation $lamb_0 $lamb_1 $mu $total_tasks > debugging_info.txt
	cat proj1-a_output
fi

#MODE 1 TEST 3 ######################################################
if [[ $1 == "1" && $2 == "3" || $1 == "-a" || ($# == 1 && $1 == "1") ]]
then
	lamb_0=0.6
	lamb_1=0.2
	mu=1.3
	total_tasks=10000
	
	printf "==========================================================================================\n"	

	echo "Running mode_1 with lamb_0 = $lamb_0, lamb_1 =  $lamb_1, mu = $mu, total_tasks = $total_tasks"
	gcc -g -std=c99 -lm  -Wall -Wshadow --pedantic -Wvla -Werror simulation.c simulation_main.c -o simulation
	./simulation $lamb_0 $lamb_1 $mu $total_tasks > debugging_info.txt
	cat proj1-a_output
fi

 
#MODE 1 TEST 4 ######################################################
if [[ $1 == "1" && $2 == "4" || $1 == "-a" || ($# == 1 && $1 == "1") ]]
then
	lamb_0=0.2
	lamb_1=0.6
	mu=1.1
	total_tasks=10000
	
	printf "==========================================================================================\n"	

	echo "Running mode_1 with lamb_0 = $lamb_0, lamb_1 =  $lamb_1, mu = $mu, total_tasks = $total_tasks"
	gcc -g -std=c99 -lm  -Wall -Wshadow --pedantic -Wvla -Werror simulation.c simulation_main.c -o simulation
	./simulation $lamb_0 $lamb_1 $mu $total_tasks > debugging_info.txt
	cat proj1-a_output
fi

if [[ $1 == "2" && $2 == "1" || $1 == "-a" || ($# == 1 && $1 == "2")]]
then

	printf "===========================================================================================\n"	


	printf "RUNNING MODE_2 WITH TEST1...\n\n"
	#run mode_2 with input text_file1
	gcc -g -std=c99 -lm  -Wall -Wshadow --pedantic -Wvla -Werror simulation.c simulation_main.c -o simulation
	./simulation test_files/test1 > debugging_info.txt
	printf "ACTUAL OUTPUT: \n"
	cat proj1-a_output
	printf "\nDIFFERENCES:\n"
	python -c 'import findDifferences; findDifferences.showDifferences("expected1.txt")'
fi

if [[ $1 == "2" && $2 == "2" || $1 == "-a" || ($# == 1 && $1 == "2")]]
then
	printf "==========================================================================================\n"	


	printf "RUNNING MODE_2 WITH TEST2...\n\n"
	#run mode_2 with input text_file2
	gcc -g -std=c99 -lm  -Wall -Wshadow --pedantic -Wvla -Werror simulation.c simulation_main.c -o simulation
	./simulation test_files/test2 > debugging_info.txt
	printf "ACTUAL OUTPUT: \n"
	cat proj1-a_output 
	printf "\nDIFFERENCES:\n"
	python -c 'import findDifferences; findDifferences.showDifferences("expected2.txt")'
fi

if [[ $1 == "2" && $2 == "3" || $1 == "-a"|| ($# == 1 && $1 == "2") ]]
then
	
	printf "==========================================================================================\n"	


	printf "RUNNING MODE_2 WITH TEST3...\n\n"
	#run mode_2 with input text_file3
	gcc -g -std=c99 -lm  -Wall -Wshadow --pedantic -Wvla -Werror simulation.c simulation_main.c -o simulation
	./simulation test_files/test3 > debugging_info.txt
	printf "ACTUAL OUTPUT: \n"
	cat proj1-a_output
	printf "\nDIFFERENCES:\n"
	python -c 'import findDifferences; findDifferences.showDifferences("expected3.txt")'
fi


printf "==========================================================================================="

exit 0
