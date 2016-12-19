

/******************************************************
  NAME     : PACKETSIZE.H
  Coded by : 김 광기
  Revision : 1.0
  Date     : 2007/02/07 ~

*/

#ifndef __CMXPACKETSIZE_H__
#define __CMXPACKETSIZE_H__

#define REQUESTING_START 1
#define REQUESTING_STOP  0


#define SUCCESS 1
#define FAIL 0

#define TRUE 1
#define FALSE 0

const int HEADER_SIZE = 2;

/************************************************************
	인터페이스에서 읽을 프로토콜 버퍼 사이스
*/

// Commax Protocol Buffer Size : 8
const unsigned int COMMAX_BUFFER_SIZE = 8;

// PLANET Protocol Buffer Size : 기본 버퍼 사이즈(5) + 가스는 1 버퍼가 추가됨
const unsigned int PLANET_BUFFER_SIZE = 5;

// HAMUN : 시스템 에어컨 -> [극동 생산에 사용하기 위해 임시 대체 -> 제품이 없어 일괄 소등 사용]
const unsigned int HAMUN_BUFFER_SIZE = 8;

// 삼성 시스템 에어컨

const unsigned int SAMSUNG_RECEIVE_BUFFER_SIZE = 32;
const unsigned int SAMSUNG_TRACKING_BUFFER_SIZE = 23;
const unsigned int SAMSUNG_QUERY_BUFFER_SIZE = 15;

// 삼성 시스템 에어컨 New Protocol
const unsigned int SAMSUNG_SYSTEMAIRCON_QUERY_BUFFER_SIZE  = 17;	
const unsigned int SAMSUNG_SYSTEMAIRCON_TRACKING_RECEIVE_BUFFER_SIZE_20H = 43;	
const unsigned int SAMSUNG_SYSTEMAIRCON_TRACKING_RECEIVE_BUFFER_SIZE_30H = 59;	
const unsigned int SAMSUNG_SYSTEMAIRCON_TRACKING_RECEIVE_BUFFER_SIZE_40H = 75;	
const unsigned int SAMSUNG_SYSTEMAIRCON_STATUS_RECEIVE_BUFFER_SIZE = 1024;	
const unsigned int SAMSUNG_SYSTEMAIRCON_CONTROL_RECEIVE_BUFFER_SIZE = 11;	
// LG 시스템 에어컨
const unsigned int LG_RECEIVE_BUFFER_SIZE = 16;
const unsigned int LG_QUERY_BUFFER_SIZE = 8;
const unsigned int LG_CONTROL_BUFFER_SIZE = 8;

// 고아이엠 RF 모듈
const unsigned int RFMODULE_BUFFER_SIZE = 24;

// 스마트도어폰
const unsigned int SMARTDOORPHONE_BUFFER_SIZE = 140;
const unsigned int SMARTDOORPHONE_STATUS_BUFFER_SIZE = 5;
 
const unsigned int TECHNO_SMARTDOORPHONE_BUFFER_SIZE = 16;
const unsigned int TECHNO_SMARTDOORPHONE_MESSAGE_BUFFER_SIZE = 512;
const unsigned int TECHNO_SMARTDOORPHONE_ONEPANSS_BUFFER_SIZE = 256;
const unsigned int TECHNO_SMARTDOORPHONE_MAX_CONTROL_BUFFER_SIZE = 512;
const unsigned int TECHNO_SMARTDOORPHONE_MAX_RECEIVE_BUFFER_SIZE = 256;

// HNA 
const unsigned int HNA_BUFFER_SIZE = 512;
const unsigned int HNA_SEND_BUFFER_SIZE = 7;
const unsigned int HNA_SMARTMETER_EACH_RECEIVE_BUFFER_SIZE = 13;
const unsigned int HNA_SMARTMETER_TOTAL_RECEIVE_BUFFER_SIZE = 32;
const unsigned int HNA_SMARTMETER_PROPERTY_RECEIVE_BUFFER_SIZE = 9;

