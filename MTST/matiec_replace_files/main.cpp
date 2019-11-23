#include <stdio.h>
#include <stdbool.h>
#include "POUS.h"
#include "LOCATED_VARIABLES.h"
#include "config.h"
#include "resource1.c"
#include "tport.hpp"

IEC_TIME __CURRENT_TIME;
bool alive = false;
int period = 5;

int main(int argc, char* argv[])
{
        tport::TPort<int> port(1);
        RESOURCE1_init__();
        printf("Initialization complete\n");
        alive = true;
        while (alive)
        {
                //usleep(sleep);
                RESOURCE1_run__(period, port);
        }
        return 0;
}
