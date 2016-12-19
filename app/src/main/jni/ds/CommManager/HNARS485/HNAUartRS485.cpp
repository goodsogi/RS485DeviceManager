

/******************************************************
  NAME     : HNAUartRS485.cpp
  Coded by : �� ����
  Revision : 1.0
  Date     : 2014/02/04 ~

*/


#include "HNAUartRS485.h"

// �� ���� 
#include  "../../PacketRouter/PacketRouter.h"
class PacketRouter HNA_Router;


HNAUartRS485::HNAUartRS485() : b_open(false), b_portSet(false), run_flag(true), mediaInterfaceType(COMPANY_DUMMY), mediaInterfaceProtocol(PROTOCOL_DUMMY)
{

}

HNAUartRS485::~HNAUartRS485() 
{
	UartClose();
}

int HNAUartRS485::UartOpen(char* UartPort, unsigned int BAUDRATE, enum UARTINTERFACECOMPANY InterfaceCompany , enum UARTINTERFACEPROTOCOL InterfaceProtocol)
{
	char uartPortStr[40] = {0x00, };

    struct termios newtio;	

	if(  GetInterfaceCompany() != 0) return FAIL;

	if (b_open)  UartClose();	 

 	sprintf(uartPortStr, "/dev/%s", UartPort);
	i_SLfd = ::open(uartPortStr, O_RDWR | O_NOCTTY | O_NONBLOCK);
	Log(Wall::LOG_RS485, "### [ HNA ] RS-485 PORT OPEN [ %s ] :: SUCCESS", uartPortStr);	

		
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
			 Log(Wall::LOG_HNA, "### [ HNA ] RS-485 PORT BAUDRATE [ B4800 - B38400 ] :: NOT FOUNDED\n");	
			break;

	}

	if (i_SLfd < 0) {

		Log(Wall::LOG_HNA, "### [ HNA ] RS-485 PORT OPEN [ COMMPROT : %s ] :: ERROR\n", uartPortStr);	
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

   Log(Wall::LOG_HNA, " [ HNA ] SERIAL Successfully Serial Open:\n");	
   
   mediaInterfaceType = InterfaceCompany;

   mediaInterfaceProtocol = InterfaceProtocol;
   
   return SUCCESS;


}


 /** shows if the serial link is opened */
 bool HNAUartRS485::isOpen() const
 {
	return b_open;
 }

void HNAUartRS485::isSleep(unsigned long sec)
{
	sleep(sec);
	
}

/** closing the serial port */
int HNAUartRS485::UartClose()
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
void HNAUartRS485::SetInterfaceCompany(enum UARTINTERFACECOMPANY mediaType)
{

	mediaInterfaceType = mediaType;		

}

enum UARTINTERFACECOMPANY HNAUartRS485::GetInterfaceCompany()
{
	return mediaInterfaceType;
}

 /** identify that The company using of device interface protocol : �ڸƽ� RS485��������, �浿 RS485�������� */
void HNAUartRS485::SetProtocol(enum UARTINTERFACEPROTOCOL mediaProtocol)
{

	 mediaInterfaceProtocol = mediaProtocol;
}

enum UARTINTERFACEPROTOCOL HNAUartRS485::GetInterfaceProtocol()
{
	return mediaInterfaceProtocol;
}


