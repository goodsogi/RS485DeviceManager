/******************************************************
  NAME     : UartRS485.cpp
  Coded by : ±Ë ±§±‚
  Revision : 1.0
  Date     : 2007/02/07 ~

*/


#include "UartRS485.h"

// º± º±æπÆ
#include  "../../PacketRouter/PacketRouter.h"

class PacketRouter P_Router;


UartRS485::UartRS485() : b_open(false), b_portSet(false), run_flag(true),
                         mediaInterfaceType(COMPANY_DUMMY), mediaInterfaceProtocol(PROTOCOL_DUMMY) {

}

UartRS485::~UartRS485() {
    UartClose();
}

int i_RLfd = 0;
int UartRS485::UartOpen(char* UartPort, unsigned int BAUDRATE, enum UARTINTERFACECOMPANY InterfaceCompany , enum UARTINTERFACEPROTOCOL InterfaceProtocol)
{
    char uartPortStr[40] = {0x00, };
    char uartRcvPortStr[40] = {0x00, };
    struct termios newtio;

    if( GetInterfaceCompany() != 0) return FAIL;

    if (b_open)
        UartClose();

    LOGD(UartPort);
#if 0 // ttySPI0, ttySPI1
    sprintf(uartPortStr, "/dev/%s", "ttySPI0");
	sprintf(uartRcvPortStr, "/dev/%s", "ttySPI1");
	i_SLfd = ::open(uartPortStr, O_RDWR | O_NOCTTY);
	i_RLfd = ::open(uartRcvPortStr, O_RDWR | O_NOCTTY);
	Log(Wall::LOG_RS485, "### [ COMMAX ] RS-485 PORT OPEN [ T:%s \tR:%s] :: SUCCESS", uartPortStr, uartRcvPortStr);
#else
    sprintf(uartPortStr, "/dev/%s", UartPort);
    i_SLfd = ::open(uartPortStr, O_RDWR | O_NOCTTY);
#endif

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
            break;
    }

    if (i_SLfd < 0) {
        LOGD("i_SLfd fail");
        return FAIL;
    }
    else
        b_open = true;

    if (!b_portSet) {
        b_portSet = true;
    }

    bzero(&newtio, sizeof(newtio));

    newtio.c_cflag = BAUDRATE | CS8 | CLOCAL | CREAD;
    newtio.c_iflag = 0;
    newtio.c_oflag = 0;
    newtio.c_lflag = 0;
    newtio.c_cc[VTIME] = 0;   //πÆ¿⁄ ªÁ¿Ã¿« timer∏¶ disable
    newtio.c_cc[VMIN] = 0;   //√÷º“ 1 πÆ¿⁄ πﬁ¿ª ∂ß±Ó¡¯ blocking

#if 1
    tcflush(i_SLfd, TCIFLUSH);
    cfmakeraw(&newtio);
    cfsetispeed(&newtio, BAUDRATE);
    cfsetospeed(&newtio, BAUDRATE);

    if ( tcsetattr(i_SLfd,TCSANOW,&newtio) )
    {
        close(i_SLfd);
        return FAIL;
    }

#if 0
    tcflush(i_RLfd, TCIFLUSH);
	cfmakeraw(&newtio);
	cfsetispeed(&newtio, BAUDRATE);
	cfsetospeed(&newtio, BAUDRATE);

	if ( tcsetattr(i_RLfd,TCSANOW,&newtio) )
	{
		close(i_RLfd);
		Log(Wall::LOG_RS485, " [ COMMAX ] SERIAL RX Serial Open FAILED:\n");
		return FAIL;
	}
#endif
#endif

    mediaInterfaceType = InterfaceCompany;
    mediaInterfaceProtocol = InterfaceProtocol;

    return SUCCESS;
}

/** shows if the serial link is opened */
bool UartRS485::isOpen() const {
    return b_open;
}

void UartRS485::isSleep(unsigned long sec) {
    sleep(sec);

}

/** closing the serial port */
int UartRS485::UartClose() {
    /* restore the old port settings */
    if (b_portSet)  //tcsetattr(i_SLfd,TCSANOW,&oldtio);
        b_portSet = false;

    if (b_open) ::close(i_SLfd);
    b_open = false;

    run_flag = false;
    return SUCCESS;
}

/** identify that company of device interface type : ƒ⁄∏∆Ω∫, ∞Êµø*/
void UartRS485::SetInterfaceCompany(enum UARTINTERFACECOMPANY mediaType) {

    mediaInterfaceType = mediaType;

}

enum UARTINTERFACECOMPANY UartRS485::GetInterfaceCompany() {
    return mediaInterfaceType;
}

