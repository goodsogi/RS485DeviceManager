LOCAL_PATH := $(call my-dir)
include $(CLEAR_VARS)

LOCAL_MODULE := JNIManager
LOCAL_SRC_FILES := JNIManager.cpp

include $(BUILD_SHARED_LIBRARY)
