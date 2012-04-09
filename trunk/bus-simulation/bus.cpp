#include "bus.h"
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
