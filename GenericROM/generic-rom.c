#include <stddef.h>
#include <stdio.h>
#include <stdint.h>
#include "qsdk_if.h"
#include "qsdk_qemu_gateway.h"

static void * generic_rom_init(void * dev, void * init_data)
{
    void * rom_dev = QSDK_alloc_memory_region();
    qsdk_set_mr(dev, rom_dev);

    return rom_dev;
}

static void generic_rom_inst(void * dev, void * opaque)
{
    char * name;
    char * file;
    int size;
    void * rom_dev = opaque;

    size = get_property_int32(dev,  QSDK_DEVICE_SIZE);
    name = get_property_string(dev, "name");
    file = get_property_string(dev, "file");

    //memory_region_init_rom_device(rom_dev, NULL, NULL, NULL, name, size, NULL);
    memory_region_init_ram(rom_dev, NULL, name, size, NULL);

    void * ram_ptr = memory_region_get_ram_ptr(rom_dev);

    if (ram_ptr)
    {
        int fsize = 0;
        FILE * fbin = fopen(file, "rb");

        if (fbin)
        {
            fseek(fbin, 0L, SEEK_END);
            fsize = ftell(fbin);
            fseek(fbin, 0L, SEEK_SET);

            fread(ram_ptr, fsize, 1, fbin);
            fclose(fbin);
        }
        else
        {
            fprintf(stderr, "Could not open file %s\n", file);
        }
    }
    else
    {
        /* TODO: error */
    }
}

void init_qsdk_module(void)
{
    dev_init_t rom;

    rom.name = "generic_rom";
    rom.dev_init = generic_rom_init;
    rom.dev_inst = generic_rom_inst;
    rom.dev_delete = NULL;

    register_device(&rom);
}
