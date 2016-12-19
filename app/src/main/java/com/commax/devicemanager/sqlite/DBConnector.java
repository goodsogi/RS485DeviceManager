package com.commax.devicemanager.sqlite;


import android.content.ContentValues;
import android.content.Context;
import android.database.Cursor;
import android.database.sqlite.SQLiteDatabase;
import android.util.Log;

import com.commax.devicemanager.DeviceManagerConstants;
import com.commax.devicemanager.devicesetting.DBFileManager;
import com.commax.devicemanager.sqlite.DBConstants.DeviceEntry;
import com.commax.devicemanager.sqlite.DBConstants.ActiveDeviceEntry;

import java.util.ArrayList;
import java.util.List;

/**
 * 디비 관리
 *
 * @author Jeonggyu Park
 */
public class DBConnector {

    //모든 디바이스 가져옴
    private static final String SQL_SELECT_ALL_DEVICE_DATA = "SELECT * FROM "
            + DeviceEntry.TABLE_NAME;

    //모든 스캔된 디바이스 가져옴
    private static final String SQL_SELECT_ALL_ACTIVE_DEVICE_DATA = "SELECT * FROM "
            + ActiveDeviceEntry.TABLE_NAME;

    //특정 디바이스 가져옴
    private static final String SQL_GET_SELECTED_ACTIVE_DEVICE_DATA = "SELECT * FROM "
            + ActiveDeviceEntry.TABLE_NAME
            + " WHERE "
            + ActiveDeviceEntry.COLUMN_NAME_DEVICE_TYPE
            + "=?";




    private SQLiteDatabase mDB;

    private static DBConnector mInstance;
    private String mDBName;
    private final Context mContext;


    private DBConnector(Context context, String dbName) {
        mContext = context;
        mDBName = dbName;

        DBHelper dbHelper = new DBHelper(context, dbName);
        mDB = dbHelper.getWritableDatabase();


        //위 방식대로 열어도 되고 아래 방식대로 열어도 됨!!
        //String path = "/user/app/bin/standard_ver2.0_template.db";
        //mDB = SQLiteDatabase.openDatabase(path, null, 0);
    }

    private void setNewDB(String dbName) {
        mDBName = dbName;

        DBHelper dbHelper = new DBHelper(mContext, dbName);
        mDB = dbHelper.getWritableDatabase();
    }


    public static DBConnector getInstance(Context context, String dbName) {

        if (mInstance == null) {
              mInstance = new DBConnector(context, dbName);
        }

        return mInstance;
    }

    /**
     * 스캔된 디바이스 데이터를 디비에 추가
     *
     * @param device 디바이스 데이터
     */
    public void addActiveDeviceDataInDB(ActiveDevice device) {
        if(mDBName.equals(DBFileManager.DB_NAME_ALL_DEVICE)) {
            disconnectDB();
            setNewDB(DBFileManager.DB_NAME_REMOTE);
        }


        if (hasActiveDeviceDataAlready(device)) {
            Log.d(DeviceManagerConstants.LOG_TAG_2, "hasActiveDeviceDataAlready");
            updateActiveDeviceCount(device);

           return;
        }


        ContentValues cv = new ContentValues();

        cv.put(ActiveDeviceEntry.COLUMN_NAME_DEVICE_TYPE, device.getDeviceType());
        cv.put(ActiveDeviceEntry.COLUMN_NAME_PROTOCOL_COMPANY, device.getProtocolCompany());
        cv.put(ActiveDeviceEntry.COLUMN_NAME_DEVICE_COUNT, device.getDeviceCount());
        cv.put(ActiveDeviceEntry.COLUMN_NAME_UART_PORT, device.getUartPort());


        long result = mDB.insert(ActiveDeviceEntry.TABLE_NAME, null, cv);

        Log.d(DeviceManagerConstants.LOG_TAG_2, "addActiveDeviceDataInDB");


    }

