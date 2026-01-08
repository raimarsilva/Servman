#ifndef SERVICELIST_H
#define SERVICELIST_H

#include "service.h"

typedef struct {
    Service *items;
    int count;
    int capacity;
}ServiceList;

#endif