#include <stdio.h>
#include "cpu_temp.h"
#include <unistd.h>


int main(){

        cpu_temp_t ct;
        // cpu_temp_init( &ct, "/sys/class/thermal/sensors/w1" );
        cpu_temp_init( &ct, NULL );

        printf("Temp: %d\n", cpu_get_temp( &ct ) );
        sleep(1);
        printf("Temp: %d\n", ct.get_temp(&ct) );

        cpu_temp_fini( &ct );
}