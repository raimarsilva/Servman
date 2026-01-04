#ifndef SERVICE_H
#define SERVICE_H
typedef struct Service{
    char name[256];
    char description[256];
    char load_state[32];
    char active_state[32];
    char job_id[16];
};
#endif