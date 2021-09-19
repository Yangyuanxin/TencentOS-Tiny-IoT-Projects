//#include "mcu_init.h" //User microcontroller initialization
#include "tos_k.h"
#include "tos_klib.h"//For using the tos_kprintf function

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
    //board_init();//User microcontroller initialization
    tos_kprintf("Welcome to TencentOS tiny\r\n");//printf
    tos_knl_init(); // TencentOS Tiny kernel initialize
    tos_task_create(&application_task, "application_task", application_entry, NULL, 4, application_task_stk, APPLICATION_TASK_STK_SIZE, 0);
    tos_knl_start();
}


