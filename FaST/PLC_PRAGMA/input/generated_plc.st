FUNCTION_BLOCK C_Pragma
  VAR_INPUT
    NUMOUT : INT := 25;
    SIGNALDATA : ARRAY [0..31] OF INT;
  END_VAR
  VAR_OUTPUT
    DATA0 : INT;
    DATA1 : INT;
    DATA2 : INT;
    DATA3 : INT;
  END_VAR
  VAR_INPUT
    SIGNALINFO : ARRAY [0..31] OF BOOL;
    INFO0 : BOOL;
    INFO1 : BOOL;
    INFO2 : BOOL;
    INFO3 : BOOL;
  END_VAR
  VAR_OUTPUT
    VALIN : INT := 0;
  END_VAR
  VAR_INPUT
    NUMIN : INT := 24;
    PERMIT : INT := 1;
  END_VAR

  {{
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
  }}
END_FUNCTION_BLOCK

PROGRAM plc_prg
  VAR_INPUT
    InputPinNumber : INT := 24;
    Data : ARRAY [0..31] OF INT;
  END_VAR
  VAR
    Info : ARRAY [0..31] OF BOOL;
  END_VAR
  VAR_INPUT
    OutputPinNumber : INT := 25;
  END_VAR
  VAR
    State : INT := 0;
  END_VAR
  VAR_OUTPUT
    Result : INT := 0;
  END_VAR
  VAR
    C_Pragma0 : C_Pragma;
    INT_TO_BOOL21_OUT : BOOL;
    INT_TO_BOOL22_OUT : BOOL;
    INT_TO_BOOL23_OUT : BOOL;
    INT_TO_BOOL24_OUT : BOOL;
  END_VAR

  INT_TO_BOOL21_OUT := INT_TO_BOOL(C_Pragma0.DATA0);
  INT_TO_BOOL22_OUT := INT_TO_BOOL(C_Pragma0.DATA1);
  INT_TO_BOOL23_OUT := INT_TO_BOOL(C_Pragma0.DATA2);
  INT_TO_BOOL24_OUT := INT_TO_BOOL(C_Pragma0.DATA3);
  C_Pragma0(NUMOUT := OutputPinNumber, INFO0 := INT_TO_BOOL21_OUT, INFO1 := INT_TO_BOOL22_OUT, INFO2 := INT_TO_BOOL23_OUT, INFO3 := INT_TO_BOOL24_OUT, NUMIN := InputPinNumber, PERMIT := State);
  Result := C_Pragma0.VALIN;
END_PROGRAM


CONFIGURATION config

  RESOURCE resource1 ON PLC
    TASK GetTimeSync(INTERVAL := T#0.15ms,PRIORITY := 0);
    PROGRAM plc_task_instance WITH GetTimeSync : plc_prg;
  END_RESOURCE
END_CONFIGURATION
