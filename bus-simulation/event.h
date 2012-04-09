#ifndef EVENT_H
#define EVENT_H

#include "BusStop.h"
#include "bus.h"
#include "busline.h"
#include <QMap>
#include <iostream>

class Event{
public:
    Event(double time);
    double time() const;
    virtual int type() const = 0;
    static const int NEW_COMMUTER_EVENT = 1;
    static const int BUS_AT_STOP_EVENT = 2;
    static const int BUS_CHANGE_LINE_EVENT = 3;
private:
    double _time;
};



class EventList{

public:
    typedef QMap<double,Event*>::const_iterator const_iterator;

    void addEvent(Event *event);
    const_iterator begin() const;
    const_iterator end() const;
private:
    QMap<double,Event*> events;
};

class NewCommuterEvent : public Event{
public:
    NewCommuterEvent(double time,BusStop from, BusStop to);
    BusStop from() const;
    BusStop to() const;
    int type() const;
private:
    int _from;
    int _to;
};

class BusAtStopEvent : public Event{
public:
    BusAtStopEvent(double time,Bus bus, BusStop busStop);
    Bus bus() const;
    BusStop busStop() const;
    int type() const;
private:
    int _bus;
    int _busStop;
};

class BusChangeLineEvent : public Event{
public:
    BusChangeLineEvent(double time,Bus bus, BusLine newLine);
    Bus bus() const;
    BusLine newBusLine() const;
    int type() const;
private:
    int _bus;
    int _busLine;
};

std::ostream& operator<<(std::ostream &out,const NewCommuterEvent& nce);
std::ostream& operator<<(std::ostream &out,const BusAtStopEvent& nce);
std::ostream& operator<<(std::ostream &out,const BusChangeLineEvent& nce);

#endif // EVENT_H
