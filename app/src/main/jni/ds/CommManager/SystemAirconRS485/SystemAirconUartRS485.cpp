
/******************************************************
  NAME     : UartRS485.cpp
  Coded by : �� ����
  Revision : 1.0
  Date     : 2007/02/07 ~

*/



#include "SystemAirconUartRS485.h"

// �� ���� 
#include  "../../PacketRouter/PacketRouter.h"
class PacketRouter SystemAircon_Router;


SystemAirconUartRS485::SystemAirconUartRS485() : b_open(false), b_portSet(false), run_flag(true), mediaInterfaceType(COMPANY_DUMMY), mediaInterfaceProtocol(PROTOCOL_DUMMY)
{

}

SystemAirconUartRS485::~SystemAirconUartRS485() 
{
	UartClose();
}

int SystemAirconUartRS485::UartOpen(char* UartPort, unsigned int BAUDRATE, enum UARTINTERFACECOMPANY InterfaceCompany , enum UARTINTERFACEPROTOCOL InterfaceProtocol)
{
	char uartPortStr[40] = {0x00, };
    struct termios newtio;		
	
	// RS485 Port�� �ߺ� Open�� �����ϱ� ����
	if(  GetInterfaceCompany() != 0) return FAIL;

	if (b_open)  UartClose();	 

	sprintf(uartPortStr, "/dev/%s", UartPort);
	i_SLfd = ::open(uartPortStr, O_RDWR | O_NOCTTY);
	Log(Wall::LOG_RS485, "### [ SAMSUNG SYSTEM AIRDCON ] RS-485 PORT OPEN [ %s ] :: SUCCESS", uartPortStr);	
		
	
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
			 Log(Wall::LOG_HAMUN, "### [ SAMSUNG SYSTEM AIRDCON ]RS-485 PORT BAUDRATE [ B4800 - B38400 ] :: NOT FOUNDED");	
			break;

	}
	
	if (i_SLfd < 0) {

		Log(Wall::LOG_HAMUN, "### SAMSUNG SYSTEM RS-485 PORT OPEN [ COMMPROT : %s ] :: ERROR", uartPortStr);	
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
    CREAD   : enable receiving characters BAUDRATE | CS8 | CLOCAL | CREAD;
  */
   newtio.c_cflag =  BAUDRATE | CS8 | CLOCAL | CREAD | CSTOPB;	//stop bit 2

  //newtio.c_cflag |= PARENB;
  //newtio.c_cflag &= ~PARODD;  
  //newtio.c_cflag &= ~CSTOPB;   
  
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
	

   Log(Wall::LOG_HAMUN, "SAMSUNG SYSTEM CMX485 SERIAL Successfully Serial Open:");

   
   mediaInterfaceType = InterfaceCompany;

   mediaInterfaceProtocol = InterfaceProtocol;

   return SUCCESS;

}


 /** shows if the serial link is opened */
 bool SystemAirconUartRS485::isOpen() const
 {
	return b_open;
 }

void SystemAirconUartRS485::isSleep(unsigned long sec)
{
	sleep(sec);
	
}

/** closing the serial port */
int SystemAirconUartRS485::UartClose()
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
void SystemAirconUartRS485::SetInterfaceCompany(enum UARTINTERFACECOMPANY mediaType)
{

	mediaInterfaceType = mediaType;		

}

enum UARTINTERFACECOMPANY SystemAirconUartRS485::GetInterfaceCompany()
{
	return mediaInterfaceType;
}

 /** identify that The company using of device interface protocol : �ڸƽ� RS485��������, �浿 RS485�������� */
void SystemAirconUartRS485::SetProtocol(enum UARTINTERFACEPROTOCOL mediaProtocol)
{

	 mediaInterfaceProtocol = mediaProtocol;
}

enum UARTINTERFACEPROTOCOL SystemAirconUartRS485::GetInterfaceProtocol()
{
	return mediaInterfaceProtocol;
}

