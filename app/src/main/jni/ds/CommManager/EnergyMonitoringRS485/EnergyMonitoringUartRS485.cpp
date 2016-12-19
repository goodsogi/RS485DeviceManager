
/******************************************************
  NAME     : UartRS485.cpp
  Coded by : �� ����
  Revision : 1.0
  Date     : 2007/02/07 ~

*/


#include "EnergyMonitoringUartRS485.h"

// �� ���� 
#include  "../../PacketRouter/PacketRouter.h"
class PacketRouter EnergyMonitoring_Router;


EnergyMonitoringUartRS485::EnergyMonitoringUartRS485() : b_open(false), b_portSet(false), run_flag(true), mediaInterfaceType(COMPANY_DUMMY), mediaInterfaceProtocol(PROTOCOL_DUMMY)
{

}

EnergyMonitoringUartRS485::~EnergyMonitoringUartRS485() 
{
	UartClose();
}

int EnergyMonitoringUartRS485::UartOpen(char* UartPort, unsigned int BAUDRATE, enum UARTINTERFACECOMPANY InterfaceCompany , enum UARTINTERFACEPROTOCOL InterfaceProtocol)
{
	char uartPortStr[40] = {0x00, };
	struct termios newtio;	

	if(  GetInterfaceCompany() != 0) return FAIL;

	if (b_open)  UartClose();	 
	 

	sprintf(uartPortStr, "/dev/%s", UartPort);
	i_SLfd = ::open(uartPortStr, O_RDWR | O_NOCTTY);
	Log(Wall::LOG_EMS, "### [ EnergyMonitoring ] RS-485 PORT OPEN [ %s ] :: SUCCESS", uartPortStr);	
	
		
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
			 Log(Wall::LOG_EMS, "### [ EnergyMonitoring ] RS-485 PORT BAUDRATE [ B4800 - B38400 ] :: NOT FOUNDED\n");	
			break;

	}

	if (i_SLfd < 0) {

		Log(Wall::LOG_EMS, "### [ EnergyMonitoring ] RS-485 PORT OPEN [ COMMPROT : %s ] :: ERROR\n", uartPortStr);	
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

   Log(Wall::LOG_EMS, " [ EnergyMonitoring ] SERIAL Successfully Serial Open:\n");	
   
   mediaInterfaceType = InterfaceCompany;

   mediaInterfaceProtocol = InterfaceProtocol;
   
   return SUCCESS;


}


 /** shows if the serial link is opened */
 bool EnergyMonitoringUartRS485::isOpen() const
 {
	return b_open;
 }

void EnergyMonitoringUartRS485::isSleep(unsigned long sec)
{
	sleep(sec);
	
}

/** closing the serial port */
int EnergyMonitoringUartRS485::UartClose()
{
	 /* restore the old port settings */  	 
	if (b_portSet)  //tcsetattr(i_SLfd,TCSANOW,&oldtio);
		b_portSet = false;

	if (b_open) ::close(i_SLfd);
		b_open = false;

	run_flag = false;
	return SUCCESS;
}

void EnergyMonitoringUartRS485::SetInterfaceCompany(enum UARTINTERFACECOMPANY mediaType)
{

	mediaInterfaceType = mediaType;		

}

enum UARTINTERFACECOMPANY EnergyMonitoringUartRS485::GetInterfaceCompany()
{
	return mediaInterfaceType;
}

void EnergyMonitoringUartRS485::SetProtocol(enum UARTINTERFACEPROTOCOL mediaProtocol)
{

	 mediaInterfaceProtocol = mediaProtocol;
}

enum UARTINTERFACEPROTOCOL EnergyMonitoringUartRS485::GetInterfaceProtocol()
{
	return mediaInterfaceProtocol;
}


