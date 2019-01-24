/**
*  @delay函数
*  用于main函数默认1s处理一次pushbutton监视
*/


#include <QTime>
#include <QCoreApplication>

//addSecs参数即延迟秒数
void delay(int second)
{
	QTime dieTime = QTime::currentTime().addSecs(second);
	while (QTime::currentTime() < dieTime)
		QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
}
