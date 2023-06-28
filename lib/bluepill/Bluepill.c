#include <Bluepill.h>
#include <stm32f1xx.h>


void SP_Tiempo_init(void){
    SystemCoreClockUpdate();
    
    uint32_t const cuentas_por_milisegundo = SystemCoreClock/1000;
    SysTick_Config(cuentas_por_milisegundo); // Configura SysTick 
}

/* GPIO */

typedef struct Pin{
    GPIO_TypeDef * puerto;
    int nrPin;
}Pin;

/* Pines*/
static Pin const pines[BP_NUM_PINES] = {
    [BP_PA0] = {.puerto = GPIOA, .nrPin = 0 },
    [BP_PA1] = {.puerto = GPIOA, .nrPin = 1 },
    [BP_PA2] = {.puerto = GPIOA, .nrPin = 2 },
    [BP_PA3] = {.puerto = GPIOA, .nrPin = 3 },
    [BP_PA4] = {.puerto = GPIOA, .nrPin = 4 },
    [BP_PA5] = {.puerto = GPIOA, .nrPin = 5 },
    [BP_PA6] = {.puerto = GPIOA, .nrPin = 6 },

    [BP_PA9] = {.puerto = GPIOA, .nrPin = 9 },
    [BP_PA10] = {.puerto = GPIOA, .nrPin = 10},

    [BP_PB12] = {.puerto = GPIOA, .nrPin = 12},
    [BP_PC13] = {.puerto = GPIOA, .nrPin = 13}, 
    
    [BP_PB5] = {.puerto = GPIOB, .nrPin = 5 },
    [BP_PB6] = {.puerto = GPIOB, .nrPin = 6 },
    [BPPB7] = {.puerto = GPIOB, .nrPin = 7 },
    [BP_PB8] = {.puerto = GPIOB, .nrPin = 8 },
    [BP_PB9] = {.puerto = GPIOB, .nrPin = 9 },
    [BP_PB10] = {.puerto = GPIOB, .nrPin = 10
};

/*Lectura*/

/*Nota: Lee el estado de un pin de la Bluepill*/
bool BP_Pin_read(BP_Puerto_Pin hPin){
    return pin->puerto->IDR & (1 << pin->nrPin);
}

/*Modos:*/

void BP_Pin_Modo(BP_Puert_Pin hPin,BP_Pin_Modo modo){
    // Ver Manual de referencia de la familia sec. 9.2.1/.2
    enum ConfigsPin{
        /** 
         * Bits[1:0]: Modo E/S, 00 es modo entrada
         * Bits[3:2]: Configuración de entrada, 01 es entrada flotante
         */
        ENTRADA_FLOTANTE = 0b0100,
        /** 
         * Bits[1:0]: Modo E/S, 00 es modo entrada
         * Bits[3:2]: Configuración de entrada, 10 es entrada con pull-up/pull-dn
         */
        ENTRADA_PULLUP_PULLDN = 0b1000,
        /** 
         * Bits[1:0]: Modo E/S, 10 es modo salida con frec. máxima de 2MHz
         * Bits[3:2]: Configuración de salida, 00 es salida de propósito general normal (push/pull)
         */
        SALIDA_2MHz = 0b0010,
        /** 
         * Bits[1:0]: Modo E/S, 10 es modo salida con frec. máxima de 2MHz
         * Bits[3:2]: Configuración de salida, 01 es salida de propósito general open drain
         */
        SALIDA_2MHz_OPEN_DRAIN = 0b0110
    };

    uint32_t bits_modo;
    int const offset_habilitacion = (((uint32_t)(pines[pin].puerto) >> 10) & 0xF);
    uint32_t const mascara_habilitacion = 1UL << offset_habilitacion;
    RCC->APB2ENR |= mascara_habilitacion;

    switch (modo)
    {
    case BP_ENTRADA_PULL_UP:
        bits_modo=0b1000;
        pines[pin].puerto->ODR |= (0x1UL << pines[pin].npin);
        break;
    
    case BP_SALIDA_2MHz:
        bits_modo=0b0010;
        break;
    
    case BP_ENTRADA_FLOTANTE:
        bits_modo=0b0100;
    break;

    case BP_SALIDA_ALTERNATIVA_PUSH_PULL:
        bits_modo=0b1010;
    break;

    default:
    bits_modo=0;
    break;
    }
}


  int const OFFSET_CONFIG = ((pines[pin].npin % 8) * 4);
  int const MASCARA_CONFIG = 0b1111;
  uint32_t volatile *const CR =
      (pines[pin].nrpin < 8) ? &pines[pin].puerto->CRL : &pines[pin].puerto->CRH;

  *CR =
      (*CR & ~(MASCARA_CONFIG << OFFSET_CONFIG)) | (bitsModo << OFFSET_CONFIG);
}

/*NOTA: Establece el estado de un pin de la placa
-si valor es verdadero la funcion enciende el pin correspondiente 
utilizando el registro BSRR del puert
-si valor es falso, la funcion apaga el pin utilizando el registro BRR
*/

void BP_Pin_set(BP_PuertoPin pin, bool valor) {
  if (valor)
    pines[pin].puerto->BSRR = (0x1UL << pines[pin].npin);
  else
    pines[pin].puerto->BRR = (0x1UL << pines[pin].npin);
}

/*DELAY*/

/*NOTA: Crea un retraso en el programa durante un periodo de tiempo especificado
Verifica el tiempo transcurrido mediante la resta entre el valor actual de
"ticks" y "ticks_inicial"*/

void BP_Tiempo_delay(uint32_t tiempo){
    uint32_t const ticks_inicial = ticks;
    uint32_t tiempo_transcurrido = ticks - ticks_inicial;
    //if (tiempo_transcurrido || (tiempo < UINT32_MAX && SysTick->VAL < limiteRedondeo)) ++tiempo; // Redondeo
    while(tiempo_transcurrido < tiempo){
        __WFI();
        tiempo_transcurrido = ticks - ticks_inicial;
    }

}

void SysTick_Handler(void){
    ++ticks;
    
    if(funcion_ticks){
        funcion_ticks();
    }
}


void set_tick_handler(void (*funcion)(void)) { funcion_ticks = funcion; }

unsigned getTicks(void) { return ticks; }
