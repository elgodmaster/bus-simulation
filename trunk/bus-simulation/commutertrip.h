#ifndef COMMUTERTRIP_H
#define COMMUTERTRIP_H

#include <QMultiMap>
#include <QPair>
#include "BusStop.h"

class CommuterTripPrivate
{
public:
    int from;
    int to;
    double startTime;
    double endTime;
};

class CommuterTrip
{
public:
    CommuterTrip();
    CommuterTrip(const CommuterTrip& commuterTrip);
    CommuterTrip operator=(const CommuterTrip& commuterTrip);

    BusStop from() const;
    BusStop to() const;
    double startTime() const;
    double endTime() const;

    static void loadFromGroupedSet();
    static void load();
    static void save();

    static QList<CommuterTrip> commuterTrips();
    static int numberOfDays();
private:
    CommuterTrip(CommuterTripPrivate *ctp);
    CommuterTripPrivate *commuterTripPrivate;
    static QMultiMap<QPair<int,int>,CommuterTripPrivate*> _commuterTrips;
    static bool commuterTripsAreContinuous(CommuterTripPrivate* ctp1,CommuterTripPrivate* ctp2);
    static CommuterTripPrivate *combine(CommuterTripPrivate* ctp1,CommuterTripPrivate* ctp2);
    static int _numberOfDays;
};

#endif // COMMUTERTRIP_H

std::ostream& operator<<(std::ostream& out,const CommuterTrip& commuterTrip);
