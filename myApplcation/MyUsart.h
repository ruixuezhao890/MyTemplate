/**
*********************************************************************
*********
* @project_name :templateDevelopment
* @file : myUsart.h
* @author : zen3
* @brief : None
* @attention : None
* @date : 2023/4/27 
*********************************************************************
*********
*/
//

#ifndef TEMPLATEDEVELOPMENT_MYUSART_H
#define TEMPLATEDEVELOPMENT_MYUSART_H



#define RELENTH 256
#ifdef __cplusplus

extern "C"
{
#endif
#include "Myapplication.h"
//#include "IncludeALL.h"
/*______________________类的声明在这下面________________:*/
class MyUsart{
public:
    MyUsart();
    MyUsart(UART_HandleTypeDef *huart);
    MyUsart(uint16_t Enable);
    void ReceiveInit();
    void Send(uint8_t * sendBuf);
//    void SendString(std::string * stringBuf,uint16_t Length);
    void SendString(uint8_t * stringBuf,uint16_t Length);
    void SendString(const char* stringBuf,uint16_t Length);
    void SendOneInt(uint16_t IntBuf);
    void SendInt(uint16_t* IntBuf,uint16_t Length);
    void SendOneFloat(float FloatBuf);
    void SendFloat(float *FloatBuf,uint16_t Length);
    void ReceiveDataCallBack(DMA_HandleTypeDef * hdma_usart1_rx);
    void SendReceive();
    ~MyUsart();
private:
    UART_HandleTypeDef *huart;
    uint8_t   re_len=0;
    uint8_t   recv_end_flag=0;
    uint8_t   re_Buff[200];
};
#ifdef __cplusplus
}
#endif
#endif //TEMPLATEDEVELOPMENT_MYUSART_H
