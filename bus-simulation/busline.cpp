#include "busline.h"
#include <QDir>
#include <cassert>

using namespace std;

QMap<int,BusLinePrivate*> BusLine::_busLines;

QList<BusLine> BusLine::busLines()
{
    QList<BusLine> ret;
    QList<BusLinePrivate*> values = _busLines.values();
    foreach(BusLinePrivate* blp,values)
        ret.append(BusLine(blp));
    return ret;
}

BusLine::BusLine()
{
    _busLinePrivate = new BusLinePrivate();
    if(_busLines.isEmpty())
        _busLinePrivate->id = 0;
    else
        _busLinePrivate->id = _busLines.values().last()->id+1;
    _busLines.insert(_busLinePrivate->id,_busLinePrivate);

    _busLinePrivate->name = "N/A";
}

BusLine::BusLine(const BusLine &busLine)
{
    _busLinePrivate = busLine._busLinePrivate;
}

BusLine::BusLine(BusLinePrivate *blp)
{
    _busLinePrivate = blp;
}

void BusLine::load()
{
    QDir current = QDir::current();
    current.cdUp();
    current.cd("bus-simulation");
    QDir::setCurrent(current.absolutePath());
    QFile* file = new QFile("buslines.xml");
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

            if(xml.name() == "BusLines")
                continue;

            if(xml.name() == "BusLine") {
                BusLinePrivate *blp = new BusLinePrivate();

                xml.readNext();

                while(!(xml.tokenType() == QXmlStreamReader::EndElement &&
                        xml.name() == "BusLine")) {
                    if(xml.tokenType() == QXmlStreamReader::StartElement) {
                        if(xml.name() == "id") {
                            xml.readNext();
                            blp->id = xml.text().toString().toInt();
                        }
                        if(xml.name() == "name") {
                            xml.readNext();
                            blp->name = xml.text().toString();
                        }
                        if(xml.name() == "busStops") {
                            xml.readNextStartElement();

                            while(!(xml.tokenType() == QXmlStreamReader::EndElement &&
                                    xml.name() == "busStops")) {

                                assert(xml.name()=="BusStop");

                                assert(xml.readNextStartElement());
                                assert(xml.name()=="id");
                                xml.readNext();
                                int id = xml.text().toString().toInt();
                                assert(!xml.readNextStartElement());
                                assert(xml.name()=="id");

                                assert(xml.readNextStartElement());
                                assert(xml.name()=="offset");
                                xml.readNext();
                                double offset = xml.text().toString().toDouble();
                                assert(!xml.readNextStartElement());
                                assert(xml.name()=="offset");

                                assert(!xml.readNextStartElement());
                                assert(xml.name()=="BusStop");

                                blp->busLineStops.append(QPair<int,double>(id,offset));

                                xml.readNextStartElement();
                            }
                        }
                    }
                    xml.readNext();
                }
                _busLines.insert(blp->id,blp);
            }
        }
    }
    xml.clear();
    file->close();
}

QList<QPair<BusStop,double> > BusLine::busStops() const
{
    QList<QPair<BusStop,double> > ret;

    typedef QPair<int,double> BasicBusLineStop;
    foreach(BasicBusLineStop bbls, _busLinePrivate->busLineStops)
    {
        ret.append(QPair<BusStop,double>(BusStop::busStopById(bbls.first),bbls.second));
    }
    return ret;
}

ostream& operator<<(ostream& out, const BusLine& busLine){
    out<<"BusLine { id:"<<busLine.id()<<" name: "<<busLine.name().toStdString()<<"\n";
    typedef QPair<BusStop,double> BusLineStop;
    foreach(BusLineStop bls,busLine.busStops())
    {
        out<<"\t"<<bls.first<<", offset = "<<bls.second<<"\n";
    }
    out<<"}";
    return out;
}

int BusLine::id() const
{
    return _busLinePrivate->id;
}

QString BusLine::name() const
{
    return _busLinePrivate->name;
}

void BusLine::save()
{
    QDir current = QDir::current();
    current.cdUp();
    current.cd("bus-simulation");
    QDir::setCurrent(current.absolutePath());
    QFile* file = new QFile("buslines.xml");
    assert(file->open(QIODevice::WriteOnly | QIODevice::Text));
    QXmlStreamWriter xml(file);

    xml.setAutoFormatting(true);
    xml.writeStartDocument();
    xml.writeStartElement("BusLines");

    foreach(BusLinePrivate *blp , _busLines.values())
    {
        xml.writeStartElement("BusLine");
        xml.writeTextElement("id",QString::number(blp->id));
        xml.writeTextElement("name",blp->name);
        xml.writeStartElement("busStops");

        typedef QPair<int, double> BasicBusLineStop;
        foreach(BasicBusLineStop bbls,blp->busLineStops)
        {
            xml.writeStartElement("BusStop");
            xml.writeTextElement("id",QString::number(bbls.first));
            xml.writeTextElement("offset",QString::number(bbls.second));
            xml.writeEndElement();
        }

        xml.writeEndElement();
        xml.writeEndElement();
    }

    xml.writeEndElement();
    xml.writeEndDocument();
    file->close();
}

BusLine BusLine::busLineById(int id)
{
    assert(_busLines.contains(id));
    return BusLine(_busLines[id]);
}
