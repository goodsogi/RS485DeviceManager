/******************************************************
  NAME     : SmartDoorPhoneUartRS485.cpp
  Coded by : �� ����
  Revision : 1.0
  Date     : 2013/04/30 ~

*/

#include "SmartDoorPhoneUartRS485.h"

// �� ���� 
#include  "../../PacketRouter/PacketRouter.h"
class PacketRouter SmartDoorPhone_Router;


SmartDoorPhoneUartRS485::SmartDoorPhoneUartRS485() : b_open(false), b_portSet(false), run_flag(true), mediaInterfaceType(COMPANY_DUMMY), mediaInterfaceProtocol(PROTOCOL_DUMMY)
{

}

SmartDoorPhoneUartRS485::~SmartDoorPhoneUartRS485() 
{
	UartClose();
}

int SmartDoorPhoneUartRS485::UartOpen(char* UartPort, unsigned int BAUDRATE, enum UARTINTERFACECOMPANY InterfaceCompany , enum UARTINTERFACEPROTOCOL InterfaceProtocol)
{
/*
    struct termios newtio;	
	
	// RS485 Port�� �ߺ� Open�� �����ϱ� ����
	if(  GetInterfaceCompany() != 0) return FAIL;

	if (b_open)  UartClose();	 
	 
	switch( COMMPORT) {

		case 1:

			 i_SLfd = ::open("/dev/ttySAC0", O_RDWR | O_NOCTTY);
				
			 Log(Wall::LOG_RS485, "### [ COMMAX ] RS-485 PORT OPEN [ ttyS0 ] :: SUCCESS");	
			 break;

		case 2:
			i_SLfd = ::open("/dev/ttySAC1", O_RDWR | O_NOCTTY);
			Log(Wall::LOG_RS485, "### [ COMMAX ] RS-485 PORT OPEN [ ttyS1 ] :: SUCCESS");	
			break;

		case 3:
			i_SLfd = ::open("/dev/ttySAC2", O_RDWR | O_NOCTTY);
			Log(Wall::LOG_RS485, "### [ COMMAX ] RS-485 PORT OPEN [ ttyS2 ] :: SUCCESS");	
			break;

		case 4:
			i_SLfd = ::open("/dev/ttySAC3", O_RDWR | O_NOCTTY);
			Log(Wall::LOG_RS485, "### [ COMMAX ] RS-485 PORT OPEN [ ttyS3 ] :: SUCCESS");	
			break;

		case 5:
			i_SLfd = ::open("/dev/ttySAC4", O_RDWR | O_NDELAY);
			Log(Wall::LOG_RS485, "### [ COMMAX ] RS-485 PORT OPEN [ /dev/uart0  ] :: SUCCESS");	
			break;
		

		default:
		    Log(Wall::LOG_RS485, "### [ COMMAX ] RS-485 PORT OPEN [ ttyS0 - ttyS4 ] :: NOT FOUNDED");	
		    break;

	}	
		
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
			 Log(Wall::LOG_ERR, "### [ COMMAX ] RS-485 PORT BAUDRATE [ B4800 - B38400 ] :: NOT FOUNDED");	
			break;

	}

	if (i_SLfd < 0) {

		Log(Wall::LOG_ERR, "### [ COMMAX ] RS-485 PORT OPEN [ COMMPROT : %d ] :: ERROR", COMMPORT);	
		return FAIL;
	}
	else  b_open = true;
	

	if (!b_portSet) {

	    tcgetattr(i_SLfd,&oldtio); 
		b_portSet = true;
	}

    bzero(&newtio, sizeof(newtio)); 

  
   // BAUDRATE: Set bps rate. You could also use cfsetispeed and cfsetospeed.  
   // CS8     : 8n1 (8bit,no parity,1 stopbit)
   // CLOCAL  : local connection, no modem contol
   // CREAD   : enable receiving characters

   newtio.c_cflag =  BAUDRATE | CS8 | CLOCAL | CREAD;

   newtio.c_iflag = 0;
  
   newtio.c_oflag = 0;

 
   newtio.c_lflag = 0;

   newtio.c_cc[VTIME] = 0;   //���� ������ timer�� disable 	

   newtio.c_cc[VMIN]  = 0;   //�ּ� 1 ���� ���� ������ blocking 		
	

   //now clean the modem line and activate the settings for the port

   tcflush(i_SLfd, TCIFLUSH);
   tcsetattr(i_SLfd,TCSANOW,&newtio);

   Log(Wall::LOG_RS485, " [ COMMAX ] SERIAL Successfully Serial Open:");	
   
   
    mediaInterfaceType = InterfaceCompany;

	mediaInterfaceProtocol = InterfaceProtocol;

   return SUCCESS;
*/
	char uartPortStr[40] = {0x00, };
    struct termios newtio;	

	if(  GetInterfaceCompany() != 0) return FAIL;

	if (b_open)  UartClose();	 
	 
	sprintf(uartPortStr, "/dev/%s", UartPort);
	i_SLfd = ::open(uartPortStr, O_RDWR | O_NOCTTY);
	Log(Wall::LOG_DOOR, "### [ SmartDoorPhone ] RS-485 PORT OPEN [ %s ] :: SUCCESS", uartPortStr);		
		
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
			 Log(Wall::LOG_DOOR, "### [ SmartDoorPhone ] RS-485 PORT BAUDRATE [ B4800 - B38400 ] :: NOT FOUNDED\n");	
			break;

	}

	if (i_SLfd < 0) {

		Log(Wall::LOG_DOOR, "### [ SmartDoorPhone ] RS-485 PORT OPEN [ COMMPROT : %s ] :: ERROR\n", uartPortStr);	
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

   Log(Wall::LOG_DOOR, " [ SmartDoorPhone ] SERIAL Successfully Serial Open:\n");	
   
   mediaInterfaceType = InterfaceCompany;

   mediaInterfaceProtocol = InterfaceProtocol;
   
   return SUCCESS;


}


 /** shows if the serial link is opened */
 bool SmartDoorPhoneUartRS485::isOpen() const
 {
	return b_open;
 }

