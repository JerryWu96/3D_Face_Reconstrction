#pragma once
/********************************************************************************
** Form generated from reading UI file 'viewer.ui'
**
** Created by: Qt User Interface Compiler version 5.10.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_VIEWER_H
#define UI_VIEWER_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_viewerClass
{
public:
	QWidget * centralWidget;
	QMenuBar *menuBar;
	QToolBar *mainToolBar;
	QStatusBar *statusBar;

	void setupUi(QMainWindow *ViewerClass)
	{
		if (ViewerClass->objectName().isEmpty())
			ViewerClass->setObjectName(QStringLiteral("ViewerClass"));
		ViewerClass->resize(1051, 716);
		centralWidget = new QWidget(ViewerClass);
		centralWidget->setObjectName(QStringLiteral("centralWidget"));
		ViewerClass->setCentralWidget(centralWidget);
		menuBar = new QMenuBar(ViewerClass);
		menuBar->setObjectName(QStringLiteral("menuBar"));
		menuBar->setGeometry(QRect(0, 0, 1051, 21));
		ViewerClass->setMenuBar(menuBar);
		mainToolBar = new QToolBar(ViewerClass);
		mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
		ViewerClass->addToolBar(Qt::TopToolBarArea, mainToolBar);
		statusBar = new QStatusBar(ViewerClass);
		statusBar->setObjectName(QStringLiteral("statusBar"));
		ViewerClass->setStatusBar(statusBar);

		retranslateUi(ViewerClass);

		QMetaObject::connectSlotsByName(ViewerClass);
	} // setupUi

	void retranslateUi(QMainWindow *ViewerClass)
	{
		ViewerClass->setWindowTitle(QApplication::translate("ViewerClass", "Viewer", nullptr));
	} // retranslateUi

};

namespace Ui {
	class ViewerClass : public Ui_viewerClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_VIEWER_H
