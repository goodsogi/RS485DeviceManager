#include "util.h"
#include "wnamespace.h" //by kim
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h> // for va_list/va_end
#include <string.h>
/*
#include <qapplication.h> 
*/
unsigned int g_logType=0;

unsigned int FAKE_SMARTMETERING_ENABLE = 0;
unsigned int FAKE_READYPOWER_ENABLE = 0;
unsigned int FAKE_CURTAIN_ENABLE = 0;
unsigned int FAKE_SYSTEMAIRCON_ENABLE = 0;
unsigned int FAKE_FANSYSTEM_ENABLE = 0;
unsigned int FAKE_BUNDLELIGHT_ENABLE = 0;
unsigned int FAKE_BOILE_ENABLE = 0;
unsigned int FAKE_BOILE_ENABLE_EACH = 0;
unsigned int FAKE_GAS_ENABLE = 0;
unsigned int FAKE_LIGHT_ENABLE = 0;
unsigned int FAKE_LIGHT_ENABLE_DIMMING = 0;
unsigned int FAKE_FCU_ENABLE = 0;
unsigned int ZWAVE_ENABLE = 0;
unsigned int NAMYANGJU_BYULNAE = 0;
unsigned int POLLING_TIME	=	100000;
unsigned int LG_SYSTEMAIRCON_CONTROL_TIME = 200000;
unsigned int DEVICE_REALTIME_STATUS_CHECK = 0;
unsigned int ENERGYMONITORING_QUERY_TIME = 30;
unsigned int ENERGYMONITORING_RAND_SLEEP = 5;
char EMS_SERVER_IP[100] = {"http://10.0.0.2/ces/ces.php"};
char PARKING_SERVER_IP[100] = {"http://10.0.0.2/ces/ces.php"};
char WEATHER_SERVER_IP[100] = {"http://10.0.0.2/ces/ces.php"};
char ELEVATOR_SERVER_IP[100] = {"http://10.0.0.2:29715"};
char SMARTDOORPHONE_SERVER_IP[100] = {"http://10.0.0.2/ces/ces.php"};
char WALLPAD_IP[100] = {0, };
unsigned int LIMITED_SUBSCRIBE = 0;
unsigned int GET_THREEWAYSWITCH_ID_FROM_SERVER_FLAG = 0;

