#ifndef SERVICE_H
#define SERVICE_H

#include <stdint.h>

typedef struct {
    char *name;
    char *description;
    char *load_state;
    char *active_state;
}Service;

#endif
