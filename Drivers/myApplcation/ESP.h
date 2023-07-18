/**
*********************************************************************
*********
* @project_name :templateDevelopment
* @file : ESP.h
* @author : zen3
* @brief : None
* @attention : None
* @date : 2023/5/14 
*********************************************************************
*********
*/
//

#ifndef CPROJECT_ESP_H
#define CPROJECT_ESP_H
#ifdef __cplusplus
extern "C"
{
#endif
#include "Myapplication.h"
#include "MyUsart.h"

#define WIFI_SSID "LL1"
#define WIFI_PWD "123456789"

#define ESP_RST_GPIO_PORT           GPIOF
#define ESP_RST_GPIO_PIN            GPIO_PIN_6
#define ESP_RST_GPIO_CLK_ENABLE()   do{ __HAL_RCC_GPIOF_CLK_ENABLE(); }while(0) /* PF��ʱ��ʹ�� */

    /*IO����*/
#define ESP_RST(x)                  do{ x ?                                                                                     \
                                                HAL_GPIO_WritePin(ESP_RST_GPIO_PORT, ESP_RST_GPIO_PIN, GPIO_PIN_SET) :  \
                                                HAL_GPIO_WritePin(ESP_RST_GPIO_PORT, ESP_RST_GPIO_PIN, GPIO_PIN_RESET); \
                                            }while(0)

    /*�������*/
#define ESP_EOK         0   /* û�д��� */
#define ESP_ERROR       1   /* ͨ�ô��� */
#define ESP_ETIMEOUT    2   /* ��ʱ���� */
#define ESP_EINVAL      3   /* �������� */
/*______________________���������������________________:*/
      //������������Ϊȫ�ֱ���
    /**
     * @brief ��ļ򵥸���:һ������WiFi����\n
     * �����ϸ����:�������Լ���WiFiģ����Ķ�Ӧ�����ż�����������
     * ����esp8266 ��esp01
     *
     */
class ESP{
public:
    void ESP_Init(UART_HandleTypeDef *huart);
    void    ESP_hw_reset(void);
    uint8_t ESP_send_at_cmd(char *cmd, char *ack, uint32_t timeout);    /* ATK-MW8266D����ATָ�� */
    uint8_t ESP_init(uint32_t baudrate);                                /* ATK-MW8266D��ʼ�� */
    uint8_t ESP_restore(void);                                          /* ATK-MW8266D�ָ��������� */
    uint8_t ESP_at_test(void);                                          /* ATK-MW8266D ATָ����� */
    uint8_t ESP_set_mode(uint8_t mode);                                 /* ����ATK-MW8266D����ģʽ */
    uint8_t ESP_sw_reset(void);                                         /* ATK-MW8266D�����λ */
    uint8_t ESP_ate_config(uint8_t cfg);                                /* ATK-MW8266D���û���ģʽ */
    uint8_t ESP_join_ap(char *ssid, char *pwd);                         /* ATK-MW8266D����WIFI */
    uint8_t ESP_get_ip(char *buf);                                      /* ATK-MW8266D��ȡIP��ַ */
    uint8_t ESP_connect_tcp_server(char *server_ip, char *server_port); /* ATK-MW8266D����TCP������ */
    uint8_t ESP_enter_unvarnished(void);                                /* ATK-MW8266D����͸�� */
    void ESP_exit_unvarnished(void);                                    /* ATK-MW8266D�˳�͸�� */
    uint8_t ESP_connect_atkcld(char *id, char *pwd);                    /* ATK-MW8266D����ԭ���Ʒ����� */
    uint8_t ESP_disconnect_atkcld(void);                                /* ATK-MW8266D�Ͽ�ԭ���Ʒ��������� */

    void WIFIConnect();

    ~ESP();
    uint8_t ret;
    MyUsart * myUsart;



};
#ifdef __cplusplus
}
#endif
#endif //CPROJECT_ESP_H
