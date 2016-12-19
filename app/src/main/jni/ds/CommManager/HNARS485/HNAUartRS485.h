
/******************************************************
  NAME     : HNAUartRS485.H
  Coded by : �� ����
  Revision : 1.0
  Date     : 2014/02/04 ~

*/

#ifndef __HNAUARTRS485_H__
#define __HNAUARTRS485_H__


//system includes
#include <termios.h>
#include <sys/time.h>
#include <unistd.h>
#include <sys/types.h>  
#include <sys/stat.h>  
#include <fcntl.h>  
#include <unistd.h>  
#include <string.h>  
#include <stdio.h>
#include <stdlib.h>

//아래 2 라인은 일단 주석 처리

//#include <exception>
//#include <string>

//local includes
#include "../CommManager.h"
#include "../../Util/wnamespace.h"
#include "../../Util/util.h"

#include "../../Config/DeviceInfo.h"
#include "../../Config/CmxPacketSize.h"

//아래 라인 일단 주석 처리!!
//using namespace std;

class HNAUartRS485 :  public CommManager {	

	 private: // Private attributes
		      /** File Descriptor for the serial port */
			  int i_SLfd;
 
			  /** flag if the serial link is opened */
			  bool b_open;

			  /** stores old port settings */
			  struct termios oldtio;

			  /** if port settings are changed and old port settings are stored. */
			  bool b_portSet;

			  /** stop running thread */
			  bool run_flag;

			  fd_set fdsw;

			  /** identify that company of device interface type : �ڸƽ�, �浿*/
			  enum UARTINTERFACECOMPANY mediaInterfaceType;
			
			  /** identify that The company using of device interface protocol : �ڸƽ� RS485��������, �浿 RS485�������� */
			 enum UARTINTERFACEPROTOCOL mediaInterfaceProtocol;
	  public:		  	 

			  /** default constructor */
			  HNAUartRS485();

			  /** default destructor */
			  virtual ~HNAUartRS485();

			  /** opening the serial port */  
			  int UartOpen(char* UartPort, unsigned int,  enum UARTINTERFACECOMPANY , enum UARTINTERFACEPROTOCOL );

			  /** shows if the serial link is opened */
			  bool isOpen() const;

			  /** closing the serial port */
			  int UartClose();				  
		     
			  void isSleep(unsigned long);	
			  
			   /** identify that device interface type :: RS-485 */
			  void SetInterfaceCompany(enum UARTINTERFACECOMPANY);
			  enum UARTINTERFACECOMPANY GetInterfaceCompany();

			  void SetProtocol(enum UARTINTERFACEPROTOCOL);
			  enum UARTINTERFACEPROTOCOL GetInterfaceProtocol();

			  unsigned int  SendFrame(unsigned char *, unsigned int);
			  unsigned int  RecvFrame(unsigned char *, unsigned int );

			   // Only C Thread
			  void Start();
			  static void * run(void *);	

			 // Thread Atrribute
			 pthread_t rs485_thread;

			 pthread_attr_t rs485_thread_t;
	
};

#endif

