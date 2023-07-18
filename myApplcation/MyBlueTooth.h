/**
*********************************************************************
*********
* @project_name :templateDevelopment
* @file : MyBlueTooth.h
* @author : zen3
* @brief : None
* @attention : None
* @date : 2023/7/15 
*********************************************************************
*********
*/
//

#ifndef CPROJECT_MYBLUETOOTH_H
#define CPROJECT_MYBLUETOOTH_H
#ifdef __cplusplus

#include <string>
#include "Myapplication.h"

#include "IncludeALL.h"



extern "C"
{
#endif
/*______________________���������������________________:*/



    /**
     * @brief ��ļ򵥸���:�ú���Ϊ����ģ�������� ��Ӧ��λ��\n
     * �����ϸ����:
     *              ����ֻ������������
     *              1.�����ַ�������λ��
     *              2.�������ݵ���λ�����Ʋ���
     *              3.������λ����������ָ����ж�Ӧ�Ĳ��� ע����λ���뵥Ƭ����ָ��Ӧ���ȹ涨��
     *
     */


class MyBlueTooth{
public:
    MyBlueTooth(UART_HandleTypeDef *huart);
    ~MyBlueTooth();

    void SendString(uint8_t* SendData);
    void SendString(char* SendData);
    void SendOneChannel(uint16_t *SendData,uint16_t DataSize);
    void SendOneChannel(float32_t *SendData,uint16_t DataSize);
    void SendTwoChannel(uint16_t *SendData0,uint16_t *SendData1,uint16_t DataSize);
    void SendTwoChannel(float32_t *SendData0,float32_t *SendData1,uint16_t DataSize);

    /*void SendTwoChannel(uint16_t *SendData0,uint16_t *SendData1,uint16_t DataSize0,uint16_t DataSize1);
    void SendTwoChannel(float32_t *SendData0,float32_t *SendData1,uint16_t DataSize0,uint16_t DataSize1);*/

    void ReceiveCmdSlot(char* RecCmd,void (*funcPtr)());
    void ReceiveCmdSlot(char* RecCmd,void (*funcPtr)(uint16_t),uint16_t Parameters);
    void ReceiveCmdSlot(char* RecCmd,void (*funcPtr)(uint16_t,uint16_t),uint16_t Parameters0,uint16_t Parameters1);


    void ReceiveCmdSlot(std::string RecCmd,void (*funcPtr)());
    void ReceiveCmdSlot(std::string RecCmd,void (*funcPtr)(uint16_t),uint16_t Parameters);
    void ReceiveCmdSlot(std::string RecCmd,void (*funcPtr)(uint16_t,uint16_t),uint16_t Parameters0,uint16_t Parameters1);


    void SetUsart(UART_HandleTypeDef *huart);
    MyUsart* GetBlueUsart();
    UART_HandleTypeDef * GetUsrat();
private:
    MyUsart* BlueUsart;
    UART_HandleTypeDef *usart;
};
#ifdef __cplusplus
}
#endif
#endif //CPROJECT_MYBLUETOOTH_H
