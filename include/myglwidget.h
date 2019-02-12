// myglwidget.h

#ifndef MYGLWIDGET_H
#define MYGLWIDGET_H

#include <QGLWidget>

class Model;

class MyGLWidget : public QGLWidget
{
	Q_OBJECT
public:
	explicit MyGLWidget(QWidget *parent = 0);
	~MyGLWidget();
	QSize minimumSizeHint() const;
	QSize sizeHint() const;


protected:
	void initializeGL();
	void paintGL();
	void resizeGL(int width, int height);


	void mousePressEvent(QMouseEvent *event);
	void mouseMoveEvent(QMouseEvent *event);
	//void wheelEvent(QWheelEvent *event);
	//void closeEvent(QCloseEvent *event);


public slots:
	// X-Y-Z坐标轴调整滑块
	void setXRotation(int angle);
	void setYRotation(int angle);
	void setZRotation(int angle);
	void setFlag(bool flag);
signals:
	// 基于鼠标移动事件的信号
	void xRotationChanged(int angle);
	void yRotationChanged(int angle);
	void zRotationChanged(int angle);
private:
	void draw();
	Model *obj;
	int xRot;
	int yRot;
	int zRot;
	QPoint lastPos;
	bool flag;
};


#endif 

