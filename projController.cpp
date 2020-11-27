#include "projController.h"


using namespace std;


projectController::projectController(const string &airportFile, const string &airlineFile, const string &routeFile) {
    this->airportFile = airportFile;
    this->airlineFile = airlineFile;
    this->routeFile = routeFile;
    constructMaps();
}

void projectController::constructMaps(){
    makeIdToNameMap();
    makeAirportMap();  
   // makeRouteMap();

   //TEST
    printOutAirLine();
}

//USING TO TEST ONLY
//PRINT OUT AIRLINE NAME + ITS ID AND EXPORT IT TO TXT FILE
void projectController::printOutAirLine(){
    ofstream myfile;
    myfile.open ("result.txt");
    
    myfile << "####################### AIRLINE NAME ###################" << endl;
    for ( auto it = airlineNames.begin(); it != airlineNames.end(); ++it ){
       myfile << " " << it->first << ":" << it->second;
       myfile << endl;
    }
    myfile << "####################### ID MAP ###################" << endl;
    for ( auto it = nameToIdMap.begin(); it != nameToIdMap.end(); ++it ){
        myfile << " " << it->first << ":" << it->second;
        myfile << endl;
    }
    myfile << "####################### AIRPORT MAP ###################" << endl;
    for(auto it = airportMap.begin(); it != airportMap.end(); ++it){
        myfile << " " << it->first;
        myfile << endl;
    }
    myfile.close();
}

void projectController::makeIdToNameMap() {
    ifstream infile(airlineFile.c_str());
    string line;
    // Seperates each line into vectors, and puts needed values in map
    while(getline(infile, line)) {
        vector<string> lines = parseCSVLine(line);
        airlineNames.insert(pair<int, string>(atoi(lines[0].c_str()), lines[1]));
    }
    infile.close();
}


void projectController::makeAirportMap() {
    ifstream infile(airportFile.c_str());
    string line;

    // Seperates each line into vectors, and puts needed values in map
    while(getline(infile, line)) {
        vector<string> lines = parseCSVLine(line);
        node airport;
        airport.id = atoi(lines[AIRPORT_ID].c_str());
        airport.latitude = atof(lines[AIRPORT_LATITUDE].c_str());
        airport.longitude = atof(lines[AIRPORT_LONGITUDE].c_str());
        airport.code = lines[AIRPORT_IATA];
        airport.name = lines[AIRPORT_NAME];
        airport.city = lines[AIRPORT_CITY];
        airportMap.insert(pair<int, node>(airport.id, airport));
        nameToIdMap.insert(pair<string, int>(airport.code, airport.id));
    }
    infile.close();
}



/// HELPER FUNCTIONS
// Takes single CSV line and seperates values in vector
// Also sanitizes quotation marks from output vector
// Input example: " item1, "item2", ... "
// Output example: vector([0]: item1, [1]: item2, [2]: ...)
vector<string> projectController::parseCSVLine(const string &line) {
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