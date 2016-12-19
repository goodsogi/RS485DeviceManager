
/******************************************************
  NAME     : LedPanelUartRS485.cpp
  Coded by : �� ����
  Revision : 1.0
  Date     : 2007/02/07 ~

*/


#include "LedPanelUartRS485.h"

// �� ���� 
#include  "../../PacketRouter/PacketRouter.h"
class PacketRouter LedPanel_Router;



LedPanelUartRS485::LedPanelUartRS485() : b_open(false), b_portSet(false), run_flag(true), mediaInterfaceType(COMPANY_DUMMY), mediaInterfaceProtocol(PROTOCOL_DUMMY)
{

}

LedPanelUartRS485::~LedPanelUartRS485() 
{
	UartClose();
}

int LedPanelUartRS485::UartOpen(char* UartPort, unsigned int BAUDRATE, enum UARTINTERFACECOMPANY InterfaceCompany , enum UARTINTERFACEPROTOCOL InterfaceProtocol)
{
	char uartPortStr[40] = {0x00, };
	struct termios newtio;		

	// RS485 Port�� �ߺ� Open�� �����ϱ� ����
	if(  GetInterfaceCompany() != 0) return FAIL;

	if (b_open)  UartClose();	 


	sprintf(uartPortStr, "/dev/%s", UartPort);
	i_SLfd = ::open(uartPortStr, O_RDWR | O_NOCTTY);
	Log(Wall::LOG_LED, "### LED PANEL RS-485 PORT OPEN  [ %s ] :: SUCCESS", uartPortStr);

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
			 Log(Wall::LOG_LED, "### [LED PANEL ]RS-485 PORT BAUDRATE [ B4800 - B38400 ] :: NOT FOUNDED");	
			break;

	}
	
	if (i_SLfd < 0) {

		Log(Wall::LOG_LED, "### [LED PANEL ]RS-485 PORT OPEN [ COMMPROT : %s ] :: ERROR", uartPortStr);	
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

   Log(Wall::LOG_LED, "LED PANEL RS485 SERIAL Successfully Serial Open:");	
   
   
    mediaInterfaceType = InterfaceCompany;

	mediaInterfaceProtocol = InterfaceProtocol;

   return SUCCESS;

}


 /** shows if the serial link is opened */
 bool LedPanelUartRS485::isOpen() const
 {
	return b_open;
 }

void LedPanelUartRS485::isSleep(unsigned long sec)
{
	sleep(sec);
	
}

/** closing the serial port */
int LedPanelUartRS485::UartClose()
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
void LedPanelUartRS485::SetInterfaceCompany(enum UARTINTERFACECOMPANY mediaType)
{

	mediaInterfaceType = mediaType;		

}

enum UARTINTERFACECOMPANY LedPanelUartRS485::GetInterfaceCompany()
{
	return mediaInterfaceType;
}

 /** identify that The company using of device interface protocol : �ڸƽ� RS485��������, �浿 RS485�������� */
void LedPanelUartRS485::SetProtocol(enum UARTINTERFACEPROTOCOL mediaProtocol)
{

	 mediaInterfaceProtocol = mediaProtocol;
}

enum UARTINTERFACEPROTOCOL LedPanelUartRS485::GetInterfaceProtocol()
{
	return mediaInterfaceProtocol;
}


