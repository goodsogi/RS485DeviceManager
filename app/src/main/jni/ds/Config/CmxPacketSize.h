

/******************************************************
  NAME     : PACKETSIZE.H
  Coded by : �� ����
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
	�������̽����� ���� �������� ���� ���̽�
*/

// Commax Protocol Buffer Size : 8
const unsigned int COMMAX_BUFFER_SIZE = 8;

// PLANET Protocol Buffer Size : �⺻ ���� ������(5) + ������ 1 ���۰� �߰���
const unsigned int PLANET_BUFFER_SIZE = 5;

// HAMUN : �ý��� ������ -> [�ص� ���꿡 ����ϱ� ���� �ӽ� ��ü -> ��ǰ�� ���� �ϰ� �ҵ� ���]
const unsigned int HAMUN_BUFFER_SIZE = 8;

// �Ｚ �ý��� ������

const unsigned int SAMSUNG_RECEIVE_BUFFER_SIZE = 32;
const unsigned int SAMSUNG_TRACKING_BUFFER_SIZE = 23;
const unsigned int SAMSUNG_QUERY_BUFFER_SIZE = 15;

// �Ｚ �ý��� ������ New Protocol
const unsigned int SAMSUNG_SYSTEMAIRCON_QUERY_BUFFER_SIZE  = 17;	
const unsigned int SAMSUNG_SYSTEMAIRCON_TRACKING_RECEIVE_BUFFER_SIZE_20H = 43;	
const unsigned int SAMSUNG_SYSTEMAIRCON_TRACKING_RECEIVE_BUFFER_SIZE_30H = 59;	
const unsigned int SAMSUNG_SYSTEMAIRCON_TRACKING_RECEIVE_BUFFER_SIZE_40H = 75;	
const unsigned int SAMSUNG_SYSTEMAIRCON_STATUS_RECEIVE_BUFFER_SIZE = 1024;	
const unsigned int SAMSUNG_SYSTEMAIRCON_CONTROL_RECEIVE_BUFFER_SIZE = 11;	
// LG �ý��� ������
const unsigned int LG_RECEIVE_BUFFER_SIZE = 16;
const unsigned int LG_QUERY_BUFFER_SIZE = 8;
const unsigned int LG_CONTROL_BUFFER_SIZE = 8;

// ����̿� RF ���
const unsigned int RFMODULE_BUFFER_SIZE = 24;

// ����Ʈ������
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

// ��ũ�� ������ : ������
const unsigned int LED_MESSAGE_MAX_LENGTH = 128;
const unsigned int LEDPANEL_BUFFER_SIZE = 11;
const unsigned int LEDPANEL_ECHO_BUFFER_SIZE = 11;
const unsigned int LEDPANEL_SCREEN_ON_OFF_BUFFER_SIZE = 15;
const unsigned int LEDPANEL_RECV_BUFFER_SIZE = 10;
const unsigned int LEDPANEL_SCREEN_VIEW_BUFFER_SIZE = 15;
const unsigned int LEDPANEL_IMAGE_BUFFER_SIZE = 8192;

// ������ ����͸�
const unsigned int ENERGYMONITORING_RECV_BUFFER_SIZE = 7;
const unsigned int ENERGYMONITORING_EACH_DATA_SEND_BUFFER_SIZE = 9;
const unsigned int ENERGYMONITORING_TOTAL_DATA_SEND_BUFFER_SIZE = 17;
const unsigned int ENERGYMONITORING_CATEGORY_DATA_SEND_BUFFER_SIZE = 15;
const unsigned int ENERGYMONITORING_SEND_MAX_BUFFER_SIZE = 17;

//���� ��Ȱ ������
const unsigned int WEATHERINFO_NORMAL_RECV_BUFFER_SIZE =  15;
const unsigned int WEATHERINFO_NORMAL_SEND_BUFFER_SIZE =  15;
const unsigned int WEATHERINFO_ETCINFO_RECV_BUFFER_SIZE =  9;
const unsigned int WEATHERINFO_TIME_SEND_BUFFER_SIZE =   16;
const unsigned int WEATHERINFO_WEATHER_SEND_BUFFER_SIZE =   16;
const unsigned int WEATHERINFO_PARKING_SEND_BUFFER_SIZE =   44;
const unsigned int WEATHERINFO_MAX_BUFFER_SIZE =   44;


