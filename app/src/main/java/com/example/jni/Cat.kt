package com.example.jni

import android.util.Log

/**
 * Author：xuejingfei
 *
 * Description：
 *
 * Date：2022/1/23 11:59
 */
class Cat : Animal() {
    companion object Cat {

        @JvmStatic
        var TAG:String ?=null

        @JvmStatic
        fun setTag(tag:String) {
            TAG = tag;
        }
    }



    private var name: String? = null

    override fun run() {
        Log.d("xjf", "cat run")
    }


    fun  setName(name:String) {
        this.name = name;
    }


    fun getName():String? = name



}