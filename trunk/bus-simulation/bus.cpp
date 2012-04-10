#include "bus.h"
#include "busline.h"
#include <cassert>
using namespace std;

QMap<int, BusPrivate*> Bus::_buses;

ostream& operator<<(ostream& out, const Bus& bus)
{
    out<<"Bus{ id: "<<bus.id()<<" }";
    return out;
}

Bus Bus::busById(int id){
    assert(_buses.contains(id));
    return Bus(_buses[id]);
}

int Bus::id()const{
    return _busPrivate->id;
}

Bus::Bus(BusPrivate *bp){
   _busPrivate = bp;
}

Bus::Bus(){
    _busPrivate = new BusPrivate();
    _busPrivate->id = 0;
    if(_buses.size()!=0){
        _busPrivate->id = _buses.keys().last()+1;
    }
    _buses.insert(_busPrivate->id,_busPrivate);
    _busPrivate->busLine = BusLine::NOT_IN_ROUTE;
}

Bus::Bus(const Bus& bus){
    _busPrivate = bus._busPrivate;
}

QList<Bus> Bus::buses(){
    QList<Bus> ret;
    foreach(int bus, _buses.keys())
    {
        ret.append(Bus(_buses[bus]));
    }
    return ret;
}

void Bus::setBusLine(BusLine busLine)
{
    _busPrivate->busLine=busLine.id();
}

void Bus::addEvent(Event *event){
    _busPrivate->eventList.addEvent(event);
}

EventList Bus::eventList()const{
    return _busPrivate->eventList;
}
