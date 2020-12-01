#include <iostream>
#include <vector>
#include "openflights.h"

using namespace std;

int main(){
    OpenFlights newFlights("source/airports.dat", "source/routes.dat");

    //Test BFS from Champaign to Dallas (should only check Chicago then Dallas)
    vector<string> bfs = newFlights.BFS(4049, 1); //3670 <-Dallas, 3830 <-Chicago, 3817 <-Sacramento
    for (size_t i=0; i<bfs.size(); i++)
        cout<<bfs[i]<<endl;
}
