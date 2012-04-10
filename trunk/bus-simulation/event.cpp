#include "event.h"
#include "busstop.h"
#include "bus.h"
#include "busline.h"
#include <QDebug>

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
       <<"\n\tNewBusLine: BusLine { id: "<<nce.newBusLine().id()<<"}\n}";
    return out;
}

Bus BusChangeLineEvent::bus()const{
    return Bus::busById(_bus);
}

BusLine BusChangeLineEvent::newBusLine()const{
    return BusLine::busLineById(_busLine);
}

EventList::EventList(){}

EventList::EventList(const EventList &eventList)
{
    makeCopy(&eventList);
}
EventList EventList::operator=(const EventList &eventList){
    makeCopy(&eventList);
    return *this;
}

void EventList::makeCopy(const EventList *eventList){
    events.clear();
    foreach(Event* event, eventList->events.values())
    {
        addEvent(event);
    }
}

BusChangeLineEvent::BusChangeLineEvent(double time, Bus bus, BusLine newLine)
    :Event(time)
{
    _bus = bus.id();
    _busLine = newLine.id();
}

BusAtStopEvent::BusAtStopEvent(double time, Bus bus, BusStop busStop)
    :Event(time)
{
    _bus = bus.id();
    _busStop = busStop.id();
}

int BusChangeLineEvent::type() const{
    return Event::BUS_CHANGE_LINE_EVENT;
}

int BusAtStopEvent::type() const{
    return Event::BUS_AT_STOP_EVENT;
}

ostream& operator<<(ostream &out,const EventList& el){
    out << "EventList {\n";

    foreach(Event* event, el)
    {
        int hour = event->time()/60;
        int minute = event->time()-hour*60;
        int second = (event->time()-hour*60-minute)*60;
        out<<"\t"<<(hour>9?"":"0")<<hour<<":"
                 <<(minute>9?"":"0")<<minute<<":"
                 <<(second>9?"":"0")<<second<<"   "<<event->description().toStdString()<<endl;
    }
    out << "}";
    return out;
}

QString NewCommuterEvent::description() const{
    return "New commuter shows up at "+from().name()+", going to "+to().name();
}

QString BusAtStopEvent::description() const{
    return "Bus "+QString::number(bus().id())+" stops at "+busStop().name();
}

QString BusChangeLineEvent::description() const{
    return "Bus "+QString::number(bus().id())+" swithces to line \""+newBusLine().name()+"\"";
}

EventList operator+(const EventList& el1, const EventList& el2){
    EventList ret = el1;
    foreach(Event *event, el2)
    {
        ret.addEvent(event);
    }
    return ret;
}

ArriveEvent::ArriveEvent(double time, BusStop busStop)
    :Event(time)
{
    _busStop = busStop.id();
}

int ArriveEvent::type()const{
    return Event::ARRIVE_EVENT;
}

QString ArriveEvent::description()const{
    return "Arrives at "+BusStop::busStopById(_busStop).name();
}

ChangeLineEvent::ChangeLineEvent(double time, BusLine busLine)
    :Event(time)
{
    _busLine = busLine.id();
}

int ChangeLineEvent::type()const{
    return Event::CHANGE_LINE_EVENT;
}

QString ChangeLineEvent::description()const{
    return "Changes line to "+BusLine::busLineById(_busLine).name();
}
