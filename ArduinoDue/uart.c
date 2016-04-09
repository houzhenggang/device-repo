#include <stddef.h>
#include <stdio.h>
#include <stdint.h>
#include "uart.h"
#include "common.h"

#define UART_DEV_SIZE 0x200
#define UART_SR_TXRDY (1 << 1)

static struct {
  uint32_t UART_CR;       /* Control Register */
  uint32_t UART_MR;       /* Mode Register */
  uint32_t UART_IER;      /* Interrupt Enable Register */
  uint32_t UART_IDR;      /* Interrupt Disable Register */
  uint32_t UART_IMR;      /* Interrupt Mask Register */
  uint32_t UART_SR;       /* Status Register */
  uint32_t UART_RHR;      /* Receive Holding Register */
  uint32_t UART_THR;      /* Transmit Holding Register */
  uint32_t UART_BRGR;     /* Baud Rate Generator Register */
  uint32_t Reserved1[55];
  uint32_t UART_RPR;      /* Receive Pointer Register */
  uint32_t UART_RCR;      /* Receive Counter Register */
  uint32_t UART_TPR;      /* Transmit Pointer Register */
  uint32_t UART_TCR;      /* Transmit Counter Register */
  uint32_t UART_RNPR;     /* Receive Next Pointer Register */
  uint32_t UART_RNCR;     /* Receive Next Counter Register */
  uint32_t UART_TNPR;     /* Transmit Next Pointer Register */
  uint32_t UART_TNCR;     /* Transmit Next Counter Register */
  uint32_t UART_PTCR;     /* Transfer Control Register */
  uint32_t UART_PTSR;     /* Transfer Status Register */
} uart_str;

static mem_region mr;

static void uart_write(void * opaque, int64_t offset, uint64_t value, unsigned size)
{
    printf("%c", (int)value);

    if (offset < UART_DEV_SIZE)
    {
        WRITE_32(&uart_str, offset, value);
    }
}

static uint64_t uart_read(void *opaque, int64_t offset, unsigned size)
{
    return READ_32(&uart_str, offset);
}

void * uart_init(void * dev, void * init_data)
{
    mr = alloc_memory_region();

    qsdk_set_mr(dev, mr);

    return mr;
}

void uart_inst(void * dev, void * opaque)
{
    set_io_operations(dev, uart_read, uart_write, UART_DEV_SIZE);

    uart_str.UART_SR |= UART_SR_TXRDY;
}

