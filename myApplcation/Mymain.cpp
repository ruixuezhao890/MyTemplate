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

//���������������ֻ�������ֲ����� ��������ȫ�ַ�����Ҳ�����ַ
void Mymain()
{
    uint16_t adcNum[SIZE];
    float *fftout;
    MyFFT myFft;
    MyUsart myUsart(&huart1);
    MyADC myAdc(adcNum,SIZE,&htim3,&hadc1);
    MyLCD myLcd;
    myLcd.MyLCDInit();
    myAdc.myADCCollectData();
    myAdc.myADCShowWaveForm();
    myFft.FFTInit(adcNum);
    myFft.FFTProcess();
    myUsart.SendInt(adcNum,SIZE);
    myUsart.SendFloat(myFft.GetOutputbuf(),SIZE);

    for (;;) {


    }


}