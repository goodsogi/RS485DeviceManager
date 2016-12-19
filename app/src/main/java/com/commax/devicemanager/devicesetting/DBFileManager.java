package com.commax.devicemanager.devicesetting;

import android.content.Context;
import android.content.res.AssetManager;
import android.util.Log;
import android.widget.Toast;

import com.commax.devicemanager.DeviceManagerConstants;

import java.io.BufferedInputStream;
import java.io.BufferedOutputStream;
import java.io.File;
import java.io.FileInputStream;
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.InputStream;
import java.nio.channels.FileChannel;

/**
 * db 파일 복사 관리
 *
 * Created by bagjeong-gyu on 2016. 9. 1..
 */
public class DBFileManager {

    private static DBFileManager instance;
    private final Context mContext;

    //외부 db에 바로 접근하려고 했으나 journal mode라는 것 때문인지 데이터가 insert 안됨.
    //unknown error (code 14): Could not open database
    //기존 db 파일명에 journal이 붙은 파일을 열려고 시도하나 그 파일은 존재하지 않음
    public static final String DB_NAME_ALL_DEVICE = "all_device_standard_ver2.0.sqlite"; //내부 db
    public static final String DB_NAME_TEMPLATE = "standard_ver2.0_template.db"; //내부 db

    public static final String DB_NAME_REMOTE = "standard_ver2.0.db"; //외부 db


    private DBFileManager(Context context) {
        mContext = context;
    }

    public static DBFileManager getInstance(Context context) {
        if(instance == null) {
            instance = new DBFileManager(context);
        }
        return instance;
    }



    /**
     * db파일이 내부 메모리에 복사되어 있는 상태인지 체크
     * @return
     */
    boolean isCheckDB() {
        String filePath = "/data/data/" + mContext.getPackageName() + "/databases/" + DB_NAME_ALL_DEVICE;
        File file = new File(filePath);

        if (file.exists()) {
            return true;
        }

        return false;
    }

//    /**
//     * 월패드의 /user/app/bin 폴더 내에 있는 db 파일을 내부 메모리에 복사
//     */
//    private void copyToInternalDB() {
//
//        //user/app/bin폴더내에 db파일을 접근할 수 없다는 오류발생. 터미널에서 "chmod 777 <파일명>" 사용하여 권한을 변경하니 제대로 작동
//
//        String localDBFolderPath = "/data/data/" +  mContext.getPackageName() + "/databases";
//        String localDBFilePath = "/data/data/" +  mContext.getPackageName() + "/databases/" + DB_NAME_REMOTE;
//        File localDBFolder = new File(localDBFolderPath);
//        File localDB = new File(localDBFilePath);
//
//
//        String remoteDBFilePath = "/user/app/bin/" + DB_NAME_REMOTE;
//        File remoteDB = new File(remoteDBFilePath);
//
//        try {
//
//            if (localDBFolder.exists()) {
//            }else{
//                localDBFolder.mkdirs();
//            }
//
//
//            if (localDB.exists()) {
//                localDB.delete();
//                localDB.createNewFile();
//            }
//
//
//            if (remoteDB.exists()) {
//                FileChannel src = new FileInputStream(remoteDB).getChannel();
//                FileChannel dst = new FileOutputStream(localDB).getChannel();
//                dst.transferFrom(src, 0, src.size());
//                src.close();
//                dst.close();
//            }
//
//
//
//
//        } catch (IOException e) {
//            Log.e("ErrorMessage", e.getMessage());
//
//            Toast.makeText( mContext,e.getMessage(), Toast.LENGTH_SHORT).show();
//        }
//    }


