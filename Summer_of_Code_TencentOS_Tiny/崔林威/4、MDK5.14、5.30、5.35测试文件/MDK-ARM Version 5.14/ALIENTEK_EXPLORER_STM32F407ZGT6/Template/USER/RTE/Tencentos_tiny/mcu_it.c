/**
  * @brief  在将Tencentos tiny软件包移植到工程时，需要对xxx_it.c进行按照本文将进行修改。
  */
//void PendSV_Handler(void)
//{
//}
/**
  * @brief  This function handles SysTick Handler.
  * @param  None
  * @retval None
  */
/*
void SysTick_Handler(void)
{
	if (tos_knl_is_running())
  {
    tos_knl_irq_enter();
    tos_tick_handler();
    tos_knl_irq_leave();
  }
}*/