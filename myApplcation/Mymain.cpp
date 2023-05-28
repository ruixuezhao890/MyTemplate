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
#include "MySchedule.h"
#define SIZE 1024

ESP esp;

//定义变量或者数组只能声明局部变量 不能声明全局否则会找不到地址
static void Task1()
{
    HAL_GPIO_TogglePin(GPIOF,GPIO_PIN_9);
}
static void Task2()
{
    HAL_GPIO_TogglePin(GPIOF,GPIO_PIN_10);
}
void Mymain()
{
    MySchedule mySchedule;
    mySchedule.MyScheduleSetPeriod(5);
    mySchedule.MyTaskGreat(Task1,10,5,0);
    mySchedule.MyTaskGreat(Task2,200,5,0);
    for (;;) {
        mySchedule.MyScheduleWhile();
    }

    /*MyUsart myUsart(&huart1);
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

    }*/


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