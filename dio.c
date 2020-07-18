#include  "dio.h"


Dio_LevelType Dio_ReadChannel( Dio_ChannelType ChannelId )
{
	
	uint8_t port=ChannelId/8;
	uint8_t pin=ChannelId%8;
	if (port==PORT_A)
	{
		return (GPIOA->DATA&(1<<pin));
		
		
	}
	else if (port==PORT_B)
	{
		
		return (GPIOB->DATA&(1<<pin));
		
	}
	else if (port==PORT_C)
	{
		
		return (GPIOC->DATA&(1<<pin));
		
	}
	
	else if (port==PORT_D)
	{
		
		return (GPIOD->DATA&(1<<pin));
		
	}
	
	else if (port==PORT_E)
	{
		
		return (GPIOE->DATA&(1<<pin));
		
	}
	
	else if (port==PORT_F)
	{
		return (GPIOF->DATA&(1<<pin));	
	}
}
void Dio_WriteChannel ( Dio_ChannelType ChannelId, Dio_LevelType Level )
{
	
	
		uint8_t port=ChannelId/8;
	uint8_t pin=ChannelId%8;
	if (port==PORT_A)
	{
		GPIOA->DATA&=~(1<<pin);
    GPIOA->DATA|=Level<<pin; 
		
		
	}
	else if (port==PORT_B)
	{
	GPIOB->DATA&=~(1<<pin);
	GPIOB->DATA|=Level<<pin; 
		
	}
	else if (port==PORT_C)
	{
	 GPIOC->DATA&=~(1<<pin);
	 GPIOC->DATA|=Level<<pin; 
		
	}
	
	else if (port==PORT_D)
	{
		GPIOD->DATA&=~(1<<pin);
GPIOD->DATA|=Level<<pin; 
		
	}
	
	else if (port==PORT_E)
	{
	GPIOE->DATA&=~(1<<pin);
	GPIOE->DATA|=Level<<pin; 
		
	}
	
	else if (port==PORT_F)
	{
	 GPIOF->DATA&=~(1<<pin);
	 GPIOF->DATA|=Level<<pin; 	
	}
}
	
	Dio_PortLevelType Dio_ReadPort ( Dio_PortType PortId )
	{
		
		if(PortId==PORT_A)
		{
			return (GPIOA->DATA);
		}
		else if (PortId==PORT_B)
		{
			return (GPIOB->DATA);
		}
		else if (PortId==PORT_C)
		{
			return (GPIOC->DATA);
		}
		else if (PortId==PORT_D)
		{
			return (GPIOD->DATA);
		}
		else if (PortId==PORT_E)
		{
			//GPIOF->DATA &=~(1<<7)|(1<<6);
			return (GPIOE->DATA)&0x3F;
		}
		else if (PortId==PORT_F)
		{
			return (GPIOB->DATA)&0x1F;
		}

	}
	
	void Dio_WritePort ( Dio_PortType PortId, Dio_PortLevelType Level )
	{
		
	if (PortId==PORT_A)
	{
    GPIOA->DATA=Level;
		
	}
	else if (PortId==PORT_B)
	{
		
	GPIOB->DATA=Level; 
		
	}
	else if (PortId==PORT_C)
	{
		
	 GPIOC->DATA=Level; 
		
	}
	
	else if (PortId==PORT_D)
	{
GPIOD->DATA=Level; 
		
	}
	
	else if (PortId==PORT_E)
	{
		
	GPIOE->DATA=Level; 
		
	}
	
	else if (PortId==PORT_F)
	{
	 GPIOF->DATA=Level; 	
	}
			
		
	}
	Dio_PortLevelType Dio_ReadChannelGroup ( const Dio_ChannelGroupType* ChannelGroupIdPtr )
	{
		uint8_t temp;
		if(ChannelGroupIdPtr->port==PORT_A)                          
		{                                                              
			temp =(GPIOA->DATA)&(ChannelGroupIdPtr->mask);              
		  temp=temp >> ChannelGroupIdPtr->offset;                                        
			return temp;
		
		}
		else if (ChannelGroupIdPtr->port==PORT_B)
		{
			temp =(GPIOB->DATA)&(ChannelGroupIdPtr->mask);              
		  temp=temp >> ChannelGroupIdPtr->offset;                                        
			return temp;
			
			
		}
		else if (ChannelGroupIdPtr->port==PORT_C)
		{
			
			temp =(GPIOC->DATA)&(ChannelGroupIdPtr->mask);              
		  temp=temp >> ChannelGroupIdPtr->offset;                                        
			return temp;
			
		}
		else if (ChannelGroupIdPtr->port==PORT_D)
		{
			
			temp =(GPIOD->DATA)&(ChannelGroupIdPtr->mask);              
		  temp=temp >> ChannelGroupIdPtr->offset;                                        
			return temp;
			
		}
		else if (ChannelGroupIdPtr->port==PORT_E)
		{
			temp =(GPIOE->DATA)&(ChannelGroupIdPtr->mask);              
		  temp=temp >> ChannelGroupIdPtr->offset;                                        
			return temp;
			
		}
		else if (ChannelGroupIdPtr->port==PORT_F)
		{
			temp =(GPIOF->DATA)&(ChannelGroupIdPtr->mask);              
		  temp=temp >> ChannelGroupIdPtr->offset;                                        
			return temp;
		}
			
	}
		
		
	void Dio_WriteChannelGroup ( const Dio_ChannelGroupType* ChannelGroupIdPtr, Dio_PortLevelType Level )
	{
		
		if(ChannelGroupIdPtr->port==PORT_A)                          
		{   
     
			//GPIOA->DATA&=~(ChannelGroupIdPtr->mask);
			// GPIOA->DATA|=Level<<(ChannelGroupIdPtr->offset);
      if (Level==STD_HIGH)			
			GPIOA->DATA|=ChannelGroupIdPtr->mask;              
		else if(Level==STD_LOW)
			GPIOA->DATA&=~(ChannelGroupIdPtr->mask);
			
		}
		else if (ChannelGroupIdPtr->port==PORT_B)
		{
		if (Level==STD_HIGH)			
			GPIOB->DATA|=ChannelGroupIdPtr->mask;              
		else if(Level==STD_LOW)
			GPIOB->DATA&=~(ChannelGroupIdPtr->mask);
			
		}
		else if (ChannelGroupIdPtr->port==PORT_C)
		{
			
			if (Level==STD_HIGH)			
			GPIOC->DATA|=ChannelGroupIdPtr->mask;              
		else if(Level==STD_LOW)
			GPIOC->DATA&=~(ChannelGroupIdPtr->mask);
		}
		else if (ChannelGroupIdPtr->port==PORT_D)
		{
			
		if (Level==STD_HIGH)			
			GPIOD->DATA|=ChannelGroupIdPtr->mask;              
		else if(Level==STD_LOW)
			GPIOD->DATA&=~(ChannelGroupIdPtr->mask);
			
		}
		else if (ChannelGroupIdPtr->port==PORT_E)
		{
		if (Level==STD_HIGH)			
			GPIOE->DATA|=ChannelGroupIdPtr->mask;              
		else if(Level==STD_LOW)
			GPIOE->DATA&=~(ChannelGroupIdPtr->mask);
			
		}
		else if (ChannelGroupIdPtr->port==PORT_F)
		{
			if (Level==STD_HIGH)			
			GPIOF->DATA|=ChannelGroupIdPtr->mask;              
		else if(Level==STD_LOW)
			GPIOF->DATA&=~(ChannelGroupIdPtr->mask);
		}
		
	}
		
		
	
	
