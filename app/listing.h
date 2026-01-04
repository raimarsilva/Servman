#ifndef LISTING_H
#define LISTING_H

#include "service.h"
#include "serviceList.h"

ServiceList listServices(void);
void freeServices(Service *services, int count);
#endif

