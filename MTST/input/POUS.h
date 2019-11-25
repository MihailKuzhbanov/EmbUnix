#ifndef __POUS_H
#define __POUS_H

#include "accessor.h"
#include "iec_std_lib.h"

// FUNCTION_BLOCK C_PRAGMA
// Data part
typedef struct {
  // FB Interface - IN, OUT, IN_OUT variables
  __DECLARE_VAR(BOOL,EN)
  __DECLARE_VAR(BOOL,ENO)
  __DECLARE_VAR(INT,OUT)
  __DECLARE_VAR(INT,VALUE)
  __DECLARE_VAR(INT,IN)

  // FB private variables - TEMP, private and located variables

} C_PRAGMA;

void C_PRAGMA_init__(C_PRAGMA *data__, BOOL retain);
// Code part
void C_PRAGMA_body__(C_PRAGMA *data__);
// PROGRAM PLC_PRG
// Data part
typedef struct {
  // PROGRAM Interface - IN, OUT, IN_OUT variables
  __DECLARE_VAR(INT,INPUT)
  __DECLARE_VAR(INT,OUTPUT)

  // PROGRAM private variables - TEMP, private and located variables
  C_PRAGMA C_PRAGMA0;

} PLC_PRG;

void PLC_PRG_init__(PLC_PRG *data__, BOOL retain);
// Code part
void PLC_PRG_body__(PLC_PRG *data__);
#endif //__POUS_H