#define WRITE 1
unsigned int  SystemAirconUartRS485::SendFrame(unsigned char * frame, unsigned int frameLength)
{
	
	if (!b_open) {

		Log(Wall::LOG_HAMUN, "### SAMSUNG SYSTEMUART RS485 INTERFACE [ RS485 ] OPEN :: FAIL ");	
		return FAIL;
	}
	
	unsigned int sent = 0;
	int res = 0;
	int selectStatus = 0;	

	unsigned int indexR = 0;
	unsigned int index = 0;

	Log(Wall::LOG_HAMUN, " ### SYSTEM AIRCON SENDING DATA\n");
	/*
	for( indexR = 0; indexR < frameLength; indexR++)
		Log(Wall::LOG_HAMUN, "%02x`", frame[indexR]);

	printf("\n");
	Log(Wall::LOG_HAMUN, "### PACKET ROUTER -> INTERFACE MEDIA [SAMSUNG SYSTEM AIRCON] , FRAMESIZE : %d:: %02x`%02x`%02x`%02x`%02x`%02x`%02x`%02x", frameLength, frame[0],frame[1],frame[2],frame[3],frame[4],frame[5],frame[6],frame[7]);	
	*/
	
	while(sent < frameLength) {	
		
		FD_ZERO(&fdsw);
		FD_SET(i_SLfd,&fdsw);
		
		selectStatus = (unsigned)select(i_SLfd+1,NULL,&fdsw,NULL, NULL);

		if(selectStatus == -1) {

			//Log(Wall::LOG_Cmx485, "### SERIAL -> CMX485::  UARTSERIAL.C : uart_data_send function -> Error Select");

			return FAIL;
		}

		if(FD_ISSET(i_SLfd,&fdsw)) {
			
			res = write(i_SLfd, &frame[index], frameLength);

			Log(Wall::LOG_HAMUN, "### SERIAL -> SAMSUNG SYSTEM SYSTEM AIRCON RS485:: UARTSERIAL.C : uart_data_send function : return size -> write function : %d", res);

			if (res == -1) {
				//Log(Wall::LOG_Cmx485, "### SERIAL -> CMX485:: UARTSERIAL.C :: uart_data_send function : Error Writing to Serial Port");
				return FAIL;
			}   
			else if(res == 0 )

				Log(Wall::LOG_HAMUN, "### SERIAL -> SAMSUNG SYSTEM SYSTEM AIRCON RS485:: UARTSERIAL.C :: uart_data_send function : write res value => 0");
				
			else {				
				
				sent += res;				
				index++;							
				
			}	
					
		}else{
			if( sent > 0 ) {		

				Log(Wall::LOG_HAMUN, "### PACKET ROUTER -> INTERFACE MEDIA [SAMSUNG SYSTEM AIRCON RS485]:: SENDING TIME OUT :%d \n", sent);
				return FAIL;
			}

		}
		
	} // end of while

	return SUCCESS;
}


