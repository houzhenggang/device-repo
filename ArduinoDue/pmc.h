#ifndef PMC_H_
#define PMC_H_
#include <qsdk_if.h>

void * pmc_init(void * dev, void * init_data);
void pmc_inst(void * dev, void * opaque);

#endif /* PMC_H_ */
