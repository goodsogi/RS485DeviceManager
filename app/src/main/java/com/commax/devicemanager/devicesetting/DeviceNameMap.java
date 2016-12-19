package com.commax.devicemanager.devicesetting;

import java.util.HashMap;

/**
 * 디스플레이용 디바이스명 map
 * Created by bagjeong-gyu on 2016. 8. 24..
 */
public class DeviceNameMap {

    static HashMap<String, String> names = new HashMap<String, String>();

    public static void create() {

        names.put("rfmodule", "rfmodule");
        names.put("smartmetering", "스마트미터링(순시치)");
        names.put("systemaircon", "시스템에어컨");
        names.put("smartdoorphone", "스마트도어폰");
        names.put("ledpanel", "led panel");
        names.put("energymonitoring", "EMS");
        names.put("weatherinfo", "날씨생활정보기");
        names.put("boiler", "보일러");
        names.put("light", "전등");
        names.put("gas", "GAS");
        names.put("doorlock", "도어락");
        names.put("consent", "콘센트");
        names.put("curtain", "커튼");
        names.put("aircon", "에어컨");
        names.put("bundlelight", "일괄소등");
        names.put("fansystem", "fansystem (환기)");
        names.put("roomauto", "roomauto");
        names.put("readypower", "대기전력차단기");
        names.put("fcu", "FCU");
        names.put("time", "시간");
    }


    public static String getName(String key) {
        return names.get(key);
    }





}
