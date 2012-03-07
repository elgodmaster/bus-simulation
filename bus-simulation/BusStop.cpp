#include "BusStop.h"
#include <QFile>
#include <cassert>
#include <QDir>

using namespace std;

QMap<int,BusStopInternal*> BusStop::_busStops;

BusStop::BusStop(){
    _busStopInternal = new BusStopInternal();
    if(_busStops.isEmpty())
        _busStopInternal->id = 0;
    else
        _busStopInternal->id = _busStops.values().last()->id+1;
    _busStops.insert(_busStopInternal->id,_busStopInternal);

    _busStopInternal->name = "N/A";
    _busStopInternal->latitude = 0.0;
    _busStopInternal->longtitude = 0.0;
}

ostream& operator<<(ostream& out, const BusStop& busStop){
    out<<"BusStop{ ";
    out<<"id:"<<busStop.id()<<" ";
    out<<"name:"<<busStop.name().toStdString()<<" ";
    out<<"lat:"<<busStop.latitude()<<" ";
    out<<"long:"<<busStop.longtitude()<<" ";
    out<<"}";
    return out;
}

BusStop BusStop::operator=(const BusStop& busStop)
{
    _busStopInternal = busStop._busStopInternal;
    return *this;
}

double BusStop::latitude() const{return _busStopInternal->latitude;}
double BusStop::longtitude() const{return _busStopInternal->longtitude;}
QString BusStop::name() const{return _busStopInternal->name;}
int BusStop::id() const{return _busStopInternal->id;}

BusStop::BusStop(const BusStop &busStop)
{
    _busStopInternal = busStop._busStopInternal;
}

QList<BusStop> BusStop::busStops()
{
    QList<BusStop> ret;
    QList<BusStopInternal*> values = _busStops.values();
    foreach(BusStopInternal* bsp,values)
        ret.append(BusStop(bsp));
    return ret;
}

void BusStop::load()
{
    QDir current = QDir::current();
    current.cdUp();
    current.cd("bus-simulation");
    QDir::setCurrent(current.absolutePath());
    QFile* file = new QFile("busstops.xml");
    assert(file->open(QIODevice::ReadOnly | QIODevice::Text));
    QXmlStreamReader xml(file);
    assert(!xml.atEnd());
    while(!xml.atEnd())
    {
        QXmlStreamReader::TokenType token = xml.readNext();
        if(token == QXmlStreamReader::StartDocument) {
            continue;
        }
        if(token == QXmlStreamReader::StartElement) {

            if(xml.name() == "BusStops")
                continue;

            if(xml.name() == "BusStop") {
                BusStopInternal *bsp = new BusStopInternal();

                xml.readNext();

                while(!(xml.tokenType() == QXmlStreamReader::EndElement &&
                        xml.name() == "BusStop")) {
                    if(xml.tokenType() == QXmlStreamReader::StartElement) {
                        if(xml.name() == "id") {
                            xml.readNext();
                            bsp->id = xml.text().toString().toInt();
                        }
                        if(xml.name() == "name") {
                            xml.readNext();
                            bsp->name = xml.text().toString();
                        }
                        if(xml.name() == "latitude") {
                            xml.readNext();
                            bsp->latitude = xml.text().toString().toDouble();
                        }
                        if(xml.name() == "longtitude") {
                            xml.readNext();
                            bsp->longtitude = xml.text().toString().toDouble();
                        }
                    }
                    xml.readNext();
                }
                _busStops.insert(bsp->id,bsp);
            }
        }
    }
    xml.clear();
    file->close();
}

void BusStop::save()
{
    QDir current = QDir::current();
    current.cdUp();
    current.cd("bus-simulation");
    QDir::setCurrent(current.absolutePath());
    QFile* file = new QFile("busstops.xml");
    assert(file->open(QIODevice::WriteOnly | QIODevice::Text));
    QXmlStreamWriter xml(file);

    xml.setAutoFormatting(true);
    xml.writeStartDocument();
    xml.writeStartElement("BusStops");

    foreach(BusStopInternal *bsp , _busStops.values())
    {
        xml.writeStartElement("BusStop");
        xml.writeTextElement("id",QString::number(bsp->id));
        xml.writeTextElement("name",bsp->name);
        xml.writeTextElement("latitude",QString::number(bsp->latitude));
        xml.writeTextElement("longtitude",QString::number(bsp->longtitude));
        xml.writeEndElement();
    }

    xml.writeEndElement();
    xml.writeEndDocument();
    file->close();
}

BusStop::BusStop(BusStopInternal *bsp)
{
    _busStopInternal = bsp;
}
