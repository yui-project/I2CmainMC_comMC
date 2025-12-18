#include "I2CmainMC_comMC.h"

I2CmainMC_comMC::I2CmainMC_comMC(Wire& i2c, uint8_t address) : i2c(i2c), Address(address) {
    i2c.begin();
}

I2CmainMC_comMC::~I2CmainMC_comMC() {
    // Destructor logic if needed
}

void I2CmainMC_comMC::beginTransmission() {
    i2c.beginTransmission(Address);
}

int I2CmainMC_comMC::endTransmission(){
    return i2c.endTransmission();
}

void I2CmainMC_comMC::sendOneByte(uint8_t data) {
    beginTransmission();
    i2c.write(data);
    endTransmission();
}

uint8_t I2CmainMC_comMC::receiveOneByte() {
    beginTransmission();
    uint8_t data = i2c.read();
    endTransmission();
    return data;
}

int I2CmainMC_comMC::sendData(uint8_t* data, int size) {  
    beginTransmission();
    for(int i = 0; i < size / 32 ; i++){
        uint8_t sendbuffer[32];
        for(int j = 0; j < 32; ++j) {
            sendbuffer[j] = data[i * 32 + j];
        }
        i2c.write(sendbuffer, 32);
    }
       
    if(endTransmission() == 0){
        //送信成功
        return 1;
    }else{
        //送信失敗
        return 0;
    }
}

int I2CmainMC_comMC::receiveData(uint8_t* buffer, int size) {
    std::vector<uint8_t> recieveBuffer;
    beginTransmission();
    while(available() > 0){
        std::vector<uint8_t> preBuffer = i2c.read();
        recieveBuffer.insert(recieveBuffer.end(), preBuffer.begin(), preBuffer.end());
    }
    endTransmission();
    if(recieveBuffer.size() > 0){
        //受信成功
        return recieveBuffer.size();
    }else if(recieveBuffer.size() == 0){
        //受信失敗orデータなし
        return 0;
    }
}

int I2CmainMC_comMC::available() {
    return i2c.available();
}