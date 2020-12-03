#include <iostream>
#include <vector>
#include "openflights.h"

using namespace std;

int main(){
    OpenFlights newFlights("source/airports.dat", "source/routes.dat");

    // Get starting location
    string startLocation;
    int start = -1;  // currently no valid input for starting location
    do {
    cout<<"Please enter your starting location: ";
    getline(cin, startLocation);
    start = newFlights.convertToId(startLocation);  //  convert location to airport ID
    if (start < 0)  // checks if there is a valid input for starting location
        cout<<"Sorry, that airport does not seem to exist"<<endl;
    } while (start < 0);

    // Get final destination
    string destLocation;
    int dest = -1;  // currently no valid input for destination
    do {
    cout<<"Please enter your final destination: ";
    getline(cin, destLocation);
    dest = newFlights.convertToId(destLocation);  //  convert location to airport ID
    if (dest < 0)  // checks if there is a valid input for destination
        cout<<"Sorry, that airport does not seem to exist"<<endl;
    } while (dest < 0);
    cout<<endl;

    // perform BFS
    cout<<"For the least number of connecting flights, the airports you should fly to are: "<<endl;
    vector<string> bfs = newFlights.BFS(start, dest);
    for (size_t i=0; i<bfs.size()-1; i++)
        cout<<bfs[i]<<" -> ";
    cout<<bfs[bfs.size()-1]<<endl;
    cout<<endl;

    // perform Dijkstra's search
    cout<<"For the shortest distance traveled, the airports you should fly to are: "<<endl;
    tuple<vector<string>,double> dijkstra = newFlights.dijkstra(start, dest);
    for (size_t i=0; i<get<0>(dijkstra).size()-1; i++)
        cout<<get<0>(dijkstra)[i]<<" -> ";
    cout<<get<0>(dijkstra)[get<0>(dijkstra).size()-1]<<endl;
    cout<<"\nTotal distance of flights: "<<get<1>(dijkstra)<<" kilometers"<<endl;
    cout<<endl;

    return 0;
}
