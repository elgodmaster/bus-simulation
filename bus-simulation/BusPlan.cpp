#include "busplan.h"
#include <QDir>
#include <cassert>
#include <QXmlStreamReader>
#include <QDebug>
#include "busline.h"

using namespace std;

QMap<int, BusPlanPrivate *> BusPlan::_busPlans;

BusPlan::BusPlan(const BusPlan &busPlan)
{
    _busPlanPrivate = busPlan._busPlanPrivate;
}

BusPlan::BusPlan(BusPlanPrivate *bpp)
{
    _busPlanPrivate = bpp;
}

void BusPlan::load()
{
    QDir current = QDir::current();
    current.cdUp();
    current.cd("bus-simulation");
    QDir::setCurrent(current.absolutePath());
    QFile* file = new QFile("busplans.xml");
    assert(file->open(QIODevice::ReadOnly | QIODevice::Text));
    QXmlStreamReader xml(file);
    assert(!xml.atEnd());

    assert(xml.readNextStartElement());
    assert(xml.name()=="BusPlans");

    xml.readNextStartElement();

    while(xml.name()!="BusPlans")
    {
        assert(xml.name()=="BusPlan");

        BusPlanPrivate *bpp = new BusPlanPrivate;

        xml.readNextStartElement();
        while(xml.name()!="BusPlan")
        {
            if(xml.name()=="id")
            {
                bpp->id = xml.readElementText().toInt();
            }
            if(xml.name()=="name")
            {
                bpp->name = xml.readElementText();
            }
            if(xml.name()=="busLines")
            {
                xml.readNextStartElement();

                while(xml.name()!="busLines")
                {
                    assert(xml.name()=="BusLine");
                    int id;
                    QList<double> offsets;

                    xml.readNextStartElement();

                    while(xml.name()!="BusLine")
                    {
                        if(xml.name()=="id")
                        {
                            id = xml.readElementText().toInt();
                        }
                        if(xml.name()=="offsets")
                        {
                            xml.readNextStartElement();
                            while(xml.name()!="offsets")
                            {
                                assert(xml.name()=="offset");
                                xml.readNextStartElement();

                                int hour = 0;
                                double minute = 0;

                                while(xml.name()!="offset")
                                {

                                    if(xml.name()=="hour")
                                    {
                                        hour = xml.readElementText().toInt();
                                    }
                                    if(xml.name()=="minute")
                                    {
                                        minute = xml.readElementText().toDouble();
                                    }

                                    xml.readNextStartElement();
                                }

                                offsets.append(hour*60+minute);
                                xml.readNextStartElement();
                            }
                        }
                        xml.readNextStartElement();
                    }
                    bpp->busPlan.insert(id,offsets);
                    xml.readNextStartElement();
                }
            }

            xml.readNextStartElement();
        }
        _busPlans.insert(bpp->id,bpp);
        xml.readNextStartElement();
    }


    xml.clear();
    file->close();
}

ostream& operator<<(ostream& out, const BusPlan& busPlan)
{
    out<<"BusPlan { id: "<<busPlan.id()<<" name: "<<busPlan.name().toStdString()<<"\n";
    typedef QPair<BusLine,QList<double> > BusLineTable;
    foreach(BusLineTable blt, busPlan.busLineTables())
    {
        out<<blt.first<<endl;
        foreach(double offset, blt.second)
        {
            int hours = (int)(offset/60);
            out<<hours<<":"<<(offset-hours*60)<<",";
        }
        out<<endl;
    }
    out<<"}";
    return out;
}

QList<BusPlan> BusPlan::busPlans()
{
    QList<BusPlan> ret;
    QList<BusPlanPrivate*> values = _busPlans.values();
    foreach(BusPlanPrivate* bpp,values)
        ret.append(BusPlan(bpp));
    return ret;
}

int BusPlan::id() const
{
    return _busPlanPrivate->id;
}

QString BusPlan::name() const
{
    return _busPlanPrivate->name;
}

QList<QPair<BusLine,QList<double> > > BusPlan::busLineTables() const
{
    QList<QPair<BusLine,QList<double> > > ret;

    foreach(int id, _busPlanPrivate->busPlan.keys())
    {
        ret.append(QPair<BusLine,QList<double> >(BusLine::busLineById(id),_busPlanPrivate->busPlan[id]));
    }
    return ret;
}

void BusPlan::save()
{
    QDir current = QDir::current();
    current.cdUp();
    current.cd("bus-simulation");
    QDir::setCurrent(current.absolutePath());
    QFile* file = new QFile("busplans.xml");
    assert(file->open(QIODevice::WriteOnly | QIODevice::Text));
    QXmlStreamWriter xml(file);

    xml.setAutoFormatting(true);
    xml.writeStartDocument();
    xml.writeStartElement("BusPlans");

    foreach(BusPlanPrivate *bpp , _busPlans.values())
    {
        xml.writeStartElement("BusPlan");
        xml.writeTextElement("id",QString::number(bpp->id));
        xml.writeTextElement("name",bpp->name);
        xml.writeStartElement("busLines");

        foreach(int id,bpp->busPlan.keys())
        {
            xml.writeStartElement("BusLine");
            xml.writeTextElement("id",QString::number(id));
            xml.writeStartElement("offsets");
            foreach(double offset,bpp->busPlan[id])
            {
                xml.writeStartElement("offset");

                int hour = (int)(offset/60.0);
                xml.writeTextElement("hour",QString::number(hour));
                xml.writeTextElement("minute",QString::number(offset-hour*60));

                xml.writeEndElement();
            }
            xml.writeEndElement();
            xml.writeEndElement();
        }

        xml.writeEndElement();
        xml.writeEndElement();
    }

    xml.writeEndElement();
    xml.writeEndDocument();
    file->close();
}

EventList BusPlan::generateBusEvents() const
{
    assert(false);
    return EventList();
}
