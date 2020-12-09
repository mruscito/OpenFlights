#pragma once
#include <string>
#include <unordered_map>
#include <map>
#include <vector>
#include <cmath>
#include <cctype>
#include <algorithm>
#include "edge.h"

using namespace std;

enum airportCSVMeanings {
    AIRPORT_ID,
    AIRPORT_NAME,
    AIRPORT_CITY,
    AIRPORT_COUNTRY,
    AIRPORT_IATA,
    AIRPORT_ICAO,
    AIRPORT_LATITUDE,
    AIRPORT_LONGITUDE
};

//  struct for airports in graph
struct node {
    int id;
    double latitude;
    double longitude;
    string code;
    string city;
    unordered_map<int, Edge> departures; //  destination airport, edge between nodes
};

//  graph class connecting airports with flights
class FlightMap {
    public:
        map<int, node> airportMap;
        unordered_map<int, string> idToCodeMap; //  converts airport ID to aiport IATA code
        unordered_map<string, int> codeToIdMap; //  converts airport IATA code to ID
        
        void insertNode(vector<string> line);
        void insertEdge(vector<string> line);

    private:
        double findDistance(int start, int dest);
};
