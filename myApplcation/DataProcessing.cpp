/**
*********************************************************************
*********
* @project_name :templateDevelopment
* @file :  DataProcessing.cpp
* @author : zen3
* @brief : None
* @attention : None
* @date : 2023/7/16 
*********************************************************************
*********
*/
//

#include " DataProcessing.h"

DataProcess::DataProcess() {

}
/***************************************************************
  *  @brief     函数作用 :该函数通过移除原始信号中的一些采样点，从而减少采样率。通过选择每隔一定间隔的采样点，可以将原始信号的采样率降低。
  *                     例如，如果降采样因子为2，那么输出数据中的每个采样点都是输入数据中每隔一个点的采样值。
  *  @param     参数      输入：原始信号数据 input，原始信号数据大小 inputSize，降采样因子 decimationFactor。
                         输出：降采样后的输出数据存储在 decimatedOutput 数组中，输出数据大小存储在 decimatedOutputSize 中。
  *  @note      备注 ：无
  *  @Sample usage:     函数的使用方法 ：直接调用
   * @author     wangzibo
 **************************************************************/

void DataProcess::decimation(const uint16_t *input, uint16_t inputSize, uint16_t decimationFactor) {
    decimatedOutputSize_ = (inputSize - 1) / decimationFactor + 1;
    decimatedOutput_ = new uint16_t[decimatedOutputSize_];

    for (uint16_t i = 0; i < decimatedOutputSize_; i++) {
        decimatedOutput_[i] = input[i * decimationFactor];
    }
}


/***************************************************************
  *  @brief     函数作用 该函数使用线性插值的方法，在降采样后的数据点之间填充额外的数据点，从而增加采样率。通过计算相邻数据点之间的线性关系，可以估计中间点的值。
  *             例如，如果插值因子为2，那么输出数据中的每个采样点都是输入数据中相邻两个点之间的线性插值结果。
  *  @param     参数  输入：降采样后的数据 input，降采样后的数据大小 inputSize，插值因子 interpolationFactor。
                     输出：插值后的输出数据存储在 interpolatedOutput 数组中，输出数据大小存储在 interpolatedOutputSize 中。
  *  @note      备注 ：无
  *  @Sample usage:     函数的使用方法 ：直接调用
   * @author     wangzibo
 **************************************************************/

void DataProcess::linearInterpolation(uint16_t interpolationFactor) {
    interpolatedOutputSize_ = (decimatedOutputSize_ - 1) * interpolationFactor + 1;
    interpolatedOutput_ =(uint16_t *) malloc(interpolatedOutputSize_);
            //new uint16_t[interpolatedOutputSize_];

    for (uint16_t i = 0; i < decimatedOutputSize_ - 1; i++) {
        uint16_t currentSample = decimatedOutput_[i];
        uint16_t nextSample = decimatedOutput_[i + 1];
        uint16_t increment = (nextSample - currentSample) / interpolationFactor;

        interpolatedOutput_[i * interpolationFactor] = currentSample;

        for (uint16_t j = 1; j < interpolationFactor; j++) {
            uint16_t interpolatedValue = currentSample + (increment * j);
            interpolatedOutput_[i * interpolationFactor + j] = interpolatedValue;
        }
    }

    interpolatedOutput_[interpolatedOutputSize_ - 1] = decimatedOutput_[decimatedOutputSize_ - 1];
}

uint16_t *DataProcess::getDecimatedOutput() const {
    return decimatedOutput_;
}

uint16_t DataProcess::getDecimatedOutputSize() const {
    return decimatedOutputSize_;
}

uint16_t *DataProcess::getInterpolatedOutput() const {
    return interpolatedOutput_;
}

uint16_t DataProcess::getInterpolatedOutputSize() const {
    return interpolatedOutputSize_;
}

DataProcess::~DataProcess() {

//    free(decimatedOutput_);
//    free(interpolatedOutput_);

//    delete[] decimatedOutput_;
//    delete[] interpolatedOutput_;
}

void DataProcess::linearInterpolation(const uint16_t *input, uint16_t inputSize, uint16_t interpolationFactor) {
    interpolatedOutputSize_ = (inputSize - 1) * interpolationFactor + 1;
    interpolatedOutput_ = (uint16_t *  )malloc(interpolatedOutputSize_);
            //new uint16_t[interpolatedOutputSize_];

    for (uint16_t i = 0; i < inputSize - 1; i++) {
        uint16_t currentSample = input[i];
        uint16_t nextSample = input[i + 1];
        uint16_t increment = (nextSample - currentSample) / interpolationFactor;

        interpolatedOutput_[i * interpolationFactor] = currentSample;

        for (uint16_t j = 1; j < interpolationFactor; j++) {
            uint16_t interpolatedValue = currentSample + (increment * j);
            interpolatedOutput_[i * interpolationFactor + j] = interpolatedValue;
        }
    }

    interpolatedOutput_[interpolatedOutputSize_ - 1] = input[inputSize - 1];
}

void DataProcess::Destruct() {
//    delete[] decimatedOutput_;
//    delete[] interpolatedOutput_;
}
