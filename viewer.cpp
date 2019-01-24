/**
*  @viewer类的实现
*  主要功能为图片选取UI
*/


#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsPixmapItem>
#include <string>
#include <fstream>

#include "viewer.h"
#include "Functions.h"

using namespace std;


Viewer::Viewer(QWidget *parent)
	: QMainWindow(parent)
	//,ui(new Ui::QtGui)
{
	ui.setupUi(this);
	bool flag = 0;
	setFlag(flag);
	m_button = new QPushButton("Choose Pic", this);
	m_button->setGeometry(QRect(QPoint(100, 100), QSize(200, 50)));
	connect(m_button, SIGNAL(clicked()), this, SLOT(handleButton()));

}


QString Viewer::handleButton()
{

	QString fileName;
	QString fileDir;
	QFileDialog dialog(this);
	dialog.setNameFilter(tr("Images (*.jpg)"));
	dialog.setViewMode(QFileDialog::Detail);


	fileName = QFileDialog::getOpenFileName(this, tr("Open File"),
		"C:/", tr("Images (*.jpg)"));

	//图片路径保存txt
	QFile file("Pic.txt");
	if (file.open(QIODevice::ReadWrite))
	{
		QTextStream stream(&file);
		stream << fileName;
	}
	file.close();

	bool flag = 1;
	setFlag(flag);

	//show image ok
	QGraphicsPixmapItem * image = new QGraphicsPixmapItem(QPixmap(fileName));
	int imageWidth = image->pixmap().width();
	int imageHeight = image->pixmap().height();
	image->setOffset(-imageWidth / 2, -imageHeight / 2);
	image->setPos(0, 0);
	
	QGraphicsScene *scene = new QGraphicsScene();
	scene->setSceneRect(-imageWidth / 2, -imageHeight / 2, imageWidth, imageHeight);
	QGraphicsView * gview = new QGraphicsView();
	//ui->mainImage->addWidget(gv);
	gview->setScene(scene);
	gview->scene()->addItem(image);
	gview->show();



	return fileName;
}

void Viewer::setFlag(bool flag)
{
	this->flag = flag;
}


bool Viewer::showFlag()
{
	return this->flag;
}