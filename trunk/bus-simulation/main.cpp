#include <iostream>
#include "Simulation.h"

using namespace std;

int main(){
    loadSimulationData();

    foreach(BusStop bs, BusStop::busStops())
        cout<<bs<<endl;

    saveSimulationData();
}
