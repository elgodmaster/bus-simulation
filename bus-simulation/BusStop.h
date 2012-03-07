#ifndef BUSSTOP_H
#define BUSSTOP_H

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

    static void load();
    static void save();
    static QList<BusStop> busStops();
private:
    BusStop(BusStopInternal *bsp);
    BusStopInternal *_busStopInternal;
    static QMap<int,BusStopInternal*> _busStops;
};

std::ostream& operator<<(std::ostream& out,const BusStop& busStop);

#endif // BUSSTOP_H
