/**
*  @myglwidget类的实现
*  包含了基于OpenGL的三维模型和纹理渲染、对鼠标拖移的响应等功能
*  作为子窗口，在选取图片以后，进行模型的图形化展示
*  注意，obj必须在initializeGL()中初始化.
*/
#include <QtWidgets>
#include <QtOpenGL>

#include "myglwidget.h"
#include <Model.h>
#include <iostream>
#include <fstream>

#include <string>

using namespace std;

MyGLWidget::MyGLWidget(QWidget *parent)
	: QGLWidget(QGLFormat(QGL::SampleBuffers), parent)
{
	xRot = 0;
	yRot = 0;
	zRot = 0;
}

MyGLWidget::~MyGLWidget()
{
}

QSize MyGLWidget::minimumSizeHint() const
{
	return QSize(50, 50);
}

QSize MyGLWidget::sizeHint() const
{
	return QSize(400, 400);
}

void MyGLWidget::setXRotation(int angle)
{
	if (angle != xRot) 
	{
		xRot = angle;
		emit xRotationChanged(angle);
		updateGL();
	}
}

void MyGLWidget::setYRotation(int angle)
{
	if (angle != yRot) 
	{
		yRot = angle;
		emit yRotationChanged(angle);
		updateGL();
	}
}


void MyGLWidget::setZRotation(int angle)
{
	if (angle != zRot) 
	{
		zRot = angle;
		emit zRotationChanged(angle);
		updateGL();
	}
}


void MyGLWidget::setFlag(bool flag)
{
	this->flag = flag;
}


void MyGLWidget::initializeGL()
{
	//注意，模型必须在initializeGL成员函数中实例化！！否则无法正常渲染纹理贴图！！
	obj = new Model("out.obj");	
	qglClearColor(Qt::black);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glShadeModel(GL_SMOOTH);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_MULTISAMPLE);
	static GLfloat lightPosition[4] = { 0.5, 5.0, 7.0, 1.0 };
	glLightfv(GL_LIGHT0, GL_POSITION, lightPosition);
}

void MyGLWidget::paintGL()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	glTranslatef(0.0, 0.0, -10.0);
	glRotatef(xRot / 16.0, 1.0, 0.0, 0.0);
	glRotatef(yRot / 16.0, 0.0, 1.0, 0.0);
	glRotatef(zRot / 16.0, 0.0, 0.0, 1.0);
	draw();
}


void MyGLWidget::draw()
{
	obj->render();
}


void MyGLWidget::resizeGL(int width, int height)
{
	int side = qMin(width, height);
	glViewport((width - side) / 2, (height - side) / 2, side, side);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
#ifdef QT_OPENGL_ES_1
	glOrthof(-0.5, +0.5, -0.5, +0.5, 4.0, 15.0)

#else
	glOrtho(-100, +100, -100, +100, -100.0, 100.0);

	
#endif
	glMatrixMode(GL_MODELVIEW);
}

void MyGLWidget::mousePressEvent(QMouseEvent *event)
{
	lastPos = event->pos();
}


void MyGLWidget::mouseMoveEvent(QMouseEvent *event)
{
	int dx = event->x() - lastPos.x();
	int dy = event->y() - lastPos.y();

	if (event->buttons() & Qt::LeftButton) {
		setXRotation(xRot + 8 * dy);
		setYRotation(yRot + 8 * dx);
	}
	else if (event->buttons() & Qt::RightButton) {
		setXRotation(xRot + 8 * dy);
		setZRotation(zRot + 8 * dx);
	}

	lastPos = event->pos();
}