#define READ_BUFFER_SIZE 1
void * SystemAirconUartRS485::run(void *arg)
{
	fd_set fdsr;	
	int recvSize = 0;
	int lastCalcStatusRecvLength = 0;
	int firstCalcStatusRecvLength = 0;
    	int selectStatus = 0;	
	int packetLength = 0;

	unsigned int rcvCnt = 0;
	unsigned char readBuffer = 0x00;
	unsigned char recvBuffer[SAMSUNG_SYSTEMAIRCON_STATUS_RECEIVE_BUFFER_SIZE ] = {0x00,};

	Log(Wall::LOG_HAMUN, "### SAMSUNG SYSTEMAIRCON RS485:: THREAD STARTING [ INTERFACE THREAD ]");

	
	SystemAirconUartRS485 * rs485 = (SystemAirconUartRS485*)arg;

	while(rs485->run_flag) { 

		FD_ZERO(&fdsr);
		FD_SET(rs485->i_SLfd,&fdsr);		
		
	    selectStatus = select(rs485->i_SLfd+1, &fdsr, NULL, NULL,NULL);
	  
		if(selectStatus == -1)
		{			
			Log(Wall::LOG_HAMUN, "### SAMSUNG SYSTEMAIRCON RS485:: UARTRS485.CPP :: ERROR SELECT : RETURN  SELECT : -1\n");
			//continue;
			rs485->UartClose();			
		}
		
		if(FD_ISSET(rs485->i_SLfd,&fdsr)) {
			
			recvSize = read(rs485->i_SLfd, &readBuffer, READ_BUFFER_SIZE);	

			if (recvSize == -1) {				
				Log(Wall::LOG_HAMUN, "### SAMSUNG SYSTEMAIRCON RS485 <- SAMSUNG PROTOCOL:: ERROR WRITTING TO SERIAL PORT : -1\n");
				
				rs485->UartClose();						

				break;

			} else if(recvSize == 0 ) {
				Log(Wall::LOG_HAMUN, "### SAMSUNG SYSTEMAIRCON RS485 <- SAMSUNG PROTOCOL:: READ VALUE FROM SERIAL : 0\n");

			} else {						
				 
					//Log(Wall::LOG_HAMUN, "### RS485 <- COMMAX PROTOCOL:: READ VALUE FROM SERIAL : %02x, rcvCnt = %d\n" , readBuffer, rcvCnt);
				
					memcpy( (recvBuffer+rcvCnt), &readBuffer, recvSize);

					if( recvBuffer[0] == 0x32 )
					{
						rcvCnt += recvSize;
					}
					else 
					{
						//Log(Wall::LOG_HAMUN, "################## SERIAL <- CMX485:: TYPE MISMATCH [ %02x, %02x]\n ################",recvBuffer[0], readBuffer );							

						rcvCnt = 0;
						readBuffer = 0x00;
						memset((void*)recvBuffer, 0x00, SAMSUNG_SYSTEMAIRCON_STATUS_RECEIVE_BUFFER_SIZE );	
					}

					if(rcvCnt > 3)
					{
						if(recvBuffer[1] != 0xD0 && recvBuffer[2] != 0xF0)
						{
							rcvCnt = 0;
							readBuffer = 0x00;
							memset((void*)recvBuffer, 0x00, SAMSUNG_SYSTEMAIRCON_STATUS_RECEIVE_BUFFER_SIZE );	
						}
					}
	

					if(rcvCnt > 4)
					{
						//tracking response mode
						switch(recvBuffer[3])
						{
							case 0xB2:
							{
								switch(recvBuffer[5])
								{
									case 0x20:
										if(rcvCnt == SAMSUNG_SYSTEMAIRCON_TRACKING_RECEIVE_BUFFER_SIZE_20H)
										{
											packetLength = recvBuffer[SAMSUNG_SYSTEMAIRCON_TRACKING_RECEIVE_BUFFER_SIZE_20H - 3] * 10 + recvBuffer[SAMSUNG_SYSTEMAIRCON_TRACKING_RECEIVE_BUFFER_SIZE_20H - 2];

											if( (rcvCnt == SAMSUNG_SYSTEMAIRCON_TRACKING_RECEIVE_BUFFER_SIZE_20H)  && (rcvCnt  - 2 == packetLength) && (recvBuffer[rcvCnt - 1] == 0x34)) 
											{
												//Log(Wall::LOG_HAMUN, "tracking frame receive from 485 correctly");							
												SystemAircon_Router.FrameReceive(recvBuffer, SAMSUNG_SYSTEMAIRCON_TRACKING_RECEIVE_BUFFER_SIZE_20H ,  rs485->GetInterfaceCompany(), rs485->GetInterfaceProtocol() );
												memset((void*)recvBuffer, 0x00, SAMSUNG_SYSTEMAIRCON_TRACKING_RECEIVE_BUFFER_SIZE_20H  );
				
												readBuffer = 0x00;
												rcvCnt = 0;
											}
										}

										break;

									case 0x30:
										if(rcvCnt == SAMSUNG_SYSTEMAIRCON_TRACKING_RECEIVE_BUFFER_SIZE_30H)
										{
											packetLength = recvBuffer[SAMSUNG_SYSTEMAIRCON_TRACKING_RECEIVE_BUFFER_SIZE_30H - 3] * 10 + recvBuffer[SAMSUNG_SYSTEMAIRCON_TRACKING_RECEIVE_BUFFER_SIZE_30H - 2];

											if( (rcvCnt == SAMSUNG_SYSTEMAIRCON_TRACKING_RECEIVE_BUFFER_SIZE_30H)  && (rcvCnt - 2 == packetLength) && (recvBuffer[rcvCnt - 1] == 0x34)) 	//rcvCnt -2 �� stx, etx �� length ��
											{
												//Log(Wall::LOG_HAMUN, "ftracking frame receive from 485 correctly");							
												SystemAircon_Router.FrameReceive(recvBuffer, SAMSUNG_SYSTEMAIRCON_TRACKING_RECEIVE_BUFFER_SIZE_30H ,  rs485->GetInterfaceCompany(), rs485->GetInterfaceProtocol() );
												memset((void*)recvBuffer, 0x00, SAMSUNG_SYSTEMAIRCON_TRACKING_RECEIVE_BUFFER_SIZE_30H  );
				
												readBuffer = 0x00;
												rcvCnt = 0;
											}
										}
										
										break;

									case 0x40:
										if(rcvCnt == SAMSUNG_SYSTEMAIRCON_TRACKING_RECEIVE_BUFFER_SIZE_40H)
										{
											packetLength = recvBuffer[SAMSUNG_SYSTEMAIRCON_TRACKING_RECEIVE_BUFFER_SIZE_40H - 3] * 10 + recvBuffer[SAMSUNG_SYSTEMAIRCON_TRACKING_RECEIVE_BUFFER_SIZE_40H - 2];

											if( rcvCnt == SAMSUNG_SYSTEMAIRCON_TRACKING_RECEIVE_BUFFER_SIZE_40H  && rcvCnt - 2== packetLength && recvBuffer[rcvCnt - 1] == 0x34) 
											{
												//Log(Wall::LOG_HAMUN, "tracking frame receive from 485 correctly");							
												SystemAircon_Router.FrameReceive(recvBuffer, SAMSUNG_SYSTEMAIRCON_TRACKING_RECEIVE_BUFFER_SIZE_40H ,  rs485->GetInterfaceCompany(), rs485->GetInterfaceProtocol() );
												memset((void*)recvBuffer, 0x00, SAMSUNG_SYSTEMAIRCON_TRACKING_RECEIVE_BUFFER_SIZE_40H  );
				
												readBuffer = 0x00;
												rcvCnt = 0;
											}
										}										
										break;

									default:
										break;
								}

								if(rcvCnt > SAMSUNG_SYSTEMAIRCON_TRACKING_RECEIVE_BUFFER_SIZE_40H)
								{
									Log(Wall::LOG_HAMUN, "#### TRACKING SERIAL <- SAMSUNG SYSTEMAIRCON SYSTEM485:: RECV DATA OVERFLOE : %d", recvSize);
									rcvCnt = 0;
									memset((void*)recvBuffer, 0x00,  SAMSUNG_SYSTEMAIRCON_STATUS_RECEIVE_BUFFER_SIZE);
								}
							}
							break;

							//status response mode
							case 0xB5:
							{

								if(rcvCnt == 7)
								{
									firstCalcStatusRecvLength = 6 + (recvBuffer[5] * 11) + 1 + 18 + 1;	//�������� size ������ length
								}
								else if(firstCalcStatusRecvLength == rcvCnt)
								{
									//printf("##### firstCalcStatusRecvLength = %d, rcvCnt = %d\n", firstCalcStatusRecvLength, rcvCnt);
									if(recvBuffer[firstCalcStatusRecvLength - 1] == 0x00)
									{
										lastCalcStatusRecvLength = firstCalcStatusRecvLength + 5;	//���� ������ ���� ���
									}
									else 
									{
										lastCalcStatusRecvLength = firstCalcStatusRecvLength + (recvBuffer[firstCalcStatusRecvLength - 1] * 3) + 5;	//���������� ���� ���
									}
								}

								//printf("recvBuffer[%d] == %02x, lastCalcStatusRecvLength = %d, rcvCnt = %d\n", rcvCnt - 1, recvBuffer[rcvCnt - 1], lastCalcStatusRecvLength, rcvCnt);

								if(recvBuffer[rcvCnt - 1] == 0x34 && lastCalcStatusRecvLength == rcvCnt)
								{
									packetLength = recvBuffer[rcvCnt - 3] * 10 + recvBuffer[rcvCnt - 2];
									if(lastCalcStatusRecvLength - 2 == packetLength) 	//stx, etx�� ���� ���
									{
										Log(Wall::LOG_HAMUN, "status frame receive from 485 correctly");							
										SystemAircon_Router.FrameReceive(recvBuffer, lastCalcStatusRecvLength ,  rs485->GetInterfaceCompany(), rs485->GetInterfaceProtocol() );
										memset((void*)recvBuffer, 0x00, SAMSUNG_SYSTEMAIRCON_STATUS_RECEIVE_BUFFER_SIZE  );

										readBuffer = 0x00;
										rcvCnt = 0;
									}else{
										Log(Wall::LOG_HAMUN, "status frame receive from 485 but packetlength is wrong");							
										memset((void*)recvBuffer, 0x00, SAMSUNG_SYSTEMAIRCON_STATUS_RECEIVE_BUFFER_SIZE  );
										readBuffer = 0x00;
										rcvCnt = 0;
									}
								}
							}
							break;
			
							//control response mode
							case 0xB0:
							{
								if(recvBuffer[rcvCnt - 1] == 0x34)
								{
									packetLength = recvBuffer[rcvCnt - 3] * 10 + recvBuffer[rcvCnt - 2];
									if(rcvCnt - 2 == packetLength) 	//stx, etx�� ���� ���
									{
										Log(Wall::LOG_HAMUN, "control frame receive from 485 correctly");							
										SystemAircon_Router.FrameReceive(recvBuffer, rcvCnt ,  rs485->GetInterfaceCompany(), rs485->GetInterfaceProtocol() );
										memset((void*)recvBuffer, 0x00, SAMSUNG_SYSTEMAIRCON_STATUS_RECEIVE_BUFFER_SIZE  );

										readBuffer = 0x00;
										rcvCnt = 0;
									}
								}
							}
							break;
							
							//wrong packet
							default:
								rcvCnt = 0;
								readBuffer = 0x00;
								memset((void*)recvBuffer, 0x00,  SAMSUNG_SYSTEMAIRCON_STATUS_RECEIVE_BUFFER_SIZE);
								break;
						}

						if(rcvCnt == SAMSUNG_SYSTEMAIRCON_STATUS_RECEIVE_BUFFER_SIZE) {
							
							Log(Wall::LOG_HAMUN, "#### SERIAL <- SAMSUNG FAN SYSTEM485:: RECV DATA OVERFLOE : %d", recvSize);				
							rcvCnt = 0;
							memset((void*)recvBuffer, 0x00,  SAMSUNG_SYSTEMAIRCON_STATUS_RECEIVE_BUFFER_SIZE);
						}
					}
				}
		}
				
	} // end of while
	Log(Wall::LOG_HAMUN, "### SAMSUNG FANSYSTEM RS485:: THREAD ENDING [ INTERFACE THREAD ]");

	pthread_exit(NULL);
	return NULL;
}


