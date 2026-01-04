#ifndef SERVICE_H
#define SERVICE_H

#include <stdint.h>

typedef struct Service{
    char *name;
    char *description;
    char *load_state;
    char *active_state;
    uint32_t job_id;
} Service;
#endif