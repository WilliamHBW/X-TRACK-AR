/*
  Arduino LSM6DS3 - Simple Gyroscope

  This example reads the gyroscope values from the LSM6DS3 sensor 
  and prints them to the Serial Monitor or Serial Plotter, as a directional detection of 
  an axis' angular velocity.

  The circuit:
  - Arduino Uno WiFi Rev2 or Arduino Nano 33 IoT

  Created by Riccardo Rizzo

  Modified by Benjamin Dannegård
  30 Nov 2020

  This example code is in the public domain.
*/
#include "ArduinoIMU.h"  

ArduinoIMU::ArduinoIMU() {
    ax = 0;
    ay = 0;
    az = 0;
    gx = 0;
    gy = 0;
    gz = 0;
    serialIMU = new SerialPort("COM3");
    setup_success = serialIMU->Setup();
}

bool ArduinoIMU::setup() {
}

void ArduinoIMU::GetIMUInfo(char* info, uint32_t len)
{
    if(setup_success == -1)
    {
        snprintf(info,len,"%d\n%d\n%d\n%d\n%d\n%d",0, 0, 0, 0, 0, 0);
        return;
    }
    int imu_buf_len = sizeof(imu_info);
    DWORD imu_read_len = serialIMU->ReadData(imu_info, imu_buf_len);

    if (imu_read_len > 0) {
        ax = *(float*)&imu_info[0];
        ay = *(float*)&imu_info[4];
        az = *(float*)&imu_info[8];
        gx = *(float*)&imu_info[12];
        gy = *(float*)&imu_info[16];
        gz = *(float*)&imu_info[20];
    }
    
    ax_i = (int)(ax*100);
    ay_i = (int)(ay*100);
    az_i = (int)(az*100);
    gx_i = (int)(gx*100);
    gy_i = (int)(gy*100);
    gz_i = (int)(gz*100);

    std::cout << "ax_i: " << ax_i << std::endl;
    std::cout << "ay_i: " << ay_i << std::endl;
    std::cout << "az_i: " << az_i << std::endl;
    std::cout << "gx_i: " << gx_i << std::endl;
    std::cout << "gy_i: " << gy_i << std::endl;
    std::cout << "gz_i: " << gz_i << std::endl;

    snprintf(info,len,"%d\n%d\n%d\n%d\n%d\n%d",ax_i, ay_i, az_i, gx_i, gy_i, gz_i);
}