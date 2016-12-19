#ifndef CBRDAUJNI_LOG_H
#define CBRDAUJNI_LOG_H

#include <android/log.h>

#define  LOG_TAG    "CommaxJni"
#define  LOG_TAG_2    "CommaxDevice"
#define  LOG_TAG_3    "CommaxFinal"

#define _UNKNOWN    0
#define _DEFAULT    1
#define _VERBOSE    2
#define _DEBUG      3
#define _INFO      4
#define _WARN      5
#define _ERROR      6
#define _FATAL      7
#define _SILENT    8

#define  LOGUNK(...)  __android_log_print(_UNKNOWN,LOG_TAG,__VA_ARGS__)
#define  LOGDEF(...)  __android_log_print(_DEFAULT,LOG_TAG,__VA_ARGS__)
#define  LOGV(...)  __android_log_print(_VERBOSE,LOG_TAG,__VA_ARGS__)
#define  LOGD(...)  __android_log_print(_DEBUG,LOG_TAG,__VA_ARGS__)
#define  LOGD2(...)  __android_log_print(_DEBUG,LOG_TAG_2,__VA_ARGS__)
#define  LOGD3(...)  __android_log_print(_DEBUG,LOG_TAG_3,__VA_ARGS__)
#define  LOGI(...)  __android_log_print(_INFO,LOG_TAG,__VA_ARGS__)
#define  LOGW(...)  __android_log_print(_WARN,LOG_TAG,__VA_ARGS__)
#define  LOGE(...)  __android_log_print(_ERROR,LOG_TAG,__VA_ARGS__)
#define  LOGF(...)  __android_log_print(_FATAL,LOG_TAG,__VA_ARGS__)
#define  LOGS(...)  __android_log_print(_SILENT,LOG_TAG,__VA_ARGS__)

#endif //CBRDAUJNI_LOG_H



