void C_PRAGMA_init__(C_PRAGMA *data__, BOOL retain) {
  __INIT_VAR(data__->EN,__BOOL_LITERAL(TRUE),retain)
  __INIT_VAR(data__->ENO,__BOOL_LITERAL(TRUE),retain)
  __INIT_VAR(data__->NUMOUT,25,retain)
  {
    static const __ARRAY_OF_INT_32 temp = {{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}};
    __SET_VAR(data__->,SIGNALDATA,,temp);
  }
  __INIT_VAR(data__->DATA0,0,retain)
  __INIT_VAR(data__->DATA1,0,retain)
  __INIT_VAR(data__->DATA2,0,retain)
  __INIT_VAR(data__->DATA3,0,retain)
  {
    static const __ARRAY_OF_BOOL_32 temp = {{__BOOL_LITERAL(FALSE),__BOOL_LITERAL(FALSE),__BOOL_LITERAL(FALSE),__BOOL_LITERAL(FALSE),__BOOL_LITERAL(FALSE),__BOOL_LITERAL(FALSE),__BOOL_LITERAL(FALSE),__BOOL_LITERAL(FALSE),__BOOL_LITERAL(FALSE),__BOOL_LITERAL(FALSE),__BOOL_LITERAL(FALSE),__BOOL_LITERAL(FALSE),__BOOL_LITERAL(FALSE),__BOOL_LITERAL(FALSE),__BOOL_LITERAL(FALSE),__BOOL_LITERAL(FALSE),__BOOL_LITERAL(FALSE),__BOOL_LITERAL(FALSE),__BOOL_LITERAL(FALSE),__BOOL_LITERAL(FALSE),__BOOL_LITERAL(FALSE),__BOOL_LITERAL(FALSE),__BOOL_LITERAL(FALSE),__BOOL_LITERAL(FALSE),__BOOL_LITERAL(FALSE),__BOOL_LITERAL(FALSE),__BOOL_LITERAL(FALSE),__BOOL_LITERAL(FALSE),__BOOL_LITERAL(FALSE),__BOOL_LITERAL(FALSE),__BOOL_LITERAL(FALSE),__BOOL_LITERAL(FALSE)}};
    __SET_VAR(data__->,SIGNALINFO,,temp);
  }
  __INIT_VAR(data__->INFO0,__BOOL_LITERAL(FALSE),retain)
  __INIT_VAR(data__->INFO1,__BOOL_LITERAL(FALSE),retain)
  __INIT_VAR(data__->INFO2,__BOOL_LITERAL(FALSE),retain)
  __INIT_VAR(data__->INFO3,__BOOL_LITERAL(FALSE),retain)
  __INIT_VAR(data__->VALIN,0,retain)
  __INIT_VAR(data__->NUMIN,24,retain)
  __INIT_VAR(data__->PERMIT,1,retain)
}

// Code part
void C_PRAGMA_body__(C_PRAGMA *data__) {
  // Control execution
  if (!__GET_VAR(data__->EN)) {
    __SET_VAR(data__->,ENO,,__BOOL_LITERAL(FALSE));
    return;
  }
  else {
    __SET_VAR(data__->,ENO,,__BOOL_LITERAL(TRUE));
  }
  // Initialise TEMP variables

  __IL_DEFVAR_T __IL_DEFVAR;
  __IL_DEFVAR_T __IL_DEFVAR_BACK;
  #define GetFbVar(var,...) __GET_VAR(data__->var,__VA_ARGS__)
  #define SetFbVar(var,val,...) __SET_VAR(data__->,var,__VA_ARGS__,val)

      extern void WritePin(int, int);
      extern void InitPin(int, int);
      extern void CheckPin();
      extern int ReadPin(int);
      
      CheckPin();
      InitPin(GetFbVar(NUMIN), 0);
      InitPin(GetFbVar(NUMOUT), 1);
      if (GetFbVar(PERMIT) > 0) {
        WritePin(GetFbVar(NUMOUT), ReadPin(GetFbVar(NUMIN)));
      }
      SetFbVar(VALIN, ReadPin(GetFbVar(NUMIN)));
  
  #undef GetFbVar
  #undef SetFbVar
;

  goto __end;

__end:
  return;
} // C_PRAGMA_body__() 





