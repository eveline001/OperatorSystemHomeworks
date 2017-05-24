#ifndef __WINDOW_H
#define __WINDOW_H

#include <QtGui>
#include <QWidget>
#include <QPainter>
#include "common.h"

class Window: public QWidget {
	Q_OBJECT

public:
	Window();
	void timerEvent(QTimerEvent *);
	QLabel *wait[100], *barber;

};

#endif
