#include "flightmap.h"

void FlightMap::insertNode(vector<string> line) {
    node airport;
    airport.id = atoi(line[AIRPORT_ID].c_str());
    airport.latitude = atof(line[AIRPORT_LATITUDE].c_str());
    airport.longitude = atof(line[AIRPORT_LONGITUDE].c_str());
    airport.code = line[AIRPORT_IATA];
    airport.city = line[AIRPORT_CITY];
    airportMap.insert(pair<int, node>(airport.id, airport));
    idToCodeMap.insert(pair<int, string>(airport.id, airport.code));
}

void FlightMap::insertEdge(vector<string> line) {
    int source = atoi(line[ROUTE_SOURCEID].c_str());
    int dest = atoi(line[ROUTE_DESTINATIONID].c_str());
    Edge flight(source, dest);
    if (airportMap[source].departures.find(dest) == airportMap[source].departures.end())    //  checks for existing edge
        airportMap[source].departures.insert(pair<int, Edge>(dest, flight));
}
