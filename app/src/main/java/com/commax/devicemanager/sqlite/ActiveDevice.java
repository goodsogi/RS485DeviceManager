package com.commax.devicemanager.sqlite;

/**
 * 스캔된 디바이스 모델
 * Created by bagjeong-gyu on 2016. 8. 19..
 */
public class ActiveDevice {
    private String deviceType;
    private String protocolCompany;
    private String deviceCount;
    private String UartPort;


    public String getDeviceType() {
        return deviceType;
    }

    public void setDeviceType(String deviceType) {
        this.deviceType = deviceType;
    }

    public String getProtocolCompany() {
        return protocolCompany;
    }

    public void setProtocolCompany(String protocolCompany) {
        this.protocolCompany = protocolCompany;
    }

    public String getDeviceCount() {
        return deviceCount;
    }

    public void setDeviceCount(String deviceCount) {
        this.deviceCount = deviceCount;
    }

    public String getUartPort() {
        return UartPort;
    }

    public void setUartPort(String uartPort) {
        UartPort = uartPort;
    }


}
