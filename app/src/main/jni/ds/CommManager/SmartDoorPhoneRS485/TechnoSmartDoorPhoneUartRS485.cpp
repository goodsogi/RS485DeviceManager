/******************************************************
  NAME     : SmartDoorPhoneUartRS485.cpp
  Coded by : �� ����
  Revision : 1.0
  Date     : 2013/04/30 ~

*/

#include "TechnoSmartDoorPhoneUartRS485.h"

// �� ���� 
#include  "../../PacketRouter/PacketRouter.h"
class PacketRouter TechnoSmartDoorPhone_Router;


TechnoSmartDoorPhoneUartRS485::TechnoSmartDoorPhoneUartRS485() : b_open(false), b_portSet(false), run_flag(true), mediaInterfaceType(COMPANY_DUMMY), mediaInterfaceProtocol(PROTOCOL_DUMMY)
{

}

TechnoSmartDoorPhoneUartRS485::~TechnoSmartDoorPhoneUartRS485() 
{
	UartClose();
}

int TechnoSmartDoorPhoneUartRS485::UartOpen(char* UartPort, unsigned int BAUDRATE, enum UARTINTERFACECOMPANY InterfaceCompany , enum UARTINTERFACEPROTOCOL InterfaceProtocol)
{
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
 bool TechnoSmartDoorPhoneUartRS485::isOpen() const
 {
	return b_open;
 }

void TechnoSmartDoorPhoneUartRS485::isSleep(unsigned long sec)
{
	sleep(sec);
	
}

/** closing the serial port */
int TechnoSmartDoorPhoneUartRS485::UartClose()
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
void TechnoSmartDoorPhoneUartRS485::SetInterfaceCompany(enum UARTINTERFACECOMPANY mediaType)
{

	mediaInterfaceType = mediaType;		

}

enum UARTINTERFACECOMPANY TechnoSmartDoorPhoneUartRS485::GetInterfaceCompany()
{
	return mediaInterfaceType;
}

 /** identify that The company using of device interface protocol : �ڸƽ� RS485��������, �浿 RS485�������� */
void TechnoSmartDoorPhoneUartRS485::SetProtocol(enum UARTINTERFACEPROTOCOL mediaProtocol)
{

	 mediaInterfaceProtocol = mediaProtocol;
}

enum UARTINTERFACEPROTOCOL TechnoSmartDoorPhoneUartRS485::GetInterfaceProtocol()
{
	return mediaInterfaceProtocol;
}


#define WRITE 1
unsigned int  TechnoSmartDoorPhoneUartRS485::SendFrame(unsigned char * frame, unsigned int frameLength)
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
void * TechnoSmartDoorPhoneUartRS485::run(void *arg)
{
	fd_set fdsr;	
	int recvSize = 0;	
    	int selectStatus = 0;	
	int dataLength = 0;
	int i = 0;
	
	unsigned int rcvCnt = 0;
	unsigned char readBuffer = 0x00;
	unsigned char recvBuffer[TECHNO_SMARTDOORPHONE_MAX_RECEIVE_BUFFER_SIZE] = {0x00,};
	
	Log(Wall::LOG_DOOR, "### [ SmartDoorPhone ] RS485:: THREAD STARTING [ INTERFACE THREAD ]");

	TechnoSmartDoorPhoneUartRS485 * rs485 = (TechnoSmartDoorPhoneUartRS485*)arg;

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
							case 0x0F:
							case 0x10:
							case 0x11:
								
							case 0x81:
							case 0x82:
							case 0x83:
							case 0x85:
							case 0x86:
							case 0x87:
							case 0x88:
							case 0x89:
							case 0x8A:
							case 0x8D:
							case 0x8F:
							case 0x90:
							case 0x91:
								break;

							default:		//�� ��° recv data�� command type �� �ƴҰ��
								Log(Wall::LOG_ERR, " �� �� ���� SmartDoorPhone �������� Header Type -> %02x, %d", recvBuffer[0]);	
								rcvCnt = 0;
								readBuffer = 0x00;
								dataLength = 0x00;
								memset((void*)recvBuffer, 0x00, TECHNO_SMARTDOORPHONE_MAX_RECEIVE_BUFFER_SIZE);	
								break;
								
						}
					}

					if(rcvCnt == 6)
					{
						dataLength = recvBuffer[4] * 256 + recvBuffer[5];
					}


					if(rcvCnt == dataLength + 8)
					{
						if((recvBuffer[1] & 0x80) != 0x80)		//send data�� ���� echo data
						{
							Log(Wall::LOG_DOOR, " Echo data %02x, %d", recvBuffer[0]);	
							rcvCnt = 0;
							readBuffer = 0x00;
							dataLength = 0x00;
							memset((void*)recvBuffer, 0x00, TECHNO_SMARTDOORPHONE_MAX_RECEIVE_BUFFER_SIZE);	
						}
						else if((recvBuffer[1] & 0x80) == 0x80)		//recv data
						{
							Log(Wall::LOG_DOOR, " ���� �� ���� ��û�� ���� ���� ������ rcvCnt = %d", rcvCnt);
							/*
							for(i = 0; i < SMARTDOORPHONE_MAX_RECEIVE_BUFFER_SIZE; i++)
							{
								printf("%02x ");
								if(i % 10 = 0)
									printf("\n");								
							}
							*/
							
							Log(Wall::LOG_DOOR, " %02x %02x %02x %02x %02x %02x %02x %02x %02x %02x", recvBuffer[0], recvBuffer[1], recvBuffer[2], recvBuffer[3], recvBuffer[4], recvBuffer[5], recvBuffer[6], recvBuffer[7], recvBuffer[8], recvBuffer[9]);
							Log(Wall::LOG_DOOR, " %02x %02x %02x %02x %02x %02x %02x %02x %02x %02x", recvBuffer[10], recvBuffer[11], recvBuffer[12], recvBuffer[13], recvBuffer[14], recvBuffer[15], recvBuffer[16], recvBuffer[17], recvBuffer[18], recvBuffer[19]);
							Log(Wall::LOG_DOOR, " %02x %02x %02x %02x %02x %02x %02x %02x %02x %02x", recvBuffer[20], recvBuffer[21], recvBuffer[22], recvBuffer[23], recvBuffer[24], recvBuffer[25], recvBuffer[26], recvBuffer[27], recvBuffer[28], recvBuffer[29]);
							Log(Wall::LOG_DOOR, " %02x %02x %02x %02x %02x %02x %02x %02x %02x %02x", recvBuffer[30], recvBuffer[31], recvBuffer[32], recvBuffer[33], recvBuffer[34], recvBuffer[35], recvBuffer[36], recvBuffer[37], recvBuffer[38], recvBuffer[39]);
							Log(Wall::LOG_DOOR, " %02x %02x %02x %02x %02x %02x %02x %02x %02x %02x", recvBuffer[40], recvBuffer[41], recvBuffer[42], recvBuffer[43], recvBuffer[44], recvBuffer[45], recvBuffer[46], recvBuffer[47], recvBuffer[48], recvBuffer[49]);
							Log(Wall::LOG_DOOR, " %02x %02x %02x %02x %02x %02x %02x %02x %02x %02x", recvBuffer[50], recvBuffer[51], recvBuffer[52], recvBuffer[53], recvBuffer[54], recvBuffer[55], recvBuffer[56], recvBuffer[57], recvBuffer[58], recvBuffer[59]);
							Log(Wall::LOG_DOOR, " %02x %02x %02x %02x %02x %02x %02x %02x %02x %02x", recvBuffer[60], recvBuffer[61], recvBuffer[62], recvBuffer[63], recvBuffer[64], recvBuffer[65], recvBuffer[66], recvBuffer[67], recvBuffer[68], recvBuffer[69]);
							Log(Wall::LOG_DOOR, " %02x %02x %02x %02x %02x %02x %02x %02x %02x %02x", recvBuffer[70], recvBuffer[71], recvBuffer[72], recvBuffer[73], recvBuffer[74], recvBuffer[75], recvBuffer[76], recvBuffer[77], recvBuffer[78], recvBuffer[79]);
							Log(Wall::LOG_DOOR, " %02x %02x %02x %02x %02x %02x %02x %02x %02x %02x", recvBuffer[80], recvBuffer[81], recvBuffer[82], recvBuffer[83], recvBuffer[84], recvBuffer[85], recvBuffer[86], recvBuffer[87], recvBuffer[88], recvBuffer[89]);
							Log(Wall::LOG_DOOR, " %02x %02x %02x %02x %02x %02x %02x %02x %02x %02x", recvBuffer[90], recvBuffer[91], recvBuffer[92], recvBuffer[93], recvBuffer[94], recvBuffer[95], recvBuffer[96], recvBuffer[97], recvBuffer[98], recvBuffer[99]);
							Log(Wall::LOG_DOOR, " %02x %02x %02x %02x %02x %02x %02x %02x %02x %02x", recvBuffer[100], recvBuffer[101], recvBuffer[102], recvBuffer[103], recvBuffer[104], recvBuffer[105], recvBuffer[106], recvBuffer[107], recvBuffer[108], recvBuffer[109]);
							Log(Wall::LOG_DOOR, " %02x %02x %02x %02x %02x %02x %02x %02x %02x %02x", recvBuffer[110], recvBuffer[111], recvBuffer[112], recvBuffer[113], recvBuffer[114], recvBuffer[115], recvBuffer[116], recvBuffer[117], recvBuffer[118], recvBuffer[119]);
							Log(Wall::LOG_DOOR, " %02x %02x %02x %02x %02x %02x %02x %02x %02x %02x", recvBuffer[120], recvBuffer[121], recvBuffer[122], recvBuffer[123], recvBuffer[124], recvBuffer[125], recvBuffer[126], recvBuffer[127], recvBuffer[128], recvBuffer[129]);
							Log(Wall::LOG_DOOR, " %02x %02x %02x %02x %02x %02x %02x %02x %02x %02x", recvBuffer[130], recvBuffer[131], recvBuffer[132], recvBuffer[133], recvBuffer[134], recvBuffer[135], recvBuffer[136], recvBuffer[137], recvBuffer[138], recvBuffer[139]);
							Log(Wall::LOG_DOOR, " %02x %02x %02x %02x %02x %02x %02x %02x %02x %02x", recvBuffer[140], recvBuffer[141], recvBuffer[142], recvBuffer[143], recvBuffer[144], recvBuffer[145], recvBuffer[146], recvBuffer[147], recvBuffer[148], recvBuffer[149]);
							Log(Wall::LOG_DOOR, " %02x %02x %02x %02x %02x %02x %02x %02x %02x %02x", recvBuffer[150], recvBuffer[151], recvBuffer[152], recvBuffer[153], recvBuffer[154], recvBuffer[155], recvBuffer[156], recvBuffer[157], recvBuffer[158], recvBuffer[159]);
							Log(Wall::LOG_DOOR, " %02x %02x %02x %02x %02x %02x %02x %02x %02x %02x", recvBuffer[160], recvBuffer[161], recvBuffer[162], recvBuffer[163], recvBuffer[164], recvBuffer[165], recvBuffer[166], recvBuffer[167], recvBuffer[168], recvBuffer[169]);
							Log(Wall::LOG_DOOR, " %02x %02x %02x %02x %02x %02x %02x %02x %02x %02x", recvBuffer[170], recvBuffer[171], recvBuffer[172], recvBuffer[173], recvBuffer[174], recvBuffer[175], recvBuffer[176], recvBuffer[177], recvBuffer[178], recvBuffer[179]);
							Log(Wall::LOG_DOOR, " %02x %02x %02x %02x %02x %02x %02x %02x %02x %02x", recvBuffer[180], recvBuffer[181], recvBuffer[182], recvBuffer[183], recvBuffer[184], recvBuffer[185], recvBuffer[186], recvBuffer[187], recvBuffer[188], recvBuffer[189]);
							Log(Wall::LOG_DOOR, " %02x %02x %02x %02x %02x %02x %02x %02x %02x %02x", recvBuffer[190], recvBuffer[191], recvBuffer[192], recvBuffer[193], recvBuffer[194], recvBuffer[195], recvBuffer[196], recvBuffer[197], recvBuffer[198], recvBuffer[199]);
							Log(Wall::LOG_DOOR, " %02x %02x %02x %02x %02x %02x %02x %02x %02x %02x", recvBuffer[200], recvBuffer[201], recvBuffer[202], recvBuffer[203], recvBuffer[204], recvBuffer[205], recvBuffer[206], recvBuffer[207], recvBuffer[208], recvBuffer[209]);
							Log(Wall::LOG_DOOR, " %02x %02x %02x %02x %02x %02x %02x %02x %02x %02x", recvBuffer[210], recvBuffer[211], recvBuffer[212], recvBuffer[213], recvBuffer[214], recvBuffer[215], recvBuffer[216], recvBuffer[217], recvBuffer[218], recvBuffer[219]);
							Log(Wall::LOG_DOOR, " %02x %02x %02x %02x %02x %02x %02x %02x %02x %02x", recvBuffer[220], recvBuffer[221], recvBuffer[222], recvBuffer[223], recvBuffer[224], recvBuffer[225], recvBuffer[226], recvBuffer[227], recvBuffer[228], recvBuffer[229]);
							Log(Wall::LOG_DOOR, " %02x %02x %02x %02x %02x %02x %02x %02x %02x %02x", recvBuffer[230], recvBuffer[231], recvBuffer[232], recvBuffer[233], recvBuffer[234], recvBuffer[235], recvBuffer[236], recvBuffer[237], recvBuffer[238], recvBuffer[239]);
							Log(Wall::LOG_DOOR, " %02x %02x %02x %02x %02x %02x %02x %02x %02x %02x", recvBuffer[240], recvBuffer[241], recvBuffer[242], recvBuffer[243], recvBuffer[244], recvBuffer[245], recvBuffer[246], recvBuffer[247], recvBuffer[248], recvBuffer[249]);
							Log(Wall::LOG_DOOR, " %02x %02x %02x %02x %02x %02x", recvBuffer[250], recvBuffer[251], recvBuffer[252], recvBuffer[253], recvBuffer[254], recvBuffer[255]);	
							
							TechnoSmartDoorPhone_Router.FrameReceive(recvBuffer, dataLength + 8,  rs485->GetInterfaceCompany(), rs485->GetInterfaceProtocol() );
							rcvCnt = 0;
							readBuffer = 0x00;
							dataLength = 0x00;								
							memset((void*)recvBuffer, 0x00, TECHNO_SMARTDOORPHONE_MAX_RECEIVE_BUFFER_SIZE);	
						}
					}

				}else{

					//Log(Wall::LOG_ERR, " �� �� ���� SmartDoorPhone �������� Header Type -> %02x, %d", recvBuffer[0]);	
					rcvCnt = 0;
					readBuffer = 0x00;
					dataLength = 0x00;					
					memset((void*)recvBuffer, 0x00, TECHNO_SMARTDOORPHONE_MAX_RECEIVE_BUFFER_SIZE);	

				}
					
			} 
		}

	} 
			
	Log(Wall::LOG_DOOR, "### [ SmartDoorPhone ] RS485:: THREAD ENDING [ INTERFACE THREAD ]");

	pthread_exit(NULL);
	return NULL;
}

void TechnoSmartDoorPhoneUartRS485::Start()
 {

	int ret;	

	if( (ret = pthread_attr_init( &rs485_thread_t) ) != 0 ) {

			Log(Wall::LOG_DOOR, " [ SmartDoorPhone ] :: CAN'T  CREATE THREAD ATTRIBUTE\n");
	}
	
	if( (ret = pthread_attr_setdetachstate( &rs485_thread_t, PTHREAD_CREATE_DETACHED) ) != 0 ) {
			
			Log(Wall::LOG_DOOR, " [ SmartDoorPhone ] :: CAN'T SET THREAD SET DETACH\n");
	}

	if( (ret = pthread_create( &rs485_thread, &rs485_thread_t, TechnoSmartDoorPhoneUartRS485::run, (void*) this) ) != 0 )
	{
		Log(Wall::LOG_DOOR, " [ SmartDoorPhone ] :: CAN'T FAIL THREAD CREATE\n");
	}


	Log(Wall::LOG_RS485, " [ SmartDoorPhone ] :: SUCCESSFULLY THREAD CREATE\n");

	(void)pthread_attr_destroy(&rs485_thread_t);		


 }
