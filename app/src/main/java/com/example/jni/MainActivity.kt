package com.example.jni

import android.os.Bundle
import android.widget.TextView
import androidx.appcompat.app.AppCompatActivity


class MainActivity : AppCompatActivity() {
    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_main)

//        val arr = IntArray(10)
//        for (i in arr.indices) {
//            arr[i] = i
//        }

//        var result = "结果"
//        val array = JniNative.stringArrayTypeFromJNI(2) as Array<String>
//        array.forEach { result += it }

        // Example of a call to a native method

//        JniNative.callJavaStaticMethod()
//        JniNative.accessStaticField()

        val car = JniNative.callJavaInstanceMethod()
        JniNative.accessInstanceField(car)

        JniNative.callSuperInstanceMethod(car)

        findViewById<TextView>(R.id.sample_text).text = car.getName()

    }


}