/**
*********************************************************************
*********
* @project_name :templateDevelopment
* @file : MyFFT.cpp
* @author : zen3
* @brief : None
* @attention : None
* @date : 2023/4/29 
*********************************************************************
*********
*/
//

#include "MyFFT.h"
#include "MyUsart.h"


void MyFFT::FFTInit(uint16_t *adcNum) {

    for (int i = 0; i < FFT_LENGTH; ++i) {
        fft_Inputbuf1[i*2]=adcNum[i]*(3.3/4096);
        fft_Inputbuf1[i*2+1]=0;
    }
//    MyUsart myUsart(&huart1);
//    myUsart.SendFloat(fft_Inputbuf1,1024);
    Fmax= max_Index=0;
}
void MyFFT::FFTProcess() {
    arm_cfft_f32(&arm_cfft_sR_f32_len1024, fft_Inputbuf1, 0, 1);
    arm_cmplx_mag_f32(fft_Inputbuf1, fft_Outputbuf1, FFT_LENGTH);//求幅值
    fft_Outputbuf1[0] = 0;
    for (int i = 1; i < FFT_LENGTH; i++)//输出各次谐波幅值
    {
        fft_Outputbuf1[i] /= 512;

    }
}

float * MyFFT::GetIutputbuf() {
    return fft_Inputbuf1;
}
float * MyFFT::GetOutputbuf() {
    return fft_Outputbuf1;
}

void MyFFT::PhaProcess() {
    arm_max_f32(fft_Outputbuf1, 1024, &Fmax, &max_Index);
    float32_t real_part1 = fft_Inputbuf1[max_Index * 2];
    float32_t imaginary_part1 = fft_Inputbuf1[max_Index * 2 + 1];
    phase_diff =atan2f(imaginary_part1,real_part1);

}

uint32_t MyFFT::Getmax_Index() {
    return this->max_Index;
}

float32_t MyFFT::GetPhase() {
    return this->phase_diff;
}

float MyFFT::GetFmax() {
    return this->Fmax;
}

float32_t MyFFT::PhaProcess(MyFFT* myFFT1) {
    float32_t temp=this->phase_diff-myFFT1->phase_diff;
    if(temp>-180&&temp<180) {
        return temp;
    }
}


