package com.commax.devicemanager.devicesetting;

import android.content.Context;
import android.util.Log;

import com.commax.devicemanager.DeviceManagerConstants;
import com.commax.devicemanager.sqlite.ActiveDevice;
import com.commax.devicemanager.sqlite.DBConnector;
import com.commax.devicemanager.sqlite.DBConstants;
import com.commax.devicemanager.sqlite.Device;
import com.commax.devicemanager.util.ProgressDialogManager;

import java.util.ArrayList;
import java.util.Stack;

/**
 * 유선 디바이스 스캔 관리
 * Created by bagjeong-gyu on 2016. 8. 30..
 */
public class DeviceScanner {

    private static DeviceScanner instance;
    private final Context mContext;
    private DeviceForScan mDeviceForScan;


    private boolean mIsPort3Initialized;
    private boolean mIsPort4Initialized;


    private String mActivePort;

    private final String PORT_NO_THREE = "ttyS3";
    private final String PORT_NO_FOUR = "ttyS4";
    private ArrayList<Device> mAllDevices;
   

    private DeviceScanner(Context context) {
      JNIManager.setContext(context);
      mContext = context;
      initPortNo();
    }


    private void initPortNo() {

        mIsPort3Initialized = false;
        mIsPort4Initialized = false;
    }

    public static DeviceScanner getInstance(Context context) {

        if (instance == null) {
            instance = new DeviceScanner(context);
        }
        return instance;
    }


    private Stack<DeviceForScan> mDevicesForPort3;
    private Stack<DeviceForScan> mDevicesForPort4;

    public void setDevices(ArrayList<Device> devices) {

        mAllDevices = devices;
        mDevicesForPort3 = new Stack<DeviceForScan>();
        mDevicesForPort4 = new Stack<DeviceForScan>();

        for (Device device : devices) {

            int maxDeviceCount = Integer.parseInt(device.getMaxDeviceCount());
            int protocolCount = Integer.parseInt(device.getProtocolCount());

            for (int i = 0; i < maxDeviceCount; i++) {

                for (int j = 0; j < protocolCount; j++) {

                    //Log.d(DeviceManagerConstants.LOG_TAG, "i: " + i + "j: " + j);
                    DeviceForScan deviceForScan = new DeviceForScan();
                    deviceForScan.setDeviceType(device.getDeviceType());
                    deviceForScan.setDeviceNo(String.valueOf(i + 1));
                    deviceForScan.setDeviceNameForDisplay(device.getDeviceNameForDisplay());
                    deviceForScan.setProtocol(getDeviceProtocol(device, j));
                    deviceForScan.setRequest(getRequest(device, j));
                    deviceForScan.setResponse(getResponse(device, j));


                    mDevicesForPort3.push(deviceForScan);
                    mDevicesForPort4.push(deviceForScan);
                }

            }

        }

//        while (!mDevicesForPort3.isEmpty()) {
//            DeviceForScan deviceForScan = mDevicesForPort3.pop();
//
//
//            Log.d(DeviceManagerConstants.LOG_TAG, deviceForScan.getDevice());
//            Log.d(DeviceManagerConstants.LOG_TAG, deviceForScan.getDeviceNo());
//            if (deviceForScan.getRequest() != null) {
//                Log.d(DeviceManagerConstants.LOG_TAG, deviceForScan.getRequest());
//            }
//
//
//        }


    }

    private static String getResponse(Device device, int protocolNo) {

        switch (protocolNo) {
            case 0:
                return device.getResponse1();

            case 1:
                return device.getResponse2();

            case 2:
                return device.getResponse3();

            case 3:
                return device.getResponse4();

        }

        return null;
    }

    private static String getRequest(Device device, int protocolNo) {

        switch (protocolNo) {
            case 0:
                return device.getRequest1();

            case 1:
                return device.getRequest2();

            case 2:
                return device.getRequest3();

            case 3:
                return device.getRequest4();

        }
        return null;
    }

    private static String getDeviceProtocol(Device device, int protocolNo) {
        switch (protocolNo) {
            case 0:
                return device.getProtocol1();

            case 1:
                return device.getProtocol2();

            case 2:
                return device.getProtocol3();

            case 3:
                return device.getProtocol4();

        }
        return null;

    }

    public void scanDevice() {



        Log.d(DeviceManagerConstants.LOG_TAG, "scanDevice");
        if(mDevicesForPort3.isEmpty() && mDevicesForPort4.isEmpty()) {
            Log.d(DeviceManagerConstants.LOG_TAG, "디바이스 스캔 끝!!");
            //디바이스 스캔 종료 처리!!
            //스캔된 디바이스 db 파일 복사 처리!!
            handleDeviceScanCompleted();





        } else if (mDevicesForPort3.isEmpty()) {
            Log.d(DeviceManagerConstants.LOG_TAG, "mDevicesForPort3 스캔 끝!!");
            scanDeviceOnPort4();
        } else {
            scanDeviceOnPort3();
        }



    }

    private void handleDeviceScanCompleted() {
        
        try {
            ((DeviceScanListener) mContext).onDeviceScanCompleted();
        } catch (ClassCastException e) {
            Log.d(DeviceManagerConstants.LOG_TAG, "DeviceScanListener ClassCastException: " + e.getMessage());
        }
       
    }

