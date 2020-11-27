#include "logic.h"
#include "adc.h"
#include "tim.h"

Sensor *MQ2_Sensor = NULL;
int get_led_status(Sensor *sensor_handle);
int get_buzzer_status(Sensor *sensor_handle);
void get_smoke_value(Sensor *sensor_handle);
void alarm_led_control(Sensor *sensor_handle, uint8_t status);
void alarm_buzzer_control(Sensor *sensor_handle, uint8_t status);


/*提供访问传感器的接口*/
Sensor mq2_sensor_interface =
{
    /*设置接口*/
    .led_control = alarm_led_control,
    .buzzer_control = alarm_buzzer_control,
    /*获取接口*/
    .get_led_status = get_led_status,
    .get_buzzer_status = get_buzzer_status,
    .get_smoke_value = get_smoke_value
};

/*注册传感器*/
int Sensor_Register(Sensor *sensor_handle)
{
    if(NULL == MQ2_Sensor)
    {
        MQ2_Sensor = sensor_handle ;

        if(NULL == MQ2_Sensor)
            return -1 ;
        else
        {
            MQ2_Sensor->led_control(MQ2_Sensor, 0);
            MQ2_Sensor->buzzer_control(MQ2_Sensor, 0);
        }
    }

    return 0 ;
}


void alarm_led_control(Sensor *sensor_handle, uint8_t status)
{
    sensor_handle->Alarm_Led_Status = status ;

    if(sensor_handle->Alarm_Led_Status)
        HAL_GPIO_WritePin(SF1_LED_GPIO_Port, SF1_LED_Pin, GPIO_PIN_SET);
    else
        HAL_GPIO_WritePin(SF1_LED_GPIO_Port, SF1_LED_Pin, GPIO_PIN_RESET);
}

void alarm_buzzer_control(Sensor *sensor_handle, uint8_t status)
{
    sensor_handle->Alarm_Buzzer_Status = status ;

    if(sensor_handle->Alarm_Buzzer_Status)
        HAL_TIM_PWM_Start(&htim16, TIM_CHANNEL_1);
    else
        HAL_TIM_PWM_Stop(&htim16, TIM_CHANNEL_1);
}

int get_led_status(Sensor *sensor_handle)
{
    return sensor_handle->Alarm_Led_Status ;
}

int get_buzzer_status(Sensor *sensor_handle)
{
    return sensor_handle->Alarm_Buzzer_Status ;
}

void get_smoke_value(Sensor *sensor_handle)
{
    HAL_ADC_Start(&hadc1);
    HAL_ADC_PollForConversion(&hadc1, 50);
    sensor_handle->Smoke_Value = HAL_ADC_GetValue(&hadc1);
}



