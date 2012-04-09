#ifndef BUSPLAN_H
#define BUSPLAN_H

#include "busline.h"
#include "event.h"
#include <QMap>
#include <QString>
#include <QList>
#include <iostream>
#include <QPair>

class BusPlanPrivate
{
public:
    int id;
    QString name;
    QMap<int,QList<double> > busPlan;
};

class BusPlan
{
public:
    BusPlan();
    BusPlan(const BusPlan& busPlan);
    BusPlan operator=(const BusPlan& busPlan);

    int id() const;
    QString name() const;
    QList<QPair<BusLine,QList<double> > > busLineTables() const;

    static void load();
    static void save();

    static QList<BusPlan> busPlans();
    EventList generateBusEvents() const;
private:
    BusPlan(BusPlanPrivate *bpp);
    BusPlanPrivate *_busPlanPrivate;
    static QMap<int,BusPlanPrivate*> _busPlans;
};

std::ostream& operator<<(std::ostream& out,const BusPlan& busPlan);

#endif // BUSPLAN_H
