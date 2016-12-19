package com.commax.devicemanager.util;

/**
 * 인터넷 연결 체크 리스너
 * Created by bagjeong-gyu on 2016. 9. 1..
 */
public interface InternetConnectionCheckListener {
    public void onInternetConnected();
    public void onInternetNotConnected();
}
