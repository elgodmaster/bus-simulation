#ifndef BUSLINE_H
#define BUSLINE_H

#include "busstop.h"
#include <QPair>

class BusLinePrivate
{
public:
    QList< QPair<int,double> > busLineStops;
    int id;
    QString name;
};

class BusLine
{
public:
    BusLine();
    BusLine(const BusLine& busLine);
    BusLine operator=(const BusLine& busLine);

    QList< QPair<BusStop,double> > busStops() const;
    int id() const;
    QString name() const;

    static void load();
    static void save();

    static QList<BusLine> busLines();
private:
    BusLine(BusLinePrivate *blp);
    BusLinePrivate *_busLinePrivate;
    static QMap<int,BusLinePrivate*> _busLines;
};

std::ostream& operator<<(std::ostream& out,const BusLine& busLine);

#endif // BUSLINE_H
