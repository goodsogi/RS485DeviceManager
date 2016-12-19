package com.commax.devicemanager.sqlite;

import android.provider.BaseColumns;

/**
 * 디비 관련 상수(테이블명, 칼럼명 등)
 *
 * @author Jeonggyu Park
 */
public class DBConstants {
	
    public static class DeviceEntry implements BaseColumns {
        //같은 테이블 이름이 있으면 오류 발생
        public static final String TABLE_NAME = "deviceInfo";
        public static final String _ID = "_id";
        public static final String COLUMN_NAME_DEVICE_TYPE = "deviceType";
        public static final String COLUMN_NAME_DEVICE_NAME_FOR_DISPLAY = "deviceNameForDisplay";
        public static final String COLUMN_NAME_MAX_DEVICE_COUNT = "maxDeviceCount";
        public static final String COLUMN_NAME_PROTOCOL_1 = "protocol1";
        public static final String COLUMN_NAME_PROTOCOL_2 = "protocol2";
        public static final String COLUMN_NAME_PROTOCOL_3 = "protocol3";
        public static final String COLUMN_NAME_PROTOCOL_4 = "protocol4";
        public static final String COLUMN_NAME_REQUEST_1 = "request1";
        public static final String COLUMN_NAME_REQUEST_2 = "request2";
        public static final String COLUMN_NAME_REQUEST_3 = "request3";
        public static final String COLUMN_NAME_REQUEST_4 = "request4";
        public static final String COLUMN_NAME_RESPONSE_1 = "response1";
        public static final String COLUMN_NAME_RESPONSE_2 = "response2";
        public static final String COLUMN_NAME_RESPONSE_3 = "response3";
        public static final String COLUMN_NAME_RESPONSE_4 = "response4";
        public static final String COLUMN_NAME_PROTOCOL_COUNT = "protocolCount";


    }


    public static class ActiveDeviceEntry implements BaseColumns {
        public static final String TABLE_NAME = "deviceinfo";
        public static final String COLUMN_NAME_DEVICE_TYPE = "deviceType";
        public static final String COLUMN_NAME_PROTOCOL_COMPANY = "protocolCompany";
        public static final String COLUMN_NAME_DEVICE_COUNT = "deviceCount";
        public static final String COLUMN_NAME_UART_PORT = "UartPort";

    }

  
}
