#include <iostream>
#include "simulation.h"

using namespace std;

int main(){
    loadSimulationData();

    foreach( BusPlan bp, BusPlan::busPlans())
        cout<<bp<<endl;

    foreach( CommuterTrip ct, CommuterTrip::commuterTrips())
        cout << ct << endl;

    foreach(TripStatistic ts, TripStatistic::tripStatistics())
        cout << ts << endl;

    saveSimulationData();
}
