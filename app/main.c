#include <stdlib.h>
#include <systemd/sd-bus.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>


void listServices(void){
    sd_bus *bus = NULL;
    sd_bus_message *reply = NULL;
    sd_bus_error error = SD_BUS_ERROR_NULL;
    int r;

    // conecta ao system bus:
    r = sd_bus_open_system(&bus);
    if(r<0){
        fprintf(stderr, "erro ao conectar: %s\n", strerror(-r));
        goto finish;
    }

    // chama o metodo ListUnits do dbus:
    r = sd_bus_call_method(
        bus,
        "org.freedesktop.systemd1",         //servico
        "/org/freedesktop/systemd1",        //bin path
        "org.freedesktop.systemd1.Manager", //interface
        "ListUnits",                        //metodo
        &error,
        &reply,
        NULL
    );
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

    while ((r = sd_bus_message_enter_container(reply, SD_BUS_TYPE_STRUCT, "ssssssouso")) > 0) {
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
            printf("%-75s %-10s %-10s\n",
                name, load_state, active_state);
        }

        sd_bus_message_exit_container(reply);
    }

finish:
    sd_bus_error_free(&error);
    sd_bus_message_unref(reply);
    sd_bus_unref(bus);

    //return reply;
}

int main(){
    //system("systemctl status rabbitmq-server.service");
    listServices();
    //printf("%s\n", services);
    return 0;
}