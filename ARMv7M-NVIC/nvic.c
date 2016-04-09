#include <stddef.h>
#include <stdio.h>
#include <stdint.h>
#include "qsdk_if.h"
#include "qsdk_qemu_gateway.h"

static void * armv7m_nvic_init(void * dev, void * init_data)
{
    void * nvic_data = qdev_create(NULL, "armv7m_nvic");
    set_property_ptr(dev, "nvic_data", nvic_data);
    return dev;
}

static
void do_sys_reset(void * opaque, int n, int level)
{
    if (level) {
        qemu_system_reset_request();
    }
}

static void armv7m_reset(void * opaque)
{
    cpu_reset(opaque);
}

static void armv7m_nvic_inst(void * dev, void * opaque)
{
#define ARM_CPU_IRQ 0
    void * nvic = (void*)get_property_ptr(dev, "nvic_data");
    void * target_dev = get_property_ptr(dev, "target");
    void * cpu = (void*)get_property_ptr(target_dev, "cpu_instance");

    int num_irq = get_property_int32(dev, "num_irq");
    qdev_prop_set_uint32(nvic, "num-irq", num_irq);

    set_nvic(nvic, cpu);
    qdev_init_nofail(nvic);

    sysbus_connect_irq(get_qemu_sys_bus_device(nvic), 0,
                       qdev_get_gpio_in(get_qemu_device(cpu), ARM_CPU_IRQ));

    /* Hack to map an additional page of ram at the top of the address
       space.  This stops qemu complaining about executing code outside RAM
       when returning from an exception.  */
    mem_region hack = alloc_memory_region();
    memory_region_init_ram(hack, NULL, "armv7m.hack", 0x1000, NULL);
    memory_region_add_subregion(get_system_memory(), 0xfffff000, hack);

    qemu_register_reset(armv7m_reset, cpu);
}

void init_qsdk_module(void)
{
    dev_init_t nvic;

    nvic.name = "armv7m_nvic";
    nvic.dev_init = armv7m_nvic_init;
    nvic.dev_inst = armv7m_nvic_inst;
    nvic.dev_delete = NULL;

    register_device(&nvic);
}

