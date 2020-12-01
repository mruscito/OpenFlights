#pragma once
#include <iostream>
#include <unordered_map>
#include <fstream>
#include <vector>
#include <map>
#include <queue>
#include <stack>
#include "flightmap.h"

using namespace std;

enum airlineCSVMeanings {
    AIRLINE_ID,
    AIRLINE_NAME,
    AIRLINE_ALIAS,
    AIRLINE_IATA,
    AIRLINE_ICAO
};

class OpenFlights {
    public:
        OpenFlights(const string &airportFile, const string &routeFile);
        vector<string> BFS(int start, int destination);
        vector<string> dijkstra(int start, int destination);
    
    private:
        string airportFile_;
        string routeFile_;
        FlightMap flightMap_;
        
        void constructMap();
        void insertAirports();
        void insertFlights();

        vector<string> parseCSVLine(const string &line);
};