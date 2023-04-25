# rpi_cpu_temp
A small C program to read the cpu temperature on a raspberry pi. It includes some basic error handling.

# TO BUILD
mkdir build

make

The provided example.c should contain an extremely simplistic implementation of the library
All readings should be in millidegrees.

I am not 100% sure if the sensor has negative ranges, but if the function fails a value of 0xffffffff is returned.
This should hopefull stick out in datasets.
