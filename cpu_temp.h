#ifndef CPU_TEMP_H
#define CPU_TEMP_H

#include <stdint.h>

typedef struct cpu_temp_t cpu_temp_t;

struct cpu_temp_t{
        char* path;
        char* cpu_serial;
        int32_t (*get_temp)( cpu_temp_t* ct );
};

int cpu_temp_init( cpu_temp_t* ct, char* path );        //use NULL for path for default path
int cpu_temp_fini( cpu_temp_t *ct );

int32_t cpu_get_temp( cpu_temp_t* ct );

#endif