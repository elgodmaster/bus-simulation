#ifndef BUS_H
#define BUS_H

#include "event.h"
#include <QPair>
#include <QMap>

class BusPrivate{
public:
    int id;
    int busLine;
    EventList eventList;
};

class Bus{
public:
    Bus();
    Bus(const Bus& bus);
    Bus(BusPrivate* bp);
    Bus operator=(const Bus& bus);
    int id() const;

    void setBusLine(BusLine busLine);

    void addEvent(Event *event);
    EventList eventList() const;

    static QList<Bus> buses();
    static Bus busById(int id);
private:
    QList<int> _commuters;
    BusPrivate *_busPrivate;
    static QMap<int, BusPrivate*> _buses;
};

std::ostream& operator<<(std::ostream& out, const Bus& bus);

#endif // BUS_H
