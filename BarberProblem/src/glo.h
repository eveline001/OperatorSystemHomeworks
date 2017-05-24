#include "common.h"

extern sem_t mutex;
extern sem_t customer;
extern sem_t barber;
extern sem_t finish;
extern int nr_customer;
extern int nr_chair;
extern int current_barber;
extern int chair_status[NR_CUSTOMER];