// 테크노 빌리지 : 전광관
const unsigned int LED_MESSAGE_MAX_LENGTH = 128;
const unsigned int LEDPANEL_BUFFER_SIZE = 11;
const unsigned int LEDPANEL_ECHO_BUFFER_SIZE = 11;
const unsigned int LEDPANEL_SCREEN_ON_OFF_BUFFER_SIZE = 15;
const unsigned int LEDPANEL_RECV_BUFFER_SIZE = 10;
const unsigned int LEDPANEL_SCREEN_VIEW_BUFFER_SIZE = 15;
const unsigned int LEDPANEL_IMAGE_BUFFER_SIZE = 8192;

// 에너지 모니터링
const unsigned int ENERGYMONITORING_RECV_BUFFER_SIZE = 7;
const unsigned int ENERGYMONITORING_EACH_DATA_SEND_BUFFER_SIZE = 9;
const unsigned int ENERGYMONITORING_TOTAL_DATA_SEND_BUFFER_SIZE = 17;
const unsigned int ENERGYMONITORING_CATEGORY_DATA_SEND_BUFFER_SIZE = 15;
const unsigned int ENERGYMONITORING_SEND_MAX_BUFFER_SIZE = 17;

//날씨 생활 정보기
const unsigned int WEATHERINFO_NORMAL_RECV_BUFFER_SIZE =  15;
const unsigned int WEATHERINFO_NORMAL_SEND_BUFFER_SIZE =  15;
const unsigned int WEATHERINFO_ETCINFO_RECV_BUFFER_SIZE =  9;
const unsigned int WEATHERINFO_TIME_SEND_BUFFER_SIZE =   16;
const unsigned int WEATHERINFO_WEATHER_SEND_BUFFER_SIZE =   16;
const unsigned int WEATHERINFO_PARKING_SEND_BUFFER_SIZE =   44;
const unsigned int WEATHERINFO_MAX_BUFFER_SIZE =   44;


/*************************************************************
	[ Commax RS485지원 가능한 최대 디바이스 개수 ]

	Commax Protocol : 조명 8개, 가스 2개, 보일러 8개, 커튼 8개
	최대 허용 가능한 버퍼를 유지하기 위함
*/

// 조명 디바이스
const unsigned int COMMAX_MAX_INSTALLED_LIGHT = 24;

// 가스 디바이스
const unsigned int COMMAX_MAX_INSTALLED_GAS = 2;

// 보일러 디바이스
const unsigned int COMMAX_MAX_INSTALLED_BOILER = 8;
const unsigned int COMMAX_MAX_INSTALLED_GROUP_BOILER = 4;

// 커튼 디바이스
const unsigned int COMMAX_MAX_INSTALLED_CURTAIN = 20;

// 도어락 디바이스
const unsigned int COMMAX_MAX_INSTALLED_DOORLOCK = 2;

// 일괄소등 디바이스
const unsigned int COMMAX_MAX_INSTALLED_BUNDLELIGHT = 8;

// 코콤 환기
const unsigned int COMMAX_MAX_INSTALLED_FANCONTROLER = 8;

// 객실 자동화
const unsigned int COMMAX_MAX_INSTALLED_ROOMAUTO = 1;

// 대기전력 차단스위치
const unsigned int COMMAX_MAX_INSTALLED_READYPOWERSHOUTOFFSWITCH = 16;

// FAN COILT UNIT 디바이스
const unsigned int COMMAX_MAX_INSTALLED_FCU = 10;

//TIME
const unsigned int COMMAX_MAX_INSTALLED_TIME = 1;


/**************************************************************
		[  타사 프로토콜 ] : 고아이엠 : RF MODULE

*/
const unsigned int COMMAX_MAX_INSTALLED_RFMODULE = 1;

/**************************************************************
		[  스마트도어폰 프로토콜 ] 

*/
const unsigned int COMMAX_MAX_INSTALLED_SMARTDOORPHONE = 1;
const unsigned int TECHNO_MAX_INSTALLED_SMARTDOORPHONE = 2;


