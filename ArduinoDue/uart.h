#ifndef UART_H_
#define UART_H_
#include <qsdk_if.h>

void * uart_init(void * dev, void * init_data);
void uart_inst(void * dev, void * opaque);

#endif /* UART_H_ */
