#include "flightmap.h"

void FlightMap::insertNode(vector<string> line) {
    node airport;
    airport.id = atoi(line[AIRPORT_ID].c_str());
    airport.latitude = atof(line[AIRPORT_LATITUDE].c_str());
    airport.longitude = atof(line[AIRPORT_LONGITUDE].c_str());
    string code;
    code = line[AIRPORT_IATA];
    transform(code.begin(), code.end(), code.begin(), [](unsigned char c){return toupper(c); });
    airport.code = code;
    airportMap.insert(pair<int, node>(airport.id, airport));
    idToCodeMap.insert(pair<int, string>(airport.id, airport.code));
    codeToIdMap.insert(pair<string, int>(airport.code, airport.id));
}

void FlightMap::insertEdge(vector<string> line) {
    int source = atoi(line[ROUTE_SOURCEID].c_str());
    int dest = atoi(line[ROUTE_DESTINATIONID].c_str());
    double weight = findDistance(source, dest);
    Edge flight(source, dest, weight);
    if (airportMap[source].departures.find(dest) == airportMap[source].departures.end())    //  checks for existing edge
        airportMap[source].departures.insert(pair<int, Edge>(dest, flight));
}

//  Uses Haversine formula to calculate the distance between 2 points on a Earth
double FlightMap::findDistance(int start, int dest) {
    double lat1 = airportMap[start].latitude;
    double lon1 = airportMap[start].longitude;
    double lat2 = airportMap[dest].latitude;
    double lon2 = airportMap[dest].longitude;

    double R = 6371000; //  average radius of Earth in meters
    double phi1 = lat1 * M_PI/180;  //  convert to radians
    double phi2 = lat2 * M_PI/180;
    double deltaPhi = (lat2-lat1) * M_PI/180;
    double deltaLambda = (lon2-lon1) * M_PI/180;

    double a = ( sin(deltaPhi/2)*sin(deltaPhi/2) ) + cos(phi1) * cos(phi2) * ( sin(deltaLambda/2)*sin(deltaLambda/2) );
    double c = 2 * atan2(sqrt(a), sqrt((1-a)));
    double d = R * c;

    return d/1000;  //  returns distance in km
}