/*************************************************************
	[ Commax RS485���� ������ �ִ� ����̽� ���� ]

	Commax Protocol : ���� 8��, ���� 2��, ���Ϸ� 8��, Ŀư 8��
	�ִ� ��� ������ ���۸� �����ϱ� ����
*/

// ���� ����̽�
const unsigned int COMMAX_MAX_INSTALLED_LIGHT = 24;

// ���� ����̽�
const unsigned int COMMAX_MAX_INSTALLED_GAS = 2;

// ���Ϸ� ����̽�
const unsigned int COMMAX_MAX_INSTALLED_BOILER = 8;
const unsigned int COMMAX_MAX_INSTALLED_GROUP_BOILER = 4;

// Ŀư ����̽�
const unsigned int COMMAX_MAX_INSTALLED_CURTAIN = 20;

// ����� ����̽�
const unsigned int COMMAX_MAX_INSTALLED_DOORLOCK = 2;

// �ϰ��ҵ� ����̽�
const unsigned int COMMAX_MAX_INSTALLED_BUNDLELIGHT = 8;

// ���� ȯ��
const unsigned int COMMAX_MAX_INSTALLED_FANCONTROLER = 8;

// ���� �ڵ�ȭ
const unsigned int COMMAX_MAX_INSTALLED_ROOMAUTO = 1;

// ������� ���ܽ���ġ
const unsigned int COMMAX_MAX_INSTALLED_READYPOWERSHOUTOFFSWITCH = 16;

// FAN COILT UNIT ����̽�
const unsigned int COMMAX_MAX_INSTALLED_FCU = 10;

//TIME
const unsigned int COMMAX_MAX_INSTALLED_TIME = 1;


/**************************************************************
		[  Ÿ�� �������� ] : ����̿� : RF MODULE

*/
const unsigned int COMMAX_MAX_INSTALLED_RFMODULE = 1;

/**************************************************************
		[  ����Ʈ������ �������� ] 

*/
const unsigned int COMMAX_MAX_INSTALLED_SMARTDOORPHONE = 1;
const unsigned int TECHNO_MAX_INSTALLED_SMARTDOORPHONE = 2;


/**************************************************************
	[ �÷��� ���� ����̽� ]

	����̽� ����̹� �Ŵ������� �ִ� ��� ������ ����̽� 

	����   : 24
	����   : 2
	���Ϸ� : 8
	Ŀư   : 8
	�ܼ�Ʈ : 3

*/

const unsigned int  MAX_MANAGER_LIGHT = 0x4F;
const unsigned int  MAX_MANAGER_GAS  = 2;
const unsigned int  MAX_MANAGER_BOILER = 8;
const unsigned int  MAX_MANAGER_CURTAIN = 20;
const unsigned int  MAX_MANAGER_CONSENT = 3;
const unsigned int  MAX_MANAGER_AIRCON = 1;


/**************************************************************
	[ �Ϲ� ���� ����̽� ]

	����̽� ����̹� �Ŵ������� �ִ� ��� ������ ����̽� 

	�ý��� ������   : 3


*/

const unsigned int  MAX_MANAGER_SYSTEMAIRCON = 3;

/************************************************************
  
  [ �Ϲ� ���� ����̽� ]

	����̽� ����̹� �Ŵ������� �ִ� ��� ������ ����̽� 

	�ý��� ������   : 10

*/
const unsigned int  MAX_MANAGER_GROUP_SAMSUNG_SYSTEM_AIRCON = 1;
const unsigned int  MAX_MANAGER_SAMSUNG_SYSTEM_AIRCON = 16;
const unsigned int  MAX_MANAGER_LG_SYSTEM_AIRCON = 11;