unsigned int LedPanelUartRS485::SendFrame(unsigned char * frame, unsigned int frameLength)
{
	
	if (!b_open) {

		Log(Wall::LOG_LED, "### LedPanelUartRS485 INTERFACE [ LED PANEL RS485 ] OPEN :: FAIL ");	
		return FAIL;
	}
	
	unsigned int sent = 0;
	int res = 0;
	int selectStatus = 0;		
	unsigned int index = 0;
	
	unsigned int idx = 0;
	
	Log(Wall::LOG_LED, "### PACKET ROUTER -> INTERFACE MEDIA [LED PANEL RS485] , FRAMESIZE : %d:: %02x`%02x`%02x`%02x`%02x`%02x`%02x`%02x`%02x`%02x'%02x", frameLength, frame[0],frame[1],frame[2],frame[3],frame[4],frame[5],frame[6],frame[7],frame[8],frame[9],frame[10]);		

	while(sent < frameLength) {	
		
		FD_ZERO(&fdsw);
		FD_SET(i_SLfd,&fdsw);

		selectStatus = (unsigned)select(i_SLfd+1,NULL,&fdsw,NULL, NULL);

		if(selectStatus == -1) {

			Log(Wall::LOG_LED, "### SERIAL -> CMX485::  UARTSERIAL.C : uart_data_send function -> Error Select");

			return FAIL;
		}
		
		if(FD_ISSET(i_SLfd,&fdsw)) {
			
			res = write(i_SLfd, &frame[index], 1 );								
			//res = write(i_SLfd, frame,  frameLength);								
			
		   // Log(Wall::LOG_LED, "### SERIAL -> CMX485:: UARTSERIAL.C : uart_data_send function : return size -> write function : %d", res);

			if (res == -1) {
				Log(Wall::LOG_LED, "### SERIAL -> CMX485:: UARTSERIAL.C :: uart_data_send function : Error Writing to Serial Port");
				return FAIL;
			}   
			else if(res == 0 )

				Log(Wall::LOG_LED, "### SERIAL -> LedPanel RS485:: UARTSERIAL.C :: uart_data_send function : write res value => 0");
				
			else {						
				
				sent += res;				
				index += 1;							
				//usleep(1000);
			}	
					
		}else{
			if( sent > 0 ) {		

				Log(Wall::LOG_LED, "### PACKET ROUTER -> INTERFACE MEDIA [ LED PANEL RS485 ]:: SENDING TIME OUT :%d \n", sent);
				return FAIL;
			}
		}

		
	} // end of while

	return SUCCESS;
}


