#include <stdio.h>
#include <unistd.h>

#include "resource1.h"

#include "iec_types.h"

IEC_TIME __CURRENT_TIME;

unsigned long long ticktime = 1;

int main() {
	RESOURCE1_init__();
	printf("PLC initialized\n");
	RESOURCE1_run__(ticktime);
	return 0;
}
