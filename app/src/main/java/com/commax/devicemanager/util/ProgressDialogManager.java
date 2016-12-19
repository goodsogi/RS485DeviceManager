package com.commax.devicemanager.util;

import android.app.ProgressDialog;
import android.content.Context;
import android.content.DialogInterface;

/**
 * 프로그래스다이얼로그 표시 및 제거 등 처리하는 클래스
 *
 * @author Jeonggyu Park
 *
 */
public class ProgressDialogManager {

    private static ProgressDialog mProgressDialog;

    /**
     * 프로그래스다이얼로그 띄움
     *
     * @param context
     *            컨텍스트
     * @param msg
     *            메시지
     */
    public static void showProgessDialog(Context context, String msg) {
        if (mProgressDialog != null) {
            mProgressDialog.dismiss();
            mProgressDialog = null;
        }

        try {
            mProgressDialog = new ProgressDialog(context,
                    ProgressDialog.THEME_HOLO_LIGHT);

            mProgressDialog.setMessage(msg);
            mProgressDialog
                    .setOnCancelListener(new DialogInterface.OnCancelListener() {
                        @Override
                        public void onCancel(DialogInterface dialogInterface) {
                            mProgressDialog = null;
                        }
                    });
            // mProgressDialog.setCancelable(false);
            mProgressDialog.show();
        } catch (final IllegalArgumentException e) {
            // Handle or log or ignore
        } catch (final Exception e) {
            // Handle or loler.unca
            mProgressDialog = null;

        }

    }

    /**
     * 프로그래스다이얼로그 제거
     */
    public static void removeProgressDialog() {
        try {
            if (mProgressDialog != null && mProgressDialog.isShowing()) {
                mProgressDialog.dismiss();

            }
        } catch (final IllegalArgumentException e) {

        } catch (final Exception e) {

        } finally {
            mProgressDialog = null;
        }
    }

    /**
     * 다이얼로그 취소 가능여부 설정
     *
     * @param isCancelable
     */
    public static void setCancelable(boolean isCancelable) {
        if (mProgressDialog != null) {
            mProgressDialog.setCancelable(isCancelable);
        }
    }



}
