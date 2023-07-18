/**
*********************************************************************
*********
* @project_name :templateDevelopment
* @file :  DataProcessing.h
* @author : zen3
* @brief : None
* @attention : None
* @date : 2023/7/16 
*********************************************************************
*********
*/
//

#ifndef CPROJECT_DATAPROCESSING_H
#define CPROJECT_DATAPROCESSING_H
#ifdef __cplusplus
extern "C"
{
#endif
#include "Myapplication.h"
/*______________________类的声明在这下面________________:*/
class DataProcess{
public:
    DataProcess();
    void decimation(const uint16_t* input, uint16_t inputSize, uint16_t decimationFactor);
    void linearInterpolation(uint16_t interpolationFactor);
    void linearInterpolation(const uint16_t* input, uint16_t inputSize, uint16_t interpolationFactor);
    uint16_t* getDecimatedOutput() const;

    uint16_t getDecimatedOutputSize() const;

    uint16_t* getInterpolatedOutput() const;

    uint16_t getInterpolatedOutputSize() const;

    void Destruct();
    ~DataProcess() ;
private:
    uint16_t* decimatedOutput_;
    uint16_t decimatedOutputSize_;

    uint16_t* interpolatedOutput_;
    uint16_t interpolatedOutputSize_;
};
#ifdef __cplusplus
}
#endif
#endif //CPROJECT_DATAPROCESSING_H
