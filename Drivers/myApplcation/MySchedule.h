/**
*********************************************************************
*********
* @project_name :templateDevelopment
* @file : MySchedule.h
* @author : zen3
* @brief : None
* @attention : None
* @date : 2023/5/27 
*********************************************************************
*********
*/
//

#ifndef CPROJECT_MYSCHEDULE_H
#define CPROJECT_MYSCHEDULE_H
#include <vector>
#ifdef __cplusplus
extern "C"
{
#endif

#include "Myapplication.h"
#include "MyUsart.h"
//#include "IncludeALL.h"
#define GET_NOW_TIME_MS   HAL_GetTick()//��λ�Ǻ���
#define _MY_DEBUG_  1

#ifdef  _MY_DEBUG_
//#define    MY_DEBUG_PRINT_INFO(...)      myUsartSchedule.Myprintf( __VA_ARGS__,)//printf(__VA_ARGS__)
//#define    MY_DEBUG_PRINT_VAR(X, ...)     myUsartSchedule.Myprintf("file: " __FILE__", Line: %d:" X"\r\n",__LINE__, ##__VA_ARGS__)//printf("file: "__FILE__", Line: %d:" "\r\n",__LINE__,##__VA_ARGS__)
#else
#define    MY_DEBUG_PRINT_INFO(...)
	#define    MY_DEBUG_PRINT_VAR(X, ...)
#endif
/*______________________���������������________________:*/
class Task{
public:
    void (*task_func)(void);   //����ָ��
    uint16_t interval_ticks;   //ÿ����������ִ��һ��
    uint16_t max_time_micros;  //�ú�������һ�εĴ��ʱ��us
    uint32_t last_tick_counter;//��һ�κ�������ʱtick
};

class MySchedule{
public:
    void MyScheduleSetPeriod( uint32_t TimePeriod);
    void MyTaskGreat( void (*task_func)(void),uint16_t interval_ticks,
                      uint16_t max_time_micros,uint32_t last_tick_counter);
    void MyScheduleRun(uint32_t TimeAvailable);
    void MyScheduleWhile();
private:

    std::vector<Task> TaskVector;
    Task task;
    uint8_t num_task=0;//��������
    uint32_t tick_counter = 0;//ִ��������
    uint32_t TimePeriod=5;

/* ��¼��ǰʱ��� */
    uint32_t current_time;

/* ��¼��һ��ʱ�� */
    uint32_t last_time;
};
#ifdef __cplusplus
}
#endif
#endif //CPROJECT_MYSCHEDULE_H
