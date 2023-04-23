#ifndef FILE_FIND_H
#define FILE_FIND_H

#define CPU_TEMP_PATH_DEFAULT "/sys/class/thermal/thermal_zone0/temp"



//use null as path for default
//OR the options together to change behaviour
int validate_file( const char* path ); 

#endif