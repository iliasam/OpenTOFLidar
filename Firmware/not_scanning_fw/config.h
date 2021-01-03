/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __CONFIG_H
#define __CONFIG_H

/* Includes ------------------------------------------------------------------*/

#define BOARD_VERSION_2019              1 // PCB v1
#define BOARD_VERSION_2020              2 // PCB v4

#define BOARD_VERSION                   BOARD_VERSION_2020

// IMPORTAINT VALUE !!!!!!!!
// Length in mm
#if (BOARD_VERSION == BOARD_VERSION_2019)
#define DEFAULT_DIST_BIN_LENGTH         (14.5f) //PCB version 2019
#else
#define DEFAULT_DIST_BIN_LENGTH         (15.5f) //PCB version 2020
#endif


#define LED_GPIO                        GPIOA
#define LED_PIN                         GPIO_Pin_3

// APD ADC DC-DC feedback *****************************************************

#define ADC_SAMPLING_TIME               ADC_SampleTime_1Cycles5

#define APD_FB_ADC_NAME                 ADC2
#define APD_FB_ADC_GPIO                 GPIOB
#define APD_FB_ADC_PIN                  GPIO_Pin_2
#define APD_FB_ADC_CHANNEL              ADC_Channel_12

#define APD_FB_ADC_UPPER_R              (2000.0f * 1.02f)//KOhm
#define APD_FB_ADC_LOWER_R              20.0f//KOhm

#define MCU_VREF                        3.29f //volts

// Protection value
#if (BOARD_VERSION == BOARD_VERSION_2019)
#define APD_PWR_MAX_PWM_VALUE           65 //for AD500-8
#else
#define APD_PWR_MAX_PWM_VALUE           130 //for MTAPD-07
#endif

// APD ADC DMA ****************************************************************

#define APD_FB_DMA_CLK                  RCC_AHBPeriph_DMA2
#define APD_FB_DMA_CHANNEL              DMA2_Channel1//adc2
#define APD_FB_DMA_DONE_FLAG            DMA2_FLAG_TC1


// APD DC-DC TIMER (APD_PWM line) *********************************************
// Timer used to generate test signal
#define APD_POWER_TIMER_CLK             RCC_APB1Periph_TIM3

#define APD_POWER_TIMER                 TIM3
#define APD_POWER_TIMER_PRESCALER       (1)
#define APD_POWER_TIMER_FREQ            100000  //Hz

#define APD_POWER_TIMER_GPIO_CLK        RCC_AHBPeriph_GPIOA
#define APD_POWER_TIMER_GPIO            GPIOA
#define APD_POWER_TIMER_PIN             GPIO_Pin_7
#define APD_POWER_TIMER_AF_SOURCE       GPIO_PinSource7
#define APD_POWER_TIMER_PIN_AFIO        GPIO_AF_2

#define APD_POWER_TIMER_PWM_REG         CCR2

#define APD_DEFAULT_VOLTAGE             (90.0f)//V
#define APD_DEFAULT_PWM_DUTY            (25)

// DAC ************************************************************************
#define DAC_NAME                        DAC1
#define DAC_GPIO                        GPIOA
#define DAC_MAXIUM                      4095.0f

// Laser dc-dc voltage
#define LASER_DAC_PIN                   GPIO_Pin_5
#define LASER_DAC_CHANNEL               DAC_Channel_2

// APD comparator threshold
#define APD_COMP_DAC_PIN                GPIO_Pin_4
#define APD_COMP_DAC_CHANNEL            DAC_Channel_1

#define APD_COMP_R_UP                   4700.0f //Ohm - upper
#define APD_COMP_R_MAIN                 1000.0f //Ohm - main - middle
#define APD_COMP_R_DOWN                 20000.0f //Ohm - down
#define APD_COMP_R_COMMON               (APD_COMP_R_UP + APD_COMP_R_MAIN + APD_COMP_R_DOWN)

#define APD_COMP_DEFAULT_VOLT_MV        (50) //mV

#define LASER_DCDC_R_UP                 46000.0f //Ohm - upper
#define LASER_DCDC_R_DOWN               4700.0f //Ohm - down
#define LASER_DCDC_R_DAC                (float)(10000) //Ohm - after dac - R38 + R39
#define LASER_DCDC_VREF                 1.24f //V - internal VREF voltage of the DC-DC

#define LASER_DEFAULT_VOLTAGE           (10.0f) //V

//TDC *************************************************************************

#define TDC_SPI_NAME                    SPI2
#define TDC_SPI_CLK                     RCC_APB1Periph_SPI2

#define TDC_SPI_PORT                    GPIOB

#define TDC_SPI_AFIO                    GPIO_AF_5//spi2

#define TDC_SPI_MOSI                    GPIO_Pin_15
#define TDC_SPI_MOSI_AF                 GPIO_PinSource15

#define TDC_SPI_MISO                    GPIO_Pin_14
#define TDC_SPI_MISO_AF                 GPIO_PinSource14

#define TDC_SPI_SCK                     GPIO_Pin_13
#define TDC_SPI_SCK_AF                  GPIO_PinSource13

#define TDC_SPI_CSN_PORT                GPIOA
#define TDC_SPI_CSN                     GPIO_Pin_9

// UART  ***********************************************************************
#define UART_NAME                       USART2
#define UART_CLK                        RCC_APB1Periph_USART2

#define UART_TX_PIN                     GPIO_Pin_3
#define UART_TX_PIN_AF                  GPIO_PinSource3
#define UART_TX_GPIO                    GPIOB

#define UART_RX_PIN                     GPIO_Pin_4
#define UART_RX_PIN_AF                  GPIO_PinSource4
#define UART_RX_GPIO                    GPIOB

#define UART_AFIO                       GPIO_AF_7

#define UART_BAUD                       500000

#define UART_RX_INT_NAME                USART2_IRQn
#define UART_RX_INT_HANDLER             USART2_IRQHandler

// MOTOR - used for disabling  ************************************************

#define MOTOR_TIMER_GPIO_CLK            RCC_AHBPeriph_GPIOA
#define MOTOR_TIMER_GPIO                GPIOA
#define MOTOR_TIMER_PIN                 GPIO_Pin_1


/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */

#endif /* __CONFIG_H */