/** identify that The company using of device interface protocol : ƒ⁄∏∆Ω∫ RS485«¡∑Œ≈‰ƒ›, ∞Êµø RS485«¡∑Œ≈‰ƒ› */
void UartRS485::SetProtocol(enum UARTINTERFACEPROTOCOL mediaProtocol) {

    mediaInterfaceProtocol = mediaProtocol;
}

enum UARTINTERFACEPROTOCOL UartRS485::GetInterfaceProtocol() {
    return mediaInterfaceProtocol;
}


#define WRITE 1

unsigned int  UartRS485::SendFrame(unsigned char *frame, unsigned int frameLength) {

    for(int i = 0; i < frameLength; ++i)
    {

        unsigned char temp = frame[i];

        int  temp2 = temp;
        LOGD( "%02X", temp2);
    }



    LOGD("UartRS485::SendFrame");
    unsigned int sent = 0;
    int res = 0;
    int selectStatus = 0;
    unsigned int index = 0;

    if (!b_open) {
        LOGD("UartRS485::SendFrame FAIL !b_open");
        Log(Wall::LOG_ERR, "### [ COMMAX ] UARTRS485 INTERFACE [ RS485 ] OPEN :: FAIL ");
        return FAIL;
    }


    Log(Wall::LOG_RS485,
        "### [ COMMAX ] PACKET ROUTER -> INTERFACE MEDIA [RS 485] , FRAMESIZE : %d:: %02x`%02x`%02x`%02x`%02x`%02x`%02x`%02x",
        frameLength, frame[0], frame[1], frame[2], frame[3], frame[4], frame[5], frame[6], frame[7],
        frame[8]);


    while (sent < frameLength) {

        FD_ZERO(&fdsw);
        FD_SET(i_SLfd, &fdsw);

        selectStatus = (unsigned) select(i_SLfd + 1, NULL, &fdsw, NULL, NULL);

        if (selectStatus == -1) {

            Log(Wall::LOG_ERR,
                "### [ COMMAX ] SERIAL -> CMX485::  UARTSERIAL.C : uart_data_send function -> Error Select");
            LOGD("UartRS485::SendFrame FAIL selectStatus == -1");
            return FAIL;
        }
        LOGD("selectStatus: ");
        LOGD("%d", selectStatus);

        if (FD_ISSET(i_SLfd, &fdsw)) {
            LOGD("UartRS485::SendFrame write");
            res = write(i_SLfd, &frame[index], WRITE);

            if (res == -1) {
                LOGD("UartRS485::SendFrame res == -1");
                Log(Wall::LOG_ERR,
                    "### [ COMMAX ] SERIAL -> CMX485:: UARTSERIAL.C :: uart_data_send function : Error Writing to Serial Port");
                return FAIL;
            }
            else if (res == 0) {
                LOGD("UartRS485::SendFrame res == 0");
                Log(Wall::LOG_ERR,
                    "### [ COMMAX ] SERIAL -> CMX485:: UARTSERIAL.C :: uart_data_send function : write res value => 0");

            } else {

                sent += res;
                index++;
            }

        } else {
            if (sent > 0) {
                LOGD("UartRS485::SendFrame FAIL sent > 0");
                Log(Wall::LOG_RS485,
                    " [ COMMAX ]### PACKET ROUTER -> INTERFACE MEDIA [RS 485]:: SENDING TIME OUT :%d \n",
                    sent);
                return FAIL;
            }
        }


    } // end of while
    LOGD("UartRS485::SendFrame SUCCESS");
    return SUCCESS;
}

#define READ_BUFFER_SIZE 1



// Thread of receive data

