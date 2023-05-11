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

#include "MyUsart.h"

MyUsart::MyUsart()
{

}
MyUsart::MyUsart(UART_HandleTypeDef *huart)
{
    this->huart=huart;
}
MyUsart::MyUsart(uint16_t Enable)
{
    this->ReceiveInit();
}
void MyUsart::ReceiveInit()
{
    __HAL_UART_ENABLE_IT(&huart1, UART_IT_IDLE);//使能idle中断
    HAL_UART_Receive_DMA(&huart1, re_Buff, RELENTH);
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

//放入"stm32f4xx_it.c文件中USART1_IRQHandler(void)内
void MyUsart::ReceiveDataCallBack(DMA_HandleTypeDef * hdma_usart1_rx)
{
    uint32_t tmp_flag = 0;
    uint32_t temp;
    tmp_flag =__HAL_UART_GET_FLAG(&huart1,UART_FLAG_IDLE); //获取IDLE标志位
    if((tmp_flag != RESET))//idle标志被置位
    {
        __HAL_UART_CLEAR_IDLEFLAG(&huart1);//清除标志位
        temp = huart1.Instance->SR;  //清除状态寄存器SR,读取SR寄存器可以实现清除SR寄存器的功能
        temp = huart1.Instance->DR; //读取数据寄存器中的数据
        HAL_UART_DMAStop(&huart1); //
        temp  = __HAL_DMA_GET_COUNTER(hdma_usart1_rx); // 获取DMA中未传输的数据个数，NDTR寄存器分析见下面
        re_len = RELENTH - temp; //总计数减去未传输的数据个数，得到已经接收的数据个数
        recv_end_flag = 1;	// 接受完成标志位置1
    }
}
void MyUsart::SendReceive()
{
    if(recv_end_flag ==1)
    {
        HAL_UART_DMAStop(huart);

        //打印接收数据
        HAL_UART_Transmit(huart, re_Buff, re_len, 50);

        for(uint8_t i=0; i < re_len; i++)
        {
            re_Buff[i]=0;//清接收缓存
        }
        re_len=0;//清除计数
        recv_end_flag=0;//清除接收结束标志位
    }

    HAL_UART_Receive_DMA(&huart1, re_Buff, RELENTH);
}
MyUsart::~MyUsart() {

}
