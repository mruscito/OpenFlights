# Final Project - Open Flights

### Group members:
* ruscito2
* lbn2
* chienhn2
* jamestp3

# How does our project work?
Our program uses data from [Open Flights](https://openflights.org/data.html) to find the shortest path between two airports.
We use BFS Traversal to find the shortest airports can land to and Dijkstra's algorithm to calculate the total distances of the trip. 

# How to use our program?

To download our program, please copy and paste this line to your terminal:

```
git clone https://github-dev.cs.illinois.edu/cs225-fa20/chienhn2-lbn2-jamestp3-ruscito2.git
```

### First you will need to edit input:

Open **input.txt**, enter **IATA codes** of desired airports (3-letter codes ex. Chicago Midway -> MDW).
Capitalization does not matter, and invalid airports will be filtered by program.
Each code must be on its own line in input.txt

1. To change starting airport for BFS, enter IATA code at top of **input.txt** file
(location is noted in file and these instructions are also seen in file)

2. To change airports for shortest path algorithms:

Each test case must have 3 airports, in following order:
Starting location;
Destination location;
Landmark location;

### Second to build the program, you need to run:
```make
make
```
in the terminal.

The makefile will create a executable file which is named 'flight'
Run this command in the terminal: 
```flight
./flight
```

Your results will export automatically in terminal window or you can open the **output.txt** file which is located in your root folder.

### Example about the results:
![GitHub Logo](/images/example.png)

### OUTPUT.TXT
![GitHub Logo](/images/output.png)
# final_project_cs225
