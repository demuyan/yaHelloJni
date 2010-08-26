/*
 * Copyright (C) 2009 The Android Open Source Project
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 */
#include <string.h>
#include <android/log.h>
#include <jni.h>
#include "hello-jni.h"

#define LOG_VERBOSE (2)
#define LOG_TAG ("hello-jni!")

#define LOGD(... ) ((void)__android_log_print(ANDROID_LOG_DEBUG, LOG_TAG, __VA_ARGS__))


/*
 * Register native JNI-callable methods.
 *
 * "className" looks like "java/lang/String".
 */
int jniRegisterNativeMethods(JNIEnv* env, const char* className,
    const JNINativeMethod* gMethods, int numMethods)
{
    jclass clazz;

    LOGD("Registering %s natives\n", className);
    clazz = (*env)->FindClass(env, className);
    if (clazz == NULL) {
        LOGD("Native registration unable to find class '%s'\n", className);
        return -1;
    }
    if ((*env)->RegisterNatives(env, clazz, gMethods, numMethods) < 0) {
        LOGD("RegisterNatives failed for '%s'\n", className);
        return -1;
    }
    return 0;
}


static jstring
stringFromJNI( JNIEnv* env,jobject thiz )
{
    return (*env)->NewStringUTF(env, "Hello from JNI - jniRegisterNativeMethods ver.");
}

static JNINativeMethod sMethods[] = {
     /* name, signature, funcPtr */
    {"stringFromJNI", "()Ljava/lang/String;", (void*)stringFromJNI},
};

#define EXPORT __attribute__((visibility("default")))

EXPORT jint JNI_OnLoad(JavaVM* vm, void* reserved)
{

    LOGD("JNI_ONLOAD\n");

    JNIEnv* env = NULL;
    jint result = -1;
    
	if ((*vm)->GetEnv(vm, (void**) &env, JNI_VERSION_1_6) != JNI_OK) {
        return result;
    }


    jniRegisterNativeMethods(env, "com/example/hellojni/HelloJni", sMethods, NELEM(sMethods));
    return JNI_VERSION_1_6;
}


