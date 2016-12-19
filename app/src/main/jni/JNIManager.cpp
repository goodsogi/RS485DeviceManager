//
// Created by Next on 2016/8/12.
//

#include "com_commax_devicemanager_devicesetting_JNIManager.h"
#include "ds/PacketRouter/PacketRouter.h"

#include <string>

typedef int (*FrameReceiveCallbackType)(unsigned char *, unsigned int);


unsigned char *convertByteArrayToCharPointer(JNIEnv *env, jbyteArray array);


static JavaVM *g_JVM;


jweak javaClassLoader = NULL; // Initialized in JNI_OnLoad later in this file.


PacketRouter *packetRouter;

/**
 * 자바 클래스 검색
 */
jclass FindJavaClass(JNIEnv *env, const char *className) {


    if (env->ExceptionCheck()) {
        LOGD("ERROR: exception pending on entry to FindJavaClass()");

        return NULL;
    }

    if (javaClassLoader == NULL) {

        LOGD("javaClassLoader == NULL");
        return env->FindClass(className);
    }


    jclass javaLangClassLoader = env->FindClass("java/lang/ClassLoader");


    jmethodID loadClass =
            env->GetMethodID(javaLangClassLoader,
                             "loadClass",
                             "(Ljava/lang/String;)Ljava/lang/Class;");



    // Try to find the named class.

    jstring strClassName = env->NewStringUTF(className);
    jclass cls = (jclass) env->CallObjectMethod(javaClassLoader,
                                                loadClass,
                                                strClassName);

    if (env->ExceptionCheck()) {
        env->ExceptionDescribe();

        LOGD("ERROR: unable to load class '%s' from %p\n",
             className, javaClassLoader);

        return NULL;
    }

    return cls;
}


/**
 * so 라이브러리가 로딩되었을 때 JVM이 호출
 */
JNIEXPORT jint JNICALL JNI_OnLoad(JavaVM *jvm, void *reserved) {
    // Grab the context ClassLoader of the current thread, if any.
    JNIEnv *env;
    if (jvm->GetEnv((void **) &env, JNI_VERSION_1_6) != JNI_OK) {
        LOGD("JNI_ERR");
        return JNI_ERR; // JNI version not supported.
    }
    LOGD("jvm->GetEnv OK");
    g_JVM = jvm;


    // Find thread's context class loader.
    jclass javaLangThread = env->FindClass("java/lang/Thread");


    //jclass javaLangClassLoader = env->FindClass("java/lang/ClassLoader");


    jmethodID currentThread = env->GetStaticMethodID(
            javaLangThread, "currentThread", "()Ljava/lang/Thread;");


    jmethodID getContextClassLoader = env->GetMethodID(
            javaLangThread, "getContextClassLoader", "()Ljava/lang/ClassLoader;");


    jobject thread = env->CallStaticObjectMethod(javaLangThread, currentThread);


    jobject classLoader = env->CallObjectMethod(thread, getContextClassLoader);

    if (classLoader != NULL) {
        LOGD("classLoader != NULL");
        javaClassLoader = env->NewWeakGlobalRef(classLoader);
    }


    return JNI_VERSION_1_6;
}


/**
 * so 라이브러리가 로딩이 해제되었을 때 JVM이 호출
 */
JNIEXPORT void JNICALL JNI_OnUnLoad(JavaVM *jvm, void *reserved) {
    JNIEnv *env;
    if (jvm->GetEnv((void **) &env, JNI_VERSION_1_6) != JNI_OK) {
        return;
    }

    // TODO(benh): Must we set 'MesosNativeLibrary.loaded' to false?

    if (javaClassLoader != NULL) {
        env->DeleteWeakGlobalRef(javaClassLoader);
        javaClassLoader = NULL;
    }
}

/**
 * FrameReceive 콜백
 */
