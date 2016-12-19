

#include "PacketRouter.h"

// using memcpy
#include <string.h>


// �� ���� 
//#include  "../PacketConverter/PacketConverter.h"

//class PacketConverter P_Converter;

#define INTERFACE_MEDIA_CNT  6

CommManager *manager[INTERFACE_MEDIA_CNT] = {NULL, };

typedef int (*FrameReceiveCallbackType)(unsigned char *, unsigned int);

FrameReceiveCallbackType mCallback;


PacketRouter::PacketRouter()
{
		
	unsigned int index = 0;	

	for( index = 0; index < ( HEADER_SIZE + COMMAX_BUFFER_SIZE); index++ )
	{

		cmxBuffer[index] = 0x00;
	}

	for( index = 0; index < ( HEADER_SIZE + SAMSUNG_SYSTEMAIRCON_STATUS_RECEIVE_BUFFER_SIZE); index++ )
	{

		samsungBuffer[index] = 0x00;
	}

	for( index = 0; index < ( HEADER_SIZE + LG_RECEIVE_BUFFER_SIZE); index++ )
	{

		lgBuffer[index] = 0x00;
	}

	for( index = 0; index < ( HEADER_SIZE + RFMODULE_BUFFER_SIZE); index++ )
	{

		rfModuleBuffer[index] = 0x00;
	}

	for( index = 0; index < ( HEADER_SIZE + SMARTDOORPHONE_BUFFER_SIZE); index++ )
	{

		smartDoorPhoneBuffer[index] = 0x00;
	}

	for( index = 0; index < ( HEADER_SIZE + TECHNO_SMARTDOORPHONE_MAX_RECEIVE_BUFFER_SIZE); index++ )
	{

		technoSmartDoorPhoneBuffer[index] = 0x00;
	}

	for( index = 0; index < ( HEADER_SIZE + HNA_BUFFER_SIZE); index++ )
	{

		hnaBuffer[index] = 0x00;
	}

	for( index = 0; index < ( HEADER_SIZE + (LEDPANEL_BUFFER_SIZE + 1) ); index++ )
	{

		ledPanelBuffer[index] = 0x00;
	}

	for( index = 0; index < ( HEADER_SIZE + (ENERGYMONITORING_RECV_BUFFER_SIZE) ); index++ )
	{

		energymonitoringBuffer[index] = 0x00;
	}

	for( index = 0; index < ( HEADER_SIZE + (WEATHERINFO_MAX_BUFFER_SIZE) ); index++ )
	{

		weatherInfoBuffer[index] = 0x00;
	}	
	
	Log(Wall::LOG_PRM, " %s %d LINE :: CONSTRUCTOR CALLED\n", __FILE__, __LINE__ );
}

PacketRouter::~PacketRouter()
{
	
}

/**
	Description : Port, BaudRate

	  Port				BaudRate
	  1 : /dev/ttyS0	1:  // B2400			
	  2 : /dev/ttyS1	2:  // B4800			
	  3 : /dev/ttyS2    3:  // B9600			
	  4 : /dev/ttyS3    4:  // B19200		
	  5 : /dev/ttyS4    5:  // B38400				
	  6 : /dev/ttyS5	6:  // B57600
	  				7:  // B115200
			

*/

// Uart Comm Port
#define GWUART1  2 //->  EXT1 ( 485 )        : �ڸƽ� ��������, �÷��� ��������
#define GWUART2  3 // -> EXT2 ( 232 )        : RF Module
#define GWUART3  4 //->  EXT3 ( 232 || 485 ) : �Ｚ �ý��� ������

// Uart Baudrate

#define GWB2400 1
#define GWB4800 2
#define GWB9600 3
#define GWB19200 4
#define GWB38400 5

