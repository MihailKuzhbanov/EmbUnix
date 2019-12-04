/*
 * logic.c
 *
 *  Created on: Dec 3, 2019
 *      Author: bear
 */

#include "logic.h"
#include "POUS.h"

extern PLC_PRG RESOURCE1__PLC_TASK_INSTANCE;

void writeLogic(uint32_t val) {
  RESOURCE1__PLC_TASK_INSTANCE.STATE.value = val;
}

uint32_t readLogic() {
  return RESOURCE1__PLC_TASK_INSTANCE.STATE.value;
}

void writeData();
int readData();
void writeInfo();
bool readInfo();
