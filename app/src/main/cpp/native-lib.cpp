#include <string>
#include <memory>
#include <cstdio>
#include <unistd.h>
#include <jni.h>
#include <MemoryTrace.hpp>
#include <fstream>

static void native_memory_start(JNIEnv *env, jclass clazz){
    leaktracer::MemoryTrace::GetInstance().startMonitoringAllThreads();
}

static void native_memory_stop(JNIEnv *env, jclass clazz, jstring memoryInfoPath){
    char * memoryInfoPathStr = const_cast<char *>(env->GetStringUTFChars(memoryInfoPath, nullptr));
    leaktracer::MemoryTrace::GetInstance().stopAllMonitoring();
    std::ofstream out;
//    "/mnt/sdcard/leaktracerlhc.log"
    out.open(memoryInfoPathStr, std::ios_base::out);
    if (out.is_open()) {
        leaktracer::MemoryTrace::GetInstance().writeLeaks(out);
    }
    env->ReleaseStringUTFChars(memoryInfoPath, memoryInfoPathStr);
}

static const JNINativeMethod gMethods[] = {
        {"native_memory_start",           "()V",                                                            (void *) native_memory_start},
        {"native_memory_stop",           "(Ljava/lang/String;)V",                                                            (void *) native_memory_stop},
};


JNIEXPORT jint JNI_OnLoad(JavaVM *vm, void *) {
    JNIEnv *env;
    if (vm->GetEnv((void **) &env, JNI_VERSION_1_6) != JNI_OK) {
        return JNI_FALSE;
    }
    jclass clazz = env->FindClass("com/tuya/myapplication/LeakManager");
    if (!clazz) {
        return JNI_ERR;
    }

    if (env->RegisterNatives(clazz, gMethods, sizeof(gMethods) / sizeof(gMethods[0])) != JNI_OK) {
        return JNI_ERR;
    }
    return JNI_VERSION_1_6;
}