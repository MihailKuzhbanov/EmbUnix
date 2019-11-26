FUNCTION_BLOCK C_Pragma
  VAR_INPUT
    OUT : INT := 25;
  END_VAR
  VAR_OUTPUT
    VALUE : INT := 0;
  END_VAR
  VAR_INPUT
    IN : INT := 24;
  END_VAR

  {{
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
  }}
END_FUNCTION_BLOCK

PROGRAM plc_prg
  VAR_INPUT
    Input : INT := 24;
    Output : INT := 25;
  END_VAR
  VAR
    C_Pragma0 : C_Pragma;
  END_VAR

  C_Pragma0(OUT := Output, IN := Input);
END_PROGRAM


CONFIGURATION config

  RESOURCE resource1 ON PLC
    TASK GetTimeSync(INTERVAL := T#0.15ms,PRIORITY := 0);
    PROGRAM plc_task_instance WITH GetTimeSync : plc_prg;
  END_RESOURCE
END_CONFIGURATION
