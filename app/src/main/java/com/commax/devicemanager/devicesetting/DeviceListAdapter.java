package com.commax.devicemanager.devicesetting;

import android.content.Context;
import android.util.Log;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.ArrayAdapter;
import android.widget.CheckBox;
import android.widget.TextView;

import com.commax.devicemanager.DeviceManagerConstants;
import com.commax.devicemanager.R;
import com.commax.devicemanager.sqlite.ActiveDevice;
import com.commax.devicemanager.sqlite.Device;
import com.commax.devicemanager.util.PlusViewHolder;

import java.util.List;

/**
 * 디바이스 리스트 어댑터
 * Created by bagjeong-gyu on 2016. 8. 22..
 */
public class DeviceListAdapter extends ArrayAdapter<ActiveDevice> {


    private final LayoutInflater mLayoutInflater;
    private final List<ActiveDevice> mDatas;
    private int mRS485DeviceCount;

    public DeviceListAdapter(Context context, int resource, List<ActiveDevice> devices) {
        super(context, resource, devices);
        mLayoutInflater = LayoutInflater.from(context);
        mDatas = devices;

        DeviceNameMap.create();
    }

    @Override
    public View getView(final int position, View convertView, ViewGroup parent) {

        if (convertView == null) {
            convertView = mLayoutInflater.inflate(R.layout.list_item_device,
                    parent, false);
        }


        TextView deviceName = PlusViewHolder.get(convertView, R.id.deviceName);

        String deviceTypeString = mDatas.get(position).getDeviceType();
        String deviceNameString = DeviceNameMap.getName(deviceTypeString);
        deviceName.setText(deviceNameString);



        TextView protocolName = PlusViewHolder.get(convertView, R.id.protocolName);

        String protocolNameString = mDatas.get(position).getProtocolCompany();
        protocolName.setText(protocolNameString);



        //RS485장치는 무조건 체크되고 변경이 불가능하게 처리
        CheckBox deviceCheckbox = PlusViewHolder.get(convertView, R.id.deviceCheckbox);
        deviceCheckbox.setChecked(true);
        deviceCheckbox.setEnabled(false);
        deviceCheckbox.setButtonDrawable(R.drawable.check_03);



        return convertView;
    }

}
