

/******************************************************
  NAME     : COMMMANAGER.H
  Coded by : 김 광기
  Revision : 1.0
  Date     : 2007/02/07 ~

*/


#ifndef __COMMMANAGER_H__
#define __COMMMANAGER_H__



#include <pthread.h> 

//#include "RFInterFace/RFInterfaceTTL.h"
#include "../Config/DeviceInfo.h"



class CommManager 
{

	public:
		   virtual ~CommManager() {};
		   
		   virtual int UartOpen(char*, unsigned int, enum UARTINTERFACECOMPANY , enum UARTINTERFACEPROTOCOL ) = 0;
		   virtual int UartClose() = 0;
		   

		   // RS-485Port를 사용하는 회사
		   virtual void SetInterfaceCompany(enum UARTINTERFACECOMPANY) = 0;
		   virtual enum UARTINTERFACECOMPANY GetInterfaceCompany() = 0;

		   // RS-485Port를 사용하는 회사의 프로토콜
		   virtual void SetProtocol(enum UARTINTERFACEPROTOCOL) = 0;	
		   virtual  enum UARTINTERFACEPROTOCOL GetInterfaceProtocol() = 0;

		   // Transmission Media로 데이터 전송
		   virtual unsigned int  SendFrame(unsigned char *, unsigned int ) = 0;
		  
		   //virtual void run();

		    /** shows if the serial link is opened */
		   //virtual bool isOpen()  const;

};

#endif