void PLC_PRG_init__(PLC_PRG *data__, BOOL retain) {
  __INIT_VAR(data__->INPUTPINNUMBER,24,retain)
  {
    static const __ARRAY_OF_INT_32 temp = {{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}};
    __SET_VAR(data__->,DATA,,temp);
  }
  {
    static const __ARRAY_OF_BOOL_32 temp = {{__BOOL_LITERAL(FALSE),__BOOL_LITERAL(FALSE),__BOOL_LITERAL(FALSE),__BOOL_LITERAL(FALSE),__BOOL_LITERAL(FALSE),__BOOL_LITERAL(FALSE),__BOOL_LITERAL(FALSE),__BOOL_LITERAL(FALSE),__BOOL_LITERAL(FALSE),__BOOL_LITERAL(FALSE),__BOOL_LITERAL(FALSE),__BOOL_LITERAL(FALSE),__BOOL_LITERAL(FALSE),__BOOL_LITERAL(FALSE),__BOOL_LITERAL(FALSE),__BOOL_LITERAL(FALSE),__BOOL_LITERAL(FALSE),__BOOL_LITERAL(FALSE),__BOOL_LITERAL(FALSE),__BOOL_LITERAL(FALSE),__BOOL_LITERAL(FALSE),__BOOL_LITERAL(FALSE),__BOOL_LITERAL(FALSE),__BOOL_LITERAL(FALSE),__BOOL_LITERAL(FALSE),__BOOL_LITERAL(FALSE),__BOOL_LITERAL(FALSE),__BOOL_LITERAL(FALSE),__BOOL_LITERAL(FALSE),__BOOL_LITERAL(FALSE),__BOOL_LITERAL(FALSE),__BOOL_LITERAL(FALSE)}};
    __SET_VAR(data__->,INFO,,temp);
  }
  __INIT_VAR(data__->OUTPUTPINNUMBER,25,retain)
  __INIT_VAR(data__->STATE,0,retain)
  __INIT_VAR(data__->RESULT,0,retain)
  C_PRAGMA_init__(&data__->C_PRAGMA0,retain);
  __INIT_VAR(data__->INT_TO_BOOL21_OUT,__BOOL_LITERAL(FALSE),retain)
  __INIT_VAR(data__->INT_TO_BOOL22_OUT,__BOOL_LITERAL(FALSE),retain)
  __INIT_VAR(data__->INT_TO_BOOL23_OUT,__BOOL_LITERAL(FALSE),retain)
  __INIT_VAR(data__->INT_TO_BOOL24_OUT,__BOOL_LITERAL(FALSE),retain)
}

// Code part
void PLC_PRG_body__(PLC_PRG *data__) {
  // Initialise TEMP variables

  __SET_VAR(data__->,INT_TO_BOOL21_OUT,,INT_TO_BOOL(
    (BOOL)__BOOL_LITERAL(TRUE),
    NULL,
    (INT)__GET_VAR(data__->C_PRAGMA0.DATA0,)));
  __SET_VAR(data__->,INT_TO_BOOL22_OUT,,INT_TO_BOOL(
    (BOOL)__BOOL_LITERAL(TRUE),
    NULL,
    (INT)__GET_VAR(data__->C_PRAGMA0.DATA1,)));
  __SET_VAR(data__->,INT_TO_BOOL23_OUT,,INT_TO_BOOL(
    (BOOL)__BOOL_LITERAL(TRUE),
    NULL,
    (INT)__GET_VAR(data__->C_PRAGMA0.DATA2,)));
  __SET_VAR(data__->,INT_TO_BOOL24_OUT,,INT_TO_BOOL(
    (BOOL)__BOOL_LITERAL(TRUE),
    NULL,
    (INT)__GET_VAR(data__->C_PRAGMA0.DATA3,)));
  __SET_VAR(data__->C_PRAGMA0.,NUMOUT,,__GET_VAR(data__->OUTPUTPINNUMBER,));
  __SET_VAR(data__->C_PRAGMA0.,INFO0,,__GET_VAR(data__->INT_TO_BOOL21_OUT,));
  __SET_VAR(data__->C_PRAGMA0.,INFO1,,__GET_VAR(data__->INT_TO_BOOL22_OUT,));
  __SET_VAR(data__->C_PRAGMA0.,INFO2,,__GET_VAR(data__->INT_TO_BOOL23_OUT,));
  __SET_VAR(data__->C_PRAGMA0.,INFO3,,__GET_VAR(data__->INT_TO_BOOL24_OUT,));
  __SET_VAR(data__->C_PRAGMA0.,NUMIN,,__GET_VAR(data__->INPUTPINNUMBER,));
  __SET_VAR(data__->C_PRAGMA0.,PERMIT,,__GET_VAR(data__->STATE,));
  C_PRAGMA_body__(&data__->C_PRAGMA0);
  __SET_VAR(data__->,RESULT,,__GET_VAR(data__->C_PRAGMA0.VALIN,));

  goto __end;

__end:
  return;
} // PLC_PRG_body__() 





