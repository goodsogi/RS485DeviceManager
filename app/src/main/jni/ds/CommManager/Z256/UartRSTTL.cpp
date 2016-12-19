
/******************************************************
  NAME     : UartRSTTL.cpp
  Coded by : �� ����
  Revision : 1.0
  Date     : 2007/02/07 ~

*/


#include "UartRSTTL.h"


// �� ���� 
#include  "../../PacketRouter/PacketRouter.h"

class PacketRouter Z256_Router;


UartRSTTL::UartRSTTL() : b_open(false), b_portSet(false), run_flag(true),  mediaInterfaceType(COMPANY_DUMMY), mediaInterfaceProtocol(PROTOCOL_DUMMY)
{

}

UartRSTTL::~UartRSTTL() 
{	
	UartClose();
}

int UartRSTTL::UartOpen(char* UartPort, unsigned int BAUDRATE, enum UARTINTERFACECOMPANY InterfaceCompany , enum UARTINTERFACEPROTOCOL InterfaceProtocol)
{
	char uartPortStr[40] = {0x00, };
    struct termios newtio;		

	// TTL Port�� �ߺ� Open�� �����ϱ� ����
	if(  GetInterfaceCompany() != 0) return FAIL;
	
	if (b_open)  UartClose();	 	

	sprintf(uartPortStr, "/dev/%s", UartPort);
	i_SLfd = ::open(uartPortStr, O_RDWR | O_NOCTTY);
	Log(Wall::LOG_RS485, "### [ RS-TTL ] RS-485 PORT OPEN [ %s ] :: SUCCESS", uartPortStr);	
	
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
			 Log(Wall::LOG_Z256, "###RS-TTL[Z256] PORT BAUDRATE [ B4800 - B38400 ] :: NOT FOUNDED");	
			break;

	}
	
	if (i_SLfd < 0) {

		//Log(Wall::LOG_Z256, "### RS-485 PORT OPEN [ COMMPROT : %d ] :: ERROR", COMMPORT);	
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

  // Log(Wall::LOG_Z256, "CMX485 SERIAL Successfully Serial Open:");

   
    mediaInterfaceType = InterfaceCompany;

	mediaInterfaceProtocol = InterfaceProtocol;
	
    return SUCCESS;

}


 /** shows if the serial link is opened */
 bool UartRSTTL::isOpen() const
 {
	return b_open;
 }

void UartRSTTL::isSleep(unsigned long sec)
{
	sleep(sec);
	
}

/** closing the serial port */
int UartRSTTL::UartClose()
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
void UartRSTTL::SetInterfaceCompany(enum UARTINTERFACECOMPANY mediaType)
{

	mediaInterfaceType = mediaType;		

}

enum UARTINTERFACECOMPANY UartRSTTL::GetInterfaceCompany()
{
	return mediaInterfaceType;
}

 /** identify that The company using of device interface protocol : �÷��� �������� */
void UartRSTTL::SetProtocol(enum UARTINTERFACEPROTOCOL mediaProtocol)
{

	 mediaInterfaceProtocol = mediaProtocol;
}

enum UARTINTERFACEPROTOCOL UartRSTTL::GetInterfaceProtocol()
{
	return mediaInterfaceProtocol;
}

unsigned int  UartRSTTL::SendFrame(unsigned char * frame, unsigned int frameLength)
{
	
	if (!b_open) {

		Log(Wall::LOG_Z256, "### RS-TTL[Z256] INTERFACE OPEN :: FAIL ");	
		return FAIL;
	}
	
	unsigned int sent = 0;
	unsigned int res = 0;
	int selectStatus = 0;	
	
	Log(Wall::LOG_Z256, "### PACKET ROUTER -> INTERFACE MEDIA [Z256] , FRAMESIZE : %d:: %02x`%02x`%02x`%02x`%02x", frameLength, frame[0],frame[1],frame[2],frame[3],frame[4]);	
	
	
	while(res < frameLength) {	
		
		FD_ZERO(&fdsw);
		FD_SET(i_SLfd,&fdsw);
		
		selectStatus = (unsigned)select(i_SLfd+1,NULL,&fdsw,NULL, NULL);

		if(selectStatus == -1) {			

			return FAIL;
		}
		
		if(FD_ISSET(i_SLfd,&fdsw)) {
			
			res = write(i_SLfd, frame, frameLength);
			
			if (res == -1) {
				Log(Wall::LOG_Z256, "### SERIAL -> CMX485:: UARTRSTTL.CPP :: WRITE RESPONSE : -1");
				return FAIL;
			}   
			else if(res == 0 )

				Log(Wall::LOG_Z256, "### SERIAL -> CMX485:: UARTRSTTL.CPP :: WRITE RESPONSE : 0");
				
			else {				
				
				sent += res;				
				
			}	
					
		}else{
			if( sent > 0 ) {		

				Log(Wall::LOG_Z256, "### PACKET ROUTER -> INTERFACE MEDIA [Z256]:: SENDING TIME OUT :%d \n", sent);
				return FAIL;
			}
		}

		
	} // end of while

	return SUCCESS;
}


// Thread of receive data

#define READBUFFER 1	

