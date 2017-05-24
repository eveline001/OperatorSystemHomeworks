#ifndef __COMMON_H
#define __COMMON_H

#include <pthread.h>
#include <semaphore.h>
#include <window.h>
#include <cstdlib>

#define NR_CUSTOMER 5
#define P(a) sem_wait(&a)
#define V(a) sem_post(&a)

#endif
