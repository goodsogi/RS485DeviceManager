

/******************************************************
  NAME     : COMMMANAGER.H
  Coded by : �� ����
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
		   

		   // RS-485Port�� ����ϴ� ȸ��
		   virtual void SetInterfaceCompany(enum UARTINTERFACECOMPANY) = 0;
		   virtual enum UARTINTERFACECOMPANY GetInterfaceCompany() = 0;

		   // RS-485Port�� ����ϴ� ȸ���� ��������
		   virtual void SetProtocol(enum UARTINTERFACEPROTOCOL) = 0;	
		   virtual  enum UARTINTERFACEPROTOCOL GetInterfaceProtocol() = 0;

		   // Transmission Media�� ������ ����
		   virtual unsigned int  SendFrame(unsigned char *, unsigned int ) = 0;
		  
		   //virtual void run();

		    /** shows if the serial link is opened */
		   //virtual bool isOpen()  const;

};

#endif

