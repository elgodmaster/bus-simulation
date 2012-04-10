#ifndef BUSSTOP_H
#define BUSSTOP_H

#include "commuter.h"
#include <QList>
#include <QString>
#include <QMap>
#include <iostream>
#include <QXmlStreamReader>
#include <QXmlStreamWriter>

class BusStopInternal
{
public:
    double latitude;
    double longtitude;
    QString name;
    int id;
    QList<int> commuters;
private:
};

class BusStop{
public:
    BusStop();
    BusStop(const BusStop& busStop);
    BusStop operator=(const BusStop& busStop);

    double latitude() const;
    double longtitude() const;
    QString name() const;
    int id() const;

    void addCommuter(const Commuter& commuter);

    static void load();
    static void save();
    static QList<BusStop> busStops();
    static BusStop busStopById(int id);
    static double getTravelTime(const BusStop& bs1, const BusStop& bs2);
private:
    BusStop(BusStopInternal *bsp);
    BusStopInternal *_busStopInternal;
    static QMap<int,BusStopInternal*> _busStops;
};

std::ostream& operator<<(std::ostream& out,const BusStop& busStop);

#endif // BUSSTOP_H
