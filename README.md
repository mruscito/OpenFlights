# chienhn2-lbn2-jamestp3-ruscito2
Final Project - Open Flights

# How does our project work?
Our program uses data from https://openflights.org/data.html to find the shortest path between two airports, using how ever many layovers as needed.

or sanitizing data provided by the CSV database, the information is first separated and outputted into a formatted XML file.

*To edit input:*

Open input.txt, enter IATA codes of desired airports (3-letter codes ex. Chicago Midway -> MDW).
Capitalization does not matter, and invalid airports will be filtered by program.
Each code must be on its own line in input.txt

To change starting airport for BFS, enter IATA code at top of input.txt file
(location is noted in file and these instructions are also seen in file)

*To change airports for shortest path algorithms:*

Each test case must have 3 airports, in following order:
Starting location;
Destination location;
Landmark location;

Results are saved in output.txt and echoed on terminal (BFS is only displayed in output.txt)

*To build and execute run the following commands:*

make

./flight
