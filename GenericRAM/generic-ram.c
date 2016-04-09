#include <stddef.h>
#include <stdio.h>
#include <stdint.h>
#include "qsdk_if.h"
#include "qsdk_qemu_gateway.h"

static void * generic_ram_init(void * dev, void * init_data)
{
    void * ram_dev = QSDK_alloc_memory_region();
    qsdk_set_mr(dev, ram_dev);

    return ram_dev;
}

static void generic_ram_inst(void * dev, void * opaque)
{
    char * name;
    int size;
    void * ram_dev = opaque;

    size = get_property_int32(dev,  QSDK_DEVICE_SIZE);
    name = get_property_string(dev, "name");

    memory_region_init_ram(ram_dev, NULL, name, size, NULL);
}

void init_qsdk_module(void)
{
    dev_init_t ram;

    ram.name = "generic_ram";
    ram.dev_init = generic_ram_init;
    ram.dev_inst = generic_ram_inst;
    ram.dev_delete = NULL;

    register_device(&ram);
}
