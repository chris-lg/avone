
/**
  *2019/4/8.
  *
 */

#include "CallJava.h"
#include "../MyLog.h"


CallJava::CallJava(_JavaVM *javaVM, JNIEnv *env, jobject *obj) {

    this->javaVM = javaVM;
    this->jniEnv = env;
    this->jobj = *obj;
    this->jobj = env->NewGlobalRef(jobj);

    jclass jlz = jniEnv->GetObjectClass(jobj);
    if (!jlz) {
        LOGE("get jclass wrong");
        return;
    }

    jmid_parpared = env->GetMethodID(jlz, "onCallPrepared", "()V");
    jmid_load = env->GetMethodID(jlz, "onCallLoad", "(Z)V");
    jmid_timeinfo = env->GetMethodID(jlz, "onCallTimeInfo", "(II)V");


}

void CallJava::onCallParpared(int type) {

    if (type == MAIN_THREAD) {
        jniEnv->CallVoidMethod(jobj, jmid_parpared);
    } else if (type == CHILD_THREAD) {
        JNIEnv *jniEnv;
        if (javaVM->AttachCurrentThread(&jniEnv, 0) != JNI_OK) {
            LOGE("get child thread jnienv worng");
            return;
        }
        jniEnv->CallVoidMethod(jobj, jmid_parpared);
        javaVM->DetachCurrentThread();
    }

}

void CallJava::onCallLoad(int type, bool load) {

    if (type == MAIN_THREAD) {
        jniEnv->CallVoidMethod(jobj, jmid_load, load);
    } else if (type == CHILD_THREAD) {
        JNIEnv *jniEnv;
        if (javaVM->AttachCurrentThread(&jniEnv, 0) != JNI_OK) {
            LOGE("call onCallLoad worng");
            return;
        }
        jniEnv->CallVoidMethod(jobj, jmid_load, load);
        javaVM->DetachCurrentThread();
    }


}

void CallJava::onCallTimeInfo(int type, int curr, int total) {
    if (type == MAIN_THREAD) {
        jniEnv->CallVoidMethod(jobj, jmid_timeinfo, curr, total);
    } else if (type == CHILD_THREAD) {
        JNIEnv *jniEnv;
        if (javaVM->AttachCurrentThread(&jniEnv, 0) != JNI_OK) {
            LOGE("call onCallTimeInfo worng");
            return;
        }
        jniEnv->CallVoidMethod(jobj, jmid_timeinfo, curr, total);
        javaVM->DetachCurrentThread();
    }
}