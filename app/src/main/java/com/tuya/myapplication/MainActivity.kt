package com.tuya.myapplication

import android.os.Bundle
import android.widget.Button
import androidx.appcompat.app.AppCompatActivity

class MainActivity : AppCompatActivity() {


    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_main)
        this.findViewById<Button>(R.id.btn_start).setOnClickListener {
            LeakManager.native_memory_start()
        }

        this.findViewById<Button>(R.id.btn_stop).setOnClickListener {
            LeakManager.native_memory_stop("/sdcard/lplp.log")
        }
    }
}