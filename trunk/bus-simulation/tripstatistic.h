#ifndef TRIPSTATISTIC_H
#define TRIPSTATISTIC_H

#include "tripstatistic.h"
#include "BusStop.h"
#include <QList>
#include <QPair>

class TripStatisticPrivate{
public:
    int from;
    int to;
    QList<double> frequencies;
};

class TripStatistic{
public:
    TripStatistic();
    TripStatistic(const TripStatistic& tripStatistic);
    TripStatistic operator=(const TripStatistic& tripStatistic);

    BusStop from() const;
    BusStop to() const;
    QList<double> frequencies() const;

    static void load();

    static QList<TripStatistic> tripStatistics();
private:
    TripStatistic(TripStatisticPrivate *ctp);
    TripStatisticPrivate *tripStatisticPrivate;

    static QMap<QPair<int,int>,TripStatisticPrivate*> _tripStatistics;
    static int _numberOfDays;
};

std::ostream& operator<<(std::ostream& out,const TripStatistic& tripStatistic);

#endif


