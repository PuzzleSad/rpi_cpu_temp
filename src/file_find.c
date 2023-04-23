#include "file_find.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <dirent.h>
#include <unistd.h>
#include <stdint.h>
#include <stddef.h>
#include <inttypes.h>


static int path_len_warn( size_t len);
static int path_exist( const char* path );
static int path_valid( const char* path );




int validate_file( const char* path ){
        size_t path_len;
        const char delim[2] = "/";
        char* token;

        char *strbuf;
        

        if( path != NULL ){
                path_len = strlen(path) + 1;

                if( path_len_warn( path_len ) == EXIT_FAILURE ){
                        return EXIT_FAILURE;
                }

                strbuf = (char*)calloc( path_len, sizeof(char) );
                memcpy( strbuf, path, path_len );
        }else{
                path_len = strlen( CPU_TEMP_PATH_DEFAULT ) + 1;
                
                strbuf = (char*)calloc( path_len, sizeof(char) );
                memcpy( strbuf, CPU_TEMP_PATH_DEFAULT, path_len );
        }

        
        int path_offset = 0;
        size_t token_len = 0;
        char path_rebuild[path_len + 1];
        memset(path_rebuild, 0, path_len +1);

        

        token = strtok( strbuf, delim );

        while( token != NULL ){
                path_rebuild[path_offset] = '/';
                path_offset++;

                token_len = strlen(token);
                memcpy( &path_rebuild[path_offset], token, token_len);
                path_offset += token_len;

                if( path_exist(path_rebuild) != EXIT_SUCCESS ){
                        return EXIT_FAILURE;
                }else{
                        if( path_valid( path_rebuild ) != EXIT_SUCCESS ){
                                return EXIT_FAILURE;
                        }
                }

                token = strtok( NULL, delim );
        }
        


        free( strbuf );
        return EXIT_SUCCESS;
}



static int path_len_warn( size_t len ){
        if( len > 5000 ){
                fprintf( stderr, "Warning, path length > 5000\nLength: %"PRIu64"\n", len );
                return EXIT_FAILURE;
        }else{
                return EXIT_SUCCESS;
        }
}

static int path_exist( const char* path ){
        if( access(path, F_OK) == 0 ){
                return EXIT_SUCCESS;
        }else{
                fprintf(stderr, "Path does not exist\nPath: %s\n", path );
                return EXIT_FAILURE;
        }
}

static int path_valid( const char* path ){
        int status = 0;

        // if( access( path, X_OK ) != 0 ){
        //         fprintf(stderr, "Warning, path does not have X perm\nPath: %s\n", path);
        //         status += 1;
        // }

        if( access( path, R_OK ) != 0 ){
                fprintf(stderr, "Warning, path does not have R perm\nPath: %s\n", path);
                status += 1;
        }

        if( status != 0 ){
                return EXIT_FAILURE;
        }else{
                return EXIT_SUCCESS;
        }
}


