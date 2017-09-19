//------------------------- Step_Motor.h ------------------------------------
void Step_Motor_init(void)
{
  PHASE1_stepM_OUT;
  I01_stepM_OUT;
  I11_stepM_OUT;
  PHASE2_stepM_OUT;
  I02_stepM_OUT;
  I12_stepM_OUT;
 
  PHASE1_stepM_ON;
  I01_stepM_OFF;
  I11_stepM_OFF;
  PHASE2_stepM_ON;
  I02_stepM_OFF;
  I12_stepM_OFF;
  
  
 switch(NAP_MUZD)
 {
      case(0):
      {
         Step_Motor_Position=255*Step_Motor_Koeff;
         Step_Motor_Future=0; 
      }
      default:
      {
         Step_Motor_Position=255*Step_Motor_Koeff;
         Step_Motor_Future=0; 
      }
      break;
  }     
 
  while(Step_Motor_Future!=Step_Motor_Position) __no_operation();
  I01_stepM_ON;
  I11_stepM_ON;
  I02_stepM_ON;
  I12_stepM_ON;
}
//------------------------- end Step_Motor.h --------------------------------

