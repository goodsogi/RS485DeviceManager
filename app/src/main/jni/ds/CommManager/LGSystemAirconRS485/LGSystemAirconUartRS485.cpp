
/******************************************************
  NAME     : UartRS485.cpp
  Coded by : �� ����
  Revision : 1.0
  Date     : 2007/02/07 ~

*/





#include "LGSystemAirconUartRS485.h"

// �� ���� 
#include  "../../PacketRouter/PacketRouter.h"
class PacketRouter LGSystemAircon_Router;


LGSystemAirconUartRS485::LGSystemAirconUartRS485() : b_open(false), b_portSet(false), run_flag(true), mediaInterfaceType(COMPANY_DUMMY), mediaInterfaceProtocol(PROTOCOL_DUMMY)
{

}

LGSystemAirconUartRS485::~LGSystemAirconUartRS485() 
{
	UartClose();
}

int LGSystemAirconUartRS485::UartOpen(char* UartPort, unsigned int BAUDRATE, enum UARTINTERFACECOMPANY InterfaceCompany , enum UARTINTERFACEPROTOCOL InterfaceProtocol)
{
	char uartPortStr[40] = {0x00, };
	
	struct termios newtio;	

	if(  GetInterfaceCompany() != 0) return FAIL;

	if (b_open)  UartClose();	 
	 
	sprintf(uartPortStr, "/dev/%s", UartPort);
	i_SLfd = ::open(uartPortStr, O_RDWR | O_NOCTTY);
	Log(Wall::LOG_RS485, "### [ LGSYSTEMAIRCON ] RS-485 PORT OPEN [ %s ] :: SUCCESS", uartPortStr);	

		
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

		case 5:  // B19200
			BAUDRATE = B19200;
			break;
		
		case 6:  // B38400
			BAUDRATE = B38400;
			break;

		case 7:  // B57600
			BAUDRATE = B57600;
			break;

		case 8:  // B115200
			BAUDRATE = B115200;
			break;

		default:
			 Log(Wall::LOG_RS485, "### [ LGSYSTEMAIRCON ] RS-485 PORT BAUDRATE [ B4800 - B38400 ] :: NOT FOUNDED\n");	
			break;

	}

	if (i_SLfd < 0) {

		Log(Wall::LOG_RS485, "### [ LGSYSTEMAIRCON ] RS-485 PORT OPEN [ COMMPROT : %d ] :: ERROR\n", uartPortStr);	
		return FAIL;
	}
	else  b_open = true;
	

	if (!b_portSet) {
	    //tcgetattr(i_SLfd,&oldtio);
		b_portSet = true;
	}

    bzero(&newtio, sizeof(newtio)); 

   newtio.c_cflag =  BAUDRATE | CS8 | CLOCAL | CREAD;

   newtio.c_iflag = 0;
  
   newtio.c_oflag = 0;

 
   newtio.c_lflag = 0;

   newtio.c_cc[VTIME] = 0;   //���� ������ timer�� disable

   newtio.c_cc[VMIN]  = 0;   //�ּ� 1 ���� ���� ������ blocking
	
   //tcflush(i_SLfd, TCIFLUSH);
   //tcsetattr(i_SLfd,TCSANOW,&newtio);

   Log(Wall::LOG_RS485, " [ LGSYSTEMAIRCON ] SERIAL Successfully Serial Open:\n");	
   
   mediaInterfaceType = InterfaceCompany;

   mediaInterfaceProtocol = InterfaceProtocol;
   
   return SUCCESS;

}


 /** shows if the serial link is opened */
 bool LGSystemAirconUartRS485::isOpen() const
 {
	return b_open;
 }

void LGSystemAirconUartRS485::isSleep(unsigned long sec)
{
	sleep(sec);
	
}

/** closing the serial port */
int LGSystemAirconUartRS485::UartClose()
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
void LGSystemAirconUartRS485::SetInterfaceCompany(enum UARTINTERFACECOMPANY mediaType)
{

	mediaInterfaceType = mediaType;		

}

enum UARTINTERFACECOMPANY LGSystemAirconUartRS485 ::GetInterfaceCompany()
{
	return mediaInterfaceType;
}

 /** identify that The company using of device interface protocol : �ڸƽ� RS485��������, �浿 RS485�������� */
void LGSystemAirconUartRS485::SetProtocol(enum UARTINTERFACEPROTOCOL mediaProtocol)
{

	 mediaInterfaceProtocol = mediaProtocol;
}

enum UARTINTERFACEPROTOCOL LGSystemAirconUartRS485::GetInterfaceProtocol()
{
	return mediaInterfaceProtocol;
}