/*
	attribute
	00 - ¾øÀ½ 
	01 - ±½°Ô
	04 - ¹ØÁÙ
	05 - ±ôºý°Å¸²
	07 - ¹ÝÀü
	08 - ¼û±è
	
	colors
	30 - °ËÀº»ö
	31 - »¡°£»ö
	32 - ³ì»ö
	33 - ³ë¶û»ö
	34 - ÆÄ¶û»ö
	35 - ÀÚÈ«»ö
	36 - Ã»·Ï»ö
	37 - ÇÏ¾á»ö
	40 - °ËÁ¤»ö
	41 - »¡°£»ö
	42 - ³ì»ö
	43 - ³ë¶û»ö
	44 - ÆÄ¶û»ö
	45 - ÀÚÈ«»ö
	46 - Ã»³ì»ö
	47 - ÇÏ¾á»ö

*/
void Log(int nType, const char * s, ...) 
{
    va_list args;
	
	if((g_logType & Wall::LOG_ALL) != Wall::LOG_ALL)
	{
		if((g_logType & nType) != nType)
			return;

		if(nType == Wall::LOG_SEP)
		{
			fprintf(stderr, "***********************************************\n");
			return;
		}
	}

	va_start(args, s);

	switch(nType)
	{
		case Wall::LOG_ERR:  
			fprintf(stderr, "\033[01;31m"); 
			fprintf(stderr, "[X]Error: "); 
			break;
		
		case Wall::LOG_INF: 
			fprintf(stderr, "\033[01;37m"); 
			fprintf(stderr, "[O]Info: "); 
		break;
		case Wall::LOG_SRC: 
			fprintf(stderr, "\033[00;37m"); 
			fprintf(stderr, "[-]Source: "); 
		break;
		case Wall::LOG_VDP: 
			fprintf(stderr, "\033[01;33m"); 
			fprintf(stderr, "[*]VDP: "); 
		break;
		case Wall::LOG_UPNP: 
			fprintf(stderr, "\033[01;32m"); 
			fprintf(stderr, "[*]UPnP: "); 
		break;
		case Wall::LOG_TEST: 
			fprintf(stderr, "\033[01;35m"); 
			fprintf(stderr, "[*]Test: "); 
		break;
		case Wall::LOG_SHT: 
			fprintf(stderr, "\033[01;35m"); 
			fprintf(stderr, "[*]Temp&Humi: "); 
		break;
		/*
		case Wall::LOG_GUI: 
			fprintf(stderr, "\033[01;34m"); 
			fprintf(stderr, "[*]Gui: "); 
		break;
		
		case Wall::LOG_MSM: 
			fprintf(stderr, "\033[01;42m"); 
			fprintf(stderr, "[*]MSM7731: "); 
		break;
		*/
		case Wall::LOG_CON: 
			fprintf(stderr, "\033[01;37m"); 
			fprintf(stderr, "[*]Configure: "); 
		break;
		case Wall::LOG_APP: 
			fprintf(stderr, "\033[01;43m"); 
			fprintf(stderr, "[MAIN SERVICE]: "); 
		break;
		case Wall::LOG_FAT: 
			fprintf(stderr, "\033[01;31m"); 
			fprintf(stderr, "[*]FATAL: "); 
			//qFatal("");
		break;

		case Wall::LOG_LNCP: 
			fprintf(stderr, "\033[01;37m"); 
			fprintf(stderr, "[LG_LNCP]: "); 

		break;
		
		case Wall::LOG_Z256: 
			fprintf(stderr, "\033[01;37m"); 
			fprintf(stderr, "[PLANET_Z256]: "); 
			
		break;

		case Wall::LOG_RS485: 
			fprintf(stderr, "\033[01;37m"); 
			fprintf(stderr, "[COMMAX_DRIVER_RS485]: "); 
			
		break;
		
		case Wall::LOG_HAMUN: 
			fprintf(stderr, "\033[01;37m"); 
			fprintf(stderr, "[HAMUN DRIVER_RS485]: "); 
			
		break;

		case Wall::LOG_LG485: 
			fprintf(stderr, "\033[01;37m"); 
			fprintf(stderr, "[LG SYSTEM AIRCON DRIVER_RS485]: "); 
			
		break;

		case Wall::LOG_HNA: 
			fprintf(stderr, "\033[01;37m"); 
			fprintf(stderr, "[HNA DRIVER_RS485]: "); 
			
		break;
		
		case Wall::LOG_LED: 
			fprintf(stderr, "\033[01;37m"); 
			fprintf(stderr, "[TECHLED]: "); 
			
		break;

		case Wall::LOG_EMS: 
			fprintf(stderr, "\033[01;37m"); 
			fprintf(stderr, "[EMS]: "); 
			
		break;

		case Wall::LOG_WEATHER: 
			fprintf(stderr, "\033[01;37m"); 
			fprintf(stderr, "[WEATHER]: "); 
			
		break;			

		case Wall::LOG_RFM: 

			fprintf(stderr, "\033[01;34m"); 		
			fprintf(stderr, "[RF MODULE]: "); 
			
		break;

		case Wall::LOG_PRM: 
			fprintf(stderr, "\033[01;37m"); 
			fprintf(stderr, "[PACKET_ROUTER]: "); 
			
		break;

		case Wall::LOG_PCM: 
			fprintf(stderr, "\033[01;37m"); 
			fprintf(stderr, "[PACKET_CONVERTER]: "); 
			
		break;

		case Wall::LOG_MGR: 
			fprintf(stderr, "\033[01;37m"); 
			fprintf(stderr, "[DEVICE_DRIVER_MANAGER]: "); 
			
		break;

		case Wall::LOG_SOAP: 
			fprintf(stderr, "\033[01;36m"); 
			fprintf(stderr, "[SOAP_SERVICE]"); 
			
		break;

		case Wall::LOG_ZWAVE: 
			fprintf(stderr, "\033[01;35m"); 
			fprintf(stderr, "[ZWave_DRIVER]"); 
		break;

		case Wall::LOG_SEND: 
			fprintf(stderr, "\033[01;37m"); 
			fprintf(stderr, "[SEND DATA] : "); 
		break;
		
		case Wall::LOG_READ: 
			fprintf(stderr, "\033[00;37m"); 
			fprintf(stderr, "[READ DATA] : "); 
		break;		
		
	}


	vfprintf(stderr, s, args);
	fprintf(stderr, "\n");
	va_end(args);

	// ÀÌÀü »óÅÂ·Î º¹±¸
	fprintf(stderr, "\033[0m");
}

void debuglog_wr_frame(const char *str, unsigned char *buf, unsigned char buflen)
{
    /* Every byte in buf will be translated into 3 chars */
    char *framestr = new char[175*3];
    int n = 0;
    for (int i = 0; i < buflen; i++)
    {
        sprintf(&framestr[n], "%02X ", buf[i]);
        n += 3;
    }
    Log(Wall::LOG_MGR,"%s%s\n", str, framestr);
    delete framestr;
}