//#include "stm32f4xx.h"//更换头文件即可在其他内核或单片机下测试
#include "usart.h"
#include "tos_k.h"
#include "tos_klib.h"//用于使用tos_kprintf功能


k_task_t task1;
k_task_t task2;
k_stack_t task_stack1[1024];
k_stack_t task_stack2[1024];

void test_task1(void *Parameter)
{
    while(1)
    {
        tos_kprintf("task1 running\r\n");//printf
        tos_task_delay(200);
    }
}

void test_task2(void *Parameter)
{
    k_err_t err;
    
    tos_kprintf("task2 running\r\n");//printf
    
    tos_task_delay(2000);
    
    // suspend task1暂停
    tos_kprintf("suspend task1\r\n");//printf
    err = tos_task_suspend(&task1);
    if(err != K_ERR_NONE)
        tos_kprintf("suspend task1 fail! code : %d \r\n",err);
    
    tos_task_delay(2000);
    // resume task1恢复
    tos_kprintf("resume task1\r\n");//printf
    err = tos_task_resume(&task1);
    if(err != K_ERR_NONE)
        tos_kprintf("resume task1 fail! code : %d \r\n",err);
    
    tos_task_delay(2000);
    // destroy task1销毁
    tos_kprintf("destroy task1\r\n");//printf
    err = tos_task_destroy(&task1);
    if(err != K_ERR_NONE)
        tos_kprintf("destroy task1 fail! code : %d \r\n",err);
    // task2 running
    while(1)
    { 
        tos_kprintf("task2 running\r\n");//printf
        tos_task_delay(1000);       
    }
}
/**
  * @brief  主函数
  * @param  无
  * @retval 无
  */
int main(void)
{
    k_err_t err;
    
    /*初始化USART 配置模式为 115200 8-N-1，中断接收*/
    uart_init(115200);

    tos_kprintf("Welcome to TencentOS tiny\r\n");//printf

    tos_knl_init(); // TOS Tiny kernel initialize
    
    tos_robin_default_timeslice_config((k_timeslice_t)500u);
    
    tos_kprintf("create task1\r\n");//printf
    err = tos_task_create(&task1, 
                          "task1", 
                          test_task1,
                          NULL, 
                          3, 
                          task_stack1,
                          1024,
                          20);
    if(err != K_ERR_NONE)
        tos_kprintf("TencentOS Create task1 fail! code : %d \r\n",err);//printf
    
    tos_kprintf("create task2\r\n");//printf
    err = tos_task_create(&task2, 
                          "task2", 
                          test_task2,
                          NULL, 
                          4, 
                          task_stack2,
                          1024,
                          20);
    if(err != K_ERR_NONE)
        tos_kprintf("TencentOS Create task2 fail! code : %d \r\n",err);//printf
    
    tos_knl_start(); // Start TOS Tiny

}