#define WRITE 1
unsigned int  LGSystemAirconUartRS485 ::SendFrame(unsigned char * frame, unsigned int frameLength)
{
	
	if (!b_open) {

		Log(Wall::LOG_LG485, "### LG SYSTEMUART RS485 INTERFACE [ RS485 ] OPEN :: FAIL ");	
		return FAIL;
	}
	
	unsigned int sent = 0;
	int res = 0;
	int selectStatus = 0;	

	unsigned int indexR = 0;
	unsigned int index = 0;

	Log(Wall::LOG_LG485, " ### LG SYSTEM AIRCON SENDING DATA\n");

/*
	for( indexR = 0; indexR < frameLength; indexR++)
	{
		printf(" %02x`", frame[indexR]);
	}
	printf("\n");
*/

	Log(Wall::LOG_LG485, "### PACKET ROUTER -> INTERFACE MEDIA [LG SYSTEM AIRCON] , FRAMESIZE : %d:: %02x`%02x`%02x`%02x`%02x`%02x`%02x`%02x", frameLength, frame[0],frame[1],frame[2],frame[3],frame[4],frame[5],frame[6],frame[7]);	
	
	while(sent < frameLength) {	
		FD_ZERO(&fdsw);
		FD_SET(i_SLfd,&fdsw);
		
		selectStatus = (unsigned)select(i_SLfd+1,NULL,&fdsw,NULL, NULL);

		if(selectStatus == -1) {

			//Log(Wall::LOG_Cmx485, "### SERIAL -> CMX485::  UARTSERIAL.C : uart_data_send function -> Error Select");

			return FAIL;
		}
		
		if(FD_ISSET(i_SLfd,&fdsw)) {
			
			//res = write(i_SLfd, &frame[index], WRITE);

			res = write(i_SLfd, frame, frameLength);
			Log(Wall::LOG_LG485, "### SERIAL -> LG SYSTEM SYSTEM AIRCON RS485:: UARTSERIAL.C : uart_data_send function : return size -> write function : %d", res);

			if (res == -1) {
				//Log(Wall::LOG_Cmx485, "### SERIAL -> CMX485:: UARTSERIAL.C :: uart_data_send function : Error Writing to Serial Port");
				return FAIL;
			}   
			else if(res == 0 )

				Log(Wall::LOG_LG485, "### SERIAL -> LG SYSTEM SYSTEM AIRCON RS485:: UARTSERIAL.C :: uart_data_send function : write res value => 0");
				
			else {				
				
				sent += res;				
				index++;							
				
			}	
					
		}else{
			if( sent > 0 ) {		

				Log(Wall::LOG_LG485, "### PACKET ROUTER -> INTERFACE MEDIA [LG SYSTEM AIRCON RS485]:: SENDING TIME OUT :%d \n", sent);
				return FAIL;
			}
		}

		
	} // end of while
	
	return SUCCESS;
}