void* UartRSTTL::run(void *arg)
{
	
	fd_set fdsr;	
	int recvSize = 0;	
    int selectStatus = 0;	
	
	unsigned char readBuffer[READBUFFER] = {0x00};	
	
	unsigned  char recvBuf[PLANET_BUFFER_SIZE ] = {0x00,};

	unsigned  int rcvCount = 0;	

	UartRSTTL *z256 = (UartRSTTL*)arg;	

	while( z256->run_flag ) {	 

	
		FD_ZERO(&fdsr);
		FD_SET(z256->i_SLfd,&fdsr);		
		
	    selectStatus = select(z256->i_SLfd+1, &fdsr, NULL, NULL,NULL);
	  
		if(selectStatus == -1)
		{			
			Log(Wall::LOG_Z256, "### UARTRS_TTL <- PLC MODEM ::  ERROR SELECT : RETURN  SELECT : -1\n");
			z256->UartClose();
		}
		
		if(FD_ISSET(z256->i_SLfd,&fdsr)) {
			
			recvSize = read(z256->i_SLfd, readBuffer, READBUFFER);	
		
			if (recvSize == -1) {				
				Log(Wall::LOG_Z256, "### UARTRS_TTL <- PLC MODEM ::  ERROR WRITTING TO SERIAL PORT : -1\n");
				//return;
				z256->UartClose();
				
				break;
			}
			else if(recvSize == 0 )				
				Log(Wall::LOG_Z256, "### UARTRS_TTL <- PLC MODEM :: READ VALUE FROM SERIAL : 0\n");

			else {										
				//Log(Wall::LOG_Z256, "### UARTRS_TTL <- PLC MODEM :: %02x", readBuffer[0]);

				if(recvSize == 1) {	
					
					if( readBuffer[0] == 0x04  || readBuffer[0] == 0x06  ||  readBuffer[0] == 0x15 ) {

						if(recvBuf[0] != 0xfe) {							
							
							Z256_Router.FrameReceive(readBuffer, recvSize,  z256->GetInterfaceCompany(), z256->GetInterfaceProtocol() );
							memset(recvBuf, 0x00, sizeof(recvBuf));
							recvBuf[0] = 0x00;
							rcvCount = 0;

						}else {
							recvBuf[rcvCount++] = readBuffer[0];
						}
					}else {
							
							if(readBuffer[0] == 0xfe) {

								 if(rcvCount != 0 ) {

									 if( rcvCount == 5) { //���� Ŀư�� check_sum���� 0xfe�̹Ƿ� �ѹ� �� 0xfe�� ������
									 
										Z256_Router.FrameReceive(recvBuf, rcvCount,  z256->GetInterfaceCompany(), z256->GetInterfaceProtocol() );
										memset(recvBuf, 0x00, sizeof(recvBuf));
										rcvCount = 0;
									 }else {
																				 
									     recvBuf[rcvCount++] = readBuffer[0];
									 }
								 }else {
									 rcvCount = 0;
									 recvBuf[rcvCount++] = readBuffer[0];
								 }
							}else {
									recvBuf[rcvCount++] = readBuffer[0];
									if( (rcvCount == 5 )|| (rcvCount == 11) ) {		
										
										//process_uart_recv_from_plcmodem(recvBuf, 5);
										if( (rcvCount == 5) && (recvBuf[1] == 0x03) ) {

											Z256_Router.FrameReceive(recvBuf, rcvCount,  z256->GetInterfaceCompany(), z256->GetInterfaceProtocol() );
											memset(recvBuf, 0x00, sizeof(recvBuf));
											rcvCount = 0;
											recvBuf[rcvCount] = 0x00;
											//Log(Wall::LOG_Z256, "### UARTSERIAL.C :: RECV_DATA SIZE :: 5 BYTE\n");

										} else if( (rcvCount == 11) && (recvBuf[1] == 0x09) ) {

											Z256_Router.FrameReceive(recvBuf, 11, z256->GetInterfaceCompany(), z256->GetInterfaceProtocol() );
											memset(recvBuf, 0x00, sizeof(recvBuf));
											rcvCount = 0;
											recvBuf[rcvCount] = 0x00;
											Log(Wall::LOG_Z256, "### UARTRS_TTL <- PLC MODEM :: RECV_DATA SIZE :: 11 BYTE\n");
										}
									}

							}
						
					}
				}			
				
			}
		}
				
	} // end of while
	Log(Wall::LOG_Z256, "### UARTRS_TTL <- PLC MODEM :: RECV_DATA FUNCTION CALLED: ENDING WHILE\n");

	if( z256 != NULL) delete z256;
	pthread_exit(NULL);
	return NULL;
}

void UartRSTTL::Start()
 {

	int ret;		
	
	if( (ret = pthread_attr_init( &z256_thread_t) ) != 0 )
	{

			Log(Wall::LOG_Z256,  " CAN'T  CREATE THREAD ATTRIBUTE \n");
	}
	
	if( (ret = pthread_attr_setdetachstate( &z256_thread_t, PTHREAD_CREATE_DETACHED) ) != 0 ) 
	{
			 
			Log(Wall::LOG_Z256,  " CAN'T SET THREAD SET DETACH \n");
	}

	if( (ret = pthread_create( &z256_thread, &z256_thread_t, UartRSTTL::run, (void*) this) ) != 0 )
	{
		
		
			Log(Wall::LOG_Z256,  " CAN'T FAIL THREAD CREATE \n");

	}

	(void)pthread_attr_destroy(&z256_thread_t);		
	
 }



