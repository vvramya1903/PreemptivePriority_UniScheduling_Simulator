# PreemptivePriority_UniScheduling_Simulator

You are to implement a simple uni-processor scheduling simulator.  Your simulator will step through a sequence of time units, performing the actions of a simple operating system scheduler.
 
The main input to your simulator will be a file containing process-information.  Each line in the file will be of the form:
	
Arrive Priority CPU_Time

Examples:
	process that arrives at time 10, has a priority of 5 and has one CPU burst of duration 8:
	0 5 8

	process that arrives at time 12, has a priority of 8 and has a CPU burst of duration 72:
	2 8 72

	An example of a complete input file is given below.  It contains each of the above three  processes with first line containing a single value indicating how many processes there are:
	3
	0 5 8
	2 8 72
	5 2 7

Some helpful notes/limitations:
1)	Arrival times will be strictly increasing in the input file.
2)	Your program should accept any valid input file 
3)	There will be at most 100 processes.
4)	Lower numbers imply higher priority, with the highest priority a 0 and the lowest priority a 9.

Your scheduler should be a preemptive priority scheduler with round-robin as a secondary scheduling criteria.  The best solution will allow the user to vary the time quantum but a default of 2 should be used for quantum.

Include enough output of your program to show processes being dispatched, preempted, completed, etc.  At the end of the simulation, output the turnaround time for each process as well as average turnaround time.

Provide an electronic version of your program source on Blackboard.  I may also ask you to demonstrate program execution.
![image](https://user-images.githubusercontent.com/58719118/222627710-00c00edc-56b4-465c-9a6a-634615e91450.png)
