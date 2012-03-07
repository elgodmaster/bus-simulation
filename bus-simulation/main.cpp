#include <iostream>
#include "simulation.h"

using namespace std;

int main(){
    loadSimulationData();

    foreach(BusStop bs, BusStop::busStops())
        cout<<bs<<endl;

    foreach( BusLine bl, BusLine::busLines())
        cout<<bl<<endl;

    saveSimulationData();
}
