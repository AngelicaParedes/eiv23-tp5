#ifndef BLUEPILL_H
#define BLUEPILL_H

#include <stdbool.h> // bool, true, false
#include <stdint.h>  // uint32_t


/**
 * @brief Handles correspondientes a los pines de entrada/salida, para 
 * usar en el parámetro hPin (primer parámetro) de las funciones SP_Pin_xxx
 * 
 */
typedef enum BP_Puerto_Pin{
    SP_PA0,  ///< WKUP | USART2_CTS | ADC_IN0 | TIM2_CH1 | TIM2_ETR
    SP_PA1,  ///< USART2_RTS | ADC_IN1 | TIM2_CH2
    SP_PA2,  ///< USART2_TX  | ADC_IN2 | TIM2_CH3
    SP_PA3,  ///< USART2_RX  | ADC_IN3 | TIM2_CH4
    SP_PA4,  ///< SPI1_NSS  | ADC_IN4 | USART2_CK
    SP_PA5,  ///< SPI1_SCK  | ADC_IN5
    SP_PA6,  ///< SPI1_MISO | ADC_IN6 | TIM3_CH1 || TIM1_BKIN
    
    SP_PA9,  ///< (5V) USART1_TX  | TIM1_CH2
    SP_PA10, ///< (5V) USART1_RX  | TIM1_CH3
    
    SP_PB5,  ///< I2C1_SMBAI || TIM3_CH2 | SPI1_MOSI
    SP_PB6,  ///< (5V) I2C1_SCL   |  TIM4_CH1 | USART1_TX
    SP_PB7,  ///< (5V) I2C1_SDA   |  TIM4_CH2 | USART1_RX
    SP_PB9,  ///< (5V) TIM4_CH3 || I2C1_SCL | CANRX
    SP_PB8,  ///< (5V) TIM4_CH4 || I2C1_SDA | CANTX
    SP_PB10, ///< (5V) I2C2_SCL   | USART3_TX
    
    SP_PB12, ///< (5V) I2C2_SMBAI | USART3_CK | SPI2_NSS  | TIM1_BKIN
    
    SP_PC13, ///< TAMPER-RTC

    BP_NUM_PINES
}BP_Puerto_Pin;