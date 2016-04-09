#include <stdio.h>
#include <stddef.h>
#include <string.h>
#include "uotghs.h"

#define UOTGHS_SIZE (0x082C)
#define UOTGHS_SR_CLKUSABLE (1 << 14)

static struct {
    int32_t dummy1;
    int32_t UOTGHS_DEVISR;
} usb_inst;

static mem_region mr;

static void usb_write(void * opaque, int64_t offset, uint64_t value, unsigned size)
{
    printf("USB Write at 0x%x, value 0x%x\n", (int)offset, (int)value);

    *(uint32_t*)(((uint8_t*)&usb_inst) + (uint32_t)offset) = (uint32_t)value;
}

static uint64_t usb_read(void *opaque, int64_t offset, unsigned size)
{
    printf("USB Read at 0x%x\n", (int)offset);

    return *(uint32_t*)(((uint8_t*)&usb_inst) + (uint32_t)offset);

    return 0;
}

void * uotghs_init(void * dev, void * init_data)
{
    mr = alloc_memory_region();
    qsdk_set_mr(dev, mr);

    return dev;
}

void uotghs_inst(void * dev, void * opaque)
{
    set_io_operations(dev, usb_read, usb_write, UOTGHS_SIZE);

    memset(&usb_inst, 0, sizeof(usb_inst));

    usb_inst.UOTGHS_DEVISR |= 0xFFFFFFFF;
}
