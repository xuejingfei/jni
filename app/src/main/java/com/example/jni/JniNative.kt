package com.example.jni

/**
 * Author：xuejingfei
 *
 * Description：
 *
 * Date：2022/1/21 10:45
 */
object JniNative {
    init {
        System.loadLibrary("native-lib")
        initID()
    }


    private external fun initID()

    /**
     * 基本类型
     */
    external fun basicTypeFromJNI(
        short: Short,
        int: Int,
        long: Long,
        float: Float,
        double: Double,
        char: Char,
        boolean: Boolean,
        byte: Byte,
    ): String


    /**
     * 字符串类型
     */
    external fun stringTypeFromJNI(str:String):String


    /**
     * 访问基本数据数组
     */

    external fun basicArrayTypeFromJNI(array: IntArray):Int


    /**
     * 访问引用字符串数据类型
     */
    external fun stringArrayTypeFromJNI(size:Int):Array<String>


    /**
     * 访问java静态方法
     */
    external fun callJavaStaticMethod()


    /**
     * 访问java实例方法
     */
    external fun callJavaInstanceMethod():Cat


    /**
     * 访问实例变量
     */
    external fun accessInstanceField(cat:Cat)


    /**
     * 访问静态变量
     */
    external fun accessStaticField()


    /**
     * 调用父类的方法
     */
    external fun callSuperInstanceMethod(cat:Cat)


}