unsigned int PacketRouter::setInterfaceOpen(enum UARTINTERFACECOMPANY InterfaceCompany, enum UARTINTERFACEPROTOCOL InterfaceProtocol, char* UartPort)
{



	unsigned int interface_open_flag = 0;



	// Commax Protocol
	if( (InterfaceCompany ==  INTERFACE_COMMAX_RS485 ) && (InterfaceProtocol == COMMAX_PROTOCOL)  ) {				
		
		/**		 
		  ���� UART PORT�� �ߺ� OPEN�� ���� �ϴ� ��ƾ
		*/

		if( manager[0] == NULL) {

			manager[0] =  new UartRS485();

			LOGD("manager[0]->UartOpen");
			// Port & BaudRate
			interface_open_flag = manager[0]->UartOpen(UartPort, GWB9600, INTERFACE_COMMAX_RS485, COMMAX_PROTOCOL);


			if( interface_open_flag != SUCCESS) {

				Log(Wall::LOG_ERR, "%s %d LINE :: INTERFACE [ RS485 ] OPEN :: FAIL", __FILE__, __LINE__);	
				return FAIL;
			}

			
			//((UartRS485 *)manager[0])->Start();



			Log(Wall::LOG_PRM, "%s %d LINE :: INTERFACE [ RS485 ] OPEN :: SUCCESS", __FILE__, __LINE__);	
			

		} else {

			Log(Wall::LOG_PRM, "%s %d LINE ::  INTERFACE [ RS485 ] OPEN :: FAIL -> MANAGER[0] NOT NULL", __FILE__, __LINE__);	
			interface_open_flag =  FAIL;
		}
	
	}else if( (InterfaceCompany ==  INTERFACE_PLANET_RS232) && (InterfaceProtocol == PLANET_PROTOCOL)  ) {
		
		//�÷��� ��������
		
		if( manager[1] == NULL ) {

			manager[1] =  new UartRSTTL();

			// Port & BaudRate
			interface_open_flag = manager[1]->UartOpen(UartPort, GWB4800, INTERFACE_PLANET_RS232, PLANET_PROTOCOL);	
			
			if( interface_open_flag != SUCCESS) {
				return FAIL;
			}	
			
			((UartRSTTL*)manager[1])->Start();			

			Log(Wall::LOG_PRM, "%s, %d LINE :: PACKETROUTER INTERFACE [ Z256  ] OPEN :: SUCCESS\n", __FILE__, __LINE__);	
			

		}else {

			Log(Wall::LOG_PRM, "%s, %d LINE :: INTERFACE [ Z256 ] OPEN :: FAIL -> MANAGE[1] NOT NULL\n", __FILE__, __LINE__);	
			interface_open_flag =  FAIL;
		}
	// KyoungDong Protocol RS485
	}else if( (InterfaceCompany ==  INTERFACE_KYOUNGDONG_RS485 ) && (InterfaceProtocol == KYOUNGDONG_PROTOCOL)  ) {

	// Mat Protocol RS485
	}else if( (InterfaceCompany ==  INTERFACE_MAT_RS485 ) && (InterfaceProtocol == MAT_PROTOCOL)  ) {
	
	
	// Planet Protocol RS485
	}else if( (InterfaceCompany ==  INTERFACE_PLANET_RS485) && (InterfaceProtocol == PLANET_PROTOCOL)  ) {
	

	// Samsung Protocol 
	}else if( (InterfaceCompany ==  INTERFACE_SAMSUNG_RS485 ) && (InterfaceProtocol == SAMSUNG_PROTOCOL )  ) {				
		
		/**		 
		  ���� UART PORT�� �ߺ� OPEN�� ���� �ϴ� ��ƾ
		*/

		if( manager[4] == NULL) {

			manager[4] =  new SystemAirconUartRS485();

			// Port & BaudRate
			interface_open_flag = manager[4]->UartOpen(UartPort, GWB9600, INTERFACE_SAMSUNG_RS485, SAMSUNG_PROTOCOL);	
			
			
			if( interface_open_flag != SUCCESS) {
				return FAIL;
			}			
			
			((SystemAirconUartRS485 *)manager[4])->Start();			

			Log(Wall::LOG_PRM, "%s %d LINE ::  INTERFACE [ SAMSUNG SYSTEM AIRCON RS485 ] OPEN :: SUCCESS", __FILE__, __LINE__);	
			

		} else {

			Log(Wall::LOG_PRM, "%s %d LINE ::  INTERFACE [  SAMSUNG SYSTEM AIRCON RS485 ] OPEN :: FAIL -> MANAGER[4] NOT NULL", __FILE__, __LINE__);	
			interface_open_flag =  FAIL;
		}

	// LG Protocol 
	}else if( (InterfaceCompany ==  INTERFACE_LG_RS485 ) && (InterfaceProtocol == LG_PROTOCOL )  ) {				
		
		/**		 
		  ���� UART PORT�� �ߺ� OPEN�� ���� �ϴ� ��ƾ
		*/

		if( manager[4] == NULL) {

			manager[4] =  new LGSystemAirconUartRS485();

			// Port & BaudRate
			interface_open_flag = manager[4]->UartOpen(UartPort, 2, INTERFACE_LG_RS485, LG_PROTOCOL);	
			
			
			if( interface_open_flag != SUCCESS) {
				return FAIL;
			}			
			
			((LGSystemAirconUartRS485 *)manager[4])->Start();			

			Log(Wall::LOG_PRM, "%s %d LINE ::  INTERFACE [ LG SYSTEM AIRCON RS485 ] OPEN :: SUCCESS", __FILE__, __LINE__);	
			

		} else {

			Log(Wall::LOG_PRM, "%s %d LINE ::  INTERFACE [  LG SYSTEM AIRCON RS485 ] OPEN :: FAIL -> MANAGER[4] NOT NULL", __FILE__, __LINE__);	

			interface_open_flag =  FAIL;
		}

	// RFMODULE [ GOIM ] Protocol
	}else if( (InterfaceCompany ==  INTERFACE_GOIM_TTL ) && (InterfaceProtocol == GOIM_PROTOCOL )  ) {				
		
		/**		 
		  ���� UART PORT�� �ߺ� OPEN�� ���� �ϴ� ��ƾ
		*/

		if( manager[3] == NULL) {

			manager[3] =  new RFInterfaceTTL();

			// Port & BaudRate
			interface_open_flag = manager[3]->UartOpen(UartPort, GWB38400, INTERFACE_GOIM_TTL, GOIM_PROTOCOL);	
			
			
			if( interface_open_flag != SUCCESS) {
				return FAIL;
			}			
			
			((RFInterfaceTTL *)manager[3])->Start();			

			Log(Wall::LOG_PRM, "%s %d LINE ::  INTERFACE [ GOIM RFMODULE [ COM4 ] ] OPEN :: SUCCESS", __FILE__, __LINE__);	
			

		} else {

			Log(Wall::LOG_PRM, "%s %d LINE ::  INTERFACE [  GOIM RFMODULE[ COM4 ] ] OPEN :: FAIL -> MANAGER[3] NOT NULL", __FILE__, __LINE__);	
			interface_open_flag =  FAIL;
		}
		
	//����Ʈ������ Protocol
	}else if( (InterfaceCompany ==  INTERFACE_COMMAX_SMARTDOORPHONE ) && (InterfaceProtocol == SMARTDOORPHONE_PROTOCOL )  ) {				
		
		/**		 
		  ���� UART PORT�� �ߺ� OPEN�� ���� �ϴ� ��ƾ
		*/

		if( manager[5] == NULL) {

			manager[5] =  new SmartDoorPhoneUartRS485();

			// Port & BaudRate
			interface_open_flag = manager[5]->UartOpen(UartPort, GWB19200, INTERFACE_COMMAX_SMARTDOORPHONE, SMARTDOORPHONE_PROTOCOL);	
			
			if( interface_open_flag != SUCCESS) {
				return FAIL;
			}			
			
			((SmartDoorPhoneUartRS485 *)manager[5])->Start();			

			Log(Wall::LOG_PRM, "%s %d LINE ::  INTERFACE [ SmartDoorPhone RS485 ] OPEN :: SUCCESS", __FILE__, __LINE__);	
		
		} else {

			Log(Wall::LOG_PRM, "%s %d LINE ::  INTERFACE [  SmartDoorPhone RS485 ] OPEN :: FAIL -> MANAGER[5] NOT NULL", __FILE__, __LINE__);	
			interface_open_flag =  FAIL;
		}
	}
	
	//Techno ����Ʈ������  Protocol
	else if( (InterfaceCompany ==  INTERFACE_TECHNO_SMARTDOORPHONE ) && (InterfaceProtocol == SMARTDOORPHONE_PROTOCOL )  ) 
	{

		if( manager[5] == NULL) {

			manager[5] =  new TechnoSmartDoorPhoneUartRS485();

			// Port & BaudRate
			interface_open_flag = manager[5]->UartOpen(UartPort, GWB19200, INTERFACE_TECHNO_SMARTDOORPHONE, SMARTDOORPHONE_PROTOCOL);	
			
			if( interface_open_flag != SUCCESS) {
				return FAIL;
			}			

			((TechnoSmartDoorPhoneUartRS485 *)manager[5])->Start();			
			Log(Wall::LOG_PRM, "%s %d LINE ::  INTERFACE [ Techno SmartDoorPhone RS485 ] OPEN :: SUCCESS", __FILE__, __LINE__);	

		} else {

			Log(Wall::LOG_PRM, "%s %d LINE ::  INTERFACE [  Techno SmartDoorPhone RS485 ] OPEN :: FAIL -> MANAGER[5] NOT NULL", __FILE__, __LINE__);	
			interface_open_flag =  FAIL;
		}

	}

	//HNA
	else if( (InterfaceCompany ==  INTERFACE_HNA_RS485 ) && (InterfaceProtocol == HNA_PROTOCOL )  ) {				
		
		if( manager[3] == NULL) {

			manager[3] =  new HNAUartRS485();

			// Port & BaudRate
			interface_open_flag = manager[3]->UartOpen(UartPort, GWB9600, INTERFACE_HNA_RS485, HNA_PROTOCOL);	
			
			
			if( interface_open_flag != SUCCESS) {
				return FAIL;
			}			
			
			((HNAUartRS485 *)manager[3])->Start();			

			Log(Wall::LOG_PRM, "%s %d LINE ::  INTERFACE [ HNA [ COM1 ] ] OPEN :: SUCCESS", __FILE__, __LINE__);	
			

		} else {

			Log(Wall::LOG_PRM, "%s %d LINE ::  INTERFACE [  HNA [ COM1 ] ] OPEN :: FAIL -> MANAGER[3] NOT NULL", __FILE__, __LINE__);	
			interface_open_flag =  FAIL;
		}
	}
	//LedPanel
	else if( (InterfaceCompany ==  INTERFACE_LEDPANEL_RS485 ) && (InterfaceProtocol == LEDPANEL_PROTOCOL)  ) {				
		
		/**		 
		  ���� UART PORT�� �ߺ� OPEN�� ���� �ϴ� ��ƾ
		*/

		if( manager[5] == NULL) {

			manager[5] =  new LedPanelUartRS485();

			// Port & BaudRate
			interface_open_flag = manager[5]->UartOpen(UartPort, GWB38400, INTERFACE_LEDPANEL_RS485, LEDPANEL_PROTOCOL);	
			
			
			if( interface_open_flag != SUCCESS) {
				return FAIL;
			}			
			
			((LedPanelUartRS485 *)manager[5])->Start();			

			Log(Wall::LOG_PRM, "%s %d LINE :: INTERFACE [ LED PANEL RS485 ] OPEN :: SUCCESS", __FILE__, __LINE__);	
			

		} else {

			Log(Wall::LOG_PRM, "%s %d LINE ::  INTERFACE [ LED PANEL RS485 RS485 ] OPEN :: FAIL -> MANAGER[5] NOT NULL", __FILE__, __LINE__);	
			interface_open_flag =  FAIL;
		}
	 
	
	}

	//EnergyMonitoring
	else if( (InterfaceCompany ==  INTERFACE_ENERGYMONITORING_RS485 ) && (InterfaceProtocol == ENERGYMONITORING_PROTOCOL)  ) {				
		
		/**		 
		  ���� UART PORT�� �ߺ� OPEN�� ���� �ϴ� ��ƾ
		*/

		if( manager[1] == NULL) {

			manager[1] =  new EnergyMonitoringUartRS485();

			// Port & BaudRate
			interface_open_flag = manager[1]->UartOpen(UartPort, GWB9600, INTERFACE_ENERGYMONITORING_RS485, ENERGYMONITORING_PROTOCOL);	
			
			
			if( interface_open_flag != SUCCESS) {
				return FAIL;
			}			
			
			((EnergyMonitoringUartRS485 *)manager[1])->Start();			

			Log(Wall::LOG_PRM, "%s %d LINE :: INTERFACE [ ENERGY MONITORING RS485 ] OPEN :: SUCCESS", __FILE__, __LINE__);	
			

		} else {

			Log(Wall::LOG_PRM, "%s %d LINE ::  INTERFACE [ ENERGY MONITORING RS485 ] OPEN :: FAIL -> MANAGER[1] NOT NULL", __FILE__, __LINE__);	
			interface_open_flag =  FAIL;
		}
	 
	
	}
	
	//Weather Info
	else if( (InterfaceCompany ==  INTERFACE_WEATHERINFO_RS485 ) && (InterfaceProtocol == WEATHERINFO_PROTOCOL)  ) {				
		
		/**		 
		  ���� UART PORT�� �ߺ� OPEN�� ���� �ϴ� ��ƾ
		*/

		if( manager[2] == NULL) {

			manager[2] =  new WeatherInfoUartRS485();

			// Port & BaudRate
			interface_open_flag = manager[2]->UartOpen(UartPort, GWB9600, INTERFACE_WEATHERINFO_RS485, WEATHERINFO_PROTOCOL);	
			
			
			if( interface_open_flag != SUCCESS) {
				return FAIL;
			}			
			
			((WeatherInfoUartRS485 *)manager[2])->Start();

			Log(Wall::LOG_PRM, "%s %d LINE :: INTERFACE [ WEATHER INFO RS485 ] OPEN :: SUCCESS", __FILE__, __LINE__);	
			

		} else {

			Log(Wall::LOG_PRM, "%s %d LINE ::  INTERFACE [ WEATHER INFO RS485 ] OPEN :: FAIL -> MANAGER[2] NOT NULL", __FILE__, __LINE__);	
			interface_open_flag =  FAIL;
		}
	 
	
	}
	
	return interface_open_flag;
}