    /**
     * 디바이스 개수 하나 올림
     * @param device 디바이스
     */
    private void updateActiveDeviceCount(ActiveDevice device) {

        int deviceCount = getDeviceCount(device);
        deviceCount++;

        ContentValues values = new ContentValues();
        values.put(ActiveDeviceEntry.COLUMN_NAME_DEVICE_COUNT,String.valueOf(deviceCount));

        //디바이스 개수가 업데이트되는지 확인!!
        Log.d(DeviceManagerConstants.LOG_TAG, "device count: " + deviceCount);

        mDB.update(ActiveDeviceEntry.TABLE_NAME, values,ActiveDeviceEntry.COLUMN_NAME_DEVICE_TYPE + " = ? ",new String[]{ device.getDeviceType() });
    }

    /**
     * 기존 디바이스 개수 가져옴
     * @param device 디바이스
     * @return
     */
    private int getDeviceCount(ActiveDevice device) {
        Cursor c = null;

        c = mDB.rawQuery(
                SQL_GET_SELECTED_ACTIVE_DEVICE_DATA,
                new String[]{device.getDeviceType()});



        c.moveToFirst();

        String deviceCount = c.getString(c
                .getColumnIndex(ActiveDeviceEntry.COLUMN_NAME_DEVICE_COUNT));

        return Integer.parseInt(deviceCount);
    }

    /**
     * 디비와 연결 끊음
     */
    public void disconnectDB() {

        this.mDB.close();
        mInstance = null;
    }

    /**
     * 디비에서 모든 디바이스 데이터를 가져옴
     *
     * @return
     */
    public ArrayList<Device> getAllDeviceData() {

        Cursor cursor = mDB.rawQuery(SQL_SELECT_ALL_DEVICE_DATA, null);

        cursor.moveToFirst();

        ArrayList<Device> devices = new ArrayList<Device>();

        while (!cursor.isAfterLast()) {
            String deviceType = cursor.getString(cursor
                    .getColumnIndex(DeviceEntry.COLUMN_NAME_DEVICE_TYPE));
            String deviceNameForDisplay = cursor.getString(cursor
                    .getColumnIndex(DeviceEntry.COLUMN_NAME_DEVICE_NAME_FOR_DISPLAY));
            String maxDeviceCount = cursor.getString(cursor
                    .getColumnIndex(DeviceEntry.COLUMN_NAME_MAX_DEVICE_COUNT));
            String protocol1 = cursor.getString(cursor
                    .getColumnIndex(DeviceEntry.COLUMN_NAME_PROTOCOL_1));
            String protocol2 = cursor.getString(cursor
                    .getColumnIndex(DeviceEntry.COLUMN_NAME_PROTOCOL_2));
            String protocol3 = cursor.getString(cursor
                    .getColumnIndex(DeviceEntry.COLUMN_NAME_PROTOCOL_3));
            String protocol4 = cursor.getString(cursor
                    .getColumnIndex(DeviceEntry.COLUMN_NAME_PROTOCOL_4));
            String request1 = cursor.getString(cursor
                    .getColumnIndex(DeviceEntry.COLUMN_NAME_REQUEST_1));

            String request2 = cursor.getString(cursor
                    .getColumnIndex(DeviceEntry.COLUMN_NAME_REQUEST_2));
            String request3 = cursor.getString(cursor
                    .getColumnIndex(DeviceEntry.COLUMN_NAME_REQUEST_3));
            String request4 = cursor.getString(cursor
                    .getColumnIndex(DeviceEntry.COLUMN_NAME_REQUEST_4));
            String response1 = cursor.getString(cursor
                    .getColumnIndex(DeviceEntry.COLUMN_NAME_RESPONSE_1));
            String response2 = cursor.getString(cursor
                    .getColumnIndex(DeviceEntry.COLUMN_NAME_RESPONSE_2));
            String response3 = cursor.getString(cursor
                    .getColumnIndex(DeviceEntry.COLUMN_NAME_RESPONSE_3));
            String response4 = cursor.getString(cursor
                    .getColumnIndex(DeviceEntry.COLUMN_NAME_RESPONSE_4));

            String protocolCount = cursor.getString(cursor
                    .getColumnIndex(DeviceEntry.COLUMN_NAME_PROTOCOL_COUNT));

            Device device = new Device();

            device.setDeviceType(deviceType);
            device.setDeviceNameForDisplay(deviceNameForDisplay);
            device.setMaxDeviceCount(maxDeviceCount);
            device.setProtocol1(protocol1);
            device.setProtocol2(protocol2);
            device.setProtocol3(protocol3);
            device.setProtocol4(protocol4);
            device.setRequest1(request1);
            device.setRequest2(request2);
            device.setRequest3(request3);
            device.setRequest4(request4);
            device.setResponse1(response1);
            device.setResponse2(response2);
            device.setResponse3(response3);
            device.setResponse4(response4);
            device.setProtocolCount(protocolCount);

            devices.add(device);

            cursor.moveToNext();
        }
        cursor.close();


        return devices;

    }

