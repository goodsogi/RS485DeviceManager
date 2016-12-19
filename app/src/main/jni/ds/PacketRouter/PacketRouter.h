
/******************************************************
  NAME     : PACKETROUTER.H
  Coded by : �� ����
  Revision : 1.0
  Date     : 2007/02/07 ~

*/


#ifndef __PACKETROUTER_H__
#define __PACKETROUTER_H__

#include <string.h>
//local includes
#include "../../log.h"
#include "../Util/wnamespace.h"
#include "../Util/util.h"
#include "../Config/DeviceInfo.h"
#include "../Config/CmxPacketSize.h"

#include "../CommManager/CommManager.h"
#include "../CommManager/RS485/UartRS485.h"
#include "../CommManager/Z256/UartRSTTL.h"
#include "../CommManager/SystemAirconRS485/SystemAirconUartRS485.h"
#include "../CommManager/LGSystemAirconRS485/LGSystemAirconUartRS485.h"
#include "../CommManager/RFInterFace/RFInterfaceTTL.h"
#include "../CommManager/SmartDoorPhoneRS485/SmartDoorPhoneUartRS485.h"
#include "../CommManager/SmartDoorPhoneRS485/TechnoSmartDoorPhoneUartRS485.h"
#include "../CommManager/HNARS485/HNAUartRS485.h"
#include "../CommManager/LedPanelRS485/LedPanelUartRS485.h"
#include "../CommManager/EnergyMonitoringRS485/EnergyMonitoringUartRS485.h"
#include "../CommManager/WeatherInfoRS485/WeatherInfoUartRS485.h"
//#include "../DriverInterface/LnCP/LnCPPacketAnalysis.h"

class  PacketRouter {

	private:

		unsigned char cmxBuffer[ HEADER_SIZE + COMMAX_BUFFER_SIZE ];
		unsigned char planetBuffer[ HEADER_SIZE + PLANET_BUFFER_SIZE ];
		unsigned char samsungBuffer[ HEADER_SIZE + SAMSUNG_SYSTEMAIRCON_STATUS_RECEIVE_BUFFER_SIZE ];
		unsigned char lgBuffer[ HEADER_SIZE + LG_RECEIVE_BUFFER_SIZE ];
		unsigned char rfModuleBuffer[ HEADER_SIZE + RFMODULE_BUFFER_SIZE ];
		unsigned char smartDoorPhoneBuffer[HEADER_SIZE + SMARTDOORPHONE_BUFFER_SIZE];
		unsigned char technoSmartDoorPhoneBuffer[HEADER_SIZE + TECHNO_SMARTDOORPHONE_MAX_RECEIVE_BUFFER_SIZE];
		unsigned char hnaBuffer[HEADER_SIZE + HNA_BUFFER_SIZE];
		unsigned char ledPanelBuffer[ HEADER_SIZE + (LEDPANEL_BUFFER_SIZE + 1)];
		unsigned char ledPanelRecvBuffer[ HEADER_SIZE + (LEDPANEL_BUFFER_SIZE + 1) ];
		unsigned char energymonitoringBuffer[ HEADER_SIZE + ENERGYMONITORING_RECV_BUFFER_SIZE];
		unsigned char weatherInfoBuffer[ HEADER_SIZE + WEATHERINFO_MAX_BUFFER_SIZE];
		
	public:		

		PacketRouter();
		~PacketRouter();		
	
		void FrameReceive(unsigned char *, unsigned int, enum UARTINTERFACECOMPANY, enum UARTINTERFACEPROTOCOL);
		static unsigned int FrameSend(unsigned char *, unsigned int);	

		unsigned int setInterfaceOpen(enum UARTINTERFACECOMPANY, enum UARTINTERFACEPROTOCOL, char*);
		
		static void MediaClose();


	void setFrameReceiveCallback(int (*fun)(unsigned char *, unsigned int));


};
#endif
