package com.commax.devicemanager.sqlite;

/**
 * 디바이스 모델
 * Created by bagjeong-gyu on 2016. 8. 19..
 */
public class Device {
    private String deviceType;
    private String deviceNameForDisplay;
    private String maxDeviceCount;
    private String protocol1;
    private String protocol2;
    private String protocol3;
    private String protocol4;
    private String request1;
    private String request2;
    private String request3;
    private String request4;
    private String response1;
    private String response2;
    private String response3;
    private String response4;
    private String protocolCount;

    public String getDeviceNameForDisplay() {
        return deviceNameForDisplay;
    }

    public void setDeviceNameForDisplay(String deviceNameForDisplay) {
        this.deviceNameForDisplay = deviceNameForDisplay;
    }

    public String getMaxDeviceCount() {
        return maxDeviceCount;
    }

    public void setMaxDeviceCount(String maxDeviceCount) {
        this.maxDeviceCount = maxDeviceCount;
    }

    public String getProtocol1() {
        return protocol1;
    }

    public void setProtocol1(String protocol1) {
        this.protocol1 = protocol1;
    }

    public String getProtocol2() {
        return protocol2;
    }

    public void setProtocol2(String protocol2) {
        this.protocol2 = protocol2;
    }

    public String getProtocol3() {
        return protocol3;
    }

    public void setProtocol3(String protocol3) {
        this.protocol3 = protocol3;
    }

    public String getProtocol4() {
        return protocol4;
    }

    public void setProtocol4(String protocol4) {
        this.protocol4 = protocol4;
    }



    public String getDeviceType() {
        return deviceType;
    }

    public void setDeviceType(String deviceType) {
        this.deviceType = deviceType;
    }

    public String getRequest1() {
        return request1;
    }

    public void setRequest1(String request1) {
        this.request1 = request1;
    }

    public String getRequest2() {
        return request2;
    }

    public void setRequest2(String request2) {
        this.request2 = request2;
    }

    public String getRequest3() {
        return request3;
    }

    public void setRequest3(String request3) {
        this.request3 = request3;
    }

    public String getRequest4() {
        return request4;
    }

    public void setRequest4(String request4) {
        this.request4 = request4;
    }

    public String getResponse1() {
        return response1;
    }

    public void setResponse1(String response1) {
        this.response1 = response1;
    }

    public String getResponse2() {
        return response2;
    }

    public void setResponse2(String response2) {
        this.response2 = response2;
    }

    public String getResponse3() {
        return response3;
    }

    public void setResponse3(String response3) {
        this.response3 = response3;
    }

    public String getResponse4() {
        return response4;
    }

    public void setResponse4(String response4) {
        this.response4 = response4;
    }

    public String getProtocolCount() {
        return protocolCount;
    }

    public void setProtocolCount(String protocolCount) {
        this.protocolCount = protocolCount;
    }
}
