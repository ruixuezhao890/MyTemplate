/**
*********************************************************************
*********
* @project_name :templateDevelopment
* @file : myUsart.cpp
* @author : zen3
* @brief : None
* @attention : None
* @date : 2023/4/27 
*********************************************************************
*********
*/
//

#include <cstdarg>
#include "MyUsart.h"

MyUsart::MyUsart()
{

}
MyUsart::MyUsart(UART_HandleTypeDef *huart)
{
    this->huart=huart;
}
MyUsart::MyUsart(uint16_t Enable,UART_HandleTypeDef *huart)
{
    this->huart=huart;
    this->ReceiveInit();
}
void MyUsart::ReceiveInit()
{
    for (int i = 0; i < RELENTH; ++i) {
        re_Buff[i]=' ';
    }

    __HAL_UART_ENABLE_IT(this->huart, UART_IT_IDLE);//ʹ��idle�ж�
    HAL_UART_Receive_DMA(this->huart, re_Buff, RELENTH);
}
void MyUsart::Send(uint8_t * sendBuf)
{
    HAL_UART_Transmit(huart,sendBuf,sizeof(sendBuf)+1,50);
}

void MyUsart::SendString(uint8_t * stringBuf,uint16_t Length)
{
    HAL_UART_Transmit(huart,stringBuf,Length,50);
    HAL_UART_Transmit(huart,(uint8_t *)"\n",2,50);
}
void MyUsart::SendString(const char* stringBuf,uint16_t Length)
{
    HAL_UART_Transmit(huart,(uint8_t *)stringBuf,Length,50);
    HAL_UART_Transmit(huart,(uint8_t *)"\n",2,50);
}

void MyUsart::SendOneInt(uint16_t IntBuf)
{
    char temp[RELENTH]={0};
    sprintf(temp,"%d\n",IntBuf);
    Send((uint8_t *)temp);
}
void MyUsart::SendInt(uint16_t* IntBuf,uint16_t Length)
{
    char temp[RELENTH]={0};
    for (int i = 0; i < Length; ++i) {
        sprintf(temp,"%d\n",IntBuf[i]);
        Send((uint8_t *)temp);
//        Send("\n",huart);
    }
}
void MyUsart::SendOneFloat(float FloatBuf)
{
    char temp[RELENTH]={0};
    sprintf(temp,"%f\n",FloatBuf);
    Send((uint8_t *)temp);
//    SendString("\n",huart);
}
void MyUsart::SendFloat(float* FloatBuf,uint16_t Length)
{
    char temp[RELENTH]={0};
    for (int i = 0; i < Length; ++i) {
        sprintf(temp,"%lf",FloatBuf[i]);
        Send((uint8_t *)temp);
        SendString((uint8_t *)"\n",2);
    }
}

//����"stm32f4xx_it.c�ļ���USARTx_IRQHandler(void)��
void MyUsart::ReceiveDataCallBack(DMA_HandleTypeDef * hdma_usartx_rx)
{
    uint32_t tmp_flag = 0;
    uint32_t temp;
    tmp_flag =__HAL_UART_GET_FLAG(this->huart,UART_FLAG_IDLE); //��ȡIDLE��־λ
    if((tmp_flag != RESET))//idle��־����λ
    {
        __HAL_UART_CLEAR_IDLEFLAG(this->huart);//�����־λ
        temp = huart->Instance->SR;  //���״̬�Ĵ���SR,��ȡSR�Ĵ�������ʵ�����SR�Ĵ����Ĺ���
        temp = huart->Instance->DR; //��ȡ���ݼĴ����е�����
        HAL_UART_DMAStop(this->huart); //
        temp  = __HAL_DMA_GET_COUNTER(hdma_usartx_rx); // ��ȡDMA��δ��������ݸ�����NDTR�Ĵ�������������
        re_len = RELENTH - temp; //�ܼ�����ȥδ��������ݸ������õ��Ѿ����յ����ݸ���
        recv_end_flag = 1;	// ������ɱ�־λ��1
    }
}
void MyUsart::SendReceive()
{
    if(recv_end_flag ==1)
    {
        HAL_UART_DMAStop(huart);

        //��ӡ��������
        HAL_UART_Transmit(huart, re_Buff, re_len, 50);

        for(uint8_t i=0; i < re_len; i++)
        {
            re_Buff[i]=0;//����ջ���
        }
        re_len=0;//�������
        recv_end_flag=0;//������ս�����־λ
    }

    HAL_UART_Receive_DMA(this->huart, re_Buff, RELENTH);
}
MyUsart::~MyUsart() {

}

void MyUsart::SendCmdOut(char *fmt, ...) {
    va_list ap;
    uint16_t len;

    va_start(ap, fmt);
    vsprintf((char *)tx_Buff, fmt, ap);
    va_end(ap);

    len = strlen((const char *)tx_Buff);
    HAL_UART_Transmit(this->huart, tx_Buff, len, HAL_MAX_DELAY);
}

uint8_t *MyUsart::Re_GetData() {
    if (this->recv_end_flag==1)
    {
        this->recv_end_flag=0;
        return this->re_Buff;
    }
    else
    {
        return NULL;
    }

}

uint8_t *MyUsart::ReceiveAgain() {

    HAL_UART_Receive_DMA(this->huart, re_Buff, RELENTH);
    for (int i = 0; i < RELENTH; ++i) {
        temp[i]=re_Buff[i];
        re_Buff[i]=' ';
    }
    return temp;

}

uint8_t MyUsart::GetRECV() {
    return this->recv_end_flag;
}

uint8_t MyUsart::GetRecvLenth() {
    return this->re_len;
}

