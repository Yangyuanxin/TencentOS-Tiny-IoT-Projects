#include "tos_k.h"

/**
  * @brief  When porting the Tencentos tiny package to the project, you need to follow this procedure to make changes to xxx_it.c
  */
//void PendSV_Handler(void)
//{
//}
/**
  * @brief  This function handles SysTick Handler.
  * @param  None
  * @retval None
  */

void SysTick_Handler(void)
{
  if (tos_knl_is_running())
  {
    tos_knl_irq_enter();
    tos_tick_handler();
    tos_knl_irq_leave();
  }
}
