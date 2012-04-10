#include "commuter.h"
#include "busstop.h"
using namespace std;

QMap<int, CommuterPrivate*> Commuter::_commuters;

void Commuter::addEvent(Event *event){
    _commuterPrivate->eventList.addEvent(event);
}

int Commuter::id()const{
    return _commuterPrivate->id;
}

void  Commuter::setDestination(BusStop destination)
{
    _commuterPrivate->destination = destination.id();
}

Commuter::Commuter(){
    _commuterPrivate = new CommuterPrivate;
    _commuterPrivate->id=0;
    if(_commuters.size()!=0)
    {
        _commuterPrivate->id=_commuters.keys().last()+1;
    }
    _commuters.insert(_commuterPrivate->id,_commuterPrivate);
}

Commuter::Commuter(const Commuter &commuter){
    _commuterPrivate = commuter._commuterPrivate;
}

Commuter::Commuter(CommuterPrivate *cp){
    _commuterPrivate = cp;
}

EventList Commuter::eventList()const{
    return _commuterPrivate->eventList;
}

QList<Commuter> Commuter::commuters(){
    QList<Commuter> ret;
    foreach(int commuter,_commuters.keys()){
        ret.append(Commuter::commuterById(commuter));
    }
    return ret;
}

Commuter Commuter::commuterById(int id){
    return Commuter(_commuters[id]);
}