/************************************************************
  
  [ ����Ʈ������ ���� ����̽� ]

	����̽� ����̹� �Ŵ������� �ִ� ��� ������ ����̽� 

	�ý��� ������   : 10

*/
const unsigned int  MAX_MANAGER_SMARTDOORPHONE = 2;

/************************************************************
  
  [ HNA ����̽� ]

	����̽� ����̹� �Ŵ������� �ִ� ��� ������ ����̽� 

	����Ʈ ���͸�   : 1

*/

const unsigned int	MAX_MANAGER_HNA_SMARTMETERING = 2;


/************************************************************
  
  [ ������ ����̽� ]

	����̽� ����̹� �Ŵ������� �ִ� ��� ������ ����̽� 

	������ : ��ũ�� ������   : 1

*/
const unsigned int  MAX_MANAGER_LED_PANEL		    = 1;
const unsigned int  LED_PANEL_STATUS_PRESERVE_CNT = 2;


/************************************************************
  
  [ Z-Wave ����̽� ]

	����̽� ����̹� �Ŵ������� �ִ� ��� ������ ����̽� 

	����Ʈ �÷���   : 1
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
	�ڸƽ�, �÷��� ����̽� ���� ���� ���̺�
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

//���� : ȯ�� �ý���
const unsigned int FANCONTROLER_STATUS_PRESERVE_CNT = 10;

//���� �ڵ�ȭ
const unsigned int ROOMAUTO_STATUS_PRESERVE_CNT = 4;

//������� ���� ����ġ
const unsigned int READYPOWERSHOUTOFFSWITCH_STATUS_PRESERVE_CNT = 10;

// �ڸƽ� : �ý��� ������
const unsigned int COMMAX_MAX_INSTALLED_SYSTEM_AIRCON = 12;
const unsigned int COMMAX_SYSTEM_AIRCON_STATUS_PRESERVE_CNT = 6;

// HAMUN : �ý��� ������
const unsigned int SYSTEMAIRCON_STATUS_PRESERVE_CNT = 1;

// �Ｚ : �ý��� ������
const unsigned int SAMSUNG_SYSTEM_AIRCON_STATUS_PRESERVE_CNT = 13;

// �Ｚ : �ý��� ������
const unsigned int LG_SYSTEM_AIRCON_STATUS_PRESERVE_CNT = 8;

// �ڸƽ� : ����Ʈ������
const unsigned int SMARTDOORPHONE_STATUS_PRESERVE_CNT = 40;
const unsigned int TECHNO_SMARTDOORPHONE_STATUS_PRESERVE_CNT = 13;
const unsigned int TECHNO_SMARTDOORPHONE_EVENT_PRESERVE_CNT = 20;


//HNA : ����Ʈ���͸�
const unsigned int HNA_SMARTMETERING_STATUS_PRESERVE_CNT = 27;


/**************************************************************
  [ Ÿ�� �������� ] : ����̿� : RF MODULE ���� ���� ���̺�

*/
const unsigned int RFMODULE_STATUS_PRESERVE_CNT = 1;