int FrameReceiveCallback(unsigned char *rcvBuf, unsigned int rcvLength) {
    LOGD("FrameReceiveCallback");
    int status;
    JNIEnv *env;
    bool isAttached = false;


    status = g_JVM->GetEnv((void **) &env, JNI_VERSION_1_6);
    if (status < 0) {
        LOGD("callback_handler: failed to get JNI environment, "
                     "assuming native thread");
        //GVM에 현재 쓰레드를 붙임
        status = g_JVM->AttachCurrentThread(&env, NULL);
        if (status < 0) {
            LOGD("callback_handler: failed to attach "
                         "current thread");
            return 0;
        }
        isAttached = true;
    }


    jbyte a[] = {rcvBuf[0], rcvBuf[1], rcvBuf[2], rcvBuf[3], rcvBuf[4], rcvBuf[5], rcvBuf[6],
                 rcvBuf[7]};
    jbyteArray ret = env->NewByteArray(8);
    env->SetByteArrayRegion(ret, 0, 8, a);


    jclass classID = FindJavaClass(env, "com/commax/devicemanager/devicesetting/JNIManager");
    jmethodID methodID = env->GetStaticMethodID(classID, "callback", "([B)V");
    env->CallStaticVoidMethod(classID, methodID, ret);
    env->DeleteLocalRef(classID);


    int result;

    //GVM에서 현재 쓰레드 제거
    (g_JVM)->DetachCurrentThread();

    return result;
}

/**
 * 3번 포트 오픈
 */
JNIEXPORT jint JNICALL Java_com_commax_devicemanager_devicesetting_JNIManager_openPort3
        (JNIEnv *env, jclass obj) {

    packetRouter = new PacketRouter();

    packetRouter->setFrameReceiveCallback(FrameReceiveCallback);

    unsigned int res = 0;

    packetRouter->MediaClose();

    res = packetRouter->setInterfaceOpen(INTERFACE_COMMAX_RS485, COMMAX_PROTOCOL, "ttyS3");


    return res;

}

/**
 * 4번 포트 오픈
 */
JNIEXPORT jint JNICALL Java_com_commax_devicemanager_devicesetting_JNIManager_openPort4
        (JNIEnv *env, jclass obj) {


    unsigned int res = 0;

    res = packetRouter->setInterfaceOpen( INTERFACE_COMMAX_RS485, COMMAX_PROTOCOL,"ttyS4");
    return res;

}

/**
 * 포트 닫고 관련 클래스 메모리에서 제거
 */
JNIEXPORT jint JNICALL Java_com_commax_devicemanager_devicesetting_JNIManager_close
        (JNIEnv *env, jclass obj) {


    unsigned int res = 0;

    packetRouter->MediaClose();

    delete (packetRouter);

    return res;

}


/**
 * 디바이스 스캔
 * Class:     com_commax_devicemanager_devicesetting_JNIManager
 * Method:    scanDevice
 * Signature:
 */
JNIEXPORT void JNICALL Java_com_commax_devicemanager_devicesetting_JNIManager_scanDevice
        (JNIEnv *env, jclass obj, jbyteArray statusRequest, jint length) {


////C++에서 static 자바 메소드 호출 테스트(성공)
////    jclass classID = env->FindClass("com/commax/devicemanager/devicesetting/JNIManager");
////
////
////    jmethodID methodID = env->GetStaticMethodID(classID, "callback", "()V");
////    env->CallStaticVoidMethod(classID, methodID);
//
//
//
////C++에서 자바 메소드 호출 테스트(성공)
//
////    jclass javaClass = env->GetObjectClass(obj);
////    jmethodID method = env->GetMethodID(javaClass, "callback", "()V");
////    env->CallVoidMethod(obj, method);
////    return 0;
//



    unsigned char *statusRequestCharPointer = convertByteArrayToCharPointer(env, statusRequest);


    packetRouter->FrameSend(statusRequestCharPointer, length);


    //아래처럼 클래스의 객체를 생성하면 나중에 메모리 해제를 필수적으로 해야 함
    //PacketRouter* packetRouter = new PacketRouter();
    //res = packetRouter->setInterfaceOpen( INTERFACE_COMMAX_RS485, COMMAX_PROTOCOL, "ttyS4");

    //res가 0이지만 밑에서 로그를 찍으면 "result: 0"이 아니라 "result: "로 찍힘. 자바가 아니라서 0이 문자열로 변환되지 않는 듯함.


//    return res;


}

/**
 * byte[]를 char*로 변환
 */
unsigned char *convertByteArrayToCharPointer(JNIEnv *env, jbyteArray array) {
    int len = env->GetArrayLength(array);
    unsigned char *buf = new unsigned char[len];
    env->GetByteArrayRegion(array, 0, len, reinterpret_cast<jbyte *>(buf));
    return buf;
}



