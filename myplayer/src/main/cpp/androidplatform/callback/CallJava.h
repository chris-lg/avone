
/**
  *2019/4/8.
  *
 */

#ifndef AVONE_CALLJAVA_H
#define AVONE_CALLJAVA_H


#include "jni.h"
#include <linux/stddef.h>

#define MAIN_THREAD 0
#define CHILD_THREAD 1


class CallJava {

public:
    _JavaVM *javaVM = NULL;
    JNIEnv *jniEnv = NULL;
    jobject jobj;

    jmethodID jmid_parpared;
    jmethodID jmid_load;
    jmethodID jmid_timeinfo;

public:
    CallJava(_JavaVM *javaVM, JNIEnv *env, jobject *obj);
    ~CallJava();

    void onCallParpared(int type);

    void onCallLoad(int type, bool load);

    void onCallTimeInfo(int type, int curr, int total);

};


#endif //AVONE_CALLJAVA_H