#define WRITE 1
unsigned int  HNAUartRS485::SendFrame(unsigned char * frame, unsigned int frameLength)
{
	
	unsigned int sent = 0;
	int res = 0;
	int selectStatus = 0;
	unsigned int index = 0;

	if (!b_open) {

		Log(Wall::LOG_ERR, "### [ HNA ]  INTERFACE [ RS485 ] OPEN :: FAIL ");	
		return FAIL;
	}
	
	
	Log(Wall::LOG_HNA, "### [ HNA ] PACKET ROUTER -> INTERFACE MEDIA [RS 485] , FRAMESIZE : %d:: %02x`%02x`%02x`%02x`%02x`%02x`%02x", frameLength, frame[0],frame[1],frame[2],frame[3],frame[4],frame[5],frame[6],frame[7]);	
	
	
	while( sent < frameLength) {	
		
		FD_ZERO(&fdsw);
		FD_SET(i_SLfd,&fdsw);
		
		selectStatus = (unsigned)select(i_SLfd+1,NULL,&fdsw,NULL, NULL);

		if(selectStatus == -1) {

			Log(Wall::LOG_ERR, "### [ HNA ] SERIAL -> HNA::  UARTSERIAL.C : uart_data_send function -> Error Select");

			return FAIL;
		}
		
		if(FD_ISSET(i_SLfd,&fdsw)) {
			
			res = write(i_SLfd, &frame[index], WRITE);
			
			if (res == -1) {

				Log(Wall::LOG_ERR, "### [ HNA ] SERIAL -> HNA:: UARTSERIAL.C :: uart_data_send function : Error Writing to Serial Port");
				return FAIL;
			}   
			else if(res == 0 )

				Log(Wall::LOG_ERR, "### [ HNA ] SERIAL -> HNA:: UARTSERIAL.C :: uart_data_send function : write res value => 0");
				
			else {	
				
				sent += res;				
				index++;				
			}	
					
		}else{
			if( sent > 0 ) {		

				Log(Wall::LOG_HNA, " [ HNA ]### PACKET ROUTER -> INTERFACE MEDIA [RS 485]:: SENDING TIME OUT :%d \n", sent);
				return FAIL;
			}
		}

		
	} // end of while

	return SUCCESS;
}