void SmartDoorPhoneUartRS485::isSleep(unsigned long sec)
{
	sleep(sec);
	
}

/** closing the serial port */
int SmartDoorPhoneUartRS485::UartClose()
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
void SmartDoorPhoneUartRS485::SetInterfaceCompany(enum UARTINTERFACECOMPANY mediaType)
{

	mediaInterfaceType = mediaType;		

}

enum UARTINTERFACECOMPANY SmartDoorPhoneUartRS485::GetInterfaceCompany()
{
	return mediaInterfaceType;
}

 /** identify that The company using of device interface protocol : �ڸƽ� RS485��������, �浿 RS485�������� */
void SmartDoorPhoneUartRS485::SetProtocol(enum UARTINTERFACEPROTOCOL mediaProtocol)
{

	 mediaInterfaceProtocol = mediaProtocol;
}

enum UARTINTERFACEPROTOCOL SmartDoorPhoneUartRS485::GetInterfaceProtocol()
{
	return mediaInterfaceProtocol;
}


#define WRITE 1
unsigned int  SmartDoorPhoneUartRS485::SendFrame(unsigned char * frame, unsigned int frameLength)
{
	
	unsigned int sent = 0;
	int res = 0;
	int selectStatus = 0;
	unsigned int index = 0;

	if (!b_open) {

		Log(Wall::LOG_ERR, "### [ SmartDoorPhone ] UARTRS485 INTERFACE [ RS485 ] OPEN :: FAIL ");	
		return FAIL;
	}
	
	//Log(Wall::LOG_RS485, "### [ SmartDoorPhone ] PACKET ROUTER -> INTERFACE MEDIA [RS 485] , FRAMESIZE : %d:: %02x`%02x`%02x`%02x`%02x ", frameLength, frame[0],frame[1],frame[2],frame[3],frame[4]);	

	while( sent < frameLength) {	
		
		FD_ZERO(&fdsw);
		FD_SET(i_SLfd,&fdsw);
		
		selectStatus = (unsigned)select(i_SLfd+1,NULL,&fdsw,NULL, NULL);
		if(selectStatus == -1) {

			Log(Wall::LOG_ERR, "### [ SmartDoorPhone ] SERIAL -> CMX485::  UARTSERIAL.C : uart_data_send function -> Error Select");

			return FAIL;
		}
		
		if(FD_ISSET(i_SLfd,&fdsw)) {
			
			res = write(i_SLfd, frame, frameLength);
			if (res == -1) {

				Log(Wall::LOG_ERR, "### [ SmartDoorPhone ] SERIAL -> CMX485:: UARTSERIAL.C :: uart_data_send function : Error Writing to Serial Port");
				return FAIL;
			}   
			else if(res == 0 )

				Log(Wall::LOG_ERR, "### [ SmartDoorPhone ] SERIAL -> CMX485:: UARTSERIAL.C :: uart_data_send function : write res value => 0");
				
			else {	
				
				sent += res;				
				index++;				
			}	
					
		}else{
			if( sent > 0 ) {		

				Log(Wall::LOG_DOOR, " [ SmartDoorPhone ]### PACKET ROUTER -> INTERFACE MEDIA [RS 485]:: SENDING TIME OUT :%d \n", sent);
				return FAIL;
			}
		}

		
	} // end of while

	return SUCCESS;
}


