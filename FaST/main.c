#include <stdio.h>
#include <stdbool.h>
#include "POUS.h"
#include "LOCATED_VARIABLES.h"
#include "config.h"
#include "resource1.c"

IEC_TIME __CURRENT_TIME;
bool alive = false;
int period = 5;
int sleep = 0;

int main (int argc, char* argv[])
{
    RESOURCE1_init__();
    printf("Initialization complete\n");
    alive = true;
    while (alive)
    {
        //uncomment for cpu load control
        //usleep(sleep);
        RESOURCE1_run__(period);
    }
    return 0;
}
