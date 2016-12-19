package com.commax.devicemanager.devicesetting;

/**
 * 스캔용 유선 디바이스 모델
 * Created by bagjeong-gyu on 2016. 8. 30..
 */
public class DeviceForScan {
    private String deviceType;
    private String deviceNo;
    private String deviceNameForDisplay;
    private String protocol;
    private String request;
    private String response;

    public String getDeviceType() {
        return deviceType;
    }

    public void setDeviceType(String deviceType) {
        this.deviceType = deviceType;
    }

    public String getDeviceNameForDisplay() {
        return deviceNameForDisplay;
    }

    public void setDeviceNameForDisplay(String deviceNameForDisplay) {
        this.deviceNameForDisplay = deviceNameForDisplay;
    }

    public String getProtocol() {
        return protocol;
    }

    public void setProtocol(String protocol) {
        this.protocol = protocol;
    }

    public String getRequest() {
        return request;
    }

    public void setRequest(String request) {
        this.request = request;
    }

    public String getResponse() {
        return response;
    }

    public void setResponse(String response) {
        this.response = response;
    }

    public String getDeviceNo() {
        return deviceNo;
    }

    public void setDeviceNo(String deviceNo) {
        this.deviceNo = deviceNo;
    }
}
