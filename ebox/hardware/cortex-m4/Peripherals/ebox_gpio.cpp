#include "ebox_gpio.h"
/**
 *@name     Gpio(GPIO_TypeDef *port,uint16_t pin)
 *@brief    Gpio���캯��
 *@param    port:   GPIOA,B,C,D,E,F,G
 *          pin:    GPIO_Pin_0...15
 *@retval   None
*/
mcuGpio::mcuGpio(GPIO_TypeDef *port, uint16_t pin)
{
    uint8_t temp1,temp2;
    this->port = port;
    this->pin = pin;
    switch((uint32_t)(port))
    {
        case (uint32_t)GPIOA_BASE:
            temp1 = 0;
        break;
            
        case (uint32_t)GPIOB_BASE:
            temp1 = 1;
        break;
            
        case (uint32_t)GPIOC_BASE:
            temp1 = 2;
        break;
            
        case (uint32_t)GPIOD_BASE:
            temp1 = 3;
        break;
            
        case (uint32_t)GPIOE_BASE:
            temp1 = 4;
        break;
            
        case (uint32_t)GPIOF_BASE:
            temp1 = 5;
        break;
            
        case (uint32_t)GPIOG_BASE:
            temp1 = 6;
        break;
        case (uint32_t)GPIOH_BASE:
            temp1 = 7;
        break;
        case (uint32_t)GPIOI_BASE:
            temp1 = 8;
        break;
        default:
            temp1 = 0;
        break;
    }
    for(int i = 0; i <= 15; i ++)
    {
        if((this->pin >> i) == 0)
        {
            temp2 = i -1;
            break;
        }
    }
    this->id = (PIN_ID_t)(temp1*16 + temp2);
}
/**
 *@name     void Gpio::mode(PIN_MODE mode)
 *@brief    GPIOģʽ����
 *@param    mode:   PIN_MODEö�ٱ�������
 *@retval   None
*/
void mcuGpio::mode(PIN_MODE mode)
{
    GPIO_InitTypeDef GPIO_InitStructure;

    switch((uint32_t)this->port)
    {
    case (uint32_t)GPIOA_BASE:
        RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);
        break;

    case (uint32_t)GPIOB_BASE:
        RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);
        break;

    case (uint32_t)GPIOC_BASE:
        RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC, ENABLE);
        break;

    case (uint32_t)GPIOD_BASE:
        RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);
        break;

    case (uint32_t)GPIOE_BASE:
        RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOE, ENABLE);
        break;

    case (uint32_t)GPIOF_BASE:
        RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOF, ENABLE);
        break;
    case (uint32_t)GPIOG_BASE:
        RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOG, ENABLE);
        break;
    case (uint32_t)GPIOH_BASE:
        RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOH, ENABLE);
        break;
    case (uint32_t)GPIOI_BASE:
        RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOI, ENABLE);
        break;
    }


    GPIO_InitStructure.GPIO_Pin = this->pin;
    //GPIO_InitStructure.GPIO_Mode = (GPIOMode_TypeDef)mode;
    switch((uint8_t)mode)
    {
        /*analog input mode
        */
        case AIN:
            GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AN;
            //GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
            //GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
            GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
        break;
        
        /* digital input mode
        */
        case INPUT:
            GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
            //GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
            //GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
            GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
        break;
        
        case INPUT_PD:
            GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
            //GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
            //GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
            GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_DOWN;
        break;
            
        case INPUT_PU:
            GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
            //GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
            //GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
            GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
        break;
        
        /*digital output mode
        */
        case OUTPUT_OD:
            GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
            GPIO_InitStructure.GPIO_OType = GPIO_OType_OD;
            GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
            GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
        break;
            
        case OUTPUT_OD_PU:
            GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
            GPIO_InitStructure.GPIO_OType = GPIO_OType_OD;
            GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
            GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
        break;
            
        case OUTPUT_OD_PD:
            GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
            GPIO_InitStructure.GPIO_OType = GPIO_OType_OD;
            GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
            GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_DOWN;
        break;
            
        case OUTPUT_PP:
            GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
            GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
            GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
            GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
        break;
        
        case OUTPUT_PP_PU:
            GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
            GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
            GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
            GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
        break;
        
        case OUTPUT_PP_PD:
            GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
            GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
            GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
            GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_DOWN;
        break;
        
        
        /*af mode
        */
        case AF_OD:
            GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
            GPIO_InitStructure.GPIO_OType = GPIO_OType_OD;
            GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
            GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
        break;
            
        case AF_OD_PU:
            GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
            GPIO_InitStructure.GPIO_OType = GPIO_OType_OD;
            GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
            GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
        break;
            
        case AF_OD_PD:
            GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
            GPIO_InitStructure.GPIO_OType = GPIO_OType_OD;
            GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
            GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_DOWN;
        break;
            
        case AF_PP:
            GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
            GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
            GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
            GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
       break;
        
        case AF_PP_PU:
            GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
            GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
            GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
            GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
       break;
        
        case AF_PP_PD:
            GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
            GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
            GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
            GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_DOWN;
       break;
        /* if parament is other mode,set as INPUT mode
        */
       default:
            GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
            //GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
            //GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
            GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
            break;
    }
    GPIO_Init(this->port, &GPIO_InitStructure);   //��ʼ��GPIOC�˿�
}
void mcuGpio::mode(PIN_MODE mode,uint8_t af_configration)
{
    mcuGpio::mode(mode);
    af_config(af_configration);
}

