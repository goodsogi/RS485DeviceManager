

/******************************************************
  NAME     : DEVICEINFO.H
  Coded by : �� ����
  Revision : 1.0
  Date     : 2007/02/07 ~

*/


#ifndef __DEVICEINFO_H__
#define __DEVICEINFO_H__

#define USE 1
#define NOT_USE 0

enum PROTOCOLCOMPANY
{
	PROTOCOLCOMPANY_DUMMY 	= 0,
	COMMAX 					= 1,
	PLANET 						= 2,
	LNCP   						= 3,
	HAMUN  						= 4,
	GOIM   						= 5,
	HNA	    						= 6,
	LEDPANEL 					= 7,
	UKOSTEC					= 8,
	
};

enum UARTINTERFACECOMPANY
{

	COMPANY_DUMMY						= 0,
	INTERFACE_COMMAX_RS485				= 1,
	INTERFACE_KYOUNGDONG_RS485 			= 2,
	INTERFACE_MAT_RS485					= 3,
	INTERFACE_MAT_RS232					= 4,
	INTERFACE_PLANET_RS485				= 5,	
	INTERFACE_PLANET_RS232				= 6,	
	INTERFACE_LNCP_RS232					= 7,	
	INTERFACE_SAMSUNG_RS485				= 8,	
	INTERFACE_GOIM_TTL					= 9,
	INTERFACE_LG_RS485					= 10,
	INTERFACE_COMMAX_SMARTDOORPHONE	= 11,
	INTERFACE_HNA_RS485					= 12,
	INTERFACE_ZWAVE						= 13,
	INTERFACE_LEDPANEL_RS485 			= 14,
	INTERFACE_ENERGYMONITORING_RS485	= 15,
	INTERFACE_WEATHERINFO_RS485			= 16,
	INTERFACE_TECHNO_SMARTDOORPHONE	= 17,

};

enum UARTINTERFACEPROTOCOL
{

	PROTOCOL_DUMMY       				= 0,
	COMMAX_PROTOCOL     				= 1,
	KYOUNGDONG_PROTOCOL  			= 2,
	MAT_PROTOCOL         					= 3,
	PLANET_PROTOCOL      				= 4,
	LNCP_PROTOCOL        					= 5,
	SAMSUNG_PROTOCOL     				= 6,
	GOIM_PROTOCOL        				= 7,
	LG_PROTOCOL			 			= 8, 
	SMARTDOORPHONE_PROTOCOL			= 9,
	HNA_PROTOCOL						= 10	,
	ZWAVE_PROTOCOl					= 11,
	LEDPANEL_PROTOCOL 				= 12,
	ENERGYMONITORING_PROTOCOL		= 13,
	WEATHERINFO_PROTOCOL			= 14,
};

enum DEVICETYPE {

	DEVICE_DUMMY 					= 0,
	BOILER       						= 1,
	LIGHT		 					= 2,
	GAS			 					= 3,
	DOORLOCK     					= 4,
	CURTAIN      						= 5,
	CONSENT		 				= 6,
	AIRCON		 					= 7,
	BUNDLELIGHT					= 8,
	SYSTEMAIRCON 					= 9,
	FANCONTROLER 					= 10,
	RFMODULE     					= 11,
	READYPOWER	 				= 12,	
	ROOMAUTO	 					= 13,
	READYPOWERSWITCHOFFSWITCH 	= 14,
    	SMARTDOORPHONE				= 15,
   	SMARTMETERING					= 16,
	SMARTPLUG 						= 17,
	TECHLEDPANEL					= 18,
	ENERGYMONITORING				= 19,
	FCU								= 20,
	TIME							= 21,
	WEATHERINFO					= 22,
	
	//Z-Wave product
	MAGNETICSENSOR 				= 23,
	PIRSENSOR 						= 24,
	SMOKESENSOR 					= 25,
	FLOODSENSOR 					= 26,
	TEMPERATURESENSOR 			= 27,
	HUMIDITYSENSOR 				= 28,
};

// Ŭ���̾�Ʈ�� ó���� ����̽� ī�װ� ��û�� 
// Not Support Device�̸� ������ ���� �뺸�� �ֱ� ����

enum DEVICE_GENERAL_CONFIGURATION_ERROR {
	
	NOT_FOUND_DB_FILE = 1,
	NOT_DB_QUERY      = 2,	

};
 

#endif
