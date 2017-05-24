#include "common.h"

sem_t mutex;
sem_t customer;
sem_t barber;
sem_t finish;
int nr_customer;
int nr_chair;
int current_barber;
int chair_status[NR_CUSTOMER];

