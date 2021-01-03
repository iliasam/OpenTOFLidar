/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __CONFIG_H
#define __CONFIG_H

/* Includes ------------------------------------------------------------------*/

#define BOARD_VERSION_2019              1 //PCB_v1
#define BOARD_VERSION_2020              2 //PCB_v4

#define BOARD_VERSION                   BOARD_VERSION_2020

// IMPORTAINT VALUE !!!!!!!!
// Length in mm
#if (BOARD_VERSION == BOARD_VERSION_2019)
#define DEFAULT_DIST_BIN_LENGTH        (14.5f) //PCB version 2019
#else
#define DEFAULT_DIST_BIN_LENGTH        (15.5f) //PCB version 2020
#endif


// Number of captured points is defined by angular resolution:
// constant "CAPTURE_ANG_RESOL" below

// Distance to Reference Plate, mm
#define REF_PLATE_DIST                  (30)

#define MAX_DISTANCE_MM                 (30000)

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
#define APD_PWR_MAX_PWM_VALUE           90 //for MTAPD-07
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
#define APD_POWER_TIMER_FREQ            (100 * 1000)  //Hz

#define APD_POWER_TIMER_GPIO_CLK        RCC_AHBPeriph_GPIOA
#define APD_POWER_TIMER_GPIO            GPIOA
#define APD_POWER_TIMER_PIN             GPIO_Pin_7
#define APD_POWER_TIMER_AF_SOURCE       GPIO_PinSource7
#define APD_POWER_TIMER_PIN_AFIO        GPIO_AF_2

//Timer channel is hardcoded !!

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
#define UART_GPIO_CLK                   RCC_AHBPeriph_GPIOA

#define UART_TX_PIN                     GPIO_Pin_3
#define UART_TX_PIN_AF                  GPIO_PinSource3
#define UART_TX_GPIO                    GPIOB

#define UART_RX_PIN                     GPIO_Pin_4
#define UART_RX_PIN_AF                  GPIO_PinSource4
#define UART_RX_GPIO                    GPIOB

#define UART_AFIO                       GPIO_AF_7

#define UART_BAUD                       (500000)

#define UART_RX_IRQ                     USART2_IRQn
#define UART_RX_INT_HANDLER             USART2_IRQHandler

#define UART_DMA_TX_CHANNEL             DMA1_Channel7

// Encoder comparator  ********************************************************

#define ENCODER_COMP_GPIO_CLK           RCC_AHBPeriph_GPIOA

#define ENCODER_COMP_PIN                GPIO_Pin_0
#define ENCODER_COMP_GPIO               GPIOA
// Comparator 7
#define ENCODER_COMP                    COMP_Selection_COMP7
// Comparator negative source
#define ENCODER_COMP_NEG_SRC            COMP_InvertingInput_1_2VREFINT
// Comparator positive source
#define ENCODER_COMP_POS_SRC            COMP_NonInvertingInput_IO1

// Comparator is connected to TIM1 {line is specific for COMP7}
#define ENCODER_COMP_OUTPUT             COMP_Output_TIM1IC2 

// Encoder comparator  *********************************************
// Timer is used for processing events from encoder comparator 
#define ENCODER_COMP_TIMER_CLK          RCC_APB2Periph_TIM1

#define ENCODER_COMP_TIMER              TIM1
#define ENCODER_COMP_TIMER_FREQ         (1e6) //Hz

#define ENCODER_COMP_TIMER_PRESCALER    (uint16_t)(((SystemCoreClock) / \
                              ENCODER_COMP_TIMER_FREQ) - 1)//APB2 = HCLK

#define ENCODER_COMP_TIMER_CH           TIM_Channel_2
#define ENCODER_COMP_TIMER_IT_FLAG      TIM_IT_CC2
#define ENCODER_COMP_TIMER_IRQ          TIM1_CC_IRQn
#define ENCODER_COMP_TIMER_IRQ_HANDLER  TIM1_CC_IRQHandler
#define ENCODER_COMP_GET_CAPTURD_VALUE  TIM_GetCapture2

// Including closed one
#define ENCODER_HOLES_CNT               65

// MOTOR PWM TIMER ***********************************************************
// Timer used to control speed of the BLDC motor
#define MOTOR_TIMER_CLK                 RCC_APB1Periph_TIM2

#define MOTOR_TIMER                     TIM2
#define MOTOR_TIMER_PRESCALER           (1)
#define MOTOR_TIMER_FREQ                20000  //Hz

// Protection value
#if (BOARD_VERSION == BOARD_VERSION_2019)
#define MOTOR_TIMER_GPIO_CLK            RCC_AHBPeriph_GPIOA
#define MOTOR_TIMER_GPIO                GPIOA
#define MOTOR_TIMER_PIN                 GPIO_Pin_1
#define MOTOR_TIMER_AF_SOURCE           GPIO_PinSource1
#define MOTOR_TIMER_PIN_AFIO            GPIO_AF_1
#define MOTOR_TIMER_CHANNEL             2
#define MOTOR_TIMER_PWM_REG             CCR2
#else
#define MOTOR_TIMER_GPIO_CLK            RCC_AHBPeriph_GPIOB
#define MOTOR_TIMER_GPIO                GPIOB
#define MOTOR_TIMER_PIN                 GPIO_Pin_10
#define MOTOR_TIMER_AF_SOURCE           GPIO_PinSource10
#define MOTOR_TIMER_PIN_AFIO            GPIO_AF_1
#define MOTOR_TIMER_CHANNEL             3
#define MOTOR_TIMER_PWM_REG             CCR3
#endif


#define MOTOR_DEFAULT_PWM_DUTY          (340)
// Rotations per second
#define MOTOR_DEFAULT_SPEED             (15.0f)
// Integration coefficient
#define MOTOR_CONTROLLING_I_COEF        (1.5f)

// Rotations per second
#define MOTOR_MAX_SPEED                 (30.0f)

// Rotations per second
#define MOTOR_MIN_SPEED                 (5.0f)

// CAPTURE TIMER ***********************************************************
// Timer used to start distance measurements
// It is synchronized with encoder events

// Scanning angular resolution, in deg
#define CAPTURE_ANG_RESOL               (0.5f)

#define CAPTURE_TIMER_CLK               RCC_APB2Periph_TIM8

#define CAPTURE_TIMER                   TIM8
#define CAPTURE_TIMER_PRESCALER         ENCODER_COMP_TIMER_PRESCALER

#define CAPTURE_TIMER_IT_FLAG           TIM_IT_Update
#define CAPTURE_TIMER_IRQ               TIM8_UP_IRQn
#define CAPTURE_TIMER_IRQ_HANDLER       TIM8_UP_IRQHandler


// test ***********************************************************

#define TEST_GPIO                       GPIOA
#define TEST_PIN                        GPIO_Pin_2

// IRQ Priority ***********************************************************

// pre-emption priority
#define UART_RX_IRQ_PRIORITY            5
#define CAPTURE_TIMER_IRQ_PRIORITY      15
#define ENCODER_COMP_TIMER_IRQ_PRIORITY 10

/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */

#endif /* __CONFIG_H */
