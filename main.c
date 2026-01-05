#include "listing.h"
#include "window.h"
#include <stdlib.h>
#include <stdio.h>
int main(int argc, char *argv[]){
    //system("systemctl status rabbitmq-server.service");
    ServiceList serviceList = listServices();
    init_gui(argc, argv, &serviceList);
    freeServices(serviceList.items, serviceList.count);

    return 0;
}