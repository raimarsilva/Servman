//#include "listing.h"
//#include "window.h"
//#include <stdlib.h>
#include <stdio.h>
int main(int argc, char *argv[]){
    //system("systemctl status rabbitmq-server.service");
    //listServices();
    //init_gui(argc, argv);
    //printf("%s\n", services);

    int x = 10;
    //int *p = NULL;
    int *p = &x;
    printf("o valor de x é: %d\n", x);
    printf("o endereço de x é: %p\n\n", &x);  //d93c

    printf("o valor do ponteiro p é: %p\n", (void*)p);
    printf("o tipo de p é: %zu\n", sizeof(p));
    printf("a referencia de *p é: %d\n", *p);
    printf("o endereço do ponteiro p é: %p\n\n", &p); //d940

    *p = 2;
    printf("o valor de x é: %d\n", x);
    printf("o endereço de x é: %p\n\n", &x);  //d93c
    printf("o valor do ponteiro p é: %p\n", (void*)p);
    printf("o tipo de p é: %zu\n", sizeof(p));
    printf("a referencia de *p é: %d\n", *p);
    printf("o endereço do ponteiro p é: %p\n\n", &p); //d940

    p = NULL;


    return 0;
}