void SystemAirconUartRS485::Start()
 {

	int ret;	

	if( (ret = pthread_attr_init( &SystemAirconRs485_thread_t) ) != 0 ) {

			Log(Wall::LOG_HAMUN, " CAN'T  CREATE THREAD ATTRIBUTE :: SAMSUNG SYSTEM AIRCON RS485\n");
	}
	
	if( (ret = pthread_attr_setdetachstate( &SystemAirconRs485_thread_t, PTHREAD_CREATE_DETACHED) ) != 0 ) {
			
			Log(Wall::LOG_HAMUN, " CAN'T SET THREAD SET DETACH :: SAMSUNG SYSTEM AIRCON RS485\n");
	}

	if( (ret = pthread_create( &SystemAirconRs485_thread, &SystemAirconRs485_thread_t, SystemAirconUartRS485::run, (void*) this) ) != 0 )
	{
		
		
		Log(Wall::LOG_HAMUN, " CAN'T FAIL THREAD CREATE[SAMSUNG SYSTEM AIRCON RS485 PORT]\n");

	}


	Log(Wall::LOG_HAMUN, " SUCCESSFULLY THREAD CREATE [SAMSUNG SYSTEM AIRCON RS485 PORT]\n");

	(void)pthread_attr_destroy(&SystemAirconRs485_thread_t);	

 }