    private void scanDeviceOnPort3() {

        if(!mIsPort3Initialized) {
            mIsPort3Initialized = true;
            mActivePort = PORT_NO_THREE;
            Log.d(DeviceManagerConstants.LOG_TAG, "JNIManager.openPort3");
            JNIManager.close();
            JNIManager.openPort3();
        }
        Log.d(DeviceManagerConstants.LOG_TAG, "scanDeviceOnPort3");


        DeviceForScan deviceForScan = mDevicesForPort3.pop();

      
        mDeviceForScan = deviceForScan;

        Log.d(DeviceManagerConstants.LOG_TAG, "scanDeviceOnPort3 " + deviceForScan.getDeviceType());

        byte[] statusRequest = getStatusRequest(deviceForScan);

        JNIManager.scanDevice(statusRequest, statusRequest.length);
    }

    private void scanDeviceOnPort4() {

        if(!mIsPort4Initialized) {
            mIsPort4Initialized = true;
            mActivePort = PORT_NO_FOUR;
            Log.d(DeviceManagerConstants.LOG_TAG, "JNIManager.openPort4");
            JNIManager.openPort4();
        }

        Log.d(DeviceManagerConstants.LOG_TAG, "scanDeviceOnPort4");


        DeviceForScan deviceForScan = mDevicesForPort4.pop();

        
        mDeviceForScan = deviceForScan;

        Log.d(DeviceManagerConstants.LOG_TAG, "scanDeviceOnPort4 " + deviceForScan.getDeviceType());


        byte[] statusRequest = getStatusRequest(deviceForScan);

        JNIManager.scanDevice(statusRequest, statusRequest.length);
    }

//    /**
//     * 일괄소등 테스트용
//     * @return
//     */
//    public static byte[] getStatusRequest() {
//        //디바이스 자체에 문제가 있어 응답값을 받지 못하는 경우가 있음
//
//        byte[] request = new byte[10];
//
//        //일괄 소등 끄기 요청
//        request[0] = DeviceConstants.UARTINTERFACECOMPANY.INTERFACE_COMMAX_RS485;
//        request[1] = DeviceConstants.UARTINTERFACEPROTOCOL.COMMAX_PROTOCOL;
//        request[2] = 0x22; /* Command */
//        request[3] = 0x01; /* Sub No */
//        request[4] = 0x01; /* ON */
//        request[5] = 0x01; /* Bundle Light */
//        request[6] = 0x00;
//        request[7] = 0x00;
//        request[8] = 0x00;
//        request[9] = 0x25; /* Add Sum */
//
//        return request;
//    }





    private static byte[] getStatusRequest(DeviceForScan device) {

        //add sum이 음수값이 있는데 처리!!

        byte[] request = new byte[8];

        //일괄 소등 끄기 요청


        request[0] = convertStringToByte(device.getRequest()); /* Command */
        request[1] = convertStringToByte(device.getDeviceNo()); /* Sub No */

        //request[2]와 request[3]는 값이 0이어야 하나??

        request[2] = 0x01; /* ON */
        request[3] = 0x01; /* Bundle Light */
        request[4] = 0x00;
        request[5] = 0x00;
        request[6] = 0x00;
        request[7] = (byte) (request[0] +
                request[1] + request[2]
                + request[3]
                + request[4]
                + request[5]
                + request[6]
                + request[7]); /* Add Sum */


        return request;
    }

    private static byte convertStringToByte(String request) {

        if(request == null || request.equals("")) {
            return 0;
        }



        //request = request.replaceFirst("^0x", "");


        return (byte) (Integer.valueOf(request, 16)&0xff);

    }


    public void callback(byte[] receivedFrame) {
//        Log.d(DeviceManagerConstants.LOG_TAG_2, "Cpp에서 콜백이 왔니더");


//콜백으로 넘어온 값을 모두 표시
//        for (int i = 0; i < receivedFrame.length; ++i) {
//
//
//            byte b = receivedFrame[i];
//            String s = String.format("%02X", b); //16진수로 변환
//            Log.d(DeviceManagerConstants.LOG_TAG_2, "" + s);
//        }


        String response = convertToHex(receivedFrame);


        Log.d(DeviceManagerConstants.LOG_TAG, "response: " + response);

        //응답값이 0k(해당 디바이스가 스캔되었으면)
        if (response.equals(mDeviceForScan.getResponse())) {
            //스캔된 DB파일에 해당 디바이스 추가 처리!!
            Log.d(DeviceManagerConstants.LOG_TAG_3, "response ok");
            addScannedDeviceToDB();

        } else {
            Log.d(DeviceManagerConstants.LOG_TAG, "response fail");
        }



        scanDevice();

    }



    private void addScannedDeviceToDB() {

        ActiveDevice device = buildActiveDevice();

        DBConnector.getInstance(mContext, DBFileManager.DB_NAME_REMOTE).addActiveDeviceDataInDB(device);
    }

    private String convertToHex(byte[] receivedFrame) {

        byte b = receivedFrame[0];



        return String.format("%02X", b); //16진수로 변환
    }



    private ActiveDevice buildActiveDevice() {
        ActiveDevice activeDevice = new ActiveDevice();
        activeDevice.setDeviceType(mDeviceForScan.getDeviceType());
        activeDevice.setDeviceCount("1");
        activeDevice.setProtocolCompany(mDeviceForScan.getProtocol());
        activeDevice.setUartPort(mActivePort);


        return activeDevice;
    }
}
