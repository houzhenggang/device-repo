#include <stddef.h>
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include "qsdk_if.h"

#define DEV_SIZE 0x4

typedef struct lstr_
{
    char msg_buff[32];
    int msg_pos;
    void * mr;
} lstr_t;

static void c_logger_write(void * opaque, int64_t offset, uint64_t value, unsigned size)
{
    lstr_t * logger = (lstr_t*)opaque;

    logger->msg_buff[logger->msg_pos++] = (char)value;
    if (value == '\n')
    {
        printf("C LOGGER message: %s", logger->msg_buff);
        logger->msg_pos = 0;
    }
}

static uint64_t c_logger_read(void * opaque, int64_t offset, unsigned size)
{
    return 0;
}

static void * c_logger_init(void * dev, void * init_data)
{
    lstr_t * logger = calloc(1, sizeof(lstr_t));
    logger->mr = alloc_memory_region();

    qsdk_set_mr(dev, logger->mr);

    return logger;
}

static void c_logger_inst(void * dev, void * opaque)
{
    set_io_operations(dev, c_logger_read, c_logger_write, DEV_SIZE);
}

void init_qsdk_module(void)
{
    dev_init_t logger;

    logger.name = "c_logger";
    logger.dev_init = c_logger_init;
    logger.dev_inst = c_logger_inst;
    logger.dev_delete = NULL;

    register_device(&logger);
}
