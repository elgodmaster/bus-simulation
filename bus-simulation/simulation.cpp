#include "simulation.h"
#include "commuter.h"
#include "bus.h"
using namespace std;

void processNewCommuterEvent(NewCommuterEvent* event){
    Commuter commuter;
    commuter.setDestination(event->to());
    event->from().addCommuter(commuter);
    commuter.addEvent(new ArriveEvent(event->time(),event->from()));
}
void processBusAtStopEvent(BusAtStopEvent* event){
    event->bus().addEvent(new ArriveEvent(event->time(),event->busStop()));
}
void processBusChangeLineEvent(BusChangeLineEvent* event){
    event->bus().setBusLine(event->newBusLine());
    event->bus().addEvent(new ChangeLineEvent(event->time(),event->newBusLine()));
}

void loadSimulationData()
{
    BusStop::load();
    BusLine::load();
    BusPlan::load();
    CommuterTrip::loadFromGroupedSet();
    TripStatistic::load();
}

void saveSimulationData()
{
    BusStop::save();
    BusLine::save();
    BusPlan::save();
}

void simulate(EventList eventList){
    cout<<"Starting simulation...\n";
    foreach(Event *event, eventList)
    {
        if(event->type()==Event::NEW_COMMUTER_EVENT)
        {
            processNewCommuterEvent((NewCommuterEvent*)event);
        }
        else if(event->type()==Event::BUS_AT_STOP_EVENT)
        {
            processBusAtStopEvent((BusAtStopEvent*)event);
        }
        else
        {
            assert(event->type()==Event::BUS_CHANGE_LINE_EVENT);
            processBusChangeLineEvent((BusChangeLineEvent*)event);
        }
    }
}
