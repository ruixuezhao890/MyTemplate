/**
*********************************************************************
*********
* @project_name :templateDevelopment
* @file : Mymain.cpp
* @author : zen3
* @brief : None
* @attention : None
* @date : 2023/4/27 
*********************************************************************
*********
*/
//
#include "Myapplication.h"
#include "IncludeALL.h"

#define SIZE 1024

ESP esp;

//定义变量或者数组只能声明局部变量 不能声明全局否则会找不到地址
/*void WIFIDemo()
{
    char inputbuf[16];
    MyUsart myUsart(&huart1);
    esp.ESP_hw_reset();
    HAL_Delay(20);
    ret=esp.ESP_restore();
    ret=esp.ESP_at_test();
    //myUsart.SendString(esp.myUsart->Re_GetData(),64);
    if (ret != 0)
    {
        myUsart.SendString("ESP init failed!",20);
        while (1)
        {
            HAL_GPIO_TogglePin(GPIOF,GPIO_PIN_9);
            HAL_Delay(500);
        }
    }
    myUsart.SendString("Joining to AP",16);
    //ret=esp.ESP_restore();

    ret=esp.ESP_set_mode(3);
    ret=esp.ESP_sw_reset();
    ret=esp.ESP_ate_config(0);
    ret=esp.ESP_join_ap(WIFI_SSID,WIFI_PWD);
    //ret=esp.ESP_get_ip(inputbuf);
    if (ret!=0)
    {
        myUsart.SendString("Error",5);
        while (1) {
            HAL_GPIO_TogglePin(GPIOF, GPIO_PIN_9);
            HAL_Delay(500);
        }
    }
    ret=esp.ESP_enter_unvarnished();
    ret=esp.ESP_connect_tcp_server("192.168.97.98","9090");
    if (ret!=0)
    {
        myUsart.SendString("TCPError",9);
        while (1) {
            HAL_GPIO_TogglePin(GPIOF, GPIO_PIN_9);
            HAL_Delay(500);
        }
    }

    // HAL_UART_Transmit(&huart1,&ret, sizeof(ret),50);
   // myUsart.SendOneInt(ret);
}*/
void Mymain()
{
    MyUsart myUsart(&huart1);
    esp.ESP_Init(&huart3);
    esp.WIFIConnect();
   // WIFIDemo();
    esp.myUsart->ReceiveInit();
    for (;;) {
        if (esp.myUsart->GetRECV()==1)
        {
            myUsart.SendString(esp.myUsart->Re_GetData(),esp.myUsart->GetRecvLenth());
            esp.myUsart->ReceiveInit();
        }

    }


}
/***************************************************************
  *  @brief     让中断文件可以调用c++函数
  *  @param     参数
  *  @note      备注 ：此函数放在it文件当中
  *  @Sample usage:     函数的使用方法 ：直接调用
   * @author     wangzibo
 **************************************************************/

void ItUsart(DMA_HandleTypeDef * hdma_usartx_rx)
{
   esp.myUsart->ReceiveDataCallBack(hdma_usartx_rx);

}