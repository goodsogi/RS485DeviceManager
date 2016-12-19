package com.commax.devicemanager.devicesetting;

import android.app.Activity;
import android.content.Intent;
import android.content.res.ColorStateList;
import android.os.Bundle;
import android.text.Html;
import android.util.Log;
import android.view.View;
import android.view.WindowManager;
import android.widget.LinearLayout;
import android.widget.ListView;
import android.widget.TextView;

import com.commax.devicemanager.DeviceManagerConstants;
import com.commax.devicemanager.R;
import com.commax.devicemanager.sqlite.ActiveDevice;
import com.commax.devicemanager.sqlite.DBConnector;
import com.commax.devicemanager.sqlite.Device;
import com.commax.devicemanager.util.InternetConnectionCheckListener;
import com.commax.devicemanager.util.InternetConnectionChecker;
import com.commax.devicemanager.util.PortPermissionManager;
import com.commax.devicemanager.util.ProgressDialogManager;


import java.util.ArrayList;
import java.util.List;


/**
 * 디바이스 설정 액티비티
 */
public class DeviceSettingActivity extends Activity implements DeviceScanListener, InternetConnectionCheckListener, DBFileDownloadListener {


    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);

        //makeLayout 메소드에서 동적으로 레이아웃 생성해서 사용
        //setContentView(R.layout.activity_device_setting);


        init();

    }

    /**
     * 프로그래스다이얼로그 띄우고 인터넷 연결 상태 체크후 그에 따른 처리
     */
    private void init() {


        makeLayout();

        InternetConnectionChecker.getInstance(this).run();

    }



    /**
     * 화면 레이아웃 생성
     */
    private void makeLayout() {
        getWindow().setFlags(WindowManager.LayoutParams.FLAG_FULLSCREEN, WindowManager.LayoutParams.FLAG_FULLSCREEN);
        getWindow().setSoftInputMode(WindowManager.LayoutParams.SOFT_INPUT_STATE_ALWAYS_HIDDEN);


        LinearLayout mainLinear = new LinearLayout(this);
        mainLinear.setOrientation(LinearLayout.VERTICAL);


        //상단 타이틀
        LinearLayout topTitle = (LinearLayout) View.inflate(this, R.layout.frame_title, null);


        ((LinearLayout) topTitle.findViewById(R.id.linear_pagenumber)).setBackgroundDrawable(this.getResources().getDrawable(R.drawable.num_03));
        ((TextView) topTitle.findViewById(R.id.text_highlight)).setText(getResources().getString(R.string.STEP_DEVICE_SETTING));
        ((TextView) topTitle.findViewById(R.id.step_3)).setTextColor(ColorStateList.valueOf(0xFFFFFFFF));
        ((TextView) topTitle.findViewById(R.id.step_3)).setText(Html.fromHtml("<b>" + getResources().getString(R.string.STEP_DEVICE_SETTING) + "</b>"));

        //디바이스 리스트
        LinearLayout deviceList = (LinearLayout) View.inflate(this, R.layout.frame_device_list, null);


        //하단바
        LinearLayout bottomBar = (LinearLayout) View.inflate(this, R.layout.frame_bottom_button, null);
        bottomBar.setVisibility(View.VISIBLE);

        mainLinear.addView(topTitle);
        mainLinear.addView(deviceList);
        mainLinear.addView(bottomBar);
        setContentView(mainLinear);
    }

    /**
     * DB 초기화
     */
    private void initDB() {
        try {
            boolean bResult = DBFileManager.getInstance(this).isCheckDB();    // DB가 있는지?

            if (!bResult) {    // DB가 없으면 복사
                DBFileManager.getInstance(this).copyAllDeviceDBFileInAsset();
                DBFileManager.getInstance(this).copyDBTemplateFileInAsset();
            }


        } catch (Exception e) {
            Log.d(DeviceManagerConstants.LOG_TAG, "initDB error: " + e.getMessage());
        }
    }



    /**
     * 장치 설정 프로그래스다이얼로그 띄움
     *
     * @param stringResId 메세지의 문자열 id
     */
    private void showProgressDialog(int stringResId) {


        ProgressDialogManager.showProgessDialog(this,
                getString(stringResId));
        ProgressDialogManager.setCancelable(false);

    }



    /**
     * 디바이스 스캔 실행
     */
    public void scanAllDevices() {


        ArrayList<Device> devices = getAllDevice();

        DeviceScanner.getInstance(this).setDevices(devices);
        DeviceScanner.getInstance(this).scanDevice();


    }


    /**
     * 접점 스위치 추가
     * @param devices 스캔된 모든 디바이스
     * @return
     */

    private List<ActiveDevice> addSwitches(List<ActiveDevice> devices) {

        ActiveDevice device1 = new ActiveDevice();
        device1.setDeviceType("접점스위치1");
        device1.setProtocolCompany("commax");
        device1.setDeviceCount("1");
        device1.setUartPort("");

        ActiveDevice device2 = new ActiveDevice();
        device2.setDeviceType("접점스위치2");
        device2.setProtocolCompany("commax");
        device2.setDeviceCount("1");
        device2.setUartPort("");

        ActiveDevice device3 = new ActiveDevice();
        device3.setDeviceType("접점스위치3");
        device3.setProtocolCompany("commax");
        device3.setDeviceCount("1");
        device3.setUartPort("");


        devices.add(device1);
        devices.add(device2);
        devices.add(device3);

        return devices;
    }


    /**
     * 이전 버튼 클릭 처리
     * @param view
     */
    public void handlePrevPressed(View view) {
        Intent data = new Intent();
        data.putExtra("returnAction", "prev");
        setResult(Activity.RESULT_OK, data);
        finish();

    }

    /**
     * 다음 버튼 클릭 처리
     * @param view
     */
    public void handleNextPressed(View view) {
        Intent data = new Intent();
        data.putExtra("returnAction", "next");
        setResult(Activity.RESULT_OK, data);
        finish();

    }

    /**
     * DB에서 모든 디바이스 가져옴
     * @return
     */
    public ArrayList<Device> getAllDevice() {
        DBConnector connector = DBConnector.getInstance(this, DBFileManager.DB_NAME_ALL_DEVICE);
        return connector.getAllDeviceData();
    }


    /**
     * 디바이스 스캔이 완전히 끝난 경우 처리
     */
    @Override
    public void onDeviceScanCompleted() {
        JNIManager.close();
        dismissProgressDialog();
        DBFileManager.getInstance(this).copyToRemoteDB();
        PortPermissionManager.setDisable();
        makeListView();
    }

    /**
     * 로딩바 제거
     */
    private void dismissProgressDialog() {
        ProgressDialogManager.removeProgressDialog();
    }


    /**
     * 인터넷에 연결된 경우 처리
     */
    @Override
    public void onInternetConnected() {
        Log.d(DeviceManagerConstants.LOG_TAG, "onInternetConnected");
        new DBFileDownLoader(this).execute();

    }

    /**
     * 인터넷에 연결되지 않은 경우 처리
     */
    @Override
    public void onInternetNotConnected() {
        //port를 읽고 쓸 수 있게 권한 변경
        PortPermissionManager.setEnable();

        initDB();

        showProgressDialog(R.string.scanning_device);

        scanAllDevices();

    }

    /**
     * DB 파일 다운로드가 끝난 경우 처리
     */
    @Override
    public void onDownloadCompleted() {
        DBFileManager.getInstance(this).copyToRemoteDB();
        makeListView();
    }



    /**
     * 리스트뷰 생성
     */
    private void makeListView() {
        //점점스위치 추가관련 수정!!


        //이상하게 "Only the original thread that created a view hierarchy can touch its views" 오류가
        //발생해서 runOnUiThread로 감싸줌
       runOnUiThread(new Runnable() {
           @Override
           public void run() {
               List<ActiveDevice> devices = getAllActiveDevice();
               ListView deviceList = (ListView) findViewById(R.id.deviceList);
               DeviceListAdapter adapter = new DeviceListAdapter(DeviceSettingActivity.this, R.layout.list_item_device, devices);
               deviceList.setAdapter(adapter);
           }
       });

    }

    /**
     * 모든 스캔된 디바이스 가져옴
     * @return
     */
    private List<ActiveDevice> getAllActiveDevice() {
        DBConnector connector = DBConnector.getInstance(this, DBFileManager.DB_NAME_REMOTE);
        return connector.getAllActiveDeviceData();


    }
}
