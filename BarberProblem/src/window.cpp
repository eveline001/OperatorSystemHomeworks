#include "window.h"
#include "glo.h"

QPixmap getPicture(int d) {
	char buf[12];
	sprintf(buf, "img/%d.gif", d);
	QPixmap img(buf);
	return img.scaled(100, 100, Qt::KeepAspectRatio);
}

Window::Window() {
	int i;
	setWindowTitle(tr("Barber's problem"));

	for (i = 0; i < NR_CUSTOMER; i ++) {
		wait[i] = new QLabel(this);
		wait[i]->setPixmap(getPicture(0));
		wait[i]->move(100 * i, 200);
		wait[i]->show();

		QLabel *xx = new QLabel(this);
		char buf[50];
		sprintf(buf, "<font color=\"green\">Chair #%d</font>", i + 1);
		xx->setText(buf);
		xx->move(100 * i, 300);
		xx->show();
	}

	barber = new QLabel(this);
	barber->setPixmap(getPicture(99));
	barber->move(100 * (NR_CUSTOMER / 2), 50);
	barber->show();

	QLabel *yy = new QLabel(this);
	yy->setText("<font color=\"red\">B A R B E R</font>");
	yy->move(100 * (NR_CUSTOMER / 2), 150);
	yy->show();

	QPalette plt = palette();
	plt.setColor(QPalette::Background, QColor("white"));
	setPalette(plt);

	startTimer(100);
}
void Window::timerEvent(QTimerEvent *) {
	int data[NR_CUSTOMER], i, cnt;
	P(mutex);
	for (i = 0; i < NR_CUSTOMER; i ++)
		data[i] = chair_status[i];
	cnt = current_barber;
	V(mutex);

	barber->close();
	barber->setPixmap(getPicture( cnt == -1 ? 99 : cnt ) );
	barber->move(100 * (NR_CUSTOMER / 2), 50);
	barber->show();

	for (i = 0; i < NR_CUSTOMER; i ++) {
		wait[i]->close();
		wait[i]->setPixmap(getPicture( data[i] == -1 ? 0 : data[i]) );
		wait[i]->move(100 * i, 200);
		wait[i]->show();
	}
	update();
}

