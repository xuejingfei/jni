# jni用法
文档 https://doc.yonyoucloud.com/doc/wiki/project/jni-ndk-developer-guide/recommend.html
##### 局部引用，全局引用，弱全局引用的区别
1.局部引用使用NewLocalRef创建，会阻止GC回收所引用的对象，不能跨函数，跨线程使用，函数返回后，局部引用的对象会被jvm自动释放，或者调用DeleteLocalRef释放。
2.全局引用使用NewGlobalRef基于局部引用创建，也会阻止GC回收所引用的对象，可以跨方法跨线程使用，jvm不会自动使用，必须手动调用DeleteGlobalRef手动释放。
3.弱全局引用使用NewWeakGlobalRef基于局部引用或者全局引用创建，不会阻止GC回收所引用的对象，，可以跨方法，跨线程使用，引用不会自动释放，在jvm内存吃紧的时候进行回收。