#define READ_BUFFER_SIZE 1
void * UartRS485::run(void *arg)
{


	fd_set fdsr;
	int recvSize = 0;
	int selectStatus = 0;

	unsigned int rcvCnt = 0;
	unsigned char readBuffer = 0x00;
	unsigned char recvBuffer[COMMAX_BUFFER_SIZE] = {0x00,};

	struct timeval tv;

	Log(Wall::LOG_RS485, "### [ COMMAX ] RS485:: THREAD STARTING [ INTERFACE THREAD ]");
    LOGD("THREAD STARTING");

	UartRS485 * rs485 = (UartRS485*)arg;

	while(rs485->run_flag) {
		LOGD("while(rs485->run_flag");
		FD_ZERO(&fdsr);
		FD_SET(rs485->i_SLfd,&fdsr);


        tv.tv_sec = 0;
		tv.tv_usec = 100;

		selectStatus = select(rs485->i_SLfd+1, &fdsr, NULL, NULL,&tv);



		if(selectStatus == -1)
		{
			LOGD("ERROR SELECT : RETURN  SELECT : -1");
            sendFailFrameReceive(rs485);
			Log(Wall::LOG_RS485, "### [ COMMAX ] RS485:: UARTRS485.CPP :: ERROR SELECT : RETURN  SELECT : -1\n");
			//continue;
			rs485->UartClose();
            break;
		}

		if ( selectStatus == 0 )
		{
			LOGD("TimeOut!!");
            sendFailFrameReceive(rs485);
            break;
		}

		LOGD3("3333333333");

		if(FD_ISSET(rs485->i_SLfd,&fdsr)) {


			switch(  rs485->GetInterfaceCompany() ) {

				// COMMAX INTERFACE
				case INTERFACE_COMMAX_RS485:
				{
					//
					recvSize = read(rs485->i_SLfd, &readBuffer, READ_BUFFER_SIZE);

					if (recvSize == -1) {
						LOGD("ERROR WRITTING TO SERIAL PORT : -1");
						Log(Wall::LOG_ERR, "### [ COMMAX ] RS485 <- COMMAX PROTOCOL:: ERROR WRITTING TO SERIAL PORT : -1\n");

						rs485->UartClose();

						break;

					} else if(recvSize == 0 ) {
						LOGD("READ VALUE FROM SERIAL : 0");
						Log(Wall::LOG_ERR, "### [ COMMAX ] RS485 <- COMMAX PROTOCOL:: READ VALUE FROM SERIAL : 0\n");

					} else {

						//Log(Wall::LOG_RS485, "### RS485 <- COMMAX PROTOCOL:: READ VALUE FROM SERIAL : %02x\n" , readBuffer);
						memcpy( (recvBuffer+rcvCnt), &readBuffer, recvSize);
						rcvCnt++;

						switch( recvBuffer[0] )
						{
							//¡¶æÓ π◊ ªÛ≈¬ ø‰√ªø° ¥Î«— Echo Data
							//∫∏¿œ∑Ø
							/*
							case 0x01:
							case 0x02:
							case 0x03:
							case 0x04:
							case 0x05:
							case 0x0F:
							//∞°Ω∫
							case 0x10:
							case 0x11:
							//¿œ∞˝ Ω∫¿ßƒ°
							case 0x20:
							case 0x21:
							case 0x22:
							case 0x23:
							case 0x2D:
							case 0x2E:
							case 0x2F:
							//¿¸µÓ
							case 0x30:
							case 0x31:
							case 0x3F:
							//ƒø∆∞
							case 0x40:
							case 0x41:
							case 0x4F:
							//µµæÓ∂Ù
							case 0x72:
							case 0x73:
							//»Ø±‚
							case 0x76:
							case 0x77:
							case 0x78:
							//¥Î±‚¿¸∑¬ ¿⁄µø ¬˜¥‹±‚
							case 0x79:
							case 0x7a:
							case 0x7b:
							//∞¥Ω«
							case 0x7c:
							case 0x7d:

									if( rcvCnt == COMMAX_BUFFER_SIZE) {

										Log(Wall::LOG_RS485, " ªÛ≈¬ π◊ ¡¶æÓ ø‰√ªø° ¥Î«— Echo Data -> %02x,%02x,%02x,%02x,%02x,%02x,%02x,%02x, Size : %d", recvBuffer[0],recvBuffer[1],recvBuffer[2],recvBuffer[3],recvBuffer[4],recvBuffer[5],recvBuffer[6],recvBuffer[7], rcvCnt);
										memset((void*)recvBuffer, 0x00, COMMAX_BUFFER_SIZE);
										readBuffer = 0x00;
										rcvCnt = 0;

									}else if( rcvCnt > COMMAX_BUFFER_SIZE) {

										Log(Wall::LOG_ERR, " ¡¶æÓ π◊ ªÛ≈¬ ø‰√ªø° ¥Î«— Echo µ•¿Ã≈Õ... ø¿πˆ«√∑ŒøÏ... %02x, %d", recvBuffer[0], rcvCnt);
										rcvCnt = 0;
										memset((void*)recvBuffer, 0x00,  COMMAX_BUFFER_SIZE);

									}


							break;
							*/

							//¿¸µÓ
							case 0xb0:
							case 0xb1:
								//∫∏¿œ∑Ø
							case 0x81:
							case 0x82:
							case 0x83:
							case 0x84:
							case 0x85:
							case 0x8F:
								//∞°Ω∫
							case 0x90:
							case 0x91:
								//¿œ∞˝Ω∫¿ßƒ°
							case 0xa0:
							case 0xa1:
							case 0xa2:
							case 0xa3:

								//ƒø∆∞
							case 0xc0:
							case 0xc1:

								//FCU
							case 0xD2:
							case 0xD3:

								//µµæÓ∂Ù
							case 0xf2:
							case 0xf3:

								//Ω√Ω∫≈€ ø°æÓƒ¡
							case 0xf4:
							case 0xf5:

								//»Ø±‚
							case 0xf6:
							case 0xf7:
							case 0xf8:

								//¥Î±‚¿¸∑¬ ¿⁄µø ¬˜¥‹±‚
							case 0xf9:
							case 0xfa:

								//∞¥Ω«
							case 0xfc:
							case 0xfd:

								if( rcvCnt == COMMAX_BUFFER_SIZE) {
									LOGD("rcvCnt == COMMAX_BUFFER_SIZE");
									Log(Wall::LOG_RS485, " ¡¶æÓ π◊ ªÛ≈¬ ø‰√ªø° ¥Î«— ¿¿¥‰ µ•¿Ã≈Õ %02x,%02x,%02x,%02x,%02x,%02x,%02x,%02x,  Size -> %d", recvBuffer[0],recvBuffer[1],recvBuffer[2],recvBuffer[3],recvBuffer[4],recvBuffer[5],recvBuffer[6],recvBuffer[7], rcvCnt);
									P_Router.FrameReceive(recvBuffer, COMMAX_BUFFER_SIZE,  rs485->GetInterfaceCompany(), rs485->GetInterfaceProtocol() );
									memset((void*)recvBuffer, 0x00, COMMAX_BUFFER_SIZE);

									readBuffer = 0x00;
									rcvCnt = 0;

								}else if( rcvCnt > COMMAX_BUFFER_SIZE) {
									LOGD("rcvCnt > COMMAX_BUFFER_SIZE");
									Log(Wall::LOG_ERR, " ¡¶æÓ π◊ ªÛ≈¬ ø‰√ªø° ¥Î«— ¿¿¥‰ µ•¿Ã≈Õ... ø¿πˆ«√∑ŒøÏ... %02x, %d", recvBuffer[0], rcvCnt);
									rcvCnt = 0;
									memset((void*)recvBuffer, 0x00,  COMMAX_BUFFER_SIZE);

								}

								break;

							default:
								//Log(Wall::LOG_ERR, " æÀ ºˆ æ¯¥¬ ƒ⁄∏∆Ω∫ «¡∑Œ≈‰ƒ› Header Type -> %02x, %d", recvBuffer[0]);
								rcvCnt = 0;
								readBuffer = 0x00;
								memset((void*)recvBuffer, 0x00, COMMAX_BUFFER_SIZE);
								break;

						}	// end of case

						if( rcvCnt > COMMAX_BUFFER_SIZE) {
							LOGD("RECV DATA OVERFLOE : %02x", recvBuffer[0]);
							Log(Wall::LOG_ERR, "#### SERIAL <- CMX485:: RECV DATA OVERFLOE : %02x", recvBuffer[0]);
							rcvCnt = 0;
							readBuffer = 0x00;
							memset((void*)recvBuffer, 0x00,  COMMAX_BUFFER_SIZE);
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
	LOGD("THREAD ENDING");
	Log(Wall::LOG_RS485, "### [ COMMAX ] RS485:: THREAD ENDING [ INTERFACE THREAD ]");

	pthread_exit(NULL);
	return NULL;
}

    void UartRS485::Start() {

        int ret;

        if ((ret = pthread_attr_init(&rs485_thread_t)) != 0) {

            LOGD("CAN'T  CREATE THREAD ATTRIBUTE");

            Log(Wall::LOG_RS485, " [ COMMAX ] :: CAN'T  CREATE THREAD ATTRIBUTE\n");
        }

        if ((ret = pthread_attr_setdetachstate(&rs485_thread_t, PTHREAD_CREATE_DETACHED)) !=
            0) {
            LOGD("CAN'T SET THREAD SET DETACH");
            Log(Wall::LOG_RS485, " [ COMMAX ] :: CAN'T SET THREAD SET DETACH\n");
        }

        if ((ret = pthread_create(&rs485_thread, &rs485_thread_t, UartRS485::run,
                                  (void *) this)) != 0) {

            LOGD("CAN'T FAIL THREAD CREATE");
            Log(Wall::LOG_RS485, " [ COMMAX ] :: CAN'T FAIL THREAD CREATE\n");

        }

        LOGD("SUCCESSFULLY THREAD CREATE");
        Log(Wall::LOG_RS485, " [ COMMAX ] :: SUCCESSFULLY THREAD CREATE\n");

        (void) pthread_attr_destroy(&rs485_thread_t);


    }

void UartRS485::sendFailFrameReceive(UartRS485 *rs485) {
    unsigned char *recvBuffer = new unsigned char[8]();
    recvBuffer[0] = 0x00;
    recvBuffer[1] = 0x00;
    recvBuffer[2] = 0x00;
    recvBuffer[3] = 0x00;
    recvBuffer[4] = 0x00;
    recvBuffer[5] = 0x00;
    recvBuffer[6] = 0x00;
    recvBuffer[7] = 0x00;


    P_Router.FrameReceive(recvBuffer, COMMAX_BUFFER_SIZE,
                          rs485->GetInterfaceCompany(),
                          rs485->GetInterfaceProtocol());
}