#define READ_BUFFER_SIZE 1
// Thread of receive data
void * LGSystemAirconUartRS485::run(void *arg)
{
	

	fd_set fdsr;	
	int recvSize = 0;	
    int selectStatus = 0;	

	unsigned int rcvCnt = 0;

	unsigned char readBuffer = 0x00;
	unsigned char recvBuffer[LG_RECEIVE_BUFFER_SIZE] = {0x00,};	
	
	Log(Wall::LOG_LG485, "### LG SYSTEM AIRCON RS485 RS485:: THREAD STARTING [ INTERFACE THREAD ]");	
	
	LGSystemAirconUartRS485  * rs485 = (LGSystemAirconUartRS485*)arg;

	if (!rs485->b_open) {

		Log(Wall::LOG_LG485, "###  [LG SYSTEM THREAD RUNNING ] UARTRS485 INTERFACE [ LG SYSTEM AIRCON RS485 ] OPEN :: FAIL ");	
		return FAIL;
	}

	while(rs485->run_flag) { 

		FD_ZERO(&fdsr);
		FD_SET(rs485->i_SLfd,&fdsr);			
	    selectStatus = select(rs485->i_SLfd+1, &fdsr, NULL, NULL,NULL);
	  
		if(selectStatus == -1)
		{			
			Log(Wall::LOG_LG485, "### LG SYSTEM AIRCON RS485:: LG SYSTEM UARTRS485.CPP :: ERROR SELECT : RETURN  SELECT : -1\n");
			//continue;
			rs485->UartClose();			
		}
		
		if(FD_ISSET(rs485->i_SLfd,&fdsr)) {
			
			
			switch(  rs485->GetInterfaceCompany() ) {

				 
				case INTERFACE_LG_RS485:
				{
					
					recvSize = read(rs485->i_SLfd, &readBuffer, READ_BUFFER_SIZE );	

					if (recvSize == -1) {				
						Log(Wall::LOG_LG485, "### LG SYSTEM AIRCON RS485 <- LG SYSTEM_BUFFER_SIZE PROTOCOL:: ERROR WRITTING TO SERIAL PORT : -1\n");
						
						rs485->UartClose();						

						break;

					} else if(recvSize == 0 ) {

						Log(Wall::LOG_LG485, "### LG SYSTEM AIRCON RS485 <- LG SYSTEM_BUFFER_SIZE PROTOCOL:: READ VALUE FROM SERIAL : 0\n");

					} else {					

							Log(Wall::LOG_LG485, "### LG SYSTEM AIRCON RS485 <- LG SYSTEM_AIRCON PROTOCOL:: READ VALUE FROM SERIAL [%02x]: \n", readBuffer);
							
							 memcpy( (recvBuffer+rcvCnt), &readBuffer, recvSize);	

							 if( readBuffer == 0x10 ) {
								
								 rcvCnt += recvSize;	
								 
								 if( LG_RECEIVE_BUFFER_SIZE == rcvCnt ) {

									//Log(Wall::LOG_ERR, "### packet completely ... end data [ 0x10 ],  group and id : %02x \n", recvBuffer[4] );
									LGSystemAircon_Router.FrameReceive(recvBuffer, LG_RECEIVE_BUFFER_SIZE,  rs485->GetInterfaceCompany(), rs485->GetInterfaceProtocol() );
									memset((void*)recvBuffer, 0x00, LG_RECEIVE_BUFFER_SIZE );
								
									readBuffer = 0x00;
									rcvCnt = 0;

								//�۽� ������ �� ���� �������� ù��° �����Ͱ� 0x10�� �ƴ� ��츦 ó���ϱ� ����.
								}else if( (recvBuffer[0] == 0x10 && rcvCnt == 3) && recvBuffer[2] != 0xA0 )  {
										
									Log(Wall::LOG_ERR, "###  the received data is reset ... first data [ 0x10 ]\n");
									memset((void*)recvBuffer, 0x00, LG_RECEIVE_BUFFER_SIZE );
								
									readBuffer = 0x00;
									rcvCnt = 0;
								}
							 	
							 } else if( recvBuffer[0] == 0x10 && rcvCnt >= 1 ) {

								rcvCnt += recvSize;

								if( LG_RECEIVE_BUFFER_SIZE == rcvCnt ) {

									//Log(Wall::LOG_ERR, "### packet completely ...  group and id : %02x\n", recvBuffer[4]);
									LGSystemAircon_Router.FrameReceive(recvBuffer, LG_RECEIVE_BUFFER_SIZE,  rs485->GetInterfaceCompany(), rs485->GetInterfaceProtocol() );
									memset((void*)recvBuffer, 0x00, LG_RECEIVE_BUFFER_SIZE );
								
									readBuffer = 0x00;
									rcvCnt = 0;

								//�۽� ������ �� ���� �������� ù��° �����Ͱ� 0x16�� �ƴ� ��츦 ó���ϱ� ����.
								}else if( (recvBuffer[0] == 0x10 && rcvCnt == 3) && recvBuffer[2] != 0xA0 )  {
										
									//Log(Wall::LOG_ERR, "###  the received data is reset ... \n");
									memset((void*)recvBuffer, 0x00, LG_RECEIVE_BUFFER_SIZE );
								
									readBuffer = 0x00;
									rcvCnt = 0;
								}

							 }else {
									
									//Log(Wall::LOG_ERR, "###  the received data is reset ... not mismatch of stx [ 0x10 ] \n");
									memset((void*)recvBuffer, 0x00, LG_RECEIVE_BUFFER_SIZE );
								
									readBuffer = 0x00;
									rcvCnt = 0;
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
	Log(Wall::LOG_LG485, "### LG SYSTEM AIRCON RS485:: THREAD ENDING [ INTERFACE THREAD ]");

	pthread_exit(NULL);
	return NULL;
}

void LGSystemAirconUartRS485::Start()
 {

	int ret;	

	if( (ret = pthread_attr_init( &LGSystemAirconRs485_thread_t) ) != 0 ) {

			Log(Wall::LOG_LG485, " CAN'T  CREATE THREAD ATTRIBUTE :: LG SYSTEM AIRCON RS485\n");
	}
	
	if( (ret = pthread_attr_setdetachstate( &LGSystemAirconRs485_thread_t, PTHREAD_CREATE_DETACHED) ) != 0 ) {
			
			Log(Wall::LOG_LG485, " CAN'T SET THREAD SET DETACH :: LG SYSTEM AIRCON RS485\n");
	}

	if( (ret = pthread_create( &LGSystemAirconRs485_thread, &LGSystemAirconRs485_thread_t, LGSystemAirconUartRS485::run, (void*) this) ) != 0 )
	{
		
		
		Log(Wall::LOG_LG485, " CAN'T FAIL THREAD CREATE[LG SYSTEM AIRCON RS485 PORT]\n");

	}


	Log(Wall::LOG_LG485, " SUCCESSFULLY THREAD CREATE [LG SYSTEM AIRCON RS485 PORT]\n");

	(void)pthread_attr_destroy(&LGSystemAirconRs485_thread_t);	

 }
