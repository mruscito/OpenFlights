#include <iostream>
#include <unordered_map>
#include <fstream>
#include <vector>
#include <map>


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
struct node {
    int id;
    double latitude;
    double longitude;
    std::string name;
    std::string code;
    std::string city;
};

class projectController {
    public:
    projectController(const std::string &airportFile, const std::string &airlineFile, const std::string &routeFile);
    
    private:
    std::string airportFile;
    std::string airlineFile;
    std::string routeFile;
    std::map<int, node> airportMap;
    std::unordered_map<std::string, int> nameToIdMap;
    
    void constructMaps();
    void makeIdToNameMap();
    void makeRouteMap();
    void makeAirportMap();
    std::vector<std::string> parseCSVLine(const std::string &line);
    std::unordered_map<int, std::string> airlineNames;

    //TESTING FUNCTION ONLY USE FOR TESTING!!!!
    void printOutAirLine();
};