/*    
      ____                      _____                  +---+
     / ___\                     / __ \                 | R |
    / /                        / /_/ /                 +---+
   / /   ________  ____  ___  / ____/___  ____  __   __
  / /  / ___/ __ `/_  / / _ \/ /   / __ \/ _  \/ /  / /
 / /__/ /  / /_/ / / /_/  __/ /   / /_/ / / / / /__/ /
 \___/_/   \__,_/ /___/\___/_/    \___ /_/ /_/____  /
                                                 / /
                                            ____/ /
                                           /_____/
Battery.c file
???:??  (Camel)
??E-mail:375836945@qq.com
????:MDK-Lite  Version: 4.23
????: 2014-01-28
??:
1.????AD???
2.??????,???????????
------------------------------------
*/

#include "Battery.h"
#include "UART1.h"
#include "stdio.h"
#include "CommApp.h"
#include "ReceiveData.h"
#include "control.h"

//????????????
Bat_Typedef Battery;


//???????ADC
//??ADC1???8	
//BatteryCheck---->PB0
void BatteryCheckInit()
{
  
 //??PB0?????
  RCC->APB2ENR|=1<<3;    //??PORTB??? 
  GPIOB->CRL&=0XFFFFFFF0;//PB0	anolog??
	//??8	 
	RCC->APB2ENR|=1<<9;    //ADC1????	  
	RCC->APB2RSTR|=1<<9;   //ADC1??
	RCC->APB2RSTR&=~(1<<9);//????	    
	RCC->CFGR&=~(3<<14);   //??????	
	//SYSCLK/DIV2=12M ADC?????12M,ADC????????14M!
	//?????ADC?????! 
	RCC->CFGR|=2<<14;      	 
	ADC1->CR1&=0XF0FFFF;   //??????
	ADC1->CR1|=0<<16;      //??????  
	ADC1->CR1&=~(1<<8);    //?????	  
	ADC1->CR2&=~(1<<1);    //??????
	ADC1->CR2&=~(7<<17);	   
	ADC1->CR2|=7<<17;	     //??????  
	ADC1->CR2|=1<<20;      //???????(SWSTART)!!!	???????????
	ADC1->CR2&=~(1<<11);   //???	 
	ADC1->CR2|=1<<23;      //???????

	ADC1->SQR1&=~(0XF<<20);
	ADC1->SQR1&=0<<20;     //1????????? ??????????1 			   
	//????1?????
	ADC1->SMPR2&=~(7<<3);  //??1??????	  
 	ADC1->SMPR2|=7<<3;     //??1  239.5??,?????????????	 

 	ADC1->SMPR1&=~(7<<18);  //????16?????	 
	ADC1->SMPR1|=7<<18;     //??16  239.5??,?????????????	 

	ADC1->CR2|=1<<0;	   //??AD???	 
	ADC1->CR2|=1<<3;       //??????  
	while(ADC1->CR2&1<<3); //?????? 			 
  //???????????????????????????????? 		 
	ADC1->CR2|=1<<2;        //??AD??	   
	while(ADC1->CR2&1<<2);  //??????
	//????????????,????????????  
  
  Battery.BatReal = 3.95;//???v ??????  ???????
  Battery.ADinput = 1.98;//???v R15?R17????? ???????
  Battery.ADRef   = 3.26;//???v ???????   ???????
  Battery.Bat_K   = Battery.BatReal/Battery.ADinput;//????????
	Battery.overDischargeCnt = 0;
  
  printf("Batter voltage AD init ...\r\n");
  
}


//??ADC?
//ch:??? 0~16
//???:????
u16 Get_Adc(u8 ch)   
{
	//??????	  		 
	ADC1->SQR3&=0XFFFFFFE0;//????1 ??ch
	ADC1->SQR3|=ch;		  			    
	ADC1->CR2|=1<<22;       //???????? 
	while(!(ADC1->SR&1<<1));//??????	 	   
	return ADC1->DR;		    //??adc?	
}

//????ch????,?times?,???? 
//ch:????
//times:????
//???:??ch?times????????
u16 Get_Adc_Average(u8 ch,u8 times)
{
	u32 temp_val=0;
	u8 t;
	for(t=0;t<times;t++)
	{
		temp_val+=Get_Adc(ch);
	}
	return temp_val/times;
} 

//??ADC?????????????
//???3???? XXX*0.1C	 
int Get_Temp(void)
{				 
	u16 temp_val=0;
	u8 t;
	float temperate;   
	for(t=0;t<20;t++)//?20?,????
	{
		temp_val+=Get_Adc(16);//????????16
	}
	temp_val/=20;
	temperate=(float)temp_val*(3.3/4096);//???????????
	temperate=(1.43-temperate)/0.0043+25;//????????	 
	temperate*=10;//????,????????
	return (int)temperate;	 
}


//??????AD?
int GetBatteryAD()
{
 return Get_Adc_Average(8,5);
}

#include "BT.h"

//??????
void BatteryCheck(void)
{
		Battery.BatteryAD  = GetBatteryAD();            //??????  
		Battery.BatteryVal = Battery.Bat_K * (Battery.BatteryAD/4096.0) * Battery.ADRef;//???? ???	
	
	  if(FLY_ENABLE){
			//???????????,??????(BAT_OVERDIS_VAL)??0.03v??,????
			if(Battery.BatteryVal <= (BAT_OVERDIS_VAL + 0.03)){
					Battery.alarm=1;
			}else{
					Battery.alarm=0;
			}
			
			//????,Battery overdischarge protect
			if(Battery.BatteryVal <= BAT_OVERDIS_VAL){
				Battery.overDischargeCnt++;
				
				if(Battery.overDischargeCnt > 8){
					altCtrlMode=LANDING;
					rcData[0]=1500;rcData[1]=1500;rcData[2]=1500;rcData[3]=1500;
				}
			}else{
				Battery.overDischargeCnt = 0;
			}
		}else{
			if((Battery.BatteryVal < BAT_ALARM_VAL)&&(Battery.BatteryVal > BAT_CHG_VAL)){	//??3.7v ????????? BAT_CHG_VAL
				Battery.alarm=1;
			}else{
				Battery.alarm=0;
			}
		}
		
		if(Battery.BatteryVal < BAT_CHG_VAL){ //on charge
			Battery.chargeSta = 1; 
			BT_off();
		}else{
			Battery.chargeSta = 0;
		}

}



