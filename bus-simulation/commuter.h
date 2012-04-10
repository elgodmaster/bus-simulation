#ifndef COMMUTER_H
#define COMMUTER_H

#include "event.h"
#include <QMap>

class BusStop;

class CommuterPrivate{
public:
    int id;
    int destination;
    EventList eventList;
};

class Commuter{
public:
    Commuter();
    Commuter(CommuterPrivate* cp);
    Commuter(const Commuter& commuter);
    Commuter operator=(const Commuter& commuter);

    void setDestination(BusStop destination);
    BusStop destination() const;
    int id() const;
    void addEvent(Event* event);
    EventList eventList() const;

    static QList<Commuter> commuters();
    static Commuter commuterById(int id);
private:
    CommuterPrivate* _commuterPrivate;
    static QMap<int, CommuterPrivate*> _commuters;
};

#endif // COMMUTER_H
