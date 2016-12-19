package com.commax.devicemanager.devicesetting;

import android.content.Context;
import android.util.Log;

/**
 * JNI 관리
 * Created by Next on 2016/8/12.
 */
public class JNIManager {
    private static Context mContext;

    static {
        System.loadLibrary("JNIManager");
    }

    public static native void openPort3();

    public static native void openPort4();

    public static native void close();

    public static native void scanDevice(byte[] statusRequest, int length);

    public static void callback(byte[] receivedFrame) {

        DeviceScanner.getInstance(mContext).callback(receivedFrame);




    }

    public static void setContext(Context context) {
        mContext = context;
    }
}
