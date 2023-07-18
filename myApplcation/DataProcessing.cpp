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
  *  @brief     �������� :�ú���ͨ���Ƴ�ԭʼ�ź��е�һЩ�����㣬�Ӷ����ٲ����ʡ�ͨ��ѡ��ÿ��һ������Ĳ����㣬���Խ�ԭʼ�źŵĲ����ʽ��͡�
  *                     ���磬�������������Ϊ2����ô��������е�ÿ�������㶼������������ÿ��һ����Ĳ���ֵ��
  *  @param     ����      ���룺ԭʼ�ź����� input��ԭʼ�ź����ݴ�С inputSize������������ decimationFactor��
                         ��������������������ݴ洢�� decimatedOutput �����У�������ݴ�С�洢�� decimatedOutputSize �С�
  *  @note      ��ע ����
  *  @Sample usage:     ������ʹ�÷��� ��ֱ�ӵ���
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
  *  @brief     �������� �ú���ʹ�����Բ�ֵ�ķ������ڽ�����������ݵ�֮������������ݵ㣬�Ӷ����Ӳ����ʡ�ͨ�������������ݵ�֮������Թ�ϵ�����Թ����м���ֵ��
  *             ���磬�����ֵ����Ϊ2����ô��������е�ÿ�������㶼����������������������֮������Բ�ֵ�����
  *  @param     ����  ���룺������������� input��������������ݴ�С inputSize����ֵ���� interpolationFactor��
                     �������ֵ���������ݴ洢�� interpolatedOutput �����У�������ݴ�С�洢�� interpolatedOutputSize �С�
  *  @note      ��ע ����
  *  @Sample usage:     ������ʹ�÷��� ��ֱ�ӵ���
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
