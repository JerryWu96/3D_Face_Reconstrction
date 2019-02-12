// window.h

#ifndef VIEWER_H
#define VIEWER_H

#include <QtWidgets/QMainWindow>
#include "ui_viewer.h"
#include <QPushButton>
#include <QInputDialog>
#include <QFileDialog>
#include <QString>
#include <QFile>
#include <QTextStream>

#include <string>
#include <iostream>
#include <QImage>
#include <QLabel>

namespace Ui {
	class Viewer;
}

class Viewer : public QMainWindow
{
	Q_OBJECT

public:
	Viewer(QWidget *parent = Q_NULLPTR);
	bool showFlag();
	void setFlag(bool flag);
private slots:
	QString handleButton();
	//QString getImageName();

private:
	
	Ui::ViewerClass ui;
	bool flag;
	QPushButton *m_button;
	//QGraphicsScene *scene;
	QPixmap image;
	//QString m_image;
};

#endif
