#include "../cpu_temp.h"
#include "file_find.h"

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>


static void write_path( cpu_temp_t *ct, char* path );
static int quick_check( char* path );

int cpu_temp_init( cpu_temp_t* ct, char* path ){

        memset( ct, 0, sizeof(cpu_temp_t) );
        
        if( validate_file( path ) != EXIT_SUCCESS ){
                return EXIT_FAILURE;
        }
        
        if( path == NULL) {
                write_path( ct, CPU_TEMP_PATH_DEFAULT );
        }else{
                write_path( ct, path );
        }

        ct->get_temp = cpu_get_temp;

        return EXIT_SUCCESS;
}

int cpu_temp_fini( cpu_temp_t *ct ){
        free(ct->path);

        return EXIT_SUCCESS;
}

int32_t cpu_get_temp( cpu_temp_t* ct ){
        uint32_t temp = 0;

        if( quick_check(ct->path) != EXIT_SUCCESS ){
                return (int32_t)0xffffffff;     //This number should, in theory, stick out of the data set like a sore thumb
        }

        FILE *fp;
        fp = fopen( ct->path, "r" );
        if( fp == NULL ){
                fprintf(stderr, "Error opening file\nPath: %s\n", ct->path );
                return (int32_t)0xffffffff; 
        }

        fscanf( fp, "%d", &temp );

        fclose(fp);
        return temp;
}



















static void write_path( cpu_temp_t *ct, char* path ){
        size_t path_len = strlen(path);
        ct->path = (char*)calloc( path_len +1, sizeof(char) );
        memcpy( ct->path, path, path_len );
}

static int quick_check( char* path ){
        if( access(path, R_OK) != 0 ){
                fprintf( stderr, "Error, accessing cpu temp failed\nPath: %s\nFile has no R perms\n", path );
                return EXIT_FAILURE;
        }else{
                return EXIT_SUCCESS;
        }
}
