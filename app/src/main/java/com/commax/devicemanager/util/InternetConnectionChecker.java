package com.commax.devicemanager.util;

import android.content.Context;
import android.net.ConnectivityManager;
import android.net.NetworkInfo;
import android.os.AsyncTask;
import android.util.Log;
import android.widget.Toast;

import com.commax.devicemanager.DeviceManagerConstants;

import java.io.IOException;
import java.net.InetAddress;

/**
 * 인터넷 연결 체크
 * Created by bagjeong-gyu on 2016. 9. 1..
 */
public class InternetConnectionChecker {

    private static InternetConnectionChecker instance;
    private final Context mContext;
    private InternetConnectionCheckListener mListener;

    private InternetConnectionChecker(Context context) {

        mContext = context;

        try {
            mListener = (InternetConnectionCheckListener) context;
        } catch (ClassCastException e) {
            Log.d(DeviceManagerConstants.LOG_TAG, "InternetConnectionCheckListener ClassCastException: " + e.getMessage());
        }
    }

    public static InternetConnectionChecker getInstance(Context context) {
        if(instance == null) {
            instance = new InternetConnectionChecker(context);
        }
        return instance;
    }

    /**
     * 인터넷에 연결된 상태인지 체크
     * 랜에 연결된 경우 netInfo가 null이 되어 인터넷 연결 상태를 정확히 체크할 수 없음
     *
     * @return
     */
    public boolean isOnline() {
        ConnectivityManager cm =
                (ConnectivityManager) mContext.getSystemService(Context.CONNECTIVITY_SERVICE);
        NetworkInfo netInfo = cm.getActiveNetworkInfo();

        if (netInfo == null) {
            Toast.makeText(mContext, "netInfo == null", Toast.LENGTH_SHORT).show();
        } else if (!netInfo.isConnectedOrConnecting()) {
            Toast.makeText(mContext, "not connecting or connected", Toast.LENGTH_SHORT).show();
        } else {
            Toast.makeText(mContext, "온라인 상태입니다", Toast.LENGTH_SHORT).show();
        }

        return netInfo != null && netInfo.isConnectedOrConnecting();
    }


    /**
     * 랜에 연결된 경우 netInfo가 null이 되어 인터넷 연결 상태를 정확히 체크할 수 없음
     * 구글 사이트에 ping 날리는 방식으로 체크
     *
     * @return
     * @throws InterruptedException
     * @throws IOException
     */
    public boolean isOnlineWithLan() throws InterruptedException, IOException {
        String command = "ping -c 10 google.com"; //c는 ping을 날리는 횟수 지정 옵션, 나중에 서버 ip 주소로 변경!!
        return (Runtime.getRuntime().exec(command).waitFor() == 0);
    }

    /**
     * ping을 대신해서 InetAddress를 사용하여 인터넷 연결 체크

     * @return
     */
    public boolean isInternetAvailable() {
        try {
            InetAddress ipAddr = InetAddress.getByName("google.com"); //You can replace it with your name

            if (ipAddr.equals("")) {
                Toast.makeText(mContext, "인터넷 사용 가능", Toast.LENGTH_SHORT).show();
                return false;
            } else {
                Toast.makeText(mContext, "인터넷 사용 불가능", Toast.LENGTH_SHORT).show();
                return true;
            }

        } catch (Exception e) {
            Toast.makeText(mContext, "인터넷 사용 불가능", Toast.LENGTH_SHORT).show();
            return false;
        }
    }

    public void run() {
        new InternetCheckTask().execute();
    }

    /**
     * InetAddress가 main thread에서 돌면 오류가 발생해서 AsyncTask를 이용하여
     * 백그라운드에서 인터넷 연결 체크
     */
    public class InternetCheckTask extends AsyncTask<Void, Void, Boolean> {

        @Override
        protected void onPreExecute() {
            super.onPreExecute();
        }

        @Override
        protected Boolean doInBackground(Void... params) {

            try {

                InetAddress ipAddr = InetAddress.getByName("google.com"); //You can replace it with your name

                if (ipAddr.equals("")) {

                    return false;
                } else {

                    return true;
                }

            } catch (Exception e) {

                Log.d(DeviceManagerConstants.LOG_TAG, "오류: " + e.getMessage());
                return false;
            }
        }

        @Override
        protected void onPostExecute(Boolean isConnectedInternet) {
            super.onPostExecute(isConnectedInternet);

            if (isConnectedInternet) {
                Toast.makeText(mContext, "인터넷 사용 가능", Toast.LENGTH_SHORT).show();
                ///////////////////////////////////
                //테스트후 삭제하세요!!
                mListener.onInternetNotConnected();
                //테스트후 주석푸세요!!
                //mListener.onInternetConnected();
                //////////////////////////////////

            } else {
                Toast.makeText(mContext, "인터넷 사용 불가능", Toast.LENGTH_SHORT).show();
                mListener.onInternetNotConnected();
            }

        }

        @Override
        protected void onCancelled() {
            super.onCancelled();
        }

    }

}
