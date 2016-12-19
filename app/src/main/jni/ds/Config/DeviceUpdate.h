



#include <stdio.h>
#include <string.h>
#include <errno.h>

#include <sys/types.h>
#include <sys/ipc.h>
//#include <sys/msg.h>

#define DEVCIEINFO_BUFFER 256

enum INSTALL_DB_SETTING_TYPE
{

	CONFIG_TYPE_DUMMY    					= 0,
	CONFIG_INSERT   						= 1,
	CONFIG_UPDATE   						= 2,
	CONFIG_DELETE	 						= 3,	
	
	CONFIG_DEVICE_SETTING_REQ 			= 4,
	CONFIG_DEVICE_SETTING_RES 			= 5,

	CONFIG_DEVICE_SETTING_INFO_REQ 		= 6,
	CONFIG_DEVICE_SETTING_INFO_RES 		= 7
};

enum INSTALL_DEVICE_NAME
{

	CONFIG_NAME_DUMMY   						= 0,
	CONFIG_BOILER								= 1,
	CONFIG_LIGHT		 						= 2,
	CONFIG_GAS		     							= 3,
	CONFIG_DOORLOCK		 					= 4,
	CONFIG_CONSENT       						= 5,
	CONFIG_CURTAIN		 					= 6,	
	CONFIG_AIRCON        							= 7,
	CONFIG_BUNDLELIGHT   						= 8,
	CONFIG_SYSTEMAIRCON  						= 9,
	CONFIG_FANCONTROLER  						= 10,
	CONFIG_RFMODULE		 					= 11,
	CONFIG_ROOMAUTO		 					= 12,
	CONFIG_READYPOWERSHOUTOFFSWITCH		= 13,
	CONFIG_SMARTDOORPHONE					= 14,
	CONFIG_HNA_SMARTMETERING				= 15,
	CONFIG_LEDPANEL      						= 16,
	CONFIG_ENERGYMONITORING					= 17,
	CONFIG_FCU									= 18,
	CONFIG_TIME								= 19,
	CONFIG_WEATHERINFO						= 20,
	CONFIG_TECHNO_SMARTDOORPHONE			= 21,
};

enum INSTALL_DEVICE_PROTOCOL
{

	CONFIG_PROTOCOL_DUMMY    	= 0,
	CONFIG_COMMAX   			= 1,
	CONFIG_PLANET  		 	= 2,
	CONFIG_LNCP	 			= 3,
	CONFIG_SAMSUNG 			= 4,
	CONFIG_GOIM 				= 5,
	CONFIG_LG 					= 6,
	CONFIG_HNA				= 7,
	CONFIG_TECHNO   			= 8,
	CONFIG_UKOSTEC			= 9,
};



enum INSTALL_DEVICE_SETTING
{

	CONFIG_SETTING_DUMMY    	= 0,
	CONFIG_PLC_PLANET   		= 1,
	CONFIG_PLC_LNCP    			= 2,
	CONFIG_PLC_MAT	     		= 3,
	CONFIG_GOIM_RF      			= 4
	
};



typedef struct
{

	long int msgType;	

	enum INSTALL_DB_SETTING_TYPE idst;

	enum INSTALL_DEVICE_NAME idn;
	enum INSTALL_DEVICE_PROTOCOL idp;
	enum INSTALL_DEVICE_SETTING ids;
	char deviceInfo[DEVCIEINFO_BUFFER];
	int deviceCount;


}Install_Device_Info;