/**************************************************************
	[ 플레넷 지원 디바이스 ]

	디바이스 드라이버 매니저에서 최대 허용 가능한 디바이스 

	조명   : 24
	가스   : 2
	보일러 : 8
	커튼   : 8
	콘센트 : 3

*/

const unsigned int  MAX_MANAGER_LIGHT = 0x4F;
const unsigned int  MAX_MANAGER_GAS  = 2;
const unsigned int  MAX_MANAGER_BOILER = 8;
const unsigned int  MAX_MANAGER_CURTAIN = 20;
const unsigned int  MAX_MANAGER_CONSENT = 3;
const unsigned int  MAX_MANAGER_AIRCON = 1;


/**************************************************************
	[ 하문 지원 디바이스 ]

	디바이스 드라이버 매니저에서 최대 허용 가능한 디바이스 

	시스템 에어컨   : 3


*/

const unsigned int  MAX_MANAGER_SYSTEMAIRCON = 3;

/************************************************************
  
  [ 하문 지원 디바이스 ]

	디바이스 드라이버 매니저에서 최대 허용 가능한 디바이스 

	시스템 에어컨   : 10

*/
const unsigned int  MAX_MANAGER_GROUP_SAMSUNG_SYSTEM_AIRCON = 1;
const unsigned int  MAX_MANAGER_SAMSUNG_SYSTEM_AIRCON = 16;
const unsigned int  MAX_MANAGER_LG_SYSTEM_AIRCON = 11;

/************************************************************
  
  [ 스마트도어폰 지원 디바이스 ]

	디바이스 드라이버 매니저에서 최대 허용 가능한 디바이스 

	시스템 에어컨   : 10

*/
const unsigned int  MAX_MANAGER_SMARTDOORPHONE = 2;

/************************************************************
  
  [ HNA 디바이스 ]

	디바이스 드라이버 매니저에서 최대 허용 가능한 디바이스 

	스마트 미터링   : 1

*/

const unsigned int	MAX_MANAGER_HNA_SMARTMETERING = 2;


/************************************************************
  
  [ 전광판 디바이스 ]

	디바이스 드라이버 매니저에서 최대 허용 가능한 디바이스 

	전광판 : 테크노 빌리지   : 1

*/
const unsigned int  MAX_MANAGER_LED_PANEL		    = 1;
const unsigned int  LED_PANEL_STATUS_PRESERVE_CNT = 2;


/************************************************************
  
  [ Z-Wave 디바이스 ]

	디바이스 드라이버 매니저에서 최대 허용 가능한 디바이스 

	스마트 플러그   : 1
	Magnetic Sensor : 1
	PIR Sensor : 1
	Smoke Sensor : 1
	Flood Sensor : 1
	Temperature Sensor : 1
	Humidity Sensor : 1
	
*/

const unsigned int	MAX_MANAGER_ZWAZE_SMARTPLUG 			= 2;
const unsigned int	MAX_MANAGER_ZWAZE_MAGNETICSENSOR 		= 2;
const unsigned int	MAX_MANAGER_ZWAZE_PIRSENSOR 			= 2;
const unsigned int	MAX_MANAGER_ZWAZE_SMOKESENSOR 		= 2;
const unsigned int	MAX_MANAGER_ZWAZE_FLOODSENSOR 		= 2;
const unsigned int	MAX_MANAGER_ZWAZE_TEMPERATURESENSOR	= 2;
const unsigned int	MAX_MANAGER_ZWAZE_HUMIDITYSENSOR 		= 2;

const unsigned int ZWAVE_SMARTPLUG_STATUS_PRESERVE_CNT = 3;
const unsigned int ZWAVE_MAGNETICSENSOR_STATUS_PRESERVE_CNT = 2;
const unsigned int ZWAVE_PIRSENSOR_STATUS_PRESERVE_CNT = 2;
const unsigned int ZWAVE_SMOKESENSOR_STATUS_PRESERVE_CNT = 2;
const unsigned int ZWAVE_FLOODSENSOR_STATUS_PRESERVE_CNT = 2;
const unsigned int ZWAVE_TEMPERATURESENSOR_STATUS_PRESERVE_CNT = 2;
const unsigned int ZWAVE_HUMIDITY_STATUS_PRESERVE_CNT = 2;



