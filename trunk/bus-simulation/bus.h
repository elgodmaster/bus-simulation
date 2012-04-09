#ifndef BUS_H
#define BUS_H

#include <QPair>
#include <QMap>
#include "BusStop.h"

class BusPrivate{
public:
    int id;
};

class Bus{
public:
    Bus();
    Bus(const Bus& bus);
    Bus(BusPrivate* bp);
    Bus operator=(const Bus& bus);
    int id() const;
    static QList<Bus> buses();
    static Bus busById(int id);
private:
    QList<int> _commuters;
    BusPrivate *_busPrivate;
    static QMap<int, BusPrivate*> _buses;
};

std::ostream& operator<<(std::ostream& out, const Bus& bus);

#endif // BUS_H
