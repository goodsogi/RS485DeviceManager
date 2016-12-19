/******************************************************
  NAME     : UARTRSTTL.H
  Coded by : �� ����
  Revision : 1.0
  Date     : 2007/02/07 ~

*/

#ifndef __UARTRSTTL_H__
#define __UARTRSTTL_H__

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

/**
Class that provides communication via the serial port
  
*/

class UartRSTTL :  public CommManager {


public: 
	
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
			  UartRSTTL();

			  /** default destructor */
			  virtual ~UartRSTTL();

			  /** opening the serial port */  
			  int UartOpen(char*, unsigned int,  enum UARTINTERFACECOMPANY , enum UARTINTERFACEPROTOCOL );

			  /** shows if the serial link is opened */
			  bool isOpen() const;

			  /** closing the serial port */
			  int UartClose();				  
		     
			  void isSleep(unsigned long);	
			  
			   /** identify that device interface type :: TTL */
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
			 pthread_t z256_thread;

			 pthread_attr_t z256_thread_t;

			  

};

#endif

