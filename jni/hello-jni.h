#include <jni.h>
// #include "JNIHelp.h"

#ifndef _hello_jni_h
#define _hello_jni_h
#ifdef __cplusplus
extern "C" {
#endif

#ifndef NELEM
# define NELEM(x) ((int) (sizeof(x) / sizeof((x)[0])))
#endif

static jstring stringFromJNI(JNIEnv *, jclass);

#ifdef __cplusplus
}
#endif
#endif
