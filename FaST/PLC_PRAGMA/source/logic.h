/*
 * logic.h
 *
 *  Created on: Dec 3, 2019
 *      Author: bear
 */

#ifndef LOGIC_H_
#define LOGIC_H_

#include "stdint.h"

#ifdef __cplusplus
extern "C" {
#endif
#include <stdbool.h>
extern void writeLogic(uint32_t val);
extern uint32_t readLogic();
extern void writeData();
extern int readData();
extern void writeInfo();
extern bool readInfo();


#ifdef __cplusplus
} /* extern "C" */
#endif


#endif /* LOGIC_H_ */
