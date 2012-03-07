#include <iostream>
#include "simulation.h"

using namespace std;

int main(){
    loadSimulationData();

    foreach( BusPlan bp, BusPlan::busPlans())
        cout<<bp<<endl;

    saveSimulationData();
}
