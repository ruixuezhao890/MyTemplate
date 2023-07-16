/**
*********************************************************************
*********
* @project_name :templateDevelopment
* @file : MyBlueTooth.cpp
* @author : zen3
* @brief : None
* @attention : None
* @date : 2023/7/15 
*********************************************************************
*********
*/
//

#include "MyBlueTooth.h"

MyBlueTooth::MyBlueTooth(UART_HandleTypeDef *huart) {
    this->BlueUsart=new MyUsart(huart);
    this->usart=huart;
    this->BlueUsart->ReceiveInit();
}

MyBlueTooth::~MyBlueTooth() {
    delete BlueUsart;
}

void MyBlueTooth::SendString(uint8_t* SendData) {

        this->BlueUsart->Myprintf("%s",SendData);

}

void MyBlueTooth::SendOneChannel(uint16_t *SendData, uint16_t DataSize) {
    if (DataSize>1000){
        return;
    }
    for (int i = 0; i < DataSize; ++i) {
        this->BlueUsart->Myprintf("G%d,0*",SendData[i]);
    }
}

void MyBlueTooth::SendOneChannel(float32_t *SendData, uint16_t DataSize) {
    if (DataSize>1000){
        return;
    }
    for (int i = 0; i < DataSize; ++i) {
        this->BlueUsart->Myprintf("G%f,0*",SendData[i]);
    }
}

void MyBlueTooth::SendTwoChannel(uint16_t *SendData0,uint16_t *SendData1, uint16_t DataSize) {
    if (DataSize>1000){
        return;
    }
    for (int i = 0; i < DataSize; ++i) {
        this->BlueUsart->Myprintf("*G%d,%d*",SendData0[i],SendData1[i]);
    }
}

void MyBlueTooth::SendTwoChannel(float32_t *SendData0,float32_t *SendData1, uint16_t DataSize) {
    if (DataSize>1000){
        return;
    }
    for (int i = 0; i < DataSize; ++i) {
        this->BlueUsart->Myprintf("*G%f,%f*",SendData0[i],SendData1[i]);
    }
}
/*void MyBlueTooth::SendTwoChannel(uint16_t *SendData0, uint16_t *SendData1, uint16_t DataSize0, uint16_t DataSize1) {
    if (DataSize0>1000||DataSize1>1000){
        return;
    }
}

void MyBlueTooth::SendTwoChannel(float32_t *SendData0, float32_t *SendData1, uint16_t DataSize0, uint16_t DataSize1) {

}*//***************************************************************
  *  @brief     函数作用 此函数接收外部的指令做出对应的操作
  *  @param     参数   RecCmd:这是做出判断的指令
  *                    第二个参数时函数指针 即接收对应指令做出对应操作的函数
  *  @note      备注 ：使用string字符类型时 包含头文件#include <string>
  *                 该函数重载好几个版本 适应了不同类型的字符串支持原生的c语言char类型与c++中的string类型
  *                 以及回调函数最多支持两个参数的传入 回调函数的返回类型只有void
  *  @Sample usage:     函数的使用方法 ：直接调用
   * @author     wangzibo
 **************************************************************/

void MyBlueTooth::ReceiveCmdSlot(char* RecCmd, void (*funcPtr)()) {
    if ((*this->BlueUsart->Re_GetData())==*RecCmd){
        funcPtr();
    }
//    this->BlueUsart->ReceiveInit();
}

void MyBlueTooth::ReceiveCmdSlot(char* RecCmd, void (*funcPtr)(uint16_t),uint16_t Parameters) {
    if ((*this->BlueUsart->Re_GetData())==*RecCmd){
        funcPtr(Parameters);
    }
//    this->BlueUsart->ReceiveInit();
}

void MyBlueTooth::ReceiveCmdSlot(char* RecCmd, void (*funcPtr)(uint16_t,uint16_t),uint16_t Parameters0,uint16_t Parameters1) {
    if ((*this->BlueUsart->Re_GetData())==*RecCmd){
        funcPtr(Parameters0,Parameters1);
    }
//    this->BlueUsart->ReceiveInit();
}

void MyBlueTooth::SetUsart(UART_HandleTypeDef *huart) {
    this->usart=huart;
}

UART_HandleTypeDef *MyBlueTooth::GetUsrat() {
    return this->usart;
}

MyUsart *MyBlueTooth::GetBlueUsart() {
    return this->BlueUsart;
}


void MyBlueTooth::ReceiveCmdSlot(std::string RecCmd, void (*funcPtr)()) {
    if (RecCmd.find(*this->BlueUsart->Re_GetData())){
        funcPtr();
    }
}

void MyBlueTooth::ReceiveCmdSlot(std::string RecCmd, void (*funcPtr)(uint16_t), uint16_t Parameters) {

}

void MyBlueTooth::ReceiveCmdSlot(std::string RecCmd, void (*funcPtr)(uint16_t, uint16_t), uint16_t Parameters0,
                                 uint16_t Parameters1) {

}