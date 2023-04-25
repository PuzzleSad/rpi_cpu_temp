#include "cpu_serial.h"
#include "file_find.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <inttypes.h>


#define SERIAL_PATH_DEVTREE "/sys/firmware/devicetree/base/serial-number"

static int read_from_sys_devtree( char** write_loc );

int write_cpu_serial( char** write_loc ){
        read_from_sys_devtree(write_loc);
        return 0;
}


static int read_from_sys_devtree( char** write_loc ){
        if( write_loc == NULL ){
                fprintf( stderr, "Notice: write_loc set as NULL, cpu serial number fetch failed\n");
                return EXIT_FAILURE;
        }

        if( validate_file(SERIAL_PATH_DEVTREE) != EXIT_SUCCESS ){
                return EXIT_FAILURE;
        }

        FILE *fp;
        size_t len;

        fp = fopen( SERIAL_PATH_DEVTREE, "r" );
        if( fp == NULL ){
                return EXIT_FAILURE;
        }

        fseek( fp, 0, SEEK_END );
        len = ftell( fp );
        rewind( fp );

        if(len > 100){
                fprintf(stderr, "Warning, serial-number file len appears abnormal. Expecting <17 characters, got: %"PRIu64"\n", len);
                fclose(fp);
                return EXIT_FAILURE;
        }

        char serial[ len +1 ];
        fscanf(fp, "%s", serial);
        fclose(fp);

        size_t str_len = strlen( serial );      //TODO, might be redundant

        *write_loc = (char*)calloc( str_len +1, sizeof(char) );
        memcpy( *write_loc, serial, str_len );


        
        return EXIT_SUCCESS;
}
