#include "commutertrip.h"
#include <QDir>
#include <cassert>
#include <QDebug>
#include <iostream>
#include <QMultiMap>

using namespace std;

QMultiMap<QPair<int,int>,CommuterTripPrivate*> CommuterTrip::_commuterTrips;
int CommuterTrip::_numberOfDays;

void CommuterTrip::loadFromGroupedSet()
{
    QDir current = QDir::current();
    current.cdUp();
    current.cd("bus-simulation");
    QDir::setCurrent(current.absolutePath());
    QFile* file = new QFile("groupedcommutertrips.xml");
    assert(file->open(QIODevice::ReadOnly | QIODevice::Text));
    QXmlStreamReader xml(file);
    assert(!xml.atEnd());

    QList<QList<CommuterTripPrivate*> > groupedList;

    while(!xml.atEnd())
    {
        xml.readNextStartElement();
        assert(xml.name()=="GroupedCommuterTrips");
        assert(xml.attributes().size()==1);
        CommuterTrip::_numberOfDays = xml.attributes().first().value().toString().toInt();

        xml.readNextStartElement();
        while(xml.name()!="GroupedCommuterTrips")
        {
            assert(xml.name()=="CommuterTripGroup");
            QList<CommuterTripPrivate*> group;

            xml.readNextStartElement();
            while(xml.name()!="CommuterTripGroup")
            {
                assert(xml.name()=="CommuterTrip");
                assert(xml.tokenType() == QXmlStreamReader::StartElement);
                CommuterTripPrivate *ctp = new CommuterTripPrivate();
                xml.readNextStartElement();
                while(xml.name()!="CommuterTrip")
                {
                    if(xml.name()=="from")
                    {
                        ctp->from = xml.readElementText().toInt();
                        assert(xml.name()=="from");
                        assert(xml.tokenType()==QXmlStreamReader::EndElement);
                        xml.readNextStartElement();
                    }

                    if(xml.name()=="to")
                    {
                        ctp->to = xml.readElementText().toInt();
                        assert(xml.name()=="to");
                        assert(xml.tokenType()==QXmlStreamReader::EndElement);
                        xml.readNextStartElement();
                    }
                    if(xml.name()=="startTime")
                    {
                        xml.readNextStartElement();
                        int hour = 0;
                        double minute = 0;
                        while(xml.name()!="startTime")
                        {
                            if(xml.name()=="hour")
                            {
                                hour = xml.readElementText().toInt();
                                assert(xml.name()=="hour");
                                assert(xml.tokenType()==QXmlStreamReader::EndElement);
                                xml.readNextStartElement();
                            }
                            if(xml.name()=="minute")
                            {
                                minute = xml.readElementText().toDouble();
                                assert(xml.name()=="minute");
                                assert(xml.tokenType()==QXmlStreamReader::EndElement);
                                xml.readNextStartElement();
                            }
                        }
                        ctp->startTime = minute+hour*60.0;

                        assert(xml.name()=="startTime");
                        assert(xml.tokenType()==QXmlStreamReader::EndElement);
                        xml.readNextStartElement();
                    }
                    if(xml.name()=="endTime")
                    {
                        xml.readNextStartElement();
                        int hour = 0;
                        double minute = 0;
                        while(xml.name()!="endTime")
                        {
                            if(xml.name()=="hour")
                            {
                                hour = xml.readElementText().toInt();
                                assert(xml.name()=="hour");
                                assert(xml.tokenType()==QXmlStreamReader::EndElement);
                                xml.readNextStartElement();
                            }
                            if(xml.name()=="minute")
                            {
                                minute = xml.readElementText().toDouble();
                                assert(xml.name()=="minute");
                                assert(xml.tokenType()==QXmlStreamReader::EndElement);
                                xml.readNextStartElement();
                            }
                        }
                        ctp->endTime = minute+hour*60.0;

                        assert(xml.name()=="endTime");
                        assert(xml.tokenType()==QXmlStreamReader::EndElement);
                        xml.readNextStartElement();
                    }
                }
                assert(xml.name()=="CommuterTrip");
                assert(xml.tokenType()==QXmlStreamReader::EndElement);
                group.append(ctp);
                xml.readNextStartElement();
            }
            groupedList.append(group);
            xml.readNextStartElement();
        }
        xml.readNextStartElement();
    }
    xml.clear();
    file->close();

    foreach(QList<CommuterTripPrivate*> group,groupedList)
    {
        int i = 0;
        while(i<group.size()-1)
        {
            if(commuterTripsAreContinuous(group.at(i),group.at(i+1)))
            {
                CommuterTripPrivate *ctp1 = group.at(i);
                CommuterTripPrivate *ctp2 = group.at(i+1);
                group.removeAt(i);
                group.removeAt(i);

                CommuterTripPrivate *ctp = combine(ctp1,ctp2);
                group.insert(i,ctp);
                delete ctp1;
                delete ctp2;
            }
            else{
                i++;
            }
        }
        foreach(CommuterTripPrivate* ctp,group)
        {
            _commuterTrips.insert(QPair<int,int>(ctp->from,ctp->to),ctp);
        }
    }
}

CommuterTrip::CommuterTrip(CommuterTripPrivate *ctp)
{
    commuterTripPrivate = ctp;
}

ostream& operator<<(ostream& out,const CommuterTrip& commuterTrip)
{
    out<<"CommuterTrip { ";
    out<<"\n  from: "<<commuterTrip.from()<<", "<<(int)(commuterTrip.startTime()/60)<<":"<<(int)(commuterTrip.startTime())%60;
    out<<"\n  to:   "<<commuterTrip.to()<<", "<<(int)(commuterTrip.endTime()/60)<<":"<<(int)(commuterTrip.endTime())%60;
    out<<"\n}";
    return out;
}

BusStop CommuterTrip::from() const
{
    return BusStop::busStopById(commuterTripPrivate->from);
}

BusStop CommuterTrip::to() const
{
    return BusStop::busStopById(commuterTripPrivate->to);
}

double CommuterTrip::startTime() const
{
    return commuterTripPrivate->startTime;
}

double CommuterTrip::endTime() const
{
    return commuterTripPrivate->endTime;
}

CommuterTripPrivate *CommuterTrip::combine(CommuterTripPrivate *ctp1, CommuterTripPrivate *ctp2)
{
    CommuterTripPrivate *ctp = new CommuterTripPrivate;
    ctp->from = ctp1->from;
    ctp->startTime = ctp1->startTime;

    ctp->to = ctp2->to;
    ctp->endTime = ctp2->endTime;

    return ctp;
}

bool CommuterTrip::commuterTripsAreContinuous(CommuterTripPrivate *ctp1, CommuterTripPrivate *ctp2)
{
    if(ctp2->startTime - ctp1->endTime < 10.0)
        return true;
    return false;
}

CommuterTrip::CommuterTrip(const CommuterTrip &commuterTrip)
{
    commuterTripPrivate = commuterTrip.commuterTripPrivate;
}

QList<CommuterTrip> CommuterTrip::commuterTrips()
{
    QList<CommuterTrip> ret;
    foreach(CommuterTripPrivate* ctp,_commuterTrips.values())
    {
        ret.append(CommuterTrip(ctp));
    }
    return ret;
}

int CommuterTrip::numberOfDays()
{
    return _numberOfDays;
}
