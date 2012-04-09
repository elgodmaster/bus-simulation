#include "event.h"

using namespace std;

void EventList::addEvent(Event *event){
    events.insert(event->time(),event);
}

NewCommuterEvent::NewCommuterEvent(double time, BusStop from, BusStop to):Event(time){
    _from = from.id();
    _to = to.id();
}
int NewCommuterEvent::type() const {return Event::NEW_COMMUTER_EVENT;}

Event::Event(double time):_time(time){}
double Event::time() const {return _time;}

std::ostream& operator<<(std::ostream &out,const NewCommuterEvent& nce)
{
    int hour = nce.time()/60;
    int minute = nce.time()-hour*60;
    out<<"NewCommuterEvent { time: "<<hour<<":"<<(minute<10?"0":"")<<minute<<" \n\tfrom: "<<nce.from()<<" \n\tto: "<<nce.to()<<"\n}";
    return out;
}

EventList::const_iterator EventList::begin() const {
    return events.begin();
}

EventList::const_iterator EventList::end() const {
    return events.end();
}

BusStop NewCommuterEvent::from()const{
    return BusStop::busStopById(_from);
}

BusStop NewCommuterEvent::to()const{
    return BusStop::busStopById(_to);
}

std::ostream& operator<<(std::ostream &out,const BusAtStopEvent& nce)
{
    int hour = nce.time()/60;
    int minute = nce.time()-hour*60;
    out<<"BusAtStopEvent { time: "<<hour<<":"<<(minute<10?"0":"")<<minute
       <<"\n\tBus: "<<nce.bus()
       <<"\n\tBusStop: "<<nce.busStop()<<"\n}";
    return out;
}

Bus BusAtStopEvent::bus()const{
    return Bus::busById(_bus);
}

BusStop BusAtStopEvent::busStop()const{
    return BusStop::busStopById(_busStop);
}

std::ostream& operator<<(std::ostream &out,const BusChangeLineEvent& nce)
{
    int hour = nce.time()/60;
    int minute = nce.time()-hour*60;
    out<<"BusChangeLineEvent { time: "<<hour<<":"<<(minute<10?"0":"")<<minute
       <<"\n\tBus: "<<nce.bus()
       <<"\n\tNewBusLine: "<<nce.newBusLine()<<"\n}";
    return out;
}

Bus BusChangeLineEvent::bus()const{
    return Bus::busById(_bus);
}

BusLine BusChangeLineEvent::newBusLine()const{
    return BusLine::busLineById(_busLine);
}
