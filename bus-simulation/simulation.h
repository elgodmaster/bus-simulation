#ifndef SIMULATION_H
#define SIMULATION_H

#include "busstop.h"
#include "busline.h"
#include "busplan.h"
#include "commutertrip.h"
#include "tripstatistic.h"
#include "event.h"
#include "bus.h"
#include <cassert>

void loadSimulationData();
void saveSimulationData();

void processNewCommuterEvent(NewCommuterEvent* event);
void processBusAtStopEvent(BusAtStopEvent* event);
void processBusChangeLineEvent(BusChangeLineEvent* event);

void simulate(EventList eventList);

#endif // SIMULATION_H
