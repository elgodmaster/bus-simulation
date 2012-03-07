#ifndef SIMULATION_H
#define SIMULATION_H

#include "BusStop.h"

void loadSimulationData()
{
    BusStop::load();
}
void saveSimulationData()
{
    BusStop::save();
}

#endif // SIMULATION_H
