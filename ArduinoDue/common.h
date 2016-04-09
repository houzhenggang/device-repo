#ifndef _COMMON_H_
#define _COMMON_H_

#define WRITE_32(BASE, OFFSET, VAL) *(uint32_t*)(((uint8_t*)BASE) + (uint32_t)OFFSET) = (uint32_t)VAL;
#define READ_32(BASE, OFFSET)       *(uint32_t*)(((uint8_t*)BASE) + (uint32_t)OFFSET);

#endif
