//#include "mcu_init.h" //用户单片机初始化
#include "tos_k.h"
#include "tos_klib.h"//用于使用tos_kprintf功能

#define APPLICATION_TASK_STK_SIZE       4096
k_task_t application_task;
uint8_t application_task_stk[APPLICATION_TASK_STK_SIZE];

extern void application_entry(void *arg);

/*__weak void application_entry(void *arg)
{
    while (1) {
        printf("This is a demo task,please use your task entry!\r\n");
        tos_task_delay(1000);
    }
}*/

int main(void)
{
    //board_init();//用户单片机初始化
    tos_kprintf("Welcome to TencentOS tiny\r\n");//printf
    tos_knl_init(); // TencentOS Tiny kernel initialize
    tos_task_create(&application_task, "application_task", application_entry, NULL, 4, application_task_stk, APPLICATION_TASK_STK_SIZE, 0);
    tos_knl_start();
}


