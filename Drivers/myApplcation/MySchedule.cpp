/**
*********************************************************************
*********
* @project_name :templateDevelopment
* @file : MySchedule.cpp
* @author : zen3
* @brief : None
* @attention : None
* @date : 2023/5/27 
*********************************************************************
*********
*/
//

#include "MySchedule.h"
MyUsart myUsartSchedule(&huart1);
/***************************************************************
  *  @brief     ��������
  *  @param     ���� void (*task_func)(void)������ָ��
  *                  uint16_t interval_ticks����������ִ��һ��
  *                   uint16_t max_time_micros������һ�δ��ʱ�䣻��λms
  *                   uint32_t last_tick_counter����һ�κ�������ʱ��ʱ��
  *  @note      ��ע ��ʹ�õ���ǰ�ȴ�������ſɼ��� ����interval_ticks>last_tick_counter
  *  @Sample usage:     ������ʹ�÷��� ��ֱ�ӵ���
   * @author     wangzibo
 **************************************************************/

void MySchedule::MyTaskGreat(void (*task_func)(void), uint16_t interval_ticks, uint16_t max_time_micros,
                             uint32_t last_tick_counter) {
    this->num_task++;
    this->task.task_func=task_func;
    this->task.interval_ticks=interval_ticks;
    this->task.max_time_micros=max_time_micros;
    this->task.last_tick_counter=last_tick_counter;
    this->TaskVector.push_back(this->task);


}

void MySchedule::MyScheduleRun(uint32_t TimeAvailable) {
    uint64_t now;
    uint16_t dt;
    uint16_t interval_ticks;
    for (int i = 0; i < this->TaskVector.size(); ++i) {
        now = GET_NOW_TIME_MS;
        dt = tick_counter - TaskVector[i].last_tick_counter;//��һ�κ�������ʱtick
        interval_ticks = TaskVector[i].interval_ticks;//ÿ����������ִ��һ��


        if (dt >= interval_ticks) {
            //����ʱʹ�ã�����ʱ��δ���У�˵���������������̫������shceduler_run�Ŀ�����ʱ��̫��
            if (dt >= interval_ticks * 2) {
                myUsartSchedule.SendCmdOut("Scheduler slip task[%u] (%u/%u/%u)\n",
                                   (unsigned) i,
                                   (unsigned) dt,
                                   (unsigned) interval_ticks,
                                   (unsigned) TaskVector[i].max_time_micros);//�ú�������һ�εĴ��ʱ��us


            }
            if (TaskVector[i].max_time_micros <= TimeAvailable) {
                //��������
                TaskVector[i].task_func();
                //����last_tick_counter
                TaskVector[i].last_tick_counter = tick_counter;

#ifdef _MY_DEBUG_
                uint32_t end_time = GET_NOW_TIME_MS - now;
//����������й�����ʱ�䳬��shceduler_run�Ŀ�����ʱ��time_available��˵�������max_time_micros����С��
                if (end_time > TimeAvailable) {
                    myUsartSchedule.SendCmdOut("Scheduler slip task[%u] (%u/%u)\n",
                                       (unsigned) i,
                                       (unsigned) end_time,
                                       (unsigned) TaskVector[i].max_time_micros);
                    return;

                }
#endif //debug��ӡ
            }

        }
        TimeAvailable -= (GET_NOW_TIME_MS - now);
    }
    this->tick_counter++;
}

void MySchedule::MyScheduleWhile() {
    current_time = GET_NOW_TIME_MS- last_time;
    if(current_time >= TimePeriod)
    {
        last_time = GET_NOW_TIME_MS;
      this->MyScheduleRun(TimePeriod);
    }
}

//���ÿ������� ��λ�Ǻ���
void MySchedule::MyScheduleSetPeriod( uint32_t TimePeriod) {
    this->TimePeriod=TimePeriod;

}
