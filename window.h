// window.h

#ifndef WINDOW_H
#define WINDOW_H

#include <QWidget>
#include <QSlider>
#include <QImage>
#include <QPushButton>


namespace Ui {
class Window;
}

class Window : public QWidget
{
    Q_OBJECT

public:
    explicit Window(QWidget *parent = 0);
    ~Window();
	void flagInitial();
	bool showFlag();
	void setFlag();

private slots:
	QString handleButton();

//public slots:
	//void setFlag(bool flag);
private:
    Ui::Window *ui;
	QPushButton *m_qbutton;
	bool flag;
};

#endif // WINDOW_H
