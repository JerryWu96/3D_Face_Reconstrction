/**
*  @window类的实现
*  主要功能为图片选取UI
*
*/

#include <QtWidgets>
#include <QCloseEvent>

#include "window.h"
#include "ui_window.h"
#include "myglwidget.h"

using namespace std;


Window::Window(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Window)
{
    ui->setupUi(this);
	flagInitial();
	connect(ui->myGLWidget, SIGNAL(xRotationChanged(int)), ui->rotXSlider, SLOT(setValue(int)));
	connect(ui->myGLWidget, SIGNAL(yRotationChanged(int)), ui->rotYSlider, SLOT(setValue(int)));
	connect(ui->myGLWidget, SIGNAL(zRotationChanged(int)), ui->rotZSlider, SLOT(setValue(int)));
	m_qbutton = new QPushButton("Next", this);
	//m_qbutton->move(10, 10);
	m_qbutton->setGeometry(QRect(QPoint(400, 10), QSize(50, 50)));
	connect(m_qbutton, SIGNAL(clicked()), this, SLOT(handleButton()));
	//connect(ui->myGLWidget, SIGNAL(WidgetClosed), this, SLOT(setFlag()));
}

Window::~Window()
{
	delete ui;
}



bool Window::showFlag()
{
	return this->flag;
	//emit WidgetClosed();
}

void Window::flagInitial()
{
	this->flag = 0;
}
void Window::setFlag()
{
	//qDebug() << "~~~setflag";
	this->flag = 1;
		//emit WidgetClosed();
}

QString Window::handleButton()
{
	QString Done = "done";
	setFlag();
	return Done;
}


