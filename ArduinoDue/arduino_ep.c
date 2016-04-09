#include <stdint.h>
#include <stdlib.h>
#include "uart.h"
#include "pmc.h"
#include "uotghs.h"
#include "qsdk_if.h"


void * arduino_board_init(void * dev, void * init_data)
{
    return NULL;
}

void arduino_board_inst(void * dev, void * opaque)
{
    mem_region * sysmem = get_sysmem();

    Device * bootmem  = create_device("boot",  "memory-alias");
    Device * rom      = create_device("rom",   "generic_rom");
    Device * ram1     = create_device("ram1",  "generic_ram");
    Device * ram2     = create_device("ram2",  "generic_ram");
    Device * eef0     = create_device("eef0",  "generic_ram");
    Device * uart     = create_device("uart",  "arduinodue_uart");
    Device * pmc      = create_device("pmc",   "arduinodue_pmc");
    Device * uotghs   = create_device("usb",   "arduinodue_uotghs");
    Device * log1     = create_device("log1", "c_logger");
    Device * log2     = create_device("log2", "py_logger");
    Device * log3     = create_device("log3", "rust_logger");

    set_property_ptr(bootmem, "target", rom);
    set_property_int32(bootmem, "offset", 0);
    set_property_int32(bootmem, "size", 0xffff);

    set_property_string(rom, "file", get_property_string(dev, "kernel_file"));

    /* map device        what    where   at          how large */
    map_device_to_memory(rom,     sysmem, 0x80000,    0xf00000);
    map_device_to_memory(bootmem, sysmem, 0x0,        0xffff);
    map_device_to_memory(ram1,    sysmem, 0x20000000, 0xFFFF);
    map_device_to_memory(ram2,    sysmem, 0x20070000, 0x17FFF);
    map_device_to_memory(eef0,    sysmem, 0x400E0A00, 0x400);
    map_device_to_memory(uart,    sysmem, 0x400E0800, 0x200);
    map_device_to_memory(pmc,     sysmem, 0x400E0600, 0x200);
    map_device_to_memory(uotghs,  sysmem, 0x400AC800, 0x830);

    map_device_to_memory(log1,   sysmem, 0x400E1000, 0x50);
    map_device_to_memory(log2,   sysmem, 0x400E1200, 0x50);
    map_device_to_memory(log3,   sysmem, 0x400E1400, 0x50);

    Device * processor = create_device("mcu", "cortex_m3");

    Device * intctl    = create_device("nvic", "armv7m_nvic");
    set_property_ptr(intctl, "target", processor);
    set_property_int32(intctl, "num_irq", 64);

    /* Instantiate all created devices */
    instantiate_devices();
}

void init_qsdk_module(void)
{
    dev_init_t uart;
    dev_init_t pmc;
    dev_init_t uotghs;
    dev_init_t arduino;

    uart.name = "arduinodue_uart";
    uart.dev_init = uart_init;
    uart.dev_inst = uart_inst;
    uart.dev_delete = NULL;
    register_device(&uart);

    pmc.name = "arduinodue_pmc";
    pmc.dev_init = pmc_init;
    pmc.dev_inst = pmc_inst;
    pmc.dev_delete = NULL;
    register_device(&pmc);

    uotghs.name = "arduinodue_uotghs";
    uotghs.dev_init = uotghs_init;
    uotghs.dev_inst = uotghs_inst;
    uotghs.dev_delete = NULL;
    register_device(&uotghs);

    arduino.name = "arduino_board";
    arduino.dev_init = arduino_board_init;
    arduino.dev_inst = arduino_board_inst;
    arduino.dev_delete = NULL;
    register_board(&arduino);
}