void PacketRouter::FrameReceive(unsigned char * rcvBuf, unsigned int rcvLength, enum UARTINTERFACECOMPANY InterfaceCompany , enum UARTINTERFACEPROTOCOL InterfaceProtocol)
{
	LOGD("FrameReceive");

	for(int i = 0; i < rcvLength; ++i)
	{

		unsigned char temp = rcvBuf[i];

		int  temp2 = temp;
		LOGD( "%02X", temp2);
	}



	// Commax Protocol
	if( (InterfaceCompany ==  INTERFACE_COMMAX_RS485 ) && (InterfaceProtocol == COMMAX_PROTOCOL)  ) {

		if( rcvLength != COMMAX_BUFFER_SIZE) {
			 Log(Wall::LOG_ERR, " %s %d LINE :: COMMAX PROTOCOL SIZE NOT MISMATCH : 8\n", __FILE__, __LINE__);	
		}
		
		memcpy( cmxBuffer+2, rcvBuf, rcvLength);
		
		cmxBuffer[0] = INTERFACE_COMMAX_RS485;
		cmxBuffer[1] = COMMAX_PROTOCOL;
		
		//P_Converter.ProtocolParser(cmxBuffer, ( HEADER_SIZE + COMMAX_BUFFER_SIZE) );
		//PacketConverter::ProtocolParser(cmxBuffer, ( HEADER_SIZE + COMMAX_BUFFER_SIZE) );
		
		memset((void*)cmxBuffer, 0x00, ( HEADER_SIZE + COMMAX_BUFFER_SIZE) );

	// Samsung Protocol
	}else if( (InterfaceCompany ==  INTERFACE_SAMSUNG_RS485 ) && (InterfaceProtocol == SAMSUNG_PROTOCOL)  ) {		
		
		memcpy( samsungBuffer+2, rcvBuf, rcvLength);
		
		samsungBuffer[0] = INTERFACE_SAMSUNG_RS485;
		samsungBuffer[1] = SAMSUNG_PROTOCOL;
		
		//P_Converter.ProtocolParser(cmxBuffer, ( HEADER_SIZE + COMMAX_BUFFER_SIZE) );
		//PacketConverter::ProtocolParser(samsungBuffer, ( HEADER_SIZE + rcvLength) );
		
		memset((void*)samsungBuffer, 0x00, ( HEADER_SIZE + SAMSUNG_RECEIVE_BUFFER_SIZE) );

	// LG Protocol
	}else if( (InterfaceCompany ==  INTERFACE_LG_RS485 ) && (InterfaceProtocol == LG_PROTOCOL)  ) {		
		
	
		memcpy( lgBuffer+2, rcvBuf, rcvLength);
		
		lgBuffer[0] = INTERFACE_LG_RS485;
		lgBuffer[1] = LG_PROTOCOL;
			
		//P_Converter.ProtocolParser(cmxBuffer, ( HEADER_SIZE + COMMAX_BUFFER_SIZE) );
		//PacketConverter::ProtocolParser(lgBuffer, ( HEADER_SIZE + rcvLength) );
		
		memset((void*)lgBuffer, 0x00, ( HEADER_SIZE + LG_RECEIVE_BUFFER_SIZE) );
	
	// ����̿� RF MODULE Protocol
	}else if( (InterfaceCompany ==  INTERFACE_GOIM_TTL ) && (InterfaceProtocol == GOIM_PROTOCOL)  ) {

		if( rcvLength != RFMODULE_BUFFER_SIZE ) {

			 Log(Wall::LOG_ERR, " %s %d LINE :: ����̿� [RF MODULE] PROTOCOL SIZE NOT MISMATCH : 24\n", __FILE__, __LINE__);	
		}
		
		memcpy( rfModuleBuffer+2, rcvBuf, rcvLength);
		
		rfModuleBuffer[0] = INTERFACE_GOIM_TTL;
		rfModuleBuffer[1] = GOIM_PROTOCOL;
		
		
		//PacketConverter::ProtocolParser(rfModuleBuffer, ( HEADER_SIZE + RFMODULE_BUFFER_SIZE) );
		
		memset((void*)rfModuleBuffer, 0x00, ( HEADER_SIZE + RFMODULE_BUFFER_SIZE) );


	// KyoungDong Protocol RS485
	}else if( (InterfaceCompany ==  INTERFACE_KYOUNGDONG_RS485 ) && (InterfaceProtocol == KYOUNGDONG_PROTOCOL)  ) {

	// Mat Protocol RS485
	}else if( (InterfaceCompany ==  INTERFACE_MAT_RS485 ) && (InterfaceProtocol == MAT_PROTOCOL)  ) {


	// Planet Protocol RS485
	}else if( (InterfaceCompany ==  INTERFACE_PLANET_RS485) && (InterfaceProtocol == PLANET_PROTOCOL)  ) {

	
	// Planet Protocol RS232

	}else if( (InterfaceCompany ==  INTERFACE_PLANET_RS232) && (InterfaceProtocol == PLANET_PROTOCOL)  ) {

		if( rcvLength != PLANET_BUFFER_SIZE) {
			 Log(Wall::LOG_ERR, " %s %d LINE :: PLANET PROTOCOL SIZE NOT MISMATCH : 5\n", __FILE__, __LINE__);	
		}

		memcpy(planetBuffer+2, rcvBuf, rcvLength);

		planetBuffer[0] = INTERFACE_PLANET_RS232;
		planetBuffer[1] = PLANET_PROTOCOL;	
		
		//PacketConverter::ProtocolParser(planetBuffer, ( HEADER_SIZE + PLANET_BUFFER_SIZE) );
		
		memset((void*)planetBuffer, 0x00, ( HEADER_SIZE + PLANET_BUFFER_SIZE ) );

	//Smart Door Phone RS485
	}else if( (InterfaceCompany ==  INTERFACE_COMMAX_SMARTDOORPHONE) && (InterfaceProtocol == SMARTDOORPHONE_PROTOCOL)  ) {

		memcpy(smartDoorPhoneBuffer+2, rcvBuf, rcvLength);

		smartDoorPhoneBuffer[0] = INTERFACE_COMMAX_SMARTDOORPHONE;
		smartDoorPhoneBuffer[1] = SMARTDOORPHONE_PROTOCOL;	
		
		//PacketConverter::ProtocolParser(smartDoorPhoneBuffer, ( HEADER_SIZE + rcvLength) );
		memset((void*)smartDoorPhoneBuffer, 0x00, ( HEADER_SIZE + rcvLength ) );


	//Techno Smart Door Phone RS485
	} else if( (InterfaceCompany ==  INTERFACE_TECHNO_SMARTDOORPHONE) && (InterfaceProtocol == SMARTDOORPHONE_PROTOCOL)  ) {

		memcpy(technoSmartDoorPhoneBuffer+2, rcvBuf, rcvLength);

		technoSmartDoorPhoneBuffer[0] = INTERFACE_TECHNO_SMARTDOORPHONE;
		technoSmartDoorPhoneBuffer[1] = SMARTDOORPHONE_PROTOCOL;	
		
		//PacketConverter::ProtocolParser(technoSmartDoorPhoneBuffer, ( HEADER_SIZE + rcvLength) );
		memset((void*)technoSmartDoorPhoneBuffer, 0x00, ( HEADER_SIZE + rcvLength ) );

	// HNA Protocol 
	}else if( (InterfaceCompany ==  INTERFACE_HNA_RS485 ) && (InterfaceProtocol == HNA_PROTOCOL)  ) {

		memcpy( hnaBuffer+2, rcvBuf, rcvLength);
		
		hnaBuffer[0] = INTERFACE_HNA_RS485;
		hnaBuffer[1] = HNA_PROTOCOL;
		
		//PacketConverter::ProtocolParser(hnaBuffer, ( HEADER_SIZE + rcvLength) );
		
		memset((void*)hnaBuffer, 0x00, ( HEADER_SIZE + HNA_BUFFER_SIZE) );

	//LED Panel
	}else if( (InterfaceCompany ==  INTERFACE_LEDPANEL_RS485 ) && (InterfaceProtocol == LEDPANEL_PROTOCOL)  ) {

		if( (rcvLength != LEDPANEL_RECV_BUFFER_SIZE) && ( rcvLength != (LEDPANEL_BUFFER_SIZE + 1))  ) {

			 Log(Wall::LOG_ERR, " %s %d LINE :: LED PANEL PROTOCOL SIZE NOT MISMATCH : 8\n", __FILE__, __LINE__);	
		}
		
		memcpy( ledPanelRecvBuffer+2, rcvBuf, rcvLength);
		
		ledPanelRecvBuffer[0] = INTERFACE_LEDPANEL_RS485;
		ledPanelRecvBuffer[1] = LEDPANEL_PROTOCOL;
		
		//PacketConverter::ProtocolParser(ledPanelRecvBuffer, ( HEADER_SIZE +  rcvLength ) );
		
		memset((void*)ledPanelRecvBuffer, 0x00, ( HEADER_SIZE + (LEDPANEL_BUFFER_SIZE + 1) ) );

	//Energy Monitoring
	}else if( (InterfaceCompany ==  INTERFACE_ENERGYMONITORING_RS485 ) && (InterfaceProtocol == ENERGYMONITORING_PROTOCOL)  ) {

		if( rcvLength != ENERGYMONITORING_RECV_BUFFER_SIZE){

			 Log(Wall::LOG_ERR, " %s %d LINE :: ENERGY MONITORING PROTOCOL SIZE NOT MISMATCH : 8\n", __FILE__, __LINE__);
		}
		
		memcpy( energymonitoringBuffer+2, rcvBuf, rcvLength);
		
		energymonitoringBuffer[0] = INTERFACE_ENERGYMONITORING_RS485;
		energymonitoringBuffer[1] = ENERGYMONITORING_PROTOCOL;
		
		//PacketConverter::ProtocolParser(energymonitoringBuffer, ( HEADER_SIZE +  rcvLength ) );
		
		memset((void*)energymonitoringBuffer, 0x00, ( HEADER_SIZE + ENERGYMONITORING_RECV_BUFFER_SIZE));

	//Weather Info
	}else if( (InterfaceCompany ==  INTERFACE_WEATHERINFO_RS485 ) && (InterfaceProtocol == WEATHERINFO_PROTOCOL)  ) {

		memcpy( weatherInfoBuffer+2, rcvBuf, rcvLength);
		
		weatherInfoBuffer[0] = INTERFACE_WEATHERINFO_RS485;
		weatherInfoBuffer[1] = WEATHERINFO_PROTOCOL;
		
		//PacketConverter::ProtocolParser(weatherInfoBuffer, ( HEADER_SIZE +  rcvLength ) );
		
		memset((void*)weatherInfoBuffer, 0x00, ( HEADER_SIZE + WEATHERINFO_MAX_BUFFER_SIZE));

	}
	
}

