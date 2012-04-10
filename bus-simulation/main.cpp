#include "simulation.h"
#include <iostream>
#include <ctime>
#include <cassert>

using namespace std;

int main(){
    srand(time(NULL));
    loadSimulationData();


    //foreach( BusPlan bp, BusPlan::busPlans())
    //    cout<<bp<<endl;

    //foreach( CommuterTrip ct, CommuterTrip::commuterTrips())
    //    cout << ct << endl;

    //foreach(TripStatistic ts, TripStatistic::tripStatistics())
    //    cout << ts << endl;

    EventList newCommuterEvents = TripStatistic::generateNewCommuterEvents();
    //foreach(Event *event , newCommuterEvents){
    //    cout << *((NewCommuterEvent*)event) << endl;
    //}

    EventList busEvents = BusPlan::busPlans().at(0).generateBusEvents(BusStop::busStopById(0));
    EventList eventList = newCommuterEvents+busEvents;
    //cout << eventList << endl;

    //foreach(Event *event , busEvents){
    //    if(event->type()==Event::BUS_AT_STOP_EVENT)
    //        cout << *((BusAtStopEvent*)event) << endl;
    //    else if(event->type()==Event::BUS_CHANGE_LINE_EVENT)
    //        cout << *((BusChangeLineEvent*)event) << endl;
    //    else
    //        assert(false);
    //}

    simulate(eventList);

    foreach(Commuter commuter,Commuter::commuters())
    {
        cout << commuter.eventList() << endl;
    }

    foreach(Bus bus,Bus::buses())
    {
        cout << bus.eventList() << endl;
    }

    saveSimulationData();
}
