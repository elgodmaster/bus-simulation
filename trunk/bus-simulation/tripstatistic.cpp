#include "tripstatistic.h"
#include "commutertrip.h"
using namespace std;


int  TripStatistic::_numberOfDays;
QMap<QPair<int,int>,TripStatisticPrivate*> TripStatistic::_tripStatistics;

void TripStatistic::load()
{
    _numberOfDays = CommuterTrip::numberOfDays();

    foreach(CommuterTrip ct, CommuterTrip::commuterTrips())
    {
        int from = ct.from().id();
        int to = ct.to().id();

        double time = ct.startTime();
        int timeSlot = (int)(time/60.0);

        if(!_tripStatistics.contains(QPair<int,int>(from,to)))
        {
            TripStatisticPrivate* tsp = new TripStatisticPrivate;
            tsp->from=from;
            tsp->to=to;
            for(int i = 0 ; i < 24; i++)
                tsp->frequencies.append(0.0);
            _tripStatistics.insert(QPair<int,int>(from,to),tsp);
        }

        TripStatisticPrivate* tsp = _tripStatistics[QPair<int,int>(from,to)];
        tsp->frequencies.replace(timeSlot,tsp->frequencies.at(timeSlot)+1.0/(double)_numberOfDays);

    }
}

ostream& operator<<(ostream& out,const TripStatistic& tripStatistic)
{
    out << "TripStatistic {\n";
    out << "    from: "<<tripStatistic.from()<<"\n";
    out << "    to: "<<tripStatistic.to()<<"\n";
    for(int i = 0; i<tripStatistic.frequencies().size();i++)
    {
        if(tripStatistic.frequencies().at(i)!=0.0)
            out<<"    "<<i<<":00-"<<(i+1)<<":00    "<<tripStatistic.frequencies().at(i)<<endl;
    }
    out << "}\n";
    return out;
}

TripStatistic::TripStatistic(const TripStatistic &tripStatistic)
{
    tripStatisticPrivate = tripStatistic.tripStatisticPrivate;
}

QList<TripStatistic> TripStatistic::tripStatistics()
{
    QList<TripStatistic> ret;
    foreach(TripStatisticPrivate* tsp,_tripStatistics.values())
    {
        ret.append(TripStatistic(tsp));
    }
    return ret;
}

QList<double> TripStatistic::frequencies() const
{
    QList<double> ret;
    ret.append(tripStatisticPrivate->frequencies);
    return ret;
}

TripStatistic::TripStatistic(TripStatisticPrivate *tsp)
{
    tripStatisticPrivate = tsp;
}

BusStop TripStatistic::from() const
{
    return BusStop::busStopById(tripStatisticPrivate->from);
}

BusStop TripStatistic::to() const
{
    return BusStop::busStopById(tripStatisticPrivate->to);
}
