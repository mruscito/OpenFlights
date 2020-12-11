Week 1:
Team contracts were committed and GOALS.pdf was written. Our project will be using the OpenFlights data set, and we will implement a BFS, Dijkstra's algorithm, and the landmark algorithm.
Source CSV files were committed to git in the source folder.

Week 2:
Thanksgiving break. No work was completed over the break

Week 3:
The main skeleton of the project was outlined in the OpenFlights.cpp and OpenFlights.h files. Created a function to convert the data from the CSV files into vectors of strings so they can be
put into the graph structure with airports as vertices and flights as edges. The edge.h file outlines the class for an Edge which is then used in the Flightmap class which maintains the graph
structure. Flightmap has 3 member functions, insertNode which maps airport data into all the hash tables necessary to perform the algorithms, insertEdge which does the same but for edges, and
findDistance which uses the Haversine formula to calculate the distance between airports and assign that as the weight of each edge. In addition to the classes that maintain the data structure,
in the OpenFlights class, the function for a BFS was completed (after the mid-point check, we realized that the BFS only traverses from a start location to final destination and not a complete
traversal which will be fixed next week). Additionally, Dijkstra's algorithm was implemented and finds the most direct flight from start to destination by the shortest distance traveled. The
main.cpp file was updated in order to take input from the user for the starting location and final destination, then perform a BFS and Dijkstra's algorithm and print the results. The input
is given through the terminal and the output is printed to the terminal, so next week we will need to change this manage I/O through TXT files.

Week 4:
I/O was converted to come from input.txt and output to output.txt, terminal still prints progress of program for easy debugging purposes. Landmark algorithm was added, BFS was fixed to perform
a complete traversal. We kept the original BFS that stops at the final destination as well. Dijkstra's was debugged for the case when there are no commercial flights connecting the start to
destination. main.cpp was editted in order to perform one BFS (since a BFS is essentially the same no matter where the start location is so performing multiple would just be redundant) and
then take continuous inputs for the shortest path algorithms until the end of input.txt. Code has been extensively tested and is complete.