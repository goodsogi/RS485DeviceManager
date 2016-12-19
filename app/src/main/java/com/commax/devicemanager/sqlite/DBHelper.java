package com.commax.devicemanager.sqlite;



import android.content.Context;
import android.database.Cursor;
import android.database.sqlite.SQLiteDatabase;
import android.database.sqlite.SQLiteOpenHelper;
import android.util.Log;

import com.commax.devicemanager.DeviceManagerConstants;




/**
 * 디비 생성과 제거를 하는 클래스
 *
 * @author Jeonggyu Park
 */
class DBHelper extends SQLiteOpenHelper {

    private static final int DATABASE_VERSION = 1;



    

    public DBHelper(Context context, String dbName) {
        super(context, dbName, null, DATABASE_VERSION);
    }

    @Override
    public void onCreate(SQLiteDatabase db) {


       

    }



    @Override
    public void onUpgrade(SQLiteDatabase db, int oldVersion, int newVersion) {


    }

    public void onDowngrade(SQLiteDatabase db, int oldVersion, int newVersion) {
        onUpgrade(db, oldVersion, newVersion);
    }

}