#define WRITE 1
unsigned int  EnergyMonitoringUartRS485::SendFrame(unsigned char * frame, unsigned int frameLength)
{
	
	unsigned int sent = 0;
	int res = 0;
	int selectStatus = 0;
	unsigned int index = 0;

	if (!b_open) {

		Log(Wall::LOG_ERR, "### [ EnergyMonitoring ] UARTRS485 INTERFACE [ RS485 ] OPEN :: FAIL ");	
		return FAIL;
	}
		
	while( sent < frameLength) {	
		
		FD_ZERO(&fdsw);
		FD_SET(i_SLfd,&fdsw);
		
		selectStatus = (unsigned)select(i_SLfd+1,NULL,&fdsw,NULL, NULL);

		if(selectStatus == -1) {

			Log(Wall::LOG_ERR, "### [ EnergyMonitoring ] SERIAL -> CMX485::  UARTSERIAL.C : uart_data_send function -> Error Select");

			return FAIL;
		}
		
		if(FD_ISSET(i_SLfd,&fdsw)) {
			
			res = write(i_SLfd, &frame[index], WRITE);
			
			if (res == -1) {

				Log(Wall::LOG_ERR, "### [ EnergyMonitoring ] SERIAL -> CMX485:: UARTSERIAL.C :: uart_data_send function : Error Writing to Serial Port");
				return FAIL;
			}   
			else if(res == 0 )

				Log(Wall::LOG_ERR, "### [ EnergyMonitoring ] SERIAL -> CMX485:: UARTSERIAL.C :: uart_data_send function : write res value => 0");
				
			else {	
				
				sent += res;				
				index++;				
			}	
					
		}else{
			if( sent > 0 ) {		

				Log(Wall::LOG_EMS, " [ EnergyMonitoring ]### PACKET ROUTER -> INTERFACE MEDIA [RS 485]:: SENDING TIME OUT :%d \n", sent);
				return FAIL;
			}
		}

		
	} // end of while

	return SUCCESS;
}


// Thread of receive data