/**************************************************************
	�̵���� ���񽺿��� ����̽� ī�װ���û�� ���� ������
	����̽��� �˱� ����. ���������� ����̽� ����

	����̽� ����̹� �Ŵ��� ���

	// 2007/04/07
	���� 7�� : ���Ϸ�, ����, ����, �����, AC Consent, Ŀư, ������

	// 2007/10/16
	���� 8�� : ���Ϸ�, ����, ����, �����, AC Consent, Ŀư, ������, �ϰ��ҵ�

	// 2007/10/24
	���� 9�� : ���Ϸ�, ����, ����, �����, AC Consent, Ŀư, ������, �ϰ��ҵ�, �ý��� ������, 

	// 2007/11/28
	���� 9�� : ���Ϸ�, ����, ����, �����, AC Consent, Ŀư, ������, �ϰ��ҵ�, �ý��� ������, ȯ�� �ý���

	// 2007/12/12 : RF Module�߰�
	���� 11�� : ���Ϸ�, ����, ����, �����, AC Consent, Ŀư, ������, �ϰ��ҵ�, �ý��� ������, ȯ�� �ý���, RF Module

	// 2011/05/25 : ������� �߰�
	���� 11�� : ���Ϸ�, ����, ����, �����, AC Consent, Ŀư, ������, �ϰ��ҵ�, �ý��� ������, ȯ�� �ý���, RF Module, �ϰ��ҵ�(�������)

	// 2011/11/23 : ���� �ڵ�ȭ
	���� 13�� : ���Ϸ�, ����, ����, �����, AC Consent, Ŀư, ������, �ϰ��ҵ�, �ý��� ������, ȯ�� �ý���, RF Module, �ϰ��ҵ�(�������), �����ڵ�ȭ

	// 2012/08/20 : ������� ���� ����ġ 
	���� 14�� : ���Ϸ�, ����, ����, �����, AC Consent, Ŀư, ������, �ϰ��ҵ�, �ý��� ������, ȯ�� �ý���, RF Module, �ϰ��ҵ�(�������), �����ڵ�ȭ, ������� ���� ����ġ 

	// 2013/04/30 : ����Ʈ������
	���� 15�� : ���Ϸ�, ����, ����, �����, AC Consent, Ŀư, ������, �ϰ��ҵ�, �ý��� ������, ȯ�� �ý���, RF Module, �ϰ��ҵ�(�������), �����ڵ�ȭ, ������� ���� ����ġ, ����Ʈ ������

	// 2014/11/17 : �ǽð����ݰ�ħ
	���� 16�� : ���Ϸ�, ����, ����, �����, AC Consent, Ŀư, ������, �ϰ��ҵ�, �ý��� ������, ȯ�� �ý���, RF Module, �ϰ��ҵ�(�������), �����ڵ�ȭ, ������� ���� ����ġ, ����Ʈ ������, �ǽð� ���ݰ�ħ

	// 2015/07/20 : LEDDISPLAY
	���� 17�� : ���Ϸ�, ����, ����, �����, AC Consent, Ŀư, ������, �ϰ��ҵ�, �ý��� ������, ȯ�� �ý���, RF Module, �ϰ��ҵ�(�������), �����ڵ�ȭ, ������� ���� ����ġ, ����Ʈ ������, �ǽð� ���ݰ�ħ, ������

	// 2015/10/16 : ENERGYMONITORING
	���� 18�� : ���Ϸ�, ����, ����, �����, AC Consent, Ŀư, ������, �ϰ��ҵ�, �ý��� ������, ȯ�� �ý���, RF Module, �ϰ��ҵ�(�������), �����ڵ�ȭ, ������� ���� ����ġ, ����Ʈ ������, �ǽð� ���ݰ�ħ, ������, ����������͸�

	// 2016/01/11 : FCU
	���� 19�� : ���Ϸ�, ����, ����, �����, AC Consent, Ŀư, ������, �ϰ��ҵ�, �ý��� ������, ȯ�� �ý���, RF Module, �ϰ��ҵ�(�������), �����ڵ�ȭ, ������� ���� ����ġ, ����Ʈ ������, �ǽð� ���ݰ�ħ, ������, ����������͸�, FCU

	// 2016/01/11 : TIME
	���� 20�� : ���Ϸ�, ����, ����, �����, AC Consent, Ŀư, ������, �ϰ��ҵ�, �ý��� ������, ȯ�� �ý���, RF Module, �ϰ��ҵ�(�������), �����ڵ�ȭ, ������� ���� ����ġ, ����Ʈ ������, �ǽð� ���ݰ�ħ, ������, ����������͸�, FCU, TIME

	// 2016/01/29 : ���� ��Ȱ ������	
	���� 21�� : ���Ϸ�, ����, ����, �����, AC Consent, Ŀư, ������, �ϰ��ҵ�, �ý��� ������, ȯ�� �ý���, RF Module, �ϰ��ҵ�(�������), �����ڵ�ȭ, ������� ���� ����ġ, ����Ʈ ������, �ǽð� ���ݰ�ħ, ������, ����������͸�, FCU, TIME, ���� ��Ȱ ������
*/

const unsigned int ALL_DEVICE_STATUS_COUNT = 21;


#endif

