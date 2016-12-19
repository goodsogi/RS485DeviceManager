package com.commax.devicemanager.devicesetting;

import com.commax.devicemanager.sqlite.ActiveDevice;
import com.commax.devicemanager.sqlite.Device;

/**
 * 디바이스 스캔 리스너
 * Created by bagjeong-gyu on 2016. 9. 1..
 */
public interface DeviceScanListener {
    /**
     * 스캔 완료된 경우
     */
    public void onDeviceScanCompleted();
}
