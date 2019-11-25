void C_PRAGMA_init__(C_PRAGMA *data__, BOOL retain) {
  __INIT_VAR(data__->EN,__BOOL_LITERAL(TRUE),retain)
  __INIT_VAR(data__->ENO,__BOOL_LITERAL(TRUE),retain)
  __INIT_VAR(data__->OUT,25,retain)
  __INIT_VAR(data__->VALUE,0,retain)
  __INIT_VAR(data__->IN,24,retain)
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

      extern int GetRand();
      extern void WritePin(int, int);
      extern void InitPin(int, int);
      extern void CheckPin();
      extern int ReadPin(int);
      
      CheckPin();
      InitPin(24, 0);
      InitPin(25, 1);
      
      //SetFbVar(OUT, GetFbVar(IN));
      WritePin(25, ReadPin(24));
      //SetFbVar(ReadPin(24));
  
  #undef GetFbVar
  #undef SetFbVar
;

  goto __end;

__end:
  return;
} // C_PRAGMA_body__() 





void PLC_PRG_init__(PLC_PRG *data__, BOOL retain) {
  __INIT_VAR(data__->INPUT,24,retain)
  __INIT_VAR(data__->OUTPUT,25,retain)
  C_PRAGMA_init__(&data__->C_PRAGMA0,retain);
}

// Code part
void PLC_PRG_body__(PLC_PRG *data__) {
  // Initialise TEMP variables

  __SET_VAR(data__->C_PRAGMA0.,OUT,,__GET_VAR(data__->OUTPUT,));
  __SET_VAR(data__->C_PRAGMA0.,IN,,__GET_VAR(data__->INPUT,));
  C_PRAGMA_body__(&data__->C_PRAGMA0);

  goto __end;

__end:
  return;
} // PLC_PRG_body__() 