#define READ_BUFFER_SIZE 1
#define MAX_RECV_BUFFER_SIZE 50
void * EnergyMonitoringUartRS485::run(void *arg)
{ 
	fd_set fdsr;	
	int recvSize = 0;	
    	int selectStatus = 0;	
	unsigned int rcvCnt = 0;
	unsigned char readBuffer = 0x00;
	unsigned char recvBuffer[MAX_RECV_BUFFER_SIZE] = {0x00,};

	Log(Wall::LOG_EMS, "### [ EnergyMonitoring ] RS485:: THREAD STARTING [ INTERFACE THREAD ]");

	
	EnergyMonitoringUartRS485 * rs485 = (EnergyMonitoringUartRS485*)arg;

	while(rs485->run_flag) { 

		FD_ZERO(&fdsr);
		FD_SET(rs485->i_SLfd,&fdsr);		

		selectStatus = select(rs485->i_SLfd+1, &fdsr, NULL, NULL,NULL);
	  
		if(selectStatus == -1)
		{			
			Log(Wall::LOG_EMS, "### [ EnergyMonitoring ] RS485:: UARTRS485.CPP :: ERROR SELECT : RETURN  SELECT : -1\n");
			//continue;
			rs485->UartClose();			
		}
		
		if(FD_ISSET(rs485->i_SLfd,&fdsr)) {
			
			switch(  rs485->GetInterfaceCompany() ) 
			{

				case INTERFACE_ENERGYMONITORING_RS485:
				{
					recvSize = read(rs485->i_SLfd, &readBuffer, READ_BUFFER_SIZE);	
					Log(Wall::LOG_EMS, "### RS485 <- EMS PROTOCOL:: READ VALUE FROM SERIAL : %02x, rcvCnt = %d\n" , readBuffer, rcvCnt);
					if (recvSize == -1) {				
						Log(Wall::LOG_ERR, "### [ EnergyMonitoring ] RS485 <- EnergyMonitoring PROTOCOL:: ERROR WRITTING TO SERIAL PORT : -1\n");
						
						rs485->UartClose();						
						break;

					} else if(recvSize == 0 ) {
						Log(Wall::LOG_ERR, "### [ EnergyMonitoring ] RS485 <- EnergyMonitoring PROTOCOL:: READ VALUE FROM SERIAL : 0\n");

					} else {						
						memcpy( (recvBuffer+rcvCnt), &readBuffer, recvSize);
						rcvCnt++;

						//Header
						if(recvBuffer[0] == 0xF7)
						{

							if(rcvCnt > 2)
							{
								switch(recvBuffer[1])
								{
									case 0x10:
										//���� Data
										if(rcvCnt > 5)
										{
											if(rcvCnt == recvBuffer[4] + 7)
											{

												if(recvBuffer[recvBuffer[4] + 7 - 1] == 0xEE)
												{
													Log(Wall::LOG_EMS, " ���� �� ���� ��û�� ���� Data -> %02x,%02x,%02x,%02x,%02x,%02x,%02x ", recvBuffer[0],recvBuffer[1],recvBuffer[2],recvBuffer[3],recvBuffer[4],recvBuffer[5],recvBuffer[6]);
													EnergyMonitoring_Router.FrameReceive(recvBuffer, recvBuffer[4] + 7,  rs485->GetInterfaceCompany(), rs485->GetInterfaceProtocol() );

													memset((void*)recvBuffer, 0x00, MAX_RECV_BUFFER_SIZE);								
													readBuffer = 0x00;
													rcvCnt = 0;
												}
												else
												{
													Log(Wall::LOG_ERR, " Tail is not 0xEE -> %02x", recvBuffer[recvBuffer[4] + 7 - 1]);	
													rcvCnt = 0;
													readBuffer = 0x00;
													memset((void*)recvBuffer, 0x00, MAX_RECV_BUFFER_SIZE);	
												}
											}
											else if(rcvCnt > recvBuffer[4] + 7)
											{
												Log(Wall::LOG_ERR, " ���� Data Buffer Overflow\n");	
												rcvCnt = 0;
												readBuffer = 0x00;
												memset((void*)recvBuffer, 0x00, MAX_RECV_BUFFER_SIZE);	
											}

										}
										
										break;

									case 0x30:
										//�ǽð� Data
										if(rcvCnt > 5)
										{
											if(rcvCnt >= recvBuffer[4] + 7)
											{
												rcvCnt = 0;
												readBuffer = 0x00;
												memset((void*)recvBuffer, 0x00, MAX_RECV_BUFFER_SIZE);
												Log(Wall::LOG_EMS, " ���� ��ħ ���� ��û or ���� ����");
											}
										}
										
										break;

									default:
										Log(Wall::LOG_ERR, " �� �� ���� �������� recvBuffer[1] -> %02x", recvBuffer[1]);	
										rcvCnt = 0;
										readBuffer = 0x00;
										memset((void*)recvBuffer, 0x00, MAX_RECV_BUFFER_SIZE);	
										
										break;

								}
							}

						}
						else
						{
							Log(Wall::LOG_ERR, " �� �� ���� �������� recvBuffer[0] -> %02x", recvBuffer[0]);	
							rcvCnt = 0;
							readBuffer = 0x00;
							memset((void*)recvBuffer, 0x00, MAX_RECV_BUFFER_SIZE);	
						}

					}

				}
				break;

				default:
					break;
			}

		}
				
	} // end of while
	Log(Wall::LOG_EMS, "### [ EnergyMonitoring ] RS485:: THREAD ENDING [ INTERFACE THREAD ]");

	pthread_exit(NULL);
	return NULL;
}

void EnergyMonitoringUartRS485::Start()
 {

	int ret;	

	if( (ret = pthread_attr_init( &rs485_thread_t) ) != 0 ) {

			Log(Wall::LOG_EMS, " [ EnergyMonitoring ] :: CAN'T  CREATE THREAD ATTRIBUTE\n");
	}
	
	if( (ret = pthread_attr_setdetachstate( &rs485_thread_t, PTHREAD_CREATE_DETACHED) ) != 0 ) {
			
			Log(Wall::LOG_EMS, " [ EnergyMonitoring ] :: CAN'T SET THREAD SET DETACH\n");
	}

	if( (ret = pthread_create( &rs485_thread, &rs485_thread_t, EnergyMonitoringUartRS485::run, (void*) this) ) != 0 )
	{
		
		
		Log(Wall::LOG_EMS, " [ EnergyMonitoring ] :: CAN'T FAIL THREAD CREATE\n");

	}


	Log(Wall::LOG_EMS, " [ EnergyMonitoring ] :: SUCCESSFULLY THREAD CREATE\n");

	(void)pthread_attr_destroy(&rs485_thread_t);		


 }