/** 
	PacketConverter Class���� "����̽� �������̽� ȸ��, ��������, ������"�۽� �� �����͸�
	Encapsulate�ؼ� ��Ŷ ����ͷ� ����

	sndBuf[0] ::  RS485InterfaceCompany (RS485�� ����ϴ� ȸ��)
	sndBuf[1] ::  RS485InterfaceProtocol (RS485�� ����ϴ� ȸ���� ��������)
*/


unsigned int PacketRouter::FrameSend(unsigned char * sndBuf, unsigned int sndLength)
{
	((UartRS485 *)manager[0])->Start();
	LOGD("PacketRouter::FrameSend");
	//type mismatch unsigned char const char 발생해서 (const char *)로 일단 캐스팅


	//char *를 로그로 찍을 수가 없음 string.h에는 string으로 변환 클래스가 들어 있지 않음


	//std::string str;
	//str.append(reinterpret_cast<const char*>(foo()));
	//std::string const sName((char*) sndBuf);
	//LOGD((const char*)sndBuf);



//	for(int i = 0; i < sndLength; ++i)
//	{
//
//		unsigned char temp = sndBuf[i];
//
//		int  temp2 = temp;
//		LOGD( "%02X", temp2);
//	}

	switch( sndBuf[0] ) {

		case INTERFACE_COMMAX_RS485 :
		{
			LOGD("1111111111");
				unsigned char commaxBuffer[ COMMAX_BUFFER_SIZE ] = {0x00, };				

				memset((void*)commaxBuffer, 0x00, COMMAX_BUFFER_SIZE );			

				memcpy( commaxBuffer, sndBuf+2, COMMAX_BUFFER_SIZE);
				
				if( manager[0] == NULL) {

					 Log(Wall::LOG_PRM, "%s %d LINE :: MANAGER[0] :  NULL -> PACKET ROUTER FRAMESNED [ COMMAX PROTOCOL ]\n", __FILE__, __LINE__);	
					return FAIL;
				}
				
				manager[0]->SendFrame(commaxBuffer, COMMAX_BUFFER_SIZE);
				
		}
		break;

		case INTERFACE_SAMSUNG_RS485 :
		{
				unsigned char samsungBuffer[ SAMSUNG_RECEIVE_BUFFER_SIZE ] = {0x00, };				

				memset((void*)samsungBuffer, 0x00, SAMSUNG_RECEIVE_BUFFER_SIZE );			

				memcpy( samsungBuffer, sndBuf+2, sndLength );
				
				if( manager[4] == NULL) {

					 Log(Wall::LOG_PRM, "%s %d LINE :: MANAGER[4] :  NULL -> PACKET ROUTER FRAMESNED [ SAMSUNG SYSTEM AIRCON PROTOCOL ]\n", __FILE__, __LINE__);	
					return FAIL;
				}

				
				manager[4]->SendFrame(samsungBuffer, (sndLength -HEADER_SIZE) );
				
		}
			break;

		case INTERFACE_LG_RS485 :
		{
				unsigned char lgBuffer[ LG_CONTROL_BUFFER_SIZE ] = {0x00, };				

				memset((void*)lgBuffer, 0x00, LG_CONTROL_BUFFER_SIZE );			

				memcpy( lgBuffer, sndBuf+2, LG_CONTROL_BUFFER_SIZE );
				if( manager[4] == NULL) {

					 Log(Wall::LOG_PRM, "%s %d LINE :: MANAGER[4] :  NULL -> PACKET ROUTER FRAMESNED [ LG SYSTEM AIRCON PROTOCOL ]\n", __FILE__, __LINE__);	
					return FAIL;
				}

				
				manager[4]->SendFrame(lgBuffer, (sndLength -HEADER_SIZE) );
				
		}
			break;			

		case INTERFACE_GOIM_TTL :
		{
				unsigned char rfmoduleBuffer[ RFMODULE_BUFFER_SIZE ] = {0x00, };				

				memset((void*)rfmoduleBuffer, 0x00, RFMODULE_BUFFER_SIZE );			

				memcpy( rfmoduleBuffer, sndBuf+2, RFMODULE_BUFFER_SIZE);
				
				if( manager[3] == NULL) {

					 Log(Wall::LOG_PRM, "%s %d LINE :: MANAGER[3] :  NULL -> PACKET ROUTER FRAMESNED [ RF MODULE PROTOCOL ]\n", __FILE__, __LINE__);	
					return FAIL;
				}

				manager[3]->SendFrame(rfmoduleBuffer, RFMODULE_BUFFER_SIZE);
				
		}
			break;

		case INTERFACE_PLANET_RS232 :
		{
				unsigned char planetBuffer [ PLANET_BUFFER_SIZE ] = {0x00,};
				memset( (void*)planetBuffer, 0x00, PLANET_BUFFER_SIZE);
				memcpy( planetBuffer, sndBuf+2, sndLength);

				if( manager[1] == NULL) {
					Log(Wall::LOG_PRM, "%s %d LINE :: MANAGER[1] : NULL -> PACKET ROUTER FRAMESNED [ PLANET PROTOCOL ]\n", __FILE__, __LINE__);	
					return FAIL;
				}

				manager[1]->SendFrame(planetBuffer,sndLength);				
		}

		break;

		case INTERFACE_PLANET_RS485 :

		break;
		

		case INTERFACE_KYOUNGDONG_RS485 :
			break;

		case INTERFACE_MAT_RS485 :

			break;

		case INTERFACE_COMMAX_SMARTDOORPHONE :
		{
				unsigned char smartdoorPhoneBuffer[ SMARTDOORPHONE_BUFFER_SIZE ] = {0x00, };				

				if( manager[5] == NULL) {
					 Log(Wall::LOG_PRM, "%s %d LINE :: MANAGER[5] :  NULL -> PACKET ROUTER FRAMESNED [ SmartDoorPhone PROTOCOL ]\n", __FILE__, __LINE__);	
					return FAIL;
				}

				memset((void*)smartdoorPhoneBuffer, 0x00, SMARTDOORPHONE_BUFFER_SIZE );			
				memcpy( smartdoorPhoneBuffer, sndBuf+2, sndLength - HEADER_SIZE);
				manager[5]->SendFrame(smartdoorPhoneBuffer, sndLength -HEADER_SIZE);
		}
		break;

		case INTERFACE_TECHNO_SMARTDOORPHONE :
		{
				unsigned char technoSmartdoorPhoneBuffer[ TECHNO_SMARTDOORPHONE_MAX_CONTROL_BUFFER_SIZE ] = {0x00, };				

				if( manager[5] == NULL) {
					 Log(Wall::LOG_PRM, "%s %d LINE :: MANAGER[5] :  NULL -> PACKET ROUTER FRAMESNED [ Techno SmartDoorPhone PROTOCOL ]\n", __FILE__, __LINE__);	
					return FAIL;
				}

				memset((void*)technoSmartdoorPhoneBuffer, 0x00, TECHNO_SMARTDOORPHONE_MAX_CONTROL_BUFFER_SIZE );			
				memcpy( technoSmartdoorPhoneBuffer, sndBuf+2, sndLength - HEADER_SIZE);
				manager[5]->SendFrame(technoSmartdoorPhoneBuffer, sndLength -HEADER_SIZE);
		}
		break;		
		 
		case INTERFACE_HNA_RS485:
		{
				unsigned char hnaBuffer[ HNA_BUFFER_SIZE ] = {0x00, };				

				memset((void*)hnaBuffer, 0x00, HNA_BUFFER_SIZE );			

				memcpy( hnaBuffer, sndBuf+2, sndLength);
				
				if( manager[3] == NULL) {
					 Log(Wall::LOG_PRM, "%s %d LINE :: MANAGER[5] :  NULL -> PACKET ROUTER FRAMESNED [ HNA PROTOCOL ]\n", __FILE__, __LINE__);	
					return FAIL;
				}
				
				manager[3]->SendFrame(hnaBuffer, sndLength - HEADER_SIZE);
								
				
		}
		break;		

		case INTERFACE_LEDPANEL_RS485 :
		{

				unsigned char ledPanelBuffer[ LEDPANEL_IMAGE_BUFFER_SIZE ] = {0x00, };				

				memset((void*)ledPanelBuffer, 0x00, LEDPANEL_IMAGE_BUFFER_SIZE );			

				memcpy(ledPanelBuffer, sndBuf+2, sndLength);
				
				if( manager[5] == NULL) {
					 Log(Wall::LOG_ERR, "%s %d LINE :: MANAGER[1] :  NULL -> PACKET ROUTER FRAMESNED [ TECHNOVILLAGE PROTOCOL ]\n", __FILE__, __LINE__);	
					return FAIL;
				}

				//printf(" ######################## SEND SIZE : %d\n",  (sndLength-HEADER_SIZE) );
				manager[5]->SendFrame(ledPanelBuffer, (sndLength-HEADER_SIZE) );
				
		}
		
		break;

		case INTERFACE_ENERGYMONITORING_RS485:
		{
				unsigned char energyMonitoringBuffer[ ENERGYMONITORING_SEND_MAX_BUFFER_SIZE ] = {0x00, };				

				memset((void*)energyMonitoringBuffer, 0x00, ENERGYMONITORING_SEND_MAX_BUFFER_SIZE );

				memcpy( energyMonitoringBuffer, sndBuf+2, sndLength  - HEADER_SIZE);

				if( manager[1] == NULL) {
					 Log(Wall::LOG_PRM, "%s %d LINE :: MANAGER[1] :  NULL -> PACKET ROUTER FRAMESNED [ ENERGY MONITORING PROTOCOL ]\n", __FILE__, __LINE__);	
					return FAIL;
				}

				manager[1]->SendFrame(energyMonitoringBuffer, sndLength - HEADER_SIZE);
				memset((void*)energyMonitoringBuffer, 0x00, ENERGYMONITORING_SEND_MAX_BUFFER_SIZE );

		}
		break;

		case INTERFACE_WEATHERINFO_RS485:
		{
			LOGD("FrameSend: 222");
				unsigned char weatherInfoBuffer[ WEATHERINFO_MAX_BUFFER_SIZE ] = {0x00, };				

				memset((void*)weatherInfoBuffer, 0x00, WEATHERINFO_MAX_BUFFER_SIZE );

				memcpy( weatherInfoBuffer, sndBuf+2, sndLength  - HEADER_SIZE);

				if( manager[2] == NULL) {
					 Log(Wall::LOG_PRM, "%s %d LINE :: MANAGER[2] :  NULL -> PACKET ROUTER FRAMESNED [ WEATHERINFO PROTOCOL ]\n", __FILE__, __LINE__);	
					return FAIL;
				}

				manager[2]->SendFrame(weatherInfoBuffer, sndLength - HEADER_SIZE);
				memset((void*)weatherInfoBuffer, 0x00, WEATHERINFO_MAX_BUFFER_SIZE );

		}
		break;			
		
		default:
			break;
	}

	return SUCCESS;

}

void PacketRouter::MediaClose()
{
	unsigned int index = 0;

	for( index = 0; index < INTERFACE_MEDIA_CNT; index++) {

		if( manager[index] != NULL) {

			manager[index]->UartClose();
				
			delete manager[index];
			manager[index] = NULL;

			//Log(Wall::LOG_INF, " %s %d LINE :: MEMORY DELETE \n",__FILE__, __LINE__);
		}
	}
}

void PacketRouter::setFrameReceiveCallback(FrameReceiveCallbackType callback) {
 mCallback = callback;
}
