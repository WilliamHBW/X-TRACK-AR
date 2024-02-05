#include <stdint.h>
#include <iostream>
#include "Serial.h"

class ArduinoIMU {
public:

    float gx, gy, gz, ax, ay, az;
    int gx_i, gy_i, gz_i, ax_i, ay_i, az_i;
    SerialPort* serialIMU;
    int setup_success;
    char imu_info[25];

    ArduinoIMU();
    bool setup();
    void GetIMUInfo(char* info, uint32_t len);
};