void mcuGpio::af_config(uint8_t af_configration)
{  
  	GPIO_PinAFConfig(port, (id % 16), af_configration);  
}

/**
 *@name     void Gpio::set()
 *@brief    GPIO����ߵ�ƽ
 *@param    NONE
 *@retval   NONE
*/
void mcuGpio::set()
{
    this->port->BSRRL = this->pin;
}

/**
 *@name     void Gpio::reset()
 *@brief    GPIO����͵�ƽ
 *@param    NONE
 *@retval   NONE
*/
void mcuGpio::reset()
{
    this->port->BSRRH = this->pin;
}


/**
 *@name     void Gpio::write(uint8_t val)
 *@brief    GPIO�������
 *@param    val��1������ߵ�ƽ��0������͵�ƽ
 *@retval   NONE
*/
void mcuGpio::write(uint8_t val)
{
    if(val == 0)
        this->port->BSRRH = this->pin;
    else
        this->port->BSRRL = this->pin;
}


/**
 *@name     void Gpio::set()
 *@brief    GPIO����ߵ�ƽ
 *@param    NONE
 *@retval   NONE
*/
void mcuGpio::read(uint8_t *val)
{
    *val = this->port->IDR & this->pin;
}


/**
 *@name     uint8_t Gpio::read(void)
 *@brief    ��ȡGPIO����״̬
 *@param    NONE
 *@retval   �������ŵ�ǰ�ĵ�ƽ״̬
*/
uint8_t mcuGpio::read(void)
{
    if(this->port->IDR & this->pin)
        return 1;
    return  0;
}

/**
 *@name     void Gpio::toggle()
 *@brief    GPIO�����ƽ��ת
 *@param    NONE
 *@retval   NONE
*/
void mcuGpio::toggle()
{
    port->ODR ^= this->pin;
}
/**
 *@name     uint8_t shift_in(Gpio *data_pin, Gpio *clock_pin, uint8_t bit_order)
 *@brief    Gpio����ʱ���������һ��u8���͵����ݣ����ڴ���ͨ�š�
 *@param    data_pin��  ������������
            clock_pin:  ʱ���źŵ�����
            bit_order:  ���ݴ�С�˿���LSB_FIRST����λ�ȷ��ͣ�MSB_FIRST��λ�ȷ���
 *@retval   ���յ�������
*/
int mcuGpio::operator =(mcuGpio&) 
{
    return read();
}

mcuGpio::operator int()
{
    return read();
}

mcuGpio mcuGpio::operator= ( int value)
{
    write(value);
    return *this;
}
