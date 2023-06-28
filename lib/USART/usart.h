
#ifndef USART_H
#define USART_H

#ifndef NULL
#ifndef __cplusplus
#define NULL (void*)0
#else
#define NULL 0
#endif
#endif

#ifdef __cplusplus
extern "C"
{
#endif
/**
 * @brief Inicializa el puerto serie para transmitir los resultados
 * de las pruebas.
 * 
 * @param baudrate Símbolos por segundo
 */
void usartOutputStart(unsigned long baudrate);
/**
 * @brief Transmite un caracter por el puerto serie
 * 
 * @param c Caracter a transmitir (recortado a 8 bits)
 */
void usartOutputChar(unsigned int c);
/**
 * @brief Espera que finalice la transmisión en curso
 * 
 */
void usartOutputFlush(void);
/**
 * @brief Detiene y apaga el puerto serie
 * 
 */
void usartOutputComplete(void);

#define USART_OUTPUT_START()    usartOutputStart((unsigned long) 115200)
#define USART_OUTPUT_CHAR(c)    usartOutputChar(c)
#define USART_OUTPUT_FLUSH()    usartOutputFlush()
#define USART_OUTPUT_COMPLETE() usartOutputComplete()

/**
 * @brief habilita la recepcion de usart
 * 
 */
void usartEnableRx(void);

/**
 * @brief deshabilita la recepcion
 * 
 */

void usartDisableRx(void);

/**
 * @brief recibe caracteres
 * 
 * @return char 
 */

char usartReceiveChar(void);
#ifdef __cplusplus
}
#endif /* extern "C" */

#endif /* UNITY_CONFIG_H */

