#include <stddef.h>
#include <stdio.h>
#include <stdint.h>
#include "qsdk_if.h"
#include "qsdk_qemu_gateway.h"

static void * cortex_m3_init(void * dev, void * init_data)
{
    void * cpu = cpu_arm_init("cortex-m3");
    set_property_ptr(dev, "cpu_instance", cpu);

    return dev;
}

static void cortex_m3_inst(void * dev, void * opaque)
{
    /* TODO: investigate the need for the call below */
//    qemu_register_reset(armv7m_reset, get_created_payload(dev));
}

void init_qsdk_module(void)
{
    dev_init_t cortex_m3;

    cortex_m3.name = "cortex_m3";
    cortex_m3.dev_init = cortex_m3_init;
    cortex_m3.dev_inst = cortex_m3_inst;
    cortex_m3.dev_delete = NULL;

    register_device(&cortex_m3);
}
