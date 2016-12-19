

/******************************************************
  NAME     : RFInterfaceTTL.cpp
  Coded by : �� ����
  Revision : 1.0
  Date     : 2007/02/07 ~

*/


#include "RFInterfaceTTL.h"

// �� ���� 
#include  "../../PacketRouter/PacketRouter.h"

class PacketRouter RF_Router;


RFInterfaceTTL::RFInterfaceTTL() : b_open(false), b_portSet(false), run_flag(true), mediaInterfaceType(COMPANY_DUMMY), mediaInterfaceProtocol(PROTOCOL_DUMMY)
{

}

RFInterfaceTTL::~RFInterfaceTTL() 
{
	UartClose();
}


int RFInterfaceTTL::UartOpen(char* UartPort, unsigned int BAUDRATE, enum UARTINTERFACECOMPANY InterfaceCompany , enum UARTINTERFACEPROTOCOL InterfaceProtocol)
{
	char uartPortStr[40] = {0x00, };

    struct termios newtio;	
	
	// RS485 Port�� �ߺ� Open�� �����ϱ� ����
	if(  GetInterfaceCompany() != 0) return FAIL;

	if (b_open)  UartClose();	 

 	sprintf(uartPortStr, "/dev/%s", UartPort);
	i_SLfd = ::open(uartPortStr, O_RDWR | O_NOCTTY);
	Log(Wall::LOG_RFM, "### RF MODULE PORT OPEN [ %s] :: SUCCESS", uartPortStr);

 
	switch( BAUDRATE ) {

		case 1: // B2400
			BAUDRATE = B2400;
			break;

		case 2:  // B4800
			BAUDRATE = B4800;
			break;

		case 3:  // B9600
			BAUDRATE = B9600;
			break;

		case 4:  // B19200
			BAUDRATE = B19200;
			break;
		
		case 5:  // B38400
			BAUDRATE = B38400;			
			break;
		
		case 6:  // B57600
			BAUDRATE = B57600;
			break;

		case 7:  // B115200
			BAUDRATE = B115200;
			break;

		default:
			 Log(Wall::LOG_RFM, "### RF MODULE PORT BAUDRATE [ B4800 - B38400 ] :: NOT FOUNDED");	
			break;

	}
	
	if (i_SLfd < 0) {

		//Log(Wall::LOG_RS485, "### RS-485 PORT OPEN [ COMMPROT : %d ] :: ERROR", COMMPORT);	
		return FAIL;
	}
	else  b_open = true;
	

	if (!b_portSet) {
	 /* save current serial port settings */
	  //tcgetattr(i_SLfd,&oldtio);
		b_portSet = true;
	}

	/* clear struct for new port settings */
    bzero(&newtio, sizeof(newtio)); 

  /*
    BAUDRATE: Set bps rate. You could also use cfsetispeed and cfsetospeed.  
    CS8     : 8n1 (8bit,no parity,1 stopbit)
    CLOCAL  : local connection, no modem contol
    CREAD   : enable receiving characters
  */
   newtio.c_cflag =  BAUDRATE | CS8 | CLOCAL | CREAD;

   newtio.c_iflag = 0;
  
   newtio.c_oflag = 0;

 
   newtio.c_lflag = 0;

   newtio.c_cc[VTIME] = 0;   //���� ������ timer�� disable 	

   newtio.c_cc[VMIN]  = 0;   //�ּ� 1 ���� ���� ������ blocking 		
	
  /*
    now clean the modem line and activate the settings for the port
  */
   //tcflush(i_SLfd, TCIFLUSH);
   //tcsetattr(i_SLfd,TCSANOW,&newtio);

  // Log(Wall::LOG_RS485, "CMX485 SERIAL Successfully Serial Open:");

   
    mediaInterfaceType = InterfaceCompany;

	mediaInterfaceProtocol = InterfaceProtocol;

   return SUCCESS;

}


 /** shows if the serial link is opened */
 bool RFInterfaceTTL::isOpen() const
 {
	return b_open;
 }

void RFInterfaceTTL::isSleep(unsigned long sec)
{
	sleep(sec);
	
}

/** closing the serial port */
int RFInterfaceTTL::UartClose()
{
	 /* restore the old port settings */  
	if (b_portSet)  //tcsetattr(i_SLfd,TCSANOW,&oldtio);
		b_portSet = false;

	if (b_open) ::close(i_SLfd);
		b_open = false;

	run_flag = false;
	return SUCCESS;
}

 /** identify that company of device interface type : �ڸƽ�, �浿*/
