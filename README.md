# ECE368_project1

This project simulates an M/M/1 queue. mode_1 takes 4 parameters: lamb_0, lamb_1, mu, total_tasks.
Where lamb_0 is arrival rate of priority 0 tasks, and lamb_1 is arrival rate of priority 1 tasks. Priority 0 is greater priorty than 1. Mu is service rate of both types of tasks. Total tasks is the total number of lamb_0 arrivals and lamb_1 arrivals.

Mode_2 takes in 1 text file with the format scene in test1 file. The first 2 lines are as follows:

0 0 22
0 1 1

Column 1 is their arrival time. Column 2 is priority, Column 3 is their service time.
