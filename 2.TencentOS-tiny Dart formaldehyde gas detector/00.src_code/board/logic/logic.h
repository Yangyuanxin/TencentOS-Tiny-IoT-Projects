#ifndef __LOGIC_H
#define __LOGIC_H
#include "main.h"

typedef struct Sensor
{
    /*ÑÌ¸ÐÖµ*/
    int Smoke_Value;
    /*±¨¾¯µÆ×´Ì¬*/
    uint8_t Alarm_Led_Status : 1;
    /*±¨¾¯·äÃùÆ÷×´Ì¬*/
    uint8_t Alarm_Buzzer_Status : 1;

    void (*led_control)(struct Sensor *sensor_handle, uint8_t status);
    void (*buzzer_control)(struct Sensor *sensor_handle, uint8_t status);

    void (*get_smoke_value)(struct Sensor *sensor_handle);
    int (*get_led_status)(struct Sensor *sensor_handle);
    int (*get_buzzer_status)(struct Sensor *sensor_handle);
} Sensor ;
extern Sensor *MQ2_Sensor ;
extern Sensor mq2_sensor_interface ;
/*×¢²á´«¸ÐÆ÷*/
int Sensor_Register(Sensor *sensor_handle);



#endif //__LOGIC_H