    /**
     * Asset폴더에 있는 db 파일을 내부 메모리에 복사(모든 디바이스)
     */
    void copyAllDeviceDBFileInAsset() {


        AssetManager manager =  mContext.getAssets();
        String folderPath = "/data/data/" +  mContext.getPackageName() + "/databases";
        String filePath = "/data/data/" +  mContext.getPackageName() + "/databases/" + DB_NAME_ALL_DEVICE;
        File folder = new File(folderPath);
        File file = new File(filePath);

        FileOutputStream fos = null;
        BufferedOutputStream bos = null;
        try {
            InputStream is = manager.open(DB_NAME_ALL_DEVICE);
            BufferedInputStream bis = new BufferedInputStream(is);

            if (folder.exists()) {
            }else{
                folder.mkdirs();
            }


            if (file.exists()) {
                file.delete();
                file.createNewFile();
            }

            fos = new FileOutputStream(file);
            bos = new BufferedOutputStream(fos);
            int read = -1;
            byte[] buffer = new byte[1024];
            while ((read = bis.read(buffer, 0, 1024)) != -1) {
                bos.write(buffer, 0, read);
            }

            bos.flush();

            bos.close();
            fos.close();
            bis.close();
            is.close();

        } catch (IOException e) {
            Log.e(DeviceManagerConstants.LOG_TAG, e.getMessage());
        }
    }

    /**
     * Asset폴더에 있는 db 파일을 내부 메모리에 복사(스캔된 디바이스 db 파일 템플릿 )
     */
    void copyDBTemplateFileInAsset() {


        AssetManager manager =  mContext.getAssets();
        String folderPath = "/data/data/" +  mContext.getPackageName() + "/databases";
        String filePath = "/data/data/" +  mContext.getPackageName() + "/databases/" + DB_NAME_REMOTE;
        File folder = new File(folderPath);
        File file = new File(filePath);

        FileOutputStream fos = null;
        BufferedOutputStream bos = null;
        try {
            InputStream is = manager.open(DB_NAME_TEMPLATE);
            BufferedInputStream bis = new BufferedInputStream(is);

            if (folder.exists()) {
            }else{
                folder.mkdirs();
            }


            if (file.exists()) {
                file.delete();
                file.createNewFile();
            }

            fos = new FileOutputStream(file);
            bos = new BufferedOutputStream(fos);
            int read = -1;
            byte[] buffer = new byte[1024];
            while ((read = bis.read(buffer, 0, 1024)) != -1) {
                bos.write(buffer, 0, read);
            }

            bos.flush();

            bos.close();
            fos.close();
            bis.close();
            is.close();

        } catch (IOException e) {
            Log.e(DeviceManagerConstants.LOG_TAG, e.getMessage());
        }
    }


    /**
     * 앱 내부 DB를 월패드 외부 DB에 복사
     */
    void copyToRemoteDB() {

        //user/app/bin폴더내에 db파일을 접근할 수 없다는 오류발생. 터미널에서 "chmod 777 <파일명>" 사용하여 권한을 변경하니 제대로 작동

        String localDBFolderPath = "/data/data/" +  mContext.getPackageName() + "/databases";
        String localDBFilePath = "/data/data/" +  mContext.getPackageName() + "/databases/" + DB_NAME_REMOTE;

        File localDB = new File(localDBFilePath);


        String remoteDBFilePath = "/user/app/bin/" + DB_NAME_REMOTE;
        File remoteDB = new File(remoteDBFilePath);

        try {

            if (localDB.exists()) {

                FileChannel src = new FileInputStream(localDB).getChannel();
                FileChannel dst = new FileOutputStream(remoteDB).getChannel();
                dst.transferFrom(src, 0, src.size());
                src.close();
                dst.close();
            }else{
                return;
            }


            if (remoteDB.exists()) {
                FileChannel src = new FileInputStream(remoteDB).getChannel();
                FileChannel dst = new FileOutputStream(localDB).getChannel();
                dst.transferFrom(src, 0, src.size());
                src.close();
                dst.close();
            }




        } catch (IOException e) {
            Log.e("ErrorMessage", e.getMessage());

            Toast.makeText( mContext,e.getMessage(), Toast.LENGTH_SHORT).show();
        }
    }


}
