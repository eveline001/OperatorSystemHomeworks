#include "common.h"
#include "glo.h"

Window *win;

void *barber_thread(void *) {
	while (1) {
		P(customer);
		P(mutex);
			nr_customer --;
			puts("[barber] ready to start~");
			V(barber);
		V(mutex);
		P(finish);
		current_barber = -1;
		puts("[barber] finished.~");
	}
}

void *customer_thread(void *) {
	int i;
	P(mutex);
	if (nr_customer < NR_CUSTOMER) {
		puts("[customer] have seat, come in");
		nr_customer ++;
		for (i = 0; i < nr_chair; i ++)
			if (chair_status[i] == -1) {
				chair_status[i] = rand() % 50 + 1;
				break;
			}
		V(customer);
		V(mutex);

		P(barber);
		P(mutex);
			current_barber = chair_status[i];
			chair_status[i] = -1;
		V(mutex);
		printf("[customer] barber at : %d\n", current_barber);
		sleep(rand() % 4 + 2);
		V(finish);
	} else {
		puts("[customer] no seat, leave.");
		V(mutex);
		sleep(1);
	}
}

void *barber_main(void *) {
	sem_init(&mutex, 0, 1);
	sem_init(&customer, 0, 0);
	sem_init(&barber, 0, 0);
	sem_init(&finish, 0, 0);

	pthread_t barber;
	pthread_create(&barber, NULL, barber_thread, NULL);
	while (1) {
		if (rand() % 100 >= 50) {
			pthread_t customer;
			pthread_create(&customer, NULL, customer_thread, NULL);
		}
		sleep(1);
	}
}

int main(int argc, char *argv[]) {
	int i;
	srand(time(0));
	memset(chair_status, -1, sizeof(chair_status));

	nr_chair = NR_CUSTOMER;
	current_barber = -1;
	
	pthread_t b_main;
	pthread_create(&b_main, NULL, barber_main, NULL);

	QApplication app(argc, argv);
	win = new Window;
	win->show();
	return app.exec();
}