void RFInterfaceTTL::SetInterfaceCompany(enum UARTINTERFACECOMPANY mediaType)
{

	mediaInterfaceType = mediaType;		

}

enum UARTINTERFACECOMPANY RFInterfaceTTL::GetInterfaceCompany()
{
	return mediaInterfaceType;
}

 /** identify that The company using of device interface protocol : �ڸƽ� RS485��������, �浿 RS485�������� */
void RFInterfaceTTL::SetProtocol(enum UARTINTERFACEPROTOCOL mediaProtocol)
{

	 mediaInterfaceProtocol = mediaProtocol;
}

enum UARTINTERFACEPROTOCOL RFInterfaceTTL::GetInterfaceProtocol()
{
	return mediaInterfaceProtocol;
}

unsigned int  RFInterfaceTTL::SendFrame(unsigned char * frame, unsigned int frameLength)
{
	
	if (!b_open) {

		Log(Wall::LOG_RFM, "### RF MODULE [TTYS3 INTERFACE [ RS485 ] OPEN :: FAIL ");	
		return FAIL;
	}
	
	unsigned int sent = 0;
	int res = 0;
	int selectStatus = 0;	
	
	Log(Wall::LOG_RFM, "### PACKET ROUTER -> INTERFACE MEDIA [ RF MODULE] , FRAMESIZE : %d:: %02x`%02x`%02x`%02x`%02x`%02x`%02x`%02x", frameLength, frame[0],frame[1],frame[2],frame[3],frame[4],frame[5],frame[6],frame[7],frame[8]);	
	
	
	while(res < frameLength) {	
		
		FD_ZERO(&fdsw);
		FD_SET(i_SLfd,&fdsw);
		
		selectStatus = (unsigned)select(i_SLfd+1,NULL,&fdsw,NULL, NULL);

		if(selectStatus == -1) {

			//Log(Wall::LOG_Cmx485, "### SERIAL -> CMX485::  UARTSERIAL.C : uart_data_send function -> Error Select");

			return FAIL;
		}
		
		if(FD_ISSET(i_SLfd,&fdsw)) {
			
			res = write(i_SLfd, frame, frameLength);

			//Log(Wall::LOG_Cmx485, "### SERIAL -> CMX485:: UARTSERIAL.C : uart_data_send function : return size -> write function : %d", res);
			if (res == -1) {
				//Log(Wall::LOG_Cmx485, "### SERIAL -> CMX485:: UARTSERIAL.C :: uart_data_send function : Error Writing to Serial Port");
				return FAIL;
			}   
			else if(res == 0 )

				Log(Wall::LOG_RFM, "### SERIAL -> RF MODULE:: RFINTERFACE.CPP :: uart_data_send function : write res value => 0");
				
			else {				
				
				sent += res;				
				
			}	
					
		}else{
			if( sent > 0 ) {		

				Log(Wall::LOG_RFM, "### PACKET ROUTER -> INTERFACE MEDIA [RF MODULE]:: SENDING TIME OUT :%d \n", sent);
				return FAIL;
			}
		}

		
	} // end of while

	return SUCCESS;
}

