#ifndef SIMULATION_H
#define SIMULATION_H

#include "busstop.h"
#include "busline.h"
#include "busplan.h"

void loadSimulationData()
{
    BusStop::load();
    BusLine::load();
    BusPlan::load();
}
void saveSimulationData()
{
    BusStop::save();
    BusLine::save();
    BusPlan::save();
}

#endif // SIMULATION_H
