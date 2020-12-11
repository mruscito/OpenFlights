#include <iostream>
#include <vector>
#include <fstream>
#include "openflights.h"

using namespace std;

//  Only performs 1 BFS because the output is large and BFS are all similar so redundant to perform multiple
//  But will continue to find optimal paths between start and destination until end of input.txt
int main(){
    OpenFlights newFlights("source/airports.dat", "source/routes.dat");

    // Read in input file
    ifstream infile;
    infile.open("input.txt");
    // Write to output file
    ofstream outfile;
    outfile.open("output.txt");

    //  Get location to start BFS from
    string startBFSlocation;
    int startBFS = -1;  // currently no valid input for starting location
    do {
    getline(infile, startBFSlocation);
    startBFS = newFlights.convertToId(startBFSlocation);  //  convert location to airport ID
    } while (startBFS < 0);

    //  Perform BFS
    cout<<"Perfomring BFS beginning at "<<startBFSlocation<<endl;
    outfile<<"BFS beginning at "<<startBFSlocation<<":"<<endl;
    vector<string> bfs = newFlights.BFS(startBFS);
    for (size_t i=0; i<bfs.size()-1; i++) {
        if (bfs[i] != "")// not all airports have an IATA code, this filters those out of BFS
            outfile<<bfs[i]<<", ";
    }
    outfile<<bfs[bfs.size()-1]<<endl;
    outfile<<endl;
    cout<<"BFS Complete"<<endl;

    //  Continues to find optimal paths until end of input.txt
    while (infile.peek() != EOF) {

        // Get starting location
        string startLocation;
        int start = -1;  // currently no valid input for starting location
        do {
        if (infile.peek() == EOF) { //  check that still input.txt has a valid airport
            cout<<"Error with input.txt: Make sure to have a valid airport at end of file"<<endl;
            return 0;
        }
        getline(infile, startLocation);
        start = newFlights.convertToId(startLocation);  //  convert location to airport ID
        } while (start < 0);
        cout<<"Starting Location: "<<startLocation<<endl;
        outfile<<"Starting Location: "<<startLocation<<endl;

        // Get final destination
        string destLocation;
        int dest = -1;  // currently no valid input for destination
        do {
        if (infile.peek() == EOF) { //  check that still input.txt has a valid airport
            cout<<"Error with input.txt: Make sure to have a valid airport at end of file and a final destination"<<endl;
            return 0;
        }
        getline(infile, destLocation);
        dest = newFlights.convertToId(destLocation);  //  convert location to airport ID
        } while (dest < 0);
        cout<<"Final Destination: "<<destLocation<<endl;
        outfile<<"Final Destination: "<<destLocation<<endl;

        //  Get landmark destination
        string landmarkLocation;
        int landmark = -1;  // currently no valid input for landmark
        do {
        if (infile.peek() == EOF) { //  check that still input.txt has a valid airport
            cout<<"Error with input.txt: Make sure to have a valid airport at end of file and a landmark destination"<<endl;
            return 0;
        }
        getline(infile, landmarkLocation);
        landmark = newFlights.convertToId(landmarkLocation);  //  convert location to airport ID
        } while (landmark < 0);
        cout<<"Landmark Stop: "<<landmarkLocation<<endl;
        outfile<<"Landmark Stop: "<<landmarkLocation<<endl;

        //  Perform BFS from start to dest
        vector<string> bfsPath = newFlights.BFS(start, dest);
        if (bfsPath.empty()) {  //  no path could be found between start and destination
            cout<<"No flights connecting "<<startLocation<<" and "<<destLocation<<endl;
            outfile<<"We are sorry, there are no commercial flights between "<<startLocation<<" and "<<destLocation<<endl;
            cout<<endl;
            outfile<<endl;
            continue;   //  stops performing searches for set of locations
        }
        cout<<"For the least number of connecting flights, the airports you should fly to are: "<<endl;
        outfile<<"For the least number of connecting flights, the airports you should fly to are: "<<endl;
        for (size_t i=0; i<bfsPath.size()-1; i++) {
            cout<<bfsPath[i]<<" -> ";
            outfile<<bfsPath[i]<<" -> ";
        }
        cout<<bfsPath[bfsPath.size()-1]<<endl;
        outfile<<bfsPath[bfsPath.size()-1]<<endl;

        // Perform Dijkstra's search
        tuple<vector<string>,double> dijkstra = newFlights.dijkstra(start, dest);
        cout<<"For the shortest distance traveled, the airports you should fly to are: "<<endl;
        outfile<<"For the shortest distance traveled, the airports you should fly to are: "<<endl;
        for (size_t i=0; i<get<0>(dijkstra).size()-1; i++) {
            cout<<get<0>(dijkstra)[i]<<" -> ";
            outfile<<get<0>(dijkstra)[i]<<" -> ";
        }
        cout<<get<0>(dijkstra)[get<0>(dijkstra).size()-1]<<endl;
        outfile<<get<0>(dijkstra)[get<0>(dijkstra).size()-1]<<endl;
        cout<<"Total distance of flights: "<<get<1>(dijkstra)<<" kilometers"<<endl;
        outfile<<"Total distance of flights: "<<get<1>(dijkstra)<<" kilometers"<<endl;

        //  Perform Landmark Algorithm
        tuple<vector<string>,double> landmarkSearch = newFlights.landmark(start, landmark, dest);
        if (get<0>(landmarkSearch).empty()) {   //  no path to landmark
            cout<<"No flights connecting to "<<landmarkLocation<<endl;
            outfile<<"We are sorry, there are no commercial flights that fly to "<<landmarkLocation<<endl;
            continue;   //  stops performing searches for set of locations
        }
        cout<<"For the shortest distance from "<<startLocation<<" to "<<destLocation<<" with a pitstop at "<<landmarkLocation<<", the airports you should fly to are: "<<endl;
        outfile<<"For the shortest distance from "<<startLocation<<" to "<<destLocation<<" with a pitstop at "<<landmarkLocation<<", the airports you should fly to are: "<<endl;
        for (size_t i=0; i<get<0>(landmarkSearch).size()-1; i++) {
            cout<<get<0>(landmarkSearch)[i]<<" -> ";
            outfile<<get<0>(landmarkSearch)[i]<<" -> ";
        }
        cout<<get<0>(landmarkSearch)[get<0>(landmarkSearch).size()-1]<<endl;
        outfile<<get<0>(landmarkSearch)[get<0>(landmarkSearch).size()-1]<<endl;
        cout<<"Total distance of flights: "<<get<1>(landmarkSearch)<<" kilometers"<<endl;
        outfile<<"Total distance of flights: "<<get<1>(landmarkSearch)<<" kilometers"<<endl;
        cout<<endl;
        outfile<<endl;
    }

    infile.close();
    outfile.close();

    return 0;
}