    /**
     * 동일한 스캔된 디바이스 데이터가 디비에 이미 저장되어 있는지 체크
     *
     * @param device 디바이스 데이터
     * @return
     */
    public boolean hasActiveDeviceDataAlready(ActiveDevice device) {

        Cursor c = null;

        c = mDB.rawQuery(
                SQL_GET_SELECTED_ACTIVE_DEVICE_DATA,
                new String[]{device.getDeviceType()});


        boolean hasData = c.getCount() != 0;
        c.close();



        return hasData;
    }

    /**
     * 디비에 저장된 특정 스캔된 디바이스 데이터 제거
     */
    public void removeActiveDeviceDataInDB(ActiveDevice device) {

        mDB.delete(ActiveDeviceEntry.TABLE_NAME,
                ActiveDeviceEntry.COLUMN_NAME_DEVICE_TYPE + "=?" + " AND "
                        + ActiveDeviceEntry.COLUMN_NAME_PROTOCOL_COMPANY + "=?" + " AND "
                        + ActiveDeviceEntry.COLUMN_NAME_DEVICE_COUNT + "=?" + " AND "

                        + ActiveDeviceEntry.COLUMN_NAME_UART_PORT + "=?",
                new String[]{device.getDeviceType(), device.getProtocolCompany(), device.getDeviceCount(), device.getUartPort()});
    }

    /**
     * 디비에 저장된 모든 디바이스 데이터 제거
     */
    public void removeAllDeviceDataInDB() {
        mDB.delete(DeviceEntry.TABLE_NAME, null, null);

    }

    /**
     * 디비에 저장된 모든 스캔된 디바이스 데이터 제거
     */
    public void removeAllActiveDeviceDataInDB() {
        mDB.delete(ActiveDeviceEntry.TABLE_NAME, null, null);

    }

    /**
     * 모든 스캔된 디바이스 가져옴
     * @return
     */
    public List<ActiveDevice> getAllActiveDeviceData() {

        if(mDBName.equals(DBFileManager.DB_NAME_ALL_DEVICE)) {
            disconnectDB();
            setNewDB(DBFileManager.DB_NAME_REMOTE);
        }


        Cursor cursor = mDB.rawQuery(SQL_SELECT_ALL_ACTIVE_DEVICE_DATA, null);

        cursor.moveToFirst();

        ArrayList<ActiveDevice> devices = new ArrayList<ActiveDevice>();

        while (!cursor.isAfterLast()) {
            String deviceType = cursor.getString(cursor
                    .getColumnIndex(ActiveDeviceEntry.COLUMN_NAME_DEVICE_TYPE));

            String deviceCount = cursor.getString(cursor
                    .getColumnIndex(ActiveDeviceEntry.COLUMN_NAME_DEVICE_COUNT));
            String protocolCompany = cursor.getString(cursor
                    .getColumnIndex(ActiveDeviceEntry.COLUMN_NAME_PROTOCOL_COMPANY));
            String UartPort = cursor.getString(cursor
                    .getColumnIndex(ActiveDeviceEntry.COLUMN_NAME_UART_PORT));


            ActiveDevice device = new ActiveDevice();

            device.setDeviceType(deviceType);
            device.setDeviceCount(deviceCount);
            device.setProtocolCompany(protocolCompany);
            device.setUartPort(UartPort);

            devices.add(device);

            cursor.moveToNext();
        }
        cursor.close();


        return devices;
    }
}