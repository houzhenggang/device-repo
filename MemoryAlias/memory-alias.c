#include <stddef.h>
#include <stdio.h>
#include <stdint.h>
#include "qsdk_if.h"
#include "qsdk_qemu_gateway.h"

static void * alias_init(void * dev, void * init_data)
{
    void * alias_dev = QSDK_alloc_memory_region();
    qsdk_set_mr(dev, alias_dev);

    return alias_dev;
}

static void alias_inst(void * dev, void * opaque)
{
    uint64_t size   = get_property_int32(dev, "size");
    uint64_t offset = get_property_int32(dev, "offset");
    char * name     = get_property_string(dev, "name");
    Device * target = (Device*)get_property_ptr(dev, "target");

    void * alias_dev = opaque;
    void * target_mem_ptr = qsdk_get_mr(target);

    memory_region_init_alias(alias_dev, NULL, name, target_mem_ptr, offset, size);
}

void init_qsdk_module(void)
{
    dev_init_t alias;

    alias.name = "memory-alias";
    alias.dev_init = alias_init;
    alias.dev_inst = alias_inst;
    alias.dev_delete = NULL;

    register_device(&alias);
}
