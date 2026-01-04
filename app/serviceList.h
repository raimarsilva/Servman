#ifndef SERVICELIST_H
#define SERVICELIST_H

#include "service.h"

typedef struct ServiceList{
    Service *items;
    int count;
    int capacity;
}ServiceList;

#endif