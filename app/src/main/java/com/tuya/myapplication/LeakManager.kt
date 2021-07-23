package com.tuya.myapplication

object LeakManager {
    init {
        System.loadLibrary("leak")
    }

    external fun native_memory_start()

    /**
     * @param path 路径
     */
    external fun native_memory_stop(path :String)
}