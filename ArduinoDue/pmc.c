#include <stdint.h>
#include <stddef.h>
#include <stdio.h>
#include "pmc.h"
#include "qsdk_if.h"

#define PMC_SIZE (sizeof(pmc))

#define CKGR_MOR_MOSCSEL (0x1u << 24)   /* Main Oscillator Selection */
#define PMC_SR_MOSCSELS (0x1u << 16)    /* Main Oscillator Selection Status */
#define PMC_SR_LOCKA (0x1u << 1)        /* PLLA Lock Status */
#define PMC_SR_MCKRDY (0x1u << 3)       /* Master Clock Status */
#define PMC_SR_LOCKU (0x1u << 6)        /* UTMI PLL Lock Status */

static struct {
    uint32_t PMC_SCER;      /* System Clock Enable Register */
    uint32_t PMC_SCDR;      /* System Clock Disable Register */
    uint32_t PMC_SCSR;      /* System Clock Status Register */
    uint32_t Reserved1[1];
    uint32_t PMC_PCER0;     /* Peripheral Clock Enable Register 0 */
    uint32_t PMC_PCDR0;     /* Peripheral Clock Disable Register 0 */
    uint32_t PMC_PCSR0;     /* Peripheral Clock Status Register 0 */
    uint32_t CKGR_UCKR;     /* UTMI Clock Register */
    uint32_t CKGR_MOR;      /* Main Oscillator Register */
    uint32_t CKGR_MCFR;     /* Main Clock Frequency Register */
    uint32_t CKGR_PLLAR;    /* PLLA Register */
    uint32_t Reserved2[1];
    uint32_t PMC_MCKR;      /* Master Clock Register */
    uint32_t Reserved3[1];
    uint32_t PMC_USB;       /* USB Clock Register */
    uint32_t Reserved4[1];
    uint32_t PMC_PCK[3];    /* Programmable Clock 0 Register */
    uint32_t Reserved5[5];
    uint32_t PMC_IER;       /* Interrupt Enable Register */
    uint32_t PMC_IDR;       /* Interrupt Disable Register */
    uint32_t PMC_SR;        /* Status Register */
    uint32_t PMC_IMR;       /* Interrupt Mask Register */
    uint32_t PMC_FSMR;      /* Fast Startup Mode Register */
    uint32_t PMC_FSPR;      /* Fast Startup Polarity Register */
    uint32_t PMC_FOCR;      /* Fault Output Clear Register */
    uint32_t Reserved6[26];
    uint32_t PMC_WPMR;      /* Write Protect Mode Register */
    uint32_t PMC_WPSR;      /* Write Protect Status Register */
    uint32_t Reserved7[5];
    uint32_t PMC_PCER1;     /* Peripheral Clock Enable Register 1 */
    uint32_t PMC_PCDR1;     /* Peripheral Clock Disable Register 1 */
    uint32_t PMC_PCSR1;     /* Peripheral Clock Status Register 1 */
    uint32_t PMC_PCR;       /* Peripheral Control Register */
} pmc;

static mem_region mr;

static void pmc_write(void * opaque, int64_t offset, uint64_t value, unsigned size)
{
    printf("PMC Write at 0x%x, value 0x%x\n", (int)offset, (int)value);
    if (offset < PMC_SIZE)
    {
        *(uint32_t*)(((uint8_t*)&pmc) + (uint32_t)offset) = (uint32_t)value;
    }
}

static uint64_t pmc_read(void *opaque, int64_t offset, unsigned size)
{
    printf("PMC Read at 0x%x\n", (int)offset);

    if (offset < PMC_SIZE)
    {
        return *(uint32_t*)(((uint8_t*)&pmc) + (uint32_t)offset);
    }

    return 0;
}

void * pmc_init(void * dev, void * init_data)
{
    mr = alloc_memory_region();
    qsdk_set_mr(dev, mr);

    return dev;
}

void pmc_inst(void * dev, void * opaque)
{
    set_io_operations(dev, &pmc_read, &pmc_write, PMC_SIZE);

    /* Set registers to bypass arduino SystemInit */
    pmc.CKGR_MOR |= CKGR_MOR_MOSCSEL;
    pmc.PMC_SR |= PMC_SR_MOSCSELS | PMC_SR_LOCKA | PMC_SR_MCKRDY | PMC_SR_LOCKU;
}

