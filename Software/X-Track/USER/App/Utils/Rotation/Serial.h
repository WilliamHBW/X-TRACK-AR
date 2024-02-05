#pragma once  
#ifndef SERIALPORT_H_    
#define SERIALPORT_H_   

#include <windows.h>
#include <iostream>

class SerialPort {
private:
    HANDLE hSerial;
    bool connected;
    COMMTIMEOUTS timeouts;

public:
    SerialPort(const char *portName) {
        // 打开串口
        hSerial = CreateFileA("COM3",
                      GENERIC_READ | GENERIC_WRITE,
                      1,
                      NULL,
                      OPEN_EXISTING,
                      FILE_ATTRIBUTE_NORMAL,
                      NULL);

        // 检查串口是否成功打开
        if (hSerial == INVALID_HANDLE_VALUE) {
            if (GetLastError() == ERROR_FILE_NOT_FOUND) {
                std::cerr << "Serial port doesn't exist!" << std::endl;
            }
            std::cerr << "Error opening serial port!" << std::endl;
            connected = false;
        } else {
            DCB dcbSerialParams = {0};
            if (!GetCommState(hSerial, &dcbSerialParams)) {
                std::cerr << "Failed to get current serial parameters!" << std::endl;
            } else {
                // 设置串口参数
                dcbSerialParams.BaudRate = CBR_9600;
                dcbSerialParams.ByteSize = 8;
                dcbSerialParams.StopBits = ONESTOPBIT;
                dcbSerialParams.Parity = NOPARITY;
                dcbSerialParams.fDtrControl = DTR_CONTROL_ENABLE;

                if (!SetCommState(hSerial, &dcbSerialParams)) {
                    std::cerr << "Could not set Serial Port parameters" << std::endl;
                } else {
                    // 设置超时
                    timeouts.ReadIntervalTimeout = 50;
                    timeouts.ReadTotalTimeoutConstant = 50;
                    timeouts.ReadTotalTimeoutMultiplier = 10;
                    timeouts.WriteTotalTimeoutConstant = 50;
                    timeouts.WriteTotalTimeoutMultiplier = 10;
                    if (!SetCommTimeouts(hSerial, &timeouts)) {
                        std::cerr << "Could not set serial port timeouts" << std::endl;
                    } else {
                        connected = true;
                    }
                }
            }
        }
    }

    ~SerialPort() {
        if (connected) {
            // 关闭串口
            CloseHandle(hSerial);
        }
    }

    int Setup() {
        // 串口初始化过程在构造函数中已完成
        return connected ? 0 : -1;
    }

    int ReadData(char *buffer, unsigned int buf_size) {
        DWORD bytesRead;
        DWORD toRead = 0;

        // 发送isread信号 - 假定为'1'字符，你需要根据实际情况调整
        char signal[] = {1};
        if (!WriteFile(hSerial, signal, 1, &toRead, NULL)) {
            std::cerr << "Failed to send isread signal" << std::endl;
            return -1;
        }

        // 等待iswrite信号 - 假定为'2'字符，你需要根据实际情况调整
        char iswriteSignal;
        do {
            ReadFile(hSerial, buffer, buf_size, &bytesRead, NULL);
        } while (memcmp(&buffer[24], "\xff", 1) != 0);

        return bytesRead;
    }
};

#endif