#define READ_BUFFER_SIZE 1
// Thread of receive data
void * LedPanelUartRS485::run(void *arg)
{
	

	fd_set fdsr;	
	int recvSize = 0;	
    int selectStatus = 0;	

	unsigned int rcvCnt = 0;
	unsigned char readBuffer = 0x00;
	unsigned char recvBuffer[LEDPANEL_SCREEN_ON_OFF_BUFFER_SIZE+1] = {0x00,};

	Log(Wall::LOG_LED, "### RS485:: THREAD STARTING [ INTERFACE THREAD ]");
	

	LedPanelUartRS485 * rs485 = (LedPanelUartRS485*)arg;

	if (!rs485->b_open) {

		Log(Wall::LOG_LED, "###  [LED PANEL THREAD RUNNING ] LedPanelUartRS485 INTERFACE [LED PANEL  RS485 ] OPEN :: FAIL ");	
		return FAIL;
	}

	while(rs485->run_flag) { 

		FD_ZERO(&fdsr);
		FD_SET(rs485->i_SLfd,&fdsr);			
	    selectStatus = select(rs485->i_SLfd+1, &fdsr, NULL, NULL,NULL);
	  
		if(selectStatus == -1)
		{			
			Log(Wall::LOG_LED, "### LED PANEL RS485:: LedPanelUartRS485.CPP :: ERROR SELECT : RETURN  SELECT : -1\n");
			//continue;
			rs485->UartClose();			
		}
		
		if(FD_ISSET(rs485->i_SLfd,&fdsr)) {
			
			
			switch(  rs485->GetInterfaceCompany() ) {

				// LED PANEL INTERFACE
				case INTERFACE_LEDPANEL_RS485:
				{
					//
					recvSize = read(rs485->i_SLfd, &readBuffer, READ_BUFFER_SIZE);	
					
					if (recvSize == -1) {				
						Log(Wall::LOG_LED, "### LED PANEL RS485 <- LED PANEL PROTOCOL:: ERROR WRITTING TO SERIAL PORT : -1\n");
						//return;
						rs485->UartClose();						

						break;

					} else if(recvSize == 0 ) {

						Log(Wall::LOG_LED, "### LED PANEL RS485 <- LED PANEL PROTOCOL:: READ VALUE FROM SERIAL : 0\n");

					} else {						
						 
							Log(Wall::LOG_LED, "### LED PANEL RS485 <- LED PANEL PROTOCOL:: READ VALUE FROM SERIAL [%02x]: \n", readBuffer);							

						    memcpy( (recvBuffer+rcvCnt), &readBuffer, recvSize);

							
							if( recvBuffer[0] != 0x01 ) {

								memset((void*)recvBuffer, 0x00, LEDPANEL_SCREEN_ON_OFF_BUFFER_SIZE+1 );				
								rcvCnt = 0;
								continue;
							}							

							rcvCnt += recvSize;							

							if( rcvCnt == 2 ) {

								if( (recvBuffer[1] == 0x01) ||  (recvBuffer[1] == 0x10) ) {

										continue;
									
								}else {

									memset((void*)recvBuffer, 0x00, LEDPANEL_SCREEN_ON_OFF_BUFFER_SIZE+1 );				
									rcvCnt = 0;
									continue;
								}
							}

							if( rcvCnt == 3 ) {

								if( recvBuffer[2] == 0x02 )  {

									continue;

								}else {

									memset((void*)recvBuffer, 0x00, LEDPANEL_SCREEN_ON_OFF_BUFFER_SIZE+1 );				
									rcvCnt = 0;
									continue;
								}
							}

						    
							//01`01`02`00`09`10`80`00`00`9b'03 (Status Dump)
							//(Status Dump Echo ( 11Byte) + Real Data Recv ( 10 byte) ) : [01],[01],[02],[00],[09],[10],[80],[00],[00],[9b],[03],[01],[01],[02],[00],[08],[10],[73],[00],[69],[03] 
							// 
							if( (rcvCnt == LEDPANEL_RECV_BUFFER_SIZE) || ( rcvCnt == LEDPANEL_ECHO_BUFFER_SIZE ) )  {
									
								if( (recvBuffer[4] == 0x09) && (recvBuffer[6] == 0x80) ) {

										if( recvBuffer[10] == 0x03 ) { // ���� �����Ͱ� 10, 11 Byte�̹Ƿ�, �̰��� ó������ ������ ���� 11����Ʈ�� �޾ƾ� �ϳ�, 10�� ����Ʈ �ް� Echo Data�� �����. �̰��� ���� �ϱ� ����

											Log(Wall::LOG_LED, " ���� �� ���� ��û�� ���� ECHO DATA : %d\n", rcvCnt);							
											memset((void*)recvBuffer, 0x00, (LEDPANEL_SCREEN_ON_OFF_BUFFER_SIZE +1));				
											rcvCnt = 0;										
																			
										}
								}else if( (recvBuffer[4] == 0x08) && (recvBuffer[6] != 0x80) ) {

									if( (recvBuffer[0] == 0x01) && (recvBuffer[2] == 0x02) ) {

										Log(Wall::LOG_LED, "  ���� ��û ���� [0x13, 0x14, 0x16, 0x1A, 0x40]  REAL DATA[������, �����] : %d\n", rcvCnt);							
										LedPanel_Router.FrameReceive(recvBuffer, LEDPANEL_RECV_BUFFER_SIZE,  rs485->GetInterfaceCompany(), rs485->GetInterfaceProtocol() );
										memset((void*)recvBuffer, 0x00, (LEDPANEL_SCREEN_ON_OFF_BUFFER_SIZE +1) );				
										rcvCnt = 0;
									

									} else {

										Log(Wall::LOG_LED, " REAL DATA -> TYPE MISMATCH ");		
										memset((void*)recvBuffer, 0x00, (LEDPANEL_SCREEN_ON_OFF_BUFFER_SIZE +1));				
										rcvCnt = 0;
									}
									
								}
							//CDS ���� �� �б� & ���� �� �б� (0x1D)
							}else if( rcvCnt == (LEDPANEL_BUFFER_SIZE + 1) ) {												

									if( (recvBuffer[4] == 0x0a)  && (recvBuffer[6] != 0x80) ) {

										if( (recvBuffer[0] == 0x01) && (recvBuffer[2] == 0x02)   ) {

											Log(Wall::LOG_LED, " CDS ���� �� �б⿡ ���� REAL DATA ");							
											LedPanel_Router.FrameReceive(recvBuffer,  ( LEDPANEL_BUFFER_SIZE +1 ),  rs485->GetInterfaceCompany(), rs485->GetInterfaceProtocol() );
											memset((void*)recvBuffer, 0x00,(LEDPANEL_SCREEN_ON_OFF_BUFFER_SIZE +1) );				
											rcvCnt = 0;
										

										} else {

											Log(Wall::LOG_ERR, " REAL DATA -> TYPE MISMATCH ");		
											memset((void*)recvBuffer, 0x00,(LEDPANEL_SCREEN_ON_OFF_BUFFER_SIZE +1) );				
											rcvCnt = 0;
										}				
									}
							//���� ǥ����� ���� ���� [ ECHO ] -> 16����Ʈ �� : (LEDPANEL_SCREEN_ON_OFF_BUFFER_SIZE +1) -> 16����Ʈ �̻��̸� ���� Ŭ����
							}else if( rcvCnt == (LEDPANEL_SCREEN_ON_OFF_BUFFER_SIZE+1) ) {

									
									if( (recvBuffer[4] == 0x0e) && (recvBuffer[6] == 0x80) ) {

										if( recvBuffer[15] == 0x03) { 

											Log(Wall::LOG_LED, " ���� ǥ������ ��û�� ����  ECHO DATA : %d\n", rcvCnt);										
											memset((void*)recvBuffer, 0x00, (LEDPANEL_SCREEN_ON_OFF_BUFFER_SIZE +1) );				
											rcvCnt = 0;										
										
										} else {

											Log(Wall::LOG_ERR, " ���� ǥ������ ��û�� ���� REAL DATA -> TYPE MISMATCH ");		
											memset((void*)recvBuffer, 0x00, (LEDPANEL_SCREEN_ON_OFF_BUFFER_SIZE+1) );				
											rcvCnt = 0;
										}			
									}

							}else if( rcvCnt > (LEDPANEL_SCREEN_ON_OFF_BUFFER_SIZE +1) ) {
							
								Log(Wall::LOG_ERR, "#### SERIAL <- LED PANEL :: RECV DATA OVERFLOW : %d", rcvCnt );				
								rcvCnt = 0;
								memset((void*)recvBuffer, 0x00,  (LEDPANEL_SCREEN_ON_OFF_BUFFER_SIZE+1) );
						    }
						 
				   }
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
	Log(Wall::LOG_LED, "### LED PANEL RS485:: THREAD ENDING [ INTERFACE THREAD ]");

	pthread_exit(NULL);
	return NULL;
}

void LedPanelUartRS485::Start()
{

	int ret;	

	if( (ret = pthread_attr_init( &rs485_thread_t) ) != 0 ) {

			Log(Wall::LOG_LED, " CAN'T  CREATE THREAD ATTRIBUTE : LED PANEL\n");
	}
	
	if( (ret = pthread_attr_setdetachstate( &rs485_thread_t, PTHREAD_CREATE_DETACHED) ) != 0 ) {
			
			Log(Wall::LOG_LED, " CAN'T SET THREAD SET DETACH : LED PANEL\n");
	}

	if( (ret = pthread_create( &rs485_thread, &rs485_thread_t, LedPanelUartRS485::run, (void*) this) ) != 0 )
	{
		
		
		Log(Wall::LOG_LED, " CAN'T FAIL THREAD CREATE : LED PANEL\n");

	}


	Log(Wall::LOG_LED, " LED PANEL RS485 SUCCESSFULLY THREAD CREATED : LED PANEL \n");

	(void)pthread_attr_destroy(&rs485_thread_t);		


 }