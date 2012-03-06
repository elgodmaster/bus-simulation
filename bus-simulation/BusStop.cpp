#include "BusStop.h"

using namespace std;

QMap<int,BusStopInternal*> BusStop::_busStops;

BusStop::BusStop(){
    _busStopInternal = new BusStopInternal();
    if(_busStops.isEmpty())
        _busStopInternal->id = 0;
    else
        _busStopInternal->id = _busStops.values().last()->id+1;
    _busStops.insert(_busStopInternal->id,_busStopInternal);
}

ostream& operator<<(ostream& out, const BusStop& busStop){
    out<<"BusStop{id:"<<busStop.id()<<" name: "<<busStop.name().toStdString()<<" }";
    return out;
}

BusStop operator=(const BusStop& busStop)
{

}
