#pragma once
#include <Arduino.h>
#include <Wire.h>
#include <vector>

class I2CmainMC_comMC {
    private:
        Wire& i2c;
        uint8_t Address = 0x08;
        void sendOneByte(uint8_t data);
        uint8_t receiveOneByte();
        void beginTransmission();
        void endTransmission();
        int available();
    public:
        I2CmainMC_comMC(Wire& i2c, uint8_t address);
        ~I2CmainMC_comMC();
        int sendData(uint8_t* data, int size);
        int receiveData(std::vector<uint8_t>& buffer);
};