/****************************************************************
	코맥스, 플래넷 디바이스 상태 유지 테이블
*/

const unsigned int LIGHT_STATUS_PRESERVE_CNT = 6;
const unsigned int GAS_STATUS_PRESERVE_CNT = 2;
const unsigned int BOILER_STATUS_PRESERVE_CNT = 6;
const unsigned int CURTAIN_STATUS_PRESERVE_CNT = 2;
const unsigned int DOORLOCK_STATUS_PRESERVE_CNT = 7;
const unsigned int BUNDLELIGHT_STATUS_PRESERVE_CNT = 3;
const unsigned int BUNDLELIGHT_PROPERTY_PRESERVE_CNT = 6;
const unsigned int CONSENT_STATUS_PRESERVE_CNT = 2;
const unsigned int AIRCON_STATUS_PRESERVE_CNT = 5;
const unsigned int FCU_STATUS_PRESERVE_CNT = 8;
const unsigned int TIME_STATUS_PRESERVE_CNT = 1;

//코콤 : 환기 시스템
const unsigned int FANCONTROLER_STATUS_PRESERVE_CNT = 10;

//객실 자동화
const unsigned int ROOMAUTO_STATUS_PRESERVE_CNT = 4;

//대기전력 차단 스위치
const unsigned int READYPOWERSHOUTOFFSWITCH_STATUS_PRESERVE_CNT = 10;

// 코맥스 : 시스템 에어컨
const unsigned int COMMAX_MAX_INSTALLED_SYSTEM_AIRCON = 12;
const unsigned int COMMAX_SYSTEM_AIRCON_STATUS_PRESERVE_CNT = 6;

// HAMUN : 시스템 에어컨
const unsigned int SYSTEMAIRCON_STATUS_PRESERVE_CNT = 1;

// 삼성 : 시스템 에어컨
const unsigned int SAMSUNG_SYSTEM_AIRCON_STATUS_PRESERVE_CNT = 13;

// 삼성 : 시스템 에어컨
const unsigned int LG_SYSTEM_AIRCON_STATUS_PRESERVE_CNT = 8;

// 코맥스 : 스마트도어폰
const unsigned int SMARTDOORPHONE_STATUS_PRESERVE_CNT = 40;
const unsigned int TECHNO_SMARTDOORPHONE_STATUS_PRESERVE_CNT = 13;
const unsigned int TECHNO_SMARTDOORPHONE_EVENT_PRESERVE_CNT = 20;


//HNA : 스마트미터링
const unsigned int HNA_SMARTMETERING_STATUS_PRESERVE_CNT = 27;


/**************************************************************
  [ 타사 프로토콜 ] : 고아이엠 : RF MODULE 상태 유지 테이블

*/
const unsigned int RFMODULE_STATUS_PRESERVE_CNT = 1;