// Thread of receive data
#define READ_BUFFER_SIZE 1
void * HNAUartRS485::run(void *arg)
{
	

	fd_set fdsr;	
	int recvSize = 0;	
    	int selectStatus = 0;	
	int receiveLength = 0;
	unsigned int rcvCnt = 0;
	unsigned char readBuffer = 0x00;
	unsigned char recvBuffer[HNA_BUFFER_SIZE] = {0x00,};

	Log(Wall::LOG_HNA, "### [ HNA ] RS485:: THREAD STARTING [ INTERFACE THREAD ]");

	
	HNAUartRS485 * rs485 = (HNAUartRS485*)arg;

	while(rs485->run_flag) { 

		FD_ZERO(&fdsr);
		FD_SET(rs485->i_SLfd,&fdsr);		

	    selectStatus = select(rs485->i_SLfd+1, &fdsr, NULL, NULL,NULL);
	  
		if(selectStatus == -1)
		{			
			Log(Wall::LOG_HNA, "### [ HNA ] RS485:: SMARTMETERINGUARTRS485.CPP :: ERROR SELECT : RETURN  SELECT : -1\n");
			//continue;
			rs485->UartClose();			
		}
		
		if(FD_ISSET(rs485->i_SLfd,&fdsr)) {
			
			
			switch(  rs485->GetInterfaceCompany() ) {

				// INTERFACE_HNA_RS485 INTERFACE
				case INTERFACE_HNA_RS485:
				{
					//
					recvSize = read(rs485->i_SLfd, &readBuffer, READ_BUFFER_SIZE);	

					if (recvSize == -1) {				
						Log(Wall::LOG_ERR, "### [ HNA ] RS485 <- SMARTMETERING PROTOCOL:: ERROR WRITTING TO SERIAL PORT : -1\n");
						
						rs485->UartClose();						

						break;

					} else if(recvSize == 0 ) {
						Log(Wall::LOG_ERR, "### [ HNA ] RS485 <- SMARTMETERING PROTOCOL:: READ VALUE FROM SERIAL : 0\n");

					} else {						
						 
						//Log(Wall::LOG_HNA, "### RS485 <- HNA PROTOCOL:: READ VALUE FROM SERIAL : %02x\n" , readBuffer);
						memcpy( (recvBuffer+rcvCnt), &readBuffer, recvSize);
						rcvCnt++;

						//Header
						if(recvBuffer[0] == 0xF7)
						{
							//����̽� ID
							if(rcvCnt >= 2)
							{
								switch(recvBuffer[1])
								{
									//����Ʈ���͸�
									case 0x30:
									{
			
										//COMMAND TYPE
										if(rcvCnt == 4)
										{
											if(recvBuffer[3] == 0x81)
											{
												if((recvBuffer[2] & 0x0F) == 0x0F)
													receiveLength = HNA_SMARTMETER_TOTAL_RECEIVE_BUFFER_SIZE;
												else
													receiveLength = HNA_SMARTMETER_EACH_RECEIVE_BUFFER_SIZE;
											}
											else if(recvBuffer[3] == 0x8F)
											{
												receiveLength = HNA_SMARTMETER_PROPERTY_RECEIVE_BUFFER_SIZE;
											}
											else
											{

												Log(Wall::LOG_ERR, " �� �� ���� �������� recvBuffer[2] -> %02x, %d", recvBuffer[2]);	
												rcvCnt = 0;
												readBuffer = 0x00;
												memset((void*)recvBuffer, 0x00, HNA_BUFFER_SIZE);	
											}
										}


										if(rcvCnt == receiveLength)
										{
											Log(Wall::LOG_HNA, " ���� �� ���� ��û�� ���� size -> Size : %d", rcvCnt);
											Log(Wall::LOG_HNA, " ���� �� ���� ��û�� ���� Data -> %02x,%02x,%02x,%02x,%02x,%02x,%02x,%02x,%02x,%02x, ", recvBuffer[0],recvBuffer[1],recvBuffer[2],recvBuffer[3],recvBuffer[4],recvBuffer[5],recvBuffer[6],recvBuffer[7], recvBuffer[8],recvBuffer[9]);
											Log(Wall::LOG_HNA, " ���� �� ���� ��û�� ���� Data -> %02x,%02x,%02x,%02x,%02x,%02x,%02x,%02x,%02x,%02x, ", recvBuffer[10],recvBuffer[11],recvBuffer[12],recvBuffer[13],recvBuffer[14],recvBuffer[15],recvBuffer[16],recvBuffer[17], recvBuffer[18],recvBuffer[19]);
											Log(Wall::LOG_HNA, " ���� �� ���� ��û�� ���� Data -> %02x,%02x,%02x,%02x,%02x,%02x,%02x,%02x,%02x,%02x, ", recvBuffer[20],recvBuffer[21],recvBuffer[22],recvBuffer[23],recvBuffer[24], recvBuffer[25],recvBuffer[26],recvBuffer[27],recvBuffer[28],recvBuffer[29]);
											Log(Wall::LOG_HNA, " ���� �� ���� ��û�� ���� Data -> %02x,%02x  ", recvBuffer[30],recvBuffer[31]);

											if(rcvCnt > 0)
												HNA_Router.FrameReceive(recvBuffer, receiveLength,  rs485->GetInterfaceCompany(), rs485->GetInterfaceProtocol() );

											memset((void*)recvBuffer, 0x00, HNA_BUFFER_SIZE);								
											readBuffer = 0x00;
											rcvCnt = 0;
										}
									}
									break;

									default:
										Log(Wall::LOG_ERR, " �� �� ���� �������� recvBuffer[1] -> %02x, %d", recvBuffer[1]);	
										rcvCnt = 0;
										readBuffer = 0x00;
										memset((void*)recvBuffer, 0x00, HNA_BUFFER_SIZE);	
									break;
								
								}

							}
						}
						else
						{
							Log(Wall::LOG_ERR, " �� �� ���� �������� Header Type -> %02x, %d", recvBuffer[0], recvBuffer[0]);	
							rcvCnt = 0;
							readBuffer = 0x00;
							memset((void*)recvBuffer, 0x00, HNA_BUFFER_SIZE);	
						}

					}
					
				} // end of case
				break;
				
				default:
					break;

		    } // end of switch statement
			
		}
				
	} // end of while
	
	Log(Wall::LOG_RS485, "### [ HNA ] RS485:: THREAD ENDING [ INTERFACE THREAD ]");

	pthread_exit(NULL);
	return NULL;
}

void HNAUartRS485::Start()
 {

	int ret;	

	if( (ret = pthread_attr_init( &rs485_thread_t) ) != 0 ) {

			Log(Wall::LOG_HNA, " [ HNA ] :: CAN'T  CREATE THREAD ATTRIBUTE\n");
	}
	
	if( (ret = pthread_attr_setdetachstate( &rs485_thread_t, PTHREAD_CREATE_DETACHED) ) != 0 ) {
			
			Log(Wall::LOG_HNA, " [ HNA ] :: CAN'T SET THREAD SET DETACH\n");
	}

	if( (ret = pthread_create( &rs485_thread, &rs485_thread_t, HNAUartRS485::run, (void*) this) ) != 0 )
	{
		
		
		Log(Wall::LOG_HNA, " [ HNA ] :: CAN'T FAIL THREAD CREATE\n");

	}


	Log(Wall::LOG_HNA, " [ HNA ] :: SUCCESSFULLY THREAD CREATE\n");

	(void)pthread_attr_destroy(&rs485_thread_t);		


 }