// Thread of receive data

#define READ_BUFFER_SIZE 1
void * SmartDoorPhoneUartRS485::run(void *arg)
{
	fd_set fdsr;	
	int recvSize = 0;	
    	int selectStatus = 0;	
	int dataLength = 0;
	
	unsigned int rcvCnt = 0;
	unsigned char readBuffer = 0x00;
	unsigned char recvBuffer[SMARTDOORPHONE_BUFFER_SIZE] = {0x00,};
	
	Log(Wall::LOG_DOOR, "### [ SmartDoorPhone ] RS485:: THREAD STARTING [ INTERFACE THREAD ]");

	SmartDoorPhoneUartRS485 * rs485 = (SmartDoorPhoneUartRS485*)arg;

	while(rs485->run_flag) { 

		FD_ZERO(&fdsr);
		FD_SET(rs485->i_SLfd,&fdsr);		

	    	selectStatus = select(rs485->i_SLfd+1, &fdsr, NULL, NULL,NULL);
		
		if(selectStatus == -1)
		{			
			Log(Wall::LOG_DOOR, "### [ SmartDoorPhone ] RS485:: UARTRS485.CPP :: ERROR SELECT : RETURN  SELECT : -1\n");
			//continue;
			rs485->UartClose();			
		}
		
		if(FD_ISSET(rs485->i_SLfd,&fdsr)) {
			recvSize = read(rs485->i_SLfd, &readBuffer, READ_BUFFER_SIZE);	
			//Log(Wall::LOG_RS485, "### [ SmartDoorPhone ] readBuffer: %02x\n", readBuffer);

			if (recvSize == -1) {				
				Log(Wall::LOG_ERR, "### [ SmartDoorPhone ] RS485 <- COMMAX PROTOCOL:: ERROR WRITTING TO SERIAL PORT : -1\n");
				
				rs485->UartClose();						

				break;

			} else if(recvSize == 0 ) {
				Log(Wall::LOG_ERR, "### [ SmartDoorPhone ] RS485 <- COMMAX PROTOCOL:: READ VALUE FROM SERIAL : 0\n");

			} else {						
						 
				Log(Wall::LOG_DOOR, "### RS485 <- SmartDoorPhone PROTOCOL:: READ VALUE FROM SERIAL : %02x\n" , readBuffer);
				memcpy( (recvBuffer+rcvCnt), &readBuffer, recvSize);
				rcvCnt++;

				if(recvBuffer[0] == 0xF7)
				{

					if(rcvCnt == 2)
					{
						switch(recvBuffer[1])
						{
							case 0x01:
							case 0x02:
							case 0x03:
							case 0x04:
							case 0x05:
							case 0x06:
							case 0x07:
							case 0x08:
							case 0x09:
							case 0x0A:
							case 0x0B:
							case 0x0C:
							case 0x0D:
							case 0x0E:
							case 0x81:
							case 0x82:
							case 0x83:
							case 0x84:
							case 0x85:
							case 0x86:
							case 0x87:
							case 0x88:
							case 0x89:
							case 0x8A:
							case 0x8B:
							case 0x8C:
							case 0x8D:
							case 0x8E:
								break;

							default:		//�� ��° recv data�� command type �� �ƴҰ��
								Log(Wall::LOG_ERR, " �� �� ���� SmartDoorPhone �������� Header Type -> %02x, %d", recvBuffer[0]);	
								rcvCnt = 0;
								readBuffer = 0x00;
								dataLength = 0x00;
								memset((void*)recvBuffer, 0x00, SMARTDOORPHONE_BUFFER_SIZE);	
								break;
								
						}
					}

					if(rcvCnt == 3)
					{
						if(recvBuffer[2] > 134)
						{
							Log(Wall::LOG_DOOR, "Data Length OverFlow");	
							rcvCnt = 0;
							readBuffer = 0x00;
							dataLength = 0x00;
							memset((void*)recvBuffer, 0x00, SMARTDOORPHONE_BUFFER_SIZE);	
						}
						else
							dataLength = recvBuffer[2];
					}

					if(rcvCnt == dataLength + 5)
					{
						if((recvBuffer[1] & 0x80) != 0x80)		//send data�� ���� echo data
						{
							Log(Wall::LOG_DOOR, " Echo data %02x, %d", recvBuffer[0]);	
							rcvCnt = 0;
							readBuffer = 0x00;
							dataLength = 0x00;
							memset((void*)recvBuffer, 0x00, SMARTDOORPHONE_BUFFER_SIZE);	
						}


						if((recvBuffer[1] & 0x80) == 0x80)		//recv data
						{
							Log(Wall::LOG_DOOR, " ���� �� ���� ��û�� ���� ���� ������ rcvCnt = %d", rcvCnt);
/*							
							Log(Wall::LOG_RS485, " %02x %02x %02x %02x %02x %02x %02x %02x %02x %02x", recvBuffer[0], recvBuffer[1], recvBuffer[2], recvBuffer[3], recvBuffer[4], recvBuffer[5], recvBuffer[6], recvBuffer[7], recvBuffer[8], recvBuffer[9]);
							Log(Wall::LOG_RS485, " %02x %02x %02x %02x %02x %02x %02x %02x %02x %02x", recvBuffer[10], recvBuffer[11], recvBuffer[12], recvBuffer[13], recvBuffer[14], recvBuffer[15], recvBuffer[16], recvBuffer[17], recvBuffer[18], recvBuffer[19]);
							Log(Wall::LOG_RS485, " %02x %02x %02x %02x %02x %02x %02x %02x %02x %02x", recvBuffer[20], recvBuffer[21], recvBuffer[22], recvBuffer[23], recvBuffer[24], recvBuffer[25], recvBuffer[26], recvBuffer[27], recvBuffer[28], recvBuffer[29]);
							Log(Wall::LOG_RS485, " %02x %02x %02x %02x %02x %02x %02x %02x %02x %02x", recvBuffer[30], recvBuffer[31], recvBuffer[32], recvBuffer[33], recvBuffer[34], recvBuffer[35], recvBuffer[36], recvBuffer[37], recvBuffer[38], recvBuffer[39]);
							Log(Wall::LOG_RS485, " %02x %02x %02x %02x %02x %02x %02x %02x %02x %02x", recvBuffer[40], recvBuffer[41], recvBuffer[42], recvBuffer[43], recvBuffer[44], recvBuffer[45], recvBuffer[46], recvBuffer[47], recvBuffer[48], recvBuffer[49]);
							Log(Wall::LOG_RS485, " %02x %02x %02x %02x %02x %02x %02x %02x %02x %02x", recvBuffer[50], recvBuffer[51], recvBuffer[52], recvBuffer[53], recvBuffer[54], recvBuffer[55], recvBuffer[56], recvBuffer[57], recvBuffer[58], recvBuffer[59]);
							Log(Wall::LOG_RS485, " %02x %02x %02x %02x %02x %02x %02x %02x %02x %02x", recvBuffer[60], recvBuffer[61], recvBuffer[62], recvBuffer[63], recvBuffer[64], recvBuffer[65], recvBuffer[66], recvBuffer[67], recvBuffer[68], recvBuffer[69]);
							Log(Wall::LOG_RS485, " %02x %02x %02x %02x %02x %02x %02x %02x %02x %02x", recvBuffer[70], recvBuffer[71], recvBuffer[72], recvBuffer[73], recvBuffer[74], recvBuffer[75], recvBuffer[76], recvBuffer[77], recvBuffer[78], recvBuffer[79]);
							Log(Wall::LOG_RS485, " %02x %02x %02x %02x %02x %02x %02x %02x %02x %02x", recvBuffer[80], recvBuffer[81], recvBuffer[82], recvBuffer[83], recvBuffer[84], recvBuffer[85], recvBuffer[86], recvBuffer[87], recvBuffer[88], recvBuffer[89]);
							Log(Wall::LOG_RS485, " %02x %02x %02x %02x %02x %02x %02x %02x %02x %02x", recvBuffer[90], recvBuffer[91], recvBuffer[92], recvBuffer[93], recvBuffer[94], recvBuffer[95], recvBuffer[96], recvBuffer[97], recvBuffer[98], recvBuffer[99]);
							Log(Wall::LOG_RS485, " %02x %02x %02x %02x %02x %02x %02x %02x %02x %02x", recvBuffer[100], recvBuffer[101], recvBuffer[102], recvBuffer[103], recvBuffer[104], recvBuffer[105], recvBuffer[106], recvBuffer[107], recvBuffer[108], recvBuffer[109]);
							Log(Wall::LOG_RS485, " %02x %02x %02x %02x %02x %02x %02x %02x %02x %02x", recvBuffer[110], recvBuffer[111], recvBuffer[112], recvBuffer[113], recvBuffer[114], recvBuffer[115], recvBuffer[116], recvBuffer[117], recvBuffer[118], recvBuffer[119]);
							Log(Wall::LOG_RS485, " %02x %02x %02x %02x %02x %02x %02x %02x %02x %02x", recvBuffer[120], recvBuffer[121], recvBuffer[122], recvBuffer[123], recvBuffer[124], recvBuffer[125], recvBuffer[126], recvBuffer[127], recvBuffer[128], recvBuffer[129]);
							Log(Wall::LOG_RS485, " %02x %02x %02x %02x %02x %02x %02x %02x %02x %02x", recvBuffer[130], recvBuffer[131], recvBuffer[132], recvBuffer[133], recvBuffer[134], recvBuffer[135], recvBuffer[136], recvBuffer[137], recvBuffer[138], recvBuffer[139]);
*/							
							SmartDoorPhone_Router.FrameReceive(recvBuffer, dataLength + 5,  rs485->GetInterfaceCompany(), rs485->GetInterfaceProtocol() );
							rcvCnt = 0;
							readBuffer = 0x00;
							dataLength = 0x00;								
							memset((void*)recvBuffer, 0x00, SMARTDOORPHONE_BUFFER_SIZE);	
						}
					}

				}else{

					//Log(Wall::LOG_ERR, " �� �� ���� SmartDoorPhone �������� Header Type -> %02x, %d", recvBuffer[0]);	
					rcvCnt = 0;
					readBuffer = 0x00;
					dataLength = 0x00;					
					memset((void*)recvBuffer, 0x00, SMARTDOORPHONE_BUFFER_SIZE);	

				}
					
			} 
		}

	} 
			
	Log(Wall::LOG_DOOR, "### [ SmartDoorPhone ] RS485:: THREAD ENDING [ INTERFACE THREAD ]");

	pthread_exit(NULL);
	return NULL;
}

void SmartDoorPhoneUartRS485::Start()
 {

	int ret;	

	if( (ret = pthread_attr_init( &rs485_thread_t) ) != 0 ) {

			Log(Wall::LOG_DOOR, " [ SmartDoorPhone ] :: CAN'T  CREATE THREAD ATTRIBUTE\n");
	}
	
	if( (ret = pthread_attr_setdetachstate( &rs485_thread_t, PTHREAD_CREATE_DETACHED) ) != 0 ) {
			
			Log(Wall::LOG_DOOR, " [ SmartDoorPhone ] :: CAN'T SET THREAD SET DETACH\n");
	}

	if( (ret = pthread_create( &rs485_thread, &rs485_thread_t, SmartDoorPhoneUartRS485::run, (void*) this) ) != 0 )
	{
		Log(Wall::LOG_DOOR, " [ SmartDoorPhone ] :: CAN'T FAIL THREAD CREATE\n");
	}


	Log(Wall::LOG_RS485, " [ SmartDoorPhone ] :: SUCCESSFULLY THREAD CREATE\n");

	(void)pthread_attr_destroy(&rs485_thread_t);		


 }
