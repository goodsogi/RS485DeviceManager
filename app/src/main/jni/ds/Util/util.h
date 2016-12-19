#ifndef WALL_UTIL_H_BY_HSHAN
#define WALL_UTIL_H_BY_HSHAN
//#include "common.h" //by kim


extern unsigned int FAKE_SMARTMETERING_ENABLE;
extern unsigned int FAKE_READYPOWER_ENABLE;
extern unsigned int FAKE_CURTAIN_ENABLE;
extern unsigned int FAKE_SYSTEMAIRCON_ENABLE;
extern unsigned int FAKE_FANSYSTEM_ENABLE;
extern unsigned int FAKE_BUNDLELIGHT_ENABLE;
extern unsigned int FAKE_BOILE_ENABLE;
extern unsigned int FAKE_BOILE_ENABLE_EACH;
extern unsigned int FAKE_GAS_ENABLE;
extern unsigned int FAKE_LIGHT_ENABLE;
extern unsigned int FAKE_LIGHT_ENABLE_DIMMING;
extern unsigned int FAKE_FCU_ENABLE;
extern unsigned int POLLING_TIME;
extern unsigned int ZWAVE_ENABLE;
extern unsigned int NAMYANGJU_BYULNAE;
extern unsigned int LG_SYSTEMAIRCON_CONTROL_TIME;
extern unsigned int DEVICE_REALTIME_STATUS_CHECK;
extern unsigned int ENERGYMONITORING_QUERY_TIME;
extern unsigned int ENERGYMONITORING_RAND_SLEEP;
extern char EMS_SERVER_IP[100];
extern char WALLPAD_IP[100];
extern char PARKING_SERVER_IP[100];
extern char WEATHER_SERVER_IP[100];
extern char ELEVATOR_SERVER_IP[100];
extern char SMARTDOORPHONE_SERVER_IP[100];
extern unsigned int LIMITED_SUBSCRIBE;
extern unsigned int GET_THREEWAYSWITCH_ID_FROM_SERVER_FLAG;


extern unsigned int	g_logType;
extern void Log(int nType, const char * s, ...);
extern void debuglog_wr_frame(const char *str, unsigned char *buf, unsigned char buflen);

#endif //WALL_UTIL_H_BY_HSHAN

