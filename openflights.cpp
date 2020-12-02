#include "openflights.h"

using namespace std;

//  Constructor
OpenFlights::OpenFlights(const string &airportFile, const string &routeFile) {
    //  copy files to private members
    airportFile_ = airportFile;
    routeFile_ = routeFile;
    constructMap();
}

//  constructor helper
//  creates graph containing Airports and Flights
void OpenFlights::constructMap(){
    insertAirports();
    insertFlights();
    
    // TO DO: create functions to convert City names (or airport IATA codes) to airport Ids (probably done in flightmap insertAiports)
}

//  adds airports to map
void OpenFlights::insertAirports() {
    ifstream infile(airportFile_.c_str());
    string lines;

    // Seperates each line into vectors, and puts airport onto map
    while(getline(infile, lines)) {
        vector<string> line = parseCSVLine(lines);
        flightMap_.insertNode(line);
    }
    //getting a bug that the first line of file is not being parsed above -- manual insert
    flightMap_.insertNode(vector<string>{string("1"),string("Goroka Airport"),string("Goroka"),string("Papua New Guinea"),string("GKA"),string("AYGA"),
                            string("-6.081689834590001"),string("145.391998291"),string("5282"),string("10"),string("U"),string("Pacific/Port_Moresby"),
                            string("airport"),string("OurAirports")});
    infile.close();
}

//  adds flights connecting airports on map
void OpenFlights::insertFlights() {
    ifstream infile(routeFile_.c_str());
    string lines;

    // Seperates each line into vectors, and connects airports on map (without distances calculated)
    while(getline(infile, lines)) {
        vector<string> line = parseCSVLine(lines);
        flightMap_.insertEdge(line);
    }
    //getting a bug that the first line of file is not being parsed above -- manual insert
    flightMap_.insertEdge(vector<string>{string("2B"),string("410"),string("AER"),string("2965"),string("KZN"),string("2990"),string(""),string("0"),string("CR2")});
    infile.close();
}

//  Performs BFS to find route frtom start airport to destination airport
vector<string> OpenFlights::BFS(int start, int destination) {
    //  Mark all airports as not visited
    vector<bool> visited(12058);    //  highest airport ID #
    for (unsigned i=0; i<12058; i++) {
        visited[i] = false;
    }
    //  initialize BFS
    queue<int> airportQueue;    //  queue for BFS
    vector<int> previous(12058); //  maintains previous airport visited
    previous[start] = start;    //  initialize starting airport to start
    airportQueue.push(start);   //  enqueue first airport
    int current = start;    //  current airport being visited

    //  BFS
    while (!airportQueue.empty()) {
        current = airportQueue.front();
        for (auto it=flightMap_.airportMap[current].departures.begin(); it!=flightMap_.airportMap[current].departures.end(); it++) {    //  search all departures from current airport
            if (!visited[it->first]) {  //  next airport has not been visited
                previous[it->first] = current;  //  mark previous airport as current airport
                airportQueue.push(it->first);   //  enqueue next airport
                visited[it->first] = true;
            }
        }
        if (current == destination) {   //  stop once destination is reached
            break;
        }
        airportQueue.pop();
    }

    if (current != destination) { //  no path could be found between start and destination using BFS
        vector<string> T;
        return T;
    }

    //  trace back path from destination to start
    stack<int> pathId;
    while (current != start) {
        pathId.push(current);
        current = previous[current];
    }
    pathId.push(start);

    //  convert airport IDs to Airport Code
    vector<string> path;
    while (!pathId.empty()) {
        int ap = pathId.top();
        path.push_back(flightMap_.idToCodeMap[ap]);  //  To Do: add city or name (change path to vector<pair<string, string>>)
        pathId.pop();
    }
    return path;
}

//  Performs Dijkstra's algorithm to find shortest path between start and destination airports
tuple<vector<string>,double> OpenFlights::dijkstra(int start, int destination) {
    vector<double> distanceFromStart(12058);    //  total distance from start to current airport
    vector<int> previous(12058); //  maintains previous airport visited (with shortest distance to start)
    vector<int> unvisited;   //  all unvisited airports

    for (auto it=flightMap_.airportMap.begin(); it!=flightMap_.airportMap.end(); it++) {
        distanceFromStart[it->first] = INT_MAX; //  set all distances to infinity
        unvisited.push_back(it->first);
    }
    distanceFromStart[start] = 0;   //  distance from start to start
    previous[start] = start;    //  initialize starting airport to start

    int current;    //  unvisited airport with shortest distanceFromStart
    while (!unvisited.empty()) {
        double minDistance = INT_MAX;   //  minimum distance from start
        int minIndex;   //  index into unvisited of node with shortest distance from start
        for (size_t i=0; i<unvisited.size(); i++) { // find node in unvisited with min distanceFromStart
            if (distanceFromStart[unvisited[i]] < minDistance) {
                minDistance = distanceFromStart[unvisited[i]];
                minIndex = i;
            }
        }
        current = unvisited[minIndex];  //  update current
        unvisited.erase(unvisited.begin()+minIndex);    //  remove current from unvisited
        if (current == destination) //  end search if destination has minimum distance
            break;
        for (auto it=flightMap_.airportMap[current].departures.begin(); it!=flightMap_.airportMap[current].departures.end(); it++) {    //  search all departures from current airport
            double newDistance = distanceFromStart[current] + (it->second).getWeight(); //  distanceFromStart through current to departure airport
            if (newDistance < distanceFromStart[it->first]) {   //  update distance if shorter flight
                distanceFromStart[it->first] = newDistance;
                previous[it->first] = current;  //  update previous airport visited
            }
        }
    }

    if (current != destination) { //  no path could be found between start and destination
        tuple<vector<string>,double> T;
        return T;
    }

    //  trace back path from destination to start
    stack<int> pathId;
    while (current != start) {
        pathId.push(current);
        current = previous[current];
    }
    pathId.push(start);

    //  convert airport IDs to Airport Code
    vector<string> path;
    while (!pathId.empty()) {
        int ap = pathId.top();
        path.push_back(flightMap_.idToCodeMap[ap]);  //  To Do: add city or name (change path to vector<pair<string, string>>)
        pathId.pop();
    }
    tuple<vector<string>,double> shortestPath(path, distanceFromStart[destination]);    //  create tuple of path and total distance
    return shortestPath;
}



// Takes single CSV line and seperates values in vector
// Also sanitizes quotation marks from output vector
// Input example: " item1, "item2", ... "
// Output example: vector([0]: item1, [1]: item2, [2]: ...)
vector<string> OpenFlights::parseCSVLine(const string &line) {
    char current;
    bool isQuote = false;
    string builtStr = "";
    vector<string> outputStrings;

    // Cycle through all characters
    for(size_t i = 0; i < line.size(); ++i) {
        current = line[i];

        // Pushes string into vector when comma found
        if(!isQuote) {
            if(current == ',') {
                outputStrings.push_back(builtStr);
                builtStr = string();
            }
            else if(current == '"')
                isQuote = true;
            else
                builtStr += current;
        }

        // Checks for matching quotation marks and removes from output
        else {
            if(current == '"' && i+1 < line.size()) {
                if(line[i+1] == '"') {
                    builtStr += '"';
                    ++i;
                }
                else
                    isQuote = false;
            }
            else
                builtStr += current;
        }
    }
    return outputStrings;
}