/**************************************************************
	미들웨어 서비스에서 디바이스 카테고리요청시 지원 가능한
	디바이스를 알기 위함. 지원가능한 디바이스 개수

	디바이스 드라이버 매니저 사용

	// 2007/04/07
	현재 7개 : 보일러, 조명, 가스, 도어락, AC Consent, 커튼, 에어컨

	// 2007/10/16
	현재 8개 : 보일러, 조명, 가스, 도어락, AC Consent, 커튼, 에어컨, 일괄소등

	// 2007/10/24
	현재 9개 : 보일러, 조명, 가스, 도어락, AC Consent, 커튼, 에어컨, 일괄소등, 시스템 에어컨, 

	// 2007/11/28
	현재 9개 : 보일러, 조명, 가스, 도어락, AC Consent, 커튼, 에어컨, 일괄소등, 시스템 에어컨, 환기 시스템

	// 2007/12/12 : RF Module추가
	현재 11개 : 보일러, 조명, 가스, 도어락, AC Consent, 커튼, 에어컨, 일괄소등, 시스템 에어컨, 환기 시스템, RF Module

	// 2011/05/25 : 대기전력 추가
	현재 11개 : 보일러, 조명, 가스, 도어락, AC Consent, 커튼, 에어컨, 일괄소등, 시스템 에어컨, 환기 시스템, RF Module, 일괄소등(대기전력)

	// 2011/11/23 : 객실 자동화
	현재 13개 : 보일러, 조명, 가스, 도어락, AC Consent, 커튼, 에어컨, 일괄소등, 시스템 에어컨, 환기 시스템, RF Module, 일괄소등(대기전력), 객실자동화

	// 2012/08/20 : 대기전력 차단 스위치 
	현재 14개 : 보일러, 조명, 가스, 도어락, AC Consent, 커튼, 에어컨, 일괄소등, 시스템 에어컨, 환기 시스템, RF Module, 일괄소등(대기전력), 객실자동화, 대기전력 차단 스위치 

	// 2013/04/30 : 스마트도어폰
	현재 15개 : 보일러, 조명, 가스, 도어락, AC Consent, 커튼, 에어컨, 일괄소등, 시스템 에어컨, 환기 시스템, RF Module, 일괄소등(대기전력), 객실자동화, 대기전력 차단 스위치, 스마트 도어폰

	// 2014/11/17 : 실시간원격검침
	현재 16개 : 보일러, 조명, 가스, 도어락, AC Consent, 커튼, 에어컨, 일괄소등, 시스템 에어컨, 환기 시스템, RF Module, 일괄소등(대기전력), 객실자동화, 대기전력 차단 스위치, 스마트 도어폰, 실시간 원격검침

	// 2015/07/20 : LEDDISPLAY
	현재 17개 : 보일러, 조명, 가스, 도어락, AC Consent, 커튼, 에어컨, 일괄소등, 시스템 에어컨, 환기 시스템, RF Module, 일괄소등(대기전력), 객실자동화, 대기전력 차단 스위치, 스마트 도어폰, 실시간 원격검침, 전광판

	// 2015/10/16 : ENERGYMONITORING
	현재 18개 : 보일러, 조명, 가스, 도어락, AC Consent, 커튼, 에어컨, 일괄소등, 시스템 에어컨, 환기 시스템, RF Module, 일괄소등(대기전력), 객실자동화, 대기전력 차단 스위치, 스마트 도어폰, 실시간 원격검침, 전광판, 에너지모니터링

	// 2016/01/11 : FCU
	현재 19개 : 보일러, 조명, 가스, 도어락, AC Consent, 커튼, 에어컨, 일괄소등, 시스템 에어컨, 환기 시스템, RF Module, 일괄소등(대기전력), 객실자동화, 대기전력 차단 스위치, 스마트 도어폰, 실시간 원격검침, 전광판, 에너지모니터링, FCU

	// 2016/01/11 : TIME
	현재 20개 : 보일러, 조명, 가스, 도어락, AC Consent, 커튼, 에어컨, 일괄소등, 시스템 에어컨, 환기 시스템, RF Module, 일괄소등(대기전력), 객실자동화, 대기전력 차단 스위치, 스마트 도어폰, 실시간 원격검침, 전광판, 에너지모니터링, FCU, TIME

	// 2016/01/29 : 날씨 생활 정보기	
	현재 21개 : 보일러, 조명, 가스, 도어락, AC Consent, 커튼, 에어컨, 일괄소등, 시스템 에어컨, 환기 시스템, RF Module, 일괄소등(대기전력), 객실자동화, 대기전력 차단 스위치, 스마트 도어폰, 실시간 원격검침, 전광판, 에너지모니터링, FCU, TIME, 날씨 생활 정보기
*/

const unsigned int ALL_DEVICE_STATUS_COUNT = 21;


#endif

