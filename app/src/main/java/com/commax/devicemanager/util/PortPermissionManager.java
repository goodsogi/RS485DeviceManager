package com.commax.devicemanager.util;

import android.content.Context;
import android.util.Log;
import android.widget.Toast;

import com.commax.devicemanager.DeviceManagerConstants;

import java.io.DataOutputStream;

/**
 * 포트 퍼미션 관리
 * Created by bagjeong-gyu on 2016. 9. 1..
 */
public class PortPermissionManager {


    public static boolean setDisable() {

        Process process = null;
        DataOutputStream dataOutputStream = null;

        try {
            //루팅이 안되었으면 오류 발생
            process = Runtime.getRuntime().exec("su");
            dataOutputStream = new DataOutputStream(process.getOutputStream());

            //원래 권한인 crw------- 으로 돌림
            dataOutputStream.writeBytes("chmod 600 /dev/ttyS3\n");
            dataOutputStream.writeBytes("chmod 600 /dev/ttyS4\n");
            dataOutputStream.writeBytes("exit\n");
            dataOutputStream.flush();
            process.waitFor();
        } catch (Exception e) {
            Log.d(DeviceManagerConstants.LOG_TAG, "포트 권한 설정 오류: " +  e.getMessage());
            return false;
        } finally {
            try {
                if (dataOutputStream != null) {
                    dataOutputStream.close();
                }
                process.destroy();
            } catch (Exception e) {
                Log.d(DeviceManagerConstants.LOG_TAG, "포트 권한 설정 오류: " +  e.getMessage());
            }
        }
        return true;
    }


    public static boolean setEnable() {

        Process process = null;
        DataOutputStream dataOutputStream = null;

        try {
            //루팅이 안되었으면 오류 발생
            process = Runtime.getRuntime().exec("su");
            dataOutputStream = new DataOutputStream(process.getOutputStream());
            dataOutputStream.writeBytes("chmod 0766 /dev/ttyS3\n");
            dataOutputStream.writeBytes("chmod 0766 /dev/ttyS4\n");
            dataOutputStream.writeBytes("exit\n");
            dataOutputStream.flush();
            process.waitFor();
        } catch (Exception e) {
            Log.d(DeviceManagerConstants.LOG_TAG, "포트 권한 설정 오류: " +  e.getMessage());
            return false;
        } finally {
            try {
                if (dataOutputStream != null) {
                    dataOutputStream.close();
                }
                process.destroy();
            } catch (Exception e) {
                Log.d(DeviceManagerConstants.LOG_TAG, "포트 권한 설정 오류: " +  e.getMessage());
            }
        }
        return true;
    }
}
