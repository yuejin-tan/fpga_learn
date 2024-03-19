#ifndef __CM3DS_DMA_H
#define __CM3DS_DMA_H
#ifdef __cplusplus //C++跨平台调用 在windows
extern "C" {
#endif
#include "CM3DS_MPS2.h"

	typedef struct
	{
		uint8_t		DMA_IT_TerninalCount;//终端计数中断使能 [31]
		uint8_t		DMA_DI;			//外设地址增量模式 [27]
		uint8_t 	DMA_SI;			//源地址增量模式   [26]
		uint8_t		DMA_DWidth;	//目的地传输宽度   [23:21] 000-8bit 001-16bit
		uint8_t		DMA_SWidth;	//源传输宽度	     [20:18] 010-32bit
		uint8_t		DMA_DBSize;	//目的地突发大小   [17:15] 000-1   001-4  010-8
		uint8_t		DMA_SBSize;	//源突发大小 			 [14:12] 011-16  100-32 101-64
		//												 110-128 111-256
		uint16_t	DMA_TXSize;	//传输数目 				 [11:00]

	}DMA_InitTypedef;

	typedef struct
	{
		// DMA_CConfiguration;
		uint8_t		DMA_Halt; //0=en 1=ignore
		//uint8_t   DMA_Active; //0=no data in the fifo  1=has data (read)
		uint8_t		DMA_Lock; //when set,locked transfers;
		uint8_t   	DMA_ITC;  //Terminal count interrupt mask
		uint8_t   	DMA_IE;   //Interrupt error mask; 0=maks  1=not mask
		uint8_t   	DMA_FlowCntrl;//[13:11] Flow control and transfer type;

		uint8_t   	DMA_DestPeripheral;//[9:6] 传输目的地为内存则忽略
		uint8_t   	DMA_SrcPeripheral; //[4:1] 来源为内存则忽略
		uint8_t   	DMA_ChannelEnabnle;//0=disable 1=enable

	}DMA_ChannelInitTypedef;
	//////////////////////////////////////////////////////////////////////////////////   	 
#define IS_DMA_ALL_PERIPH(PERIPH) (((PERIPH) == CM3DS_MPS2_DMA)) 

#define Channel_0            				(0x0)
#define Channel_1            				(0x1)

#define IS_DMA_Channel(Channel) 	(((Channel) == DMA_Channel_0)||((Channel) == DMA_Channel_1) )

/////////////////////////DMA_Control Register//////////////////////////////////    
#define I_IT_En                   	1  //Destination increment
#define I_IT_Dis            				0

#define DI_En                   		1  //Destination increment
#define DI_Dis            					0
#define SI_En                   		1  //Source increment
#define SI_Dis            					0
#define SWorDWidth_8bit_Byte        ((int)0) 
#define SWorDWidth_16bit_Halfword   ((int)1) 
#define SWorDWidth_32bit_Word       ((int)2) 

#define DB_BurstSize_1          ((int)0) 
#define DB_BurstSize_4          ((int)1) 
#define DB_BurstSize_8          ((int)2) 
#define DB_BurstSize_16         ((int)3) 
#define DB_BurstSize_32         ((int)4) 
#define DB_BurstSize_64         ((int)5) 
#define DB_BurstSize_128        ((int)6) 
#define DB_BurstSize_256        ((int)7) 

#define SB_BurstSize_1          ((int)0) 
#define SB_BurstSize_4          ((int)1) 
#define SB_BurstSize_8          ((int)2) 
#define SB_BurstSize_16         ((int)3) 
#define SB_BurstSize_32         ((int)4) 
#define SB_BurstSize_64         ((int)5) 
#define SB_BurstSize_128        ((int)6) 
#define SB_BurstSize_256        ((int)7) 


/////////////////////////DMA_ChannelConfiguration//////////////////////////////////   		
#define Halt_Dis                   	0  //Halt
#define Halt_En             				1

#define Lock_En                   	1  //Lock
#define Lock_Dis             				0

#define ITC_Mask                   	0  //Terminal count interrupt mask
#define ITC_NotMask             		1

#define IE_Mask                   	0  //Interrupt error mask
#define IE_NotMask             		  1

#define MtoM_DMA						  			((int)0)	//
#define MtoP_DMA             				((int)1)
#define PtoM_DMA						  			((int)2)
#define SPtoDP_DMA             			((int)3)
#define SPtoDP_DP						 			 	((int)4)
#define MtoP_P             					((int)5)
#define PtoM_P						  				((int)6)
#define SPtoDP_SP             			((int)7)


#define DMA_En                       1 //DMA Channel Enable
#define DMA_Dis            		       0
//////////////////////////////////////////////////////////////////////////////////   	
	uint32_t DMA_Interrupt_Status(CM3DS_MPS2_DMA_TypeDef* CM3DS_MPS2_DMAx);
	uint32_t DMA_Enable_Channel(CM3DS_MPS2_DMA_TypeDef* CM3DS_MPS2_DMAx);

	uint32_t DMA_Channel_status(CM3DS_MPS2_PL230_TypeDef* CM3DS_MPS2_DMAx);
	uint32_t DMA_Terminal_Count_status(CM3DS_MPS2_DMA_TypeDef* CM3DS_MPS2_DMAx);
	void DMA_Interrupt_Terminal_Count_Clear(CM3DS_MPS2_DMA_TypeDef* CM3DS_MPS2_DMAx, uint8_t Channel, FunctionalState NewState);

	uint32_t DMA_Interrupt_Error_Status(CM3DS_MPS2_DMA_TypeDef* CM3DS_MPS2_DMAx);
	void DMA_Interrupt_Error_Clear(CM3DS_MPS2_DMA_TypeDef* CM3DS_MPS2_DMAx, uint8_t Channel, FunctionalState NewState);
	uint32_t DMA_Raw_Interrupt_Terminal_Count_Status(CM3DS_MPS2_DMA_TypeDef* CM3DS_MPS2_DMAx);
	uint32_t DMA_Raw_Error_Interrupt_Status(CM3DS_MPS2_DMA_TypeDef* CM3DS_MPS2_DMAx);
	uint32_t DMA_Enabled_Channel(CM3DS_MPS2_DMA_TypeDef* CM3DS_MPS2_DMAx);
	void DMA_Soft_Burst_Request(CM3DS_MPS2_DMA_TypeDef* CM3DS_MPS2_DMAx);
	void DMA_Configuration(CM3DS_MPS2_DMA_TypeDef* CM3DS_MPS2_DMAx, int M, int E);



	void DMA_Source_Address(CM3DS_MPS2_DMA_TypeDef* CM3DS_MPS2_DMAx, uint8_t Channel, uint32_t addr);
	void DMA_Destination_Address(CM3DS_MPS2_DMA_TypeDef* CM3DS_MPS2_DMAx, uint8_t Channel, uint32_t addr);
	void DMA_LLI(CM3DS_MPS2_DMA_TypeDef* CM3DS_MPS2_DMAx, uint8_t Channel, uint32_t data);

	void DMA_Control_Increment(CM3DS_MPS2_DMA_TypeDef* CM3DS_MPS2_DMAx, uint8_t Channel, int I, int DI, int SI);
	void DMA_Control_DataWidth(CM3DS_MPS2_DMA_TypeDef* CM3DS_MPS2_DMAx, uint8_t Channel, int DW, int SW);
	void DMA_Control_TransferSize(CM3DS_MPS2_DMA_TypeDef* CM3DS_MPS2_DMAx, uint8_t Channel, int DB, int SB, int Tx_Size);

	void DMA_ChannelConfig(CM3DS_MPS2_DMA_TypeDef* CM3DS_MPS2_DMAx, uint8_t Channel, int Halt, int Lock, int ITC, int IE);
	void DMA_ChannelConfig_Flow(CM3DS_MPS2_DMA_TypeDef* CM3DS_MPS2_DMAx, uint8_t Channel, int Flow_Control);
	void DMA_ChannelConfig_Peri(CM3DS_MPS2_DMA_TypeDef* CM3DS_MPS2_DMAx, uint8_t Channel, int DestPeri, int SrcPeri, int EN);

	void Wait_Channel_Free(int chnl);
	void SSP_DMA_Request(CM3DS_MPS2_SSP_TypeDef* CM3DS_MPS2_SSPx, int TX_EN, int RX_EN);
	void DMA_LLI_List_Item(CM3DS_MPS2_DMA_TypeDef* CM3DS_MPS2_DMAx, uint8_t DMACCxLLI, uint32_t LLL_Address);

	void DMA_SoftwareBurstRequest(CM3DS_MPS2_DMA_TypeDef* CM3DS_MPS2_DMAx, uint16_t Breq);
	void DMA_SoftwareSingleRequest(CM3DS_MPS2_DMA_TypeDef* CM3DS_MPS2_DMAx, uint16_t Sreq);
	void DMA_SoftwareLastBurstRequest(CM3DS_MPS2_DMA_TypeDef* CM3DS_MPS2_DMAx, uint16_t LBreq);
	void DMA_SoftwareLastSingleRequest(CM3DS_MPS2_DMA_TypeDef* CM3DS_MPS2_DMAx, uint16_t LSreq);


#ifdef __cplusplus
}
#endif

#endif /* __CM3DS_UART_H */
