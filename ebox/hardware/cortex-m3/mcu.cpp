/**
  ******************************************************************************
  * @file    core.cpp
  * @author  shentq
  * @version V2.1
  * @date    2016/08/14
  * @brief   
  ******************************************************************************
  * @attention
  *
  * No part of this software may be used for any commercial activities by any form 
  * or means, without the prior written consent of shentq. This specification is 
  * preliminary and is subject to change at any time without notice. shentq assumes
  * no responsibility for any errors contained herein.
  * <h2><center>&copy; Copyright 2015 shentq. All Rights Reserved.</center></h2>
  ******************************************************************************
  */


/* Includes ------------------------------------------------------------------*/
#include "stm32f10x.h"
#include "ebox_analog.h"
#include "mcu.h"
#define systick_no_interrupt()  SysTick->CTRL &=0xfffffffd
#define systick_interrupt()     SysTick->CTRL |=0x0002
extern "C" {

    cpu_t mcu;

    extern uint16_t  AD_value[];

    __IO uint64_t millis_seconds;//�ṩһ��mills()��Ч��ȫ�ֱ���������cpu���ÿ���
    __IO uint16_t micro_para;


    void mcu_init(void)
    {
        get_system_clock(&mcu.clock);
        get_chip_info();
        mcu.company[0] = 'S';
        mcu.company[1] = 'T';
        mcu.company[2] = '\0';

        
        #ifdef __CC_ARM
            ebox_heap_init((void*)STM32_SRAM_BEGIN, (void*)STM32_SRAM_END);
        #elif __ICCARM__
            rt_system_heap_init(__segment_end("HEAP"), (void*)STM32_SRAM_END);
        #else
            rt_system_heap_init((void*)&__bss_end, (void*)STM32_SRAM_END);
        #endif

        SysTick_Config(mcu.clock.core/1000);//  ÿ�� 1ms����һ���ж�
        SysTick_CLKSourceConfig(SysTick_CLKSource_HCLK);//systemticks clock��
        micro_para = mcu.clock.core/1000000;//����micros����������
        
        
        mcu.ability = 0;
        millis_seconds = 0;
        //ͳ��cpu��������//////////////////
        do
        {
            mcu.ability++;//ͳ��cpu�������� 
        }
        while(millis_seconds < 100);
        mcu.ability = mcu.ability * 10;
        ////////////////////////////////
        ADC1_init();

        NVIC_PriorityGroupConfig(NVIC_GROUP_CONFIG);

        //��pb4Ĭ������ΪIO�ڣ�����jtag
        RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);
        GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable, ENABLE);
        set_systick_user_event_per_sec(1000);
        random_seed(AD_value[0]);//��ʼ�����������

    }
    void mcu_reset(void)
    {
        NVIC_SystemReset();
    }
    
    uint64_t mcu_micros(void)
    {
        uint64_t micro;
        uint32_t temp = __get_PRIMASK();//����֮ǰ�ж�����
        no_interrupts();
        if(SysTick->CTRL & (1 << 16))//���������
        {    
            if( __get_IPSR() ||  (temp) ) //�����ʱ�����������жϻ��߱�����жϴ���޷�ִ�У�systick�жϺ���������Ҫ��millis_secend���в���
            millis_seconds++;
        }
        micro = (millis_seconds * 1000 + (1000 - (SysTick->VAL)/(micro_para)));
        __set_PRIMASK(temp);//�ָ�֮ǰ�ж�����
        
        return  micro;
    }
    uint64_t mcu_millis( void )
    {
        return millis_seconds;
    }

    void mcu_delay_ms(uint64_t ms)
    {
        uint64_t end ;
        end = mcu_micros() + ms * 1000 - 3;
        while(mcu_micros() < end);
    }
    void mcu_delay_us(uint64_t us)
    {
        uint64_t end = mcu_micros() + us - 3;
        while(mcu_micros() < end);
    }


    callback_fun_type systick_cb_table[1] = {0};
    __IO uint16_t systick_user_event_per_sec;//��ʵ��ֵ
    __IO uint16_t _systick_user_event_per_sec;//���ڱ�millis_secondȡ����

    void set_systick_user_event_per_sec(uint16_t frq)
    {
        _systick_user_event_per_sec = 1000 / frq;
        systick_user_event_per_sec = frq;
    }

    void attach_systick_user_event(void (*callback_fun)(void))
    {
        systick_cb_table[0] = callback_fun;
    }
    void SysTick_Handler(void)//systick�ж�
    {
        millis_seconds++;
        if((millis_seconds % _systick_user_event_per_sec) == 0)
        {
            if(systick_cb_table[0] != 0)
            {
                systick_cb_table[0]();
            }
        }

    }
	static void get_system_clock(cpu_clock_t *clock)
    {
        RCC_ClocksTypeDef RCC_ClocksStatus;
        
        SystemCoreClockUpdate();                
        RCC_GetClocksFreq(&RCC_ClocksStatus);
        
        clock->core = RCC_ClocksStatus.SYSCLK_Frequency;
        clock->hclk = RCC_ClocksStatus.HCLK_Frequency;
        clock->pclk2 = RCC_ClocksStatus.PCLK2_Frequency;
        clock->pclk1 = RCC_ClocksStatus.PCLK1_Frequency;       
    }

    
    static void get_chip_info()
    {
        mcu.chip_id[2] = *(__IO uint32_t *)(0X1FFFF7E8); //���ֽ�
        mcu.chip_id[1] = *(__IO uint32_t *)(0X1FFFF7EC); //
        mcu.chip_id[0] = *(__IO uint32_t *)(0X1FFFF7F0); //���ֽ�

        mcu.flash_size = *(uint16_t *)(0x1FFFF7E0);   //оƬflash����
    }
    
    uint32_t get_cpu_calculate_per_sec(void)
    {
        return mcu.ability;
    }


}