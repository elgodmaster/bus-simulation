#ifndef SIMULATION_H
#define SIMULATION_H

#include "busstop.h"
#include "busline.h"

void loadSimulationData()
{
    BusStop::load();
    BusLine::load();
}
void saveSimulationData()
{
    BusStop::save();
    BusLine::save();
}

#endif // SIMULATION_H
