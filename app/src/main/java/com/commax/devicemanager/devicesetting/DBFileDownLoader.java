package com.commax.devicemanager.devicesetting;

import android.content.Context;
import android.os.AsyncTask;
import android.util.Log;

import com.commax.devicemanager.DeviceManagerConstants;
import com.commax.devicemanager.util.ProgressDialogManager;

import java.io.File;
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.InputStream;
import java.io.OutputStream;
import java.net.HttpURLConnection;
import java.net.URL;

/**
 * DB 파일 다운로더
 * Created by johnny on 15. 7. 9.
 */
public class DBFileDownLoader extends AsyncTask<Void, Void, Boolean> {

    private static final String SERVER_DB_DOWNLOAD_URL = "http://goodsogi.mireene.com/commax/standard_ver2.0_template.db";
    private DBFileDownloadListener mListener;
    final private Context mContext;




    public DBFileDownLoader(Context context) {
        mContext = context;
        try {
            mListener = (DBFileDownloadListener) context;
        } catch (ClassCastException e) {
            Log.d(DeviceManagerConstants.LOG_TAG,"DBFileDownloadListener ClassCastException: " + e.getMessage());

        }

    }


    @Override
    protected Boolean doInBackground(Void... params) {
        InputStream input = null;
        OutputStream output = null;
        HttpURLConnection connection = null;
        try {
            URL url = new URL(SERVER_DB_DOWNLOAD_URL);
            connection = (HttpURLConnection) url.openConnection();
            connection.connect();

            // expect HTTP 200 OK, so we don't mistakenly save error report
            // instead of the file
            if (connection.getResponseCode() != HttpURLConnection.HTTP_OK) {
                return false;
            }

            // this will be useful to display download percentage
            // might be -1: server did not report the length
            int fileLength = connection.getContentLength();

            // download the file
            input = connection.getInputStream();


            output = new FileOutputStream(getOutputFile());

            byte data[] = new byte[4096];
            long total = 0;
            int count;
            while ((count = input.read(data)) != -1) {
                // allow canceling with back button
                if (isCancelled()) {
                    input.close();
                    return null;
                }
                total += count;

                output.write(data, 0, count);
            }
        } catch (Exception e) {
            return false;
        } finally {
            try {
                if (output != null)
                    output.close();
                if (input != null)
                    input.close();
            } catch (IOException ignored) {
            }

            if (connection != null) {
                connection.disconnect();
            }
        }
        return true;
    }

    /**
     * 앱 내부 메모리에 저장할 파일 가져옴
     * @return
     */
    private File getOutputFile() {
        String folderPath = "/data/data/" +  mContext.getPackageName() + "/databases";
        String filePath = "/data/data/" +  mContext.getPackageName() + "/databases/" + DBFileManager.DB_NAME_REMOTE;
        File folder = new File(folderPath);
        File file = new File(filePath);

        if (folder.exists()) {
        }else{
            folder.mkdirs();
        }


        if (file.exists()) {
            file.delete();
            try {
                file.createNewFile();
            } catch (IOException e) {
                e.printStackTrace();
            }
        }

        return file;
    }


    @Override
    protected void onPostExecute(Boolean result) {

        ProgressDialogManager.removeProgressDialog();
        if (result) {
            Log.d(DeviceManagerConstants.LOG_TAG, "파일 다운로드 성공");
            mListener.onDownloadCompleted();
        } else {
            Log.d(DeviceManagerConstants.LOG_TAG, "파일 다운로드 오류발생");

        }


    }


    


}

