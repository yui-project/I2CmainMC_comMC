#include "I2CmainMC_comMC.h"

I2CmainMC_comMC::I2CmainMC_comMC(TwoWire& i2c, uint8_t address) : i2c(i2c), Address(address) {

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
    i2c.requestFrom(Address, (uint8_t)1);
    if(i2c.available()){
        uint8_t data = i2c.read();
        return data;
    }
    return 0;
}

int I2CmainMC_comMC::sendData(uint8_t* data, int size) {  
    size_t offset = 0;
    
    while (offset < size) {
        // 残りのデータ量と32バイトを比較し、小さい方を送信サイズとする
        size_t chunkSize = size - offset;
        if (chunkSize > 32) {
            chunkSize = 32;
        }

        beginTransmission();
        i2c.write(&data[offset], chunkSize);
        
        // 送信実行
        if(endTransmission() != 0){
            return false; // 送信失敗
        }
        
        offset += chunkSize;
    }
    return true; // 全データ送信成功
}

int I2CmainMC_comMC::receiveData(std::vector<uint8_t>& buffer, size_t readSize) {
    // I2Cバスへデータ要求
    // requestFromは読み取れたバイト数を返します
    uint8_t count = i2c.requestFrom(Address, (uint8_t)readSize);
    
    if (count != readSize) {
        return false; // 要求したサイズ分受信できなかった場合
    }

    buffer.clear(); // バッファを一度空にする
    buffer.reserve(readSize); // メモリ確保の効率化

    while(i2c.available() > 0){
        buffer.push_back(i2c.read());
    }
    return buffer.size();
}

int I2CmainMC_comMC::available() {
    return i2c.available();
}