#include <iostream>
#include <vector>
#include "openflights.h"

using namespace std;

int main(){
    OpenFlights newFlights("source/airports.dat", "source/routes.dat");

    //Test BFS from Champaign to Dallas (should only check Chicago then Dallas)
    vector<string> bfs = newFlights.BFS(4049, 1); //3670 <-Dallas, 3830 <-Chicago, 3817 <-Sacramento
    cout<<"BFS PATH:"<<endl;
    for (size_t i=0; i<bfs.size(); i++)
        cout<<bfs[i]<<endl;
    
    tuple<vector<string>,double> dijkstra = newFlights.dijkstra(4049, 3817);
    cout<<"Dijkstra's:"<<endl;
    for (size_t i=0; i<get<0>(dijkstra).size(); i++)
        cout<<get<0>(dijkstra)[i]<<endl;
    cout<<"Total Distance Travelled: "<<get<1>(dijkstra)<<" kilometers"<<endl;
}
