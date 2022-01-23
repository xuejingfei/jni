#include <jni.h>
#include <string>




#define GLOBAL(env, obj) env->NewGlobalRef(obj))


static jclass catClass;
static jmethodID setTagMethodID;
static jmethodID constructMethodID;
static jmethodID setNameMethodID;
static jfieldID nameField;
static jfieldID tagField;
static jclass animalClass;
static jmethodID runMethodID;


extern "C"
JNIEXPORT void JNICALL
Java_com_example_jni_JniNative_initID(JNIEnv *env, jobject clazz) {
    catClass = static_cast<jclass>(GLOBAL(env,(*env).FindClass("com/example/jni/Cat"));
    setTagMethodID = (*env).GetStaticMethodID(catClass,"setTAG", "(Ljava/lang/String;)V");
    constructMethodID = (*env).GetMethodID(catClass,"<init>","()V");
    setNameMethodID = (*env).GetMethodID(catClass,"setName", "(Ljava/lang/String;)V");
    nameField = (*env).GetFieldID(catClass, "name", "Ljava/lang/String;");
    tagField = (*env).GetStaticFieldID(catClass,"TAG", "Ljava/lang/String;");
    animalClass = static_cast<jclass>(GLOBAL(env,(*env).FindClass("com/example/jni/Animal"));
    runMethodID =  (*env).GetMethodID(animalClass,"run","()V");

}

/**
 * JNIEnv：JVM函数表的指针
 * jobject: 调用java中native方法的实例或class对象 如果是实例
 *
 short: Short,
        int: Int,
        long: Long,
        float: Float,
        double: Double,
        char: Char,
        boolean: Boolean,
        byte: Byte,
        string: String,
        obj: Object,
        clazz:Class<*>,
        array: Array<Int>
    ): String
**/

using namespace std;
extern "C" JNIEXPORT jstring JNICALL
Java_com_example_jni_JniNative_basicTypeFromJNI(
        JNIEnv *env,
        jobject obj,
        jshort s,
        jint i,
        jlong j,
        jfloat f,
        jdouble d,
        jchar c,
        jboolean b,
        jbyte byte) {
    string hello = "Hello from C++";

    hello.append("short = ").append(to_string(s)).append("\n");
    hello.append("int = ").append(to_string(i)).append("\n");
    hello.append("long = ").append(to_string(j)).append("\n");
    hello.append("float = ").append(to_string(f)).append("\n");
    hello.append("double = ").append(to_string(d)).append("\n");
    hello.append("char = ").append(to_string(c)).append("\n");
    hello.append("boolean = ").append(to_string(b)).append("\n");
    hello.append("byte = ").append(to_string(byte)).append("\n");

    return env->NewStringUTF(hello.c_str());
}


extern "C" JNIEXPORT jstring JNICALL
Java_com_example_jni_JniNative_stringTypeFromJNI(
        JNIEnv *env,
        jobject thiz,
        jstring str) {

    string hello = "字符串类型：\n";

    /**
     * java 默认的是Unicode编码的
     * C，C++ 默认是UFT-8编码，以'\0'结尾
     */
    const char *utfStr = NULL;
    utfStr = (*env).GetStringUTFChars(str, NULL);
    if (utfStr == NULL) {
        return NULL;
    }
    hello.append("GetStringUTFChars -->").append(utfStr).append("\n");
    jsize uft8Length = ((*env)).GetStringUTFLength(str);
    hello.append("GetStringUTFLength -->").append(to_string(uft8Length)).append("\n");
    (*env).ReleaseStringUTFChars(str, utfStr);

    jsize len = env->GetStringLength(str);
    hello.append("Unicode格式--》长度").append(to_string(len)).append("\n");

    //适合小字符串或者一个字符串的一部分
    char buff[128] = "hello ";
    char *pBuffer = buff + uft8Length;
    (*env).GetStringUTFRegion(str, 0, len, pBuffer);
    hello.append("GetStringUTFRegion -->").append(pBuffer);

    return (*env).NewStringUTF(hello.c_str());
}


extern "C"
JNIEXPORT jint JNICALL
Java_com_example_jni_JniNative_basicArrayTypeFromJNI(JNIEnv *env, jobject thiz, jintArray j_array) {
//    jint i, sum = 0;
//    jint *c_array;
//    jsize arr_len;
//    c_array = (*env).GetIntArrayElements(j_array, NULL);
//    if (c_array == NULL) {
//        return 0;
//    }
//    arr_len = (*env).GetArrayLength(j_array);
//    for (i = 0; i < arr_len; i++) {
//        sum += c_array[i];
//    }
//    (*env).ReleaseIntArrayElements(j_array, c_array, 0);


//    jint i,sum = 0;
//    jint *c_array;
//    jint array_length = (*env).GetArrayLength(j_array);
//    c_array = (jint *)malloc(sizeof(jint) * array_length);
//    memset(c_array,0,sizeof(jint) * array_length);
//
//    (*env).GetIntArrayRegion(j_array,0,array_length,c_array);
//
//    for (i =0;i<array_length;i++) {
//        sum+=c_array[i];
//    }
//
//    free(c_array);

/**
 * GetIntArrayRegion 适合小量，固定大小的数组，效率最高，需要预分配缓冲区
 * GetPrimitiveArrayCritical ：不需要预分配缓冲区，原始数组长度也不确定，本地代码不想在获取数组元素指针时被阻塞使用
 * GetIntArrayElements：最安全的，这个指针可能指向原始数据。也可能指向原始数据的复制
 *
 */
    jint i,sum=0;
    jint *c_array;
    jint arr_len;
    jboolean isCopy;
    c_array = (jint*)(*env).GetPrimitiveArrayCritical(j_array,&isCopy);
    if (c_array == NULL) {
        return 0;
    }
    arr_len = (*env).GetArrayLength(j_array);
    for (i = 0; i < arr_len; ++i) {
        sum += c_array[i];
    }

    (*env).ReleasePrimitiveArrayCritical(j_array,c_array,0);
    return sum;
}


extern "C"
JNIEXPORT jobjectArray JNICALL
Java_com_example_jni_JniNative_stringArrayTypeFromJNI(JNIEnv *env, jobject thiz, jint size) {
    jclass strClass = (*env).FindClass("java/lang/String");
    if(strClass == NULL) {
        return NULL;
    }
    jobjectArray result = (*env).NewObjectArray(size,strClass,NULL);
    if(result == NULL) {
        return NULL;
    }
    for (int i = 0; i < size; ++i) {
        (*env).SetObjectArrayElement(result,i,(*env).NewStringUTF("xx"));
    }

    (*env).DeleteLocalRef(strClass);

    return result;
}


extern "C"
JNIEXPORT void JNICALL
Java_com_example_jni_JniNative_callJavaStaticMethod(JNIEnv *env, jobject thiz) {
    jstring args = (*env).NewStringUTF("TAG");
    (*env).CallStaticVoidMethod(catClass,setTagMethodID,args);
    //删除局部引用
    (*env).DeleteLocalRef(args);
}


extern "C"
JNIEXPORT jobject JNICALL
Java_com_example_jni_JniNative_callJavaInstanceMethod(JNIEnv *env, jobject thiz) {
    jobject jobj = NULL;
    //创建该类的实例化
    jobj = (*env).NewObject(catClass,constructMethodID);
    if(jobj == NULL) {
        return NULL;
    }

    jstring args = (*env).NewStringUTF("cat");
    //执行方法
    (*env).CallVoidMethod(jobj,setNameMethodID,args);
    //删除局部引用
    (*env).DeleteLocalRef(args);
    return jobj;
}



extern "C"
JNIEXPORT void JNICALL
Java_com_example_jni_JniNative_accessInstanceField(JNIEnv *env, jobject thiz,jobject jobject1) {
    jstring name = static_cast<jstring>((*env).GetObjectField(jobject1, nameField));
    if (name == NULL){
        return;
    }

    const char* c_str = NULL;
    c_str = (*env).GetStringUTFChars(name,NULL);
    if (c_str == NULL) {
        return;
    }
    (*env).ReleaseStringUTFChars(name,c_str);

    string result;
    result.append(c_str).append("native");

    //改变变量
    (*env).SetObjectField(jobject1,nameField,(*env).NewStringUTF(result.c_str()));
    (*env).DeleteLocalRef(jobject1);
    (*env).DeleteLocalRef(name);

}


extern "C"
JNIEXPORT void JNICALL
Java_com_example_jni_JniNative_accessStaticField(JNIEnv *env, jobject thiz) {

    //获取静态变量
    jstring tag = static_cast<jstring>((*env).GetStaticObjectField(catClass, tagField));
    if(tag == NULL) {
        return;
    }

    //unicode 转 uft-8
    const char* c_tag = NULL;
    c_tag = (*env).GetStringUTFChars(tag,NULL);
    if(c_tag == NULL) {
        return;
    }
    (*env).ReleaseStringUTFChars(tag,c_tag);

    string newTag;
    newTag.append(c_tag).append("native");

    //更改静态变量
    (*env).SetStaticObjectField(catClass,tagField,(*env).NewStringUTF(newTag.c_str()));

    //释放局部引用
    //在JVM中维护着一个引用表，用于存储局部和全局引用变量，这个表的最大存储空间是512个引用，超过这个数就会造成引用表溢出
    (*env).DeleteLocalRef(tag);
}


extern "C"
JNIEXPORT void JNICALL
Java_com_example_jni_JniNative_callSuperInstanceMethod(JNIEnv *env, jobject thiz, jobject cat) {

    (*env).CallNonvirtualVoidMethod(cat,animalClass,runMethodID);

    //回收局部变量
    (*env).DeleteLocalRef(cat);
}
