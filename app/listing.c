#define _POSIX_C_SOURCE 200809L

#include <stdlib.h>
#include <systemd/sd-bus.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include "listing.h"
#include "service.h"
#include "serviceList.h"


void freeServices(Service *services, int count){
    for(int i = 0; i < count; i++){
        free(services[i].name);
        free(services[i].description);
        free(services[i].load_state);
        free(services[i].active_state);
    }
    free(services);
}

// conecta ao system bus.
int sdbusConnect(sd_bus **bus){
    return sd_bus_open_system(bus);
}

// chama um metodo do sdbus pelo seu nome.
int callSdbusMethod(sd_bus *bus, char methodName[], sd_bus_error *error, sd_bus_message **reply){
    return sd_bus_call_method(
        bus,
        "org.freedesktop.systemd1",         //servico
        "/org/freedesktop/systemd1",        //bin path
        "org.freedesktop.systemd1.Manager", //interface
        methodName,                        //metodo
        error,
        reply,
        NULL
    );
}

ServiceList listServices(void){
    int capacity = 100;
    int count = 0;
    sd_bus *bus = NULL;
    sd_bus_message *reply = NULL;
    sd_bus_error error = SD_BUS_ERROR_NULL;
    int r;

    // possivel refactoring para outro arquivo.
    Service *services = malloc(capacity * sizeof(Service));
    if(!services){
        perror("memory alocation error");
        exit(EXIT_FAILURE);
    }

    r = sdbusConnect(&bus);
    if(r<0){
        fprintf(stderr, "erro ao conectar no barramento do systemd: %s\n", strerror(-r));
        goto finish;
    }
    
    // chama o metodo ListUnits do dbus:
    r = callSdbusMethod(bus, "ListUnits", &error, &reply);
    if(r<0){
        fprintf(stderr, "erro ao conectar: %s\n", strerror(-r));
        goto finish;
    }

    // lê o array de units
    r = sd_bus_message_enter_container(
        reply,
        SD_BUS_TYPE_ARRAY,
        "(ssssssouso)"
    );
    if(r<0){
        fprintf(stderr, "Erro ao entrar no array\n");
        goto finish;
    }

    while((r = sd_bus_message_enter_container(reply, SD_BUS_TYPE_STRUCT, "ssssssouso")) > 0) {
        const char *name;
        const char *description;
        const char *load_state;
        const char *active_state;
        const char *sub_state;
        const char *following;
        const char *unit_path;
        uint32_t job_id;
        const char *job_type;
        const char *job_path;

        sd_bus_message_read(
            reply,
            "ssssssouso",
            &name,
            &description,
            &load_state,
            &active_state,
            &sub_state,
            &following,
            &unit_path,
            &job_id,
            &job_type,
            &job_path
        );

        // Mostra apenas serviços
        if (strstr(name, ".service")) {
            //printf("%-75s %-10s %-10s %-10s\n", name, description, load_state, active_state);

            if(count == capacity){
                capacity *= 2;
                Service *temp = realloc(services, capacity * sizeof(Service));
                if(!temp){
                    perror("memory reallocation error");
                    goto finish;
                }
                services = temp;
            }

            services[count].name = strdup(name);
            services[count].description = strdup(description);
            services[count].load_state = strdup(load_state);
            services[count].active_state = strdup(active_state);
            count++;
        }

        sd_bus_message_exit_container(reply);
    }

    ServiceList serviceList = {0};
    serviceList.items = services;
    serviceList.count = count;
    serviceList.capacity = capacity;

    finish:
        sd_bus_error_free(&error);
        sd_bus_message_unref(reply);
        sd_bus_unref(bus);

        if(r < 0 && services){
            freeServices(services, count);
            serviceList.items = NULL;
            serviceList.count = 0;
            serviceList.capacity = 0;
        }

    return serviceList;
}