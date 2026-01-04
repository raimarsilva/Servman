#include "listing.h"
#include "window.h"
#include <stdlib.h>
#include <stdio.h>
int main(int argc, char *argv[]){
    //system("systemctl status rabbitmq-server.service");
    ServiceList serviceList = listServices();
    freeServices(serviceList.items, serviceList.count);
    init_gui(argc, argv);

    return 0;
}