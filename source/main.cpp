/**
*  @main函数
*  进行QT初始化、其他功能的入口
*/
#include <QApplication>
#include <QDesktopWidget>
#include <Qt3DCore/QEntity>
#include <Qt3DCore/QTransform>
#include <Qt3DCore/QAspectEngine>
#include <Qt3DRender/qrenderaspect.h>
#include <Qt3DRender/QCamera>
#include <Qt3DRender/QMaterial>
#include <Qt3DRender/QMesh>
#include <Qt3DExtras/Qt3DWindow>
#include <Qt3DExtras/QTorusMesh>
#include <Qt3DExtras/QOrbitCameraController>
#include <Qt3DExtras/QPhongMaterial>


#include "viewer.h"
#include "window.h"
#include "myglwidget.h"
#include "Model.h"
#include "Functions.h"



int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
	Viewer viewer;
	viewer.show();

	while (!viewer.showFlag())
	{
		delay(1);
		if (viewer.showFlag())
		{
			Reconstruct();
			Window window;
			window.setWindowTitle("obj Model Viewer");
			window.resize(window.sizeHint());
			int desktopArea = QApplication::desktop()->width() * QApplication::desktop()->height();
			int widgetArea = window.width() * window.height();
			if (((float)widgetArea / (float)desktopArea) < 0.75f)
			{
				window.show();
			}
			else
			{
				window.showMaximized();
			}
			viewer.setFlag(0);
			while (!window.showFlag())
			{
				//qDebug() << "showFlag:" << window.showFlag();
				delay(1);
			}
		}
	}
	
    return app.exec();
}