#define MAX_BUFFER 256
// Thread of receive data
void * RFInterfaceTTL::run(void *arg)
{
	

	fd_set fdsr;	
	int recvSize = 0;	
    int selectStatus = 0;	

	unsigned int rcvCount = 0;	
	
	unsigned char readBuffer[RFMODULE_BUFFER_SIZE] = {0x00,};
	unsigned char recvBuffer[MAX_BUFFER] = {0x00,};
	unsigned char tempBuffer[MAX_BUFFER] = {0x00,};

	unsigned char recvComplete[RFMODULE_BUFFER_SIZE] = {0x00,};

	Log(Wall::LOG_RFM, "### RF MODULE :: THREAD STARTING [ INTERFACE THREAD ]");

	
	RFInterfaceTTL * rfmodule = (RFInterfaceTTL*)arg;

	while(rfmodule->run_flag) { 

		FD_ZERO(&fdsr);
		FD_SET(rfmodule->i_SLfd,&fdsr);			
	    selectStatus = select(rfmodule->i_SLfd+1, &fdsr, NULL, NULL,NULL);
	  
		if(selectStatus == -1)
		{			
			Log(Wall::LOG_RFM, "### RF MODULE:: RFINTERFACETTL.CPP :: ERROR SELECT : RETURN  SELECT : -1\n");
			//continue;
			rfmodule->UartClose();			
		}
		
		if(FD_ISSET(rfmodule->i_SLfd,&fdsr)) {
			
			
			switch(  rfmodule->GetInterfaceCompany() ) {

				// GOIM INTERFACE
				case INTERFACE_GOIM_TTL:
				{					
					recvSize = read(rfmodule->i_SLfd, readBuffer, RFMODULE_BUFFER_SIZE);					
		
					if (recvSize == -1) {			
				
						Log(Wall::LOG_RFM, "### [ GO-IM RF ]SERIAL <- RFMODULE:: UARTSERIAL.C::: ERROR WRITTING TO SERIAL PORT  : -1\n");
						rfmodule->UartClose();		
						break;
					}	
					else if(recvSize == 0 )				

						Log(Wall::LOG_RFM, "### [ GO-IM RF RF ] SERIAL <- RFMODULE:: UARTSERIAL.C :: READ VALUE FROM RF : RECVSIZE : 0 \n");

					else {										
						
						if( recvSize == RFMODULE_BUFFER_SIZE ) {					

							
							RF_Router.FrameReceive(readBuffer, RFMODULE_BUFFER_SIZE, rfmodule->GetInterfaceCompany(), rfmodule->GetInterfaceProtocol() );

							Log(Wall::LOG_RFM, "### [ GO-IM RF RF ] SERIAL <- RFMODULE:: RECV SIZE :: %d", recvSize );

						} else  {										
														
							memcpy( (recvBuffer+rcvCount), readBuffer, recvSize);
					
							rcvCount += recvSize;

							Log(Wall::LOG_RFM, "### [ GO-IM RF RF ] READ SIZE :%d\n", recvSize);

							while( rcvCount >= RFMODULE_BUFFER_SIZE ) {

								memcpy( recvComplete, recvBuffer, RFMODULE_BUFFER_SIZE);	
								
								RF_Router.FrameReceive(recvComplete, RFMODULE_BUFFER_SIZE, rfmodule->GetInterfaceCompany(), rfmodule->GetInterfaceProtocol() );

								memset( recvComplete, 0x00, RFMODULE_BUFFER_SIZE);

								rcvCount -= RFMODULE_BUFFER_SIZE;
								// RF��⿡�� Garbage Data�� ���ŵǼ� �Ʒ��� ���� ó����
								memcpy(tempBuffer, (recvBuffer+RFMODULE_BUFFER_SIZE), rcvCount);						

								memcpy(recvBuffer, tempBuffer, rcvCount);

								memset(tempBuffer, 0x00, MAX_BUFFER);

								if( rcvCount < RFMODULE_BUFFER_SIZE) {							
							
									Log(Wall::LOG_RFM, "### [ GO-IM RF RF ] LESS PACKET < 24 : Size : %d\n", rcvCount);

									if( recvBuffer[0] != 0x02) {

										Log(Wall::LOG_RFM, "### [ GO-IM RF RF ] RF RECV BUFFER RESET : %d\n", rcvCount);

										memset(recvBuffer, 0x00, MAX_BUFFER);
										rcvCount = 0;
									}
									break;
								}
							} // end of while
						 }
					} // end of outer if
					
				} // end of case
				break;
				
				// KYOUNGDONG INTERFACE
				case INTERFACE_KYOUNGDONG_RS485:

				
				break;

				// PLANET 
				case INTERFACE_PLANET_RS485 :

				break;

				default:
					break;

		    } // end of switch statement
			
		}
				
	} // end of while
	Log(Wall::LOG_RFM, "### GOIM:: THREAD ENDING [ INTERFACE THREAD ]");

	pthread_exit(NULL);
	return NULL;
}

void RFInterfaceTTL::Start()
 {

	int ret;	

	if( (ret = pthread_attr_init( &rf_ttl_thread_t) ) != 0 ) {

			Log(Wall::LOG_RFM, " CAN'T  CREATE THREAD ATTRIBUTE : RF MODULE THREAD\n");
	}
	
	if( (ret = pthread_attr_setdetachstate( &rf_ttl_thread_t, PTHREAD_CREATE_DETACHED) ) != 0 ) {
			
			Log(Wall::LOG_RFM, " CAN'T SET THREAD SET DETACH : RF MODULE THREAD\n");
	}

	if( (ret = pthread_create( &rf_ttl_thread, &rf_ttl_thread_t, RFInterfaceTTL::run, (void*)this) ) != 0 )
	{
		
		
		Log(Wall::LOG_RS485, " CAN'T FAIL THREAD CREATE\n");

	}


	Log(Wall::LOG_RFM, " SUCCESSFULLY THREAD CREATE n");

	(void)pthread_attr_destroy(&rf_ttl_thread_t);		


 }
