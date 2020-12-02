#pragma once
#include <string>
#include <limits.h>

using namespace std;

enum routeCSVMeanings {
    ROUTE_AIRLINE,
    ROUTE_AIRLINEID,
    ROUTE_SOURCE,
    ROUTE_SOURCEID,
    ROUTE_DESTINATION,
    ROUTE_DESTINATIONID
};

//  Edge class to be used in graph
class Edge {
    public:
        //  Constructor without given weight
        Edge(int s, int d)
            : source(s), dest(d), weight(INT_MAX)
            {};
        
        //  Constructor with given weight
        Edge(int s, int d, double w)
            : source(s), dest(d), weight(w)
            {};
        
        //  source getter
        int getSourceId() {
            return source;
        }

        //  destination getter
        int getDestId() {
            return dest;
        }

        //  weight getter
        double getWeight() {
            return weight;
        }

        //  weight setter
        void setWeight(double w) {
            weight = w;
        }

        //  compares weight of 2 edges
        bool operator<(const Edge& other) const {
            return weight < other.weight;
        }

        bool operator==(Edge& other) const {
            if (source != other.source)
                return false;
            if (dest != other.dest)
                return false;
            return true;
        }
    
    private:
        int source;  //  ID of source of the egde
        int dest;    //  ID of destination of the edge
        double weight;  //  distance of flight
};
