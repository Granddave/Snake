/********************************************************************************
** Form generated from reading UI file 'snake.ui'
**
** Created by: Qt User Interface Compiler version 5.5.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SNAKE_H
#define UI_SNAKE_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_SnakeClass
{
public:
    QWidget *centralWidget;
    QMenuBar *menuBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *SnakeClass)
    {
        if (SnakeClass->objectName().isEmpty())
            SnakeClass->setObjectName(QStringLiteral("SnakeClass"));
        SnakeClass->resize(600, 400);
        centralWidget = new QWidget(SnakeClass);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        SnakeClass->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(SnakeClass);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 600, 21));
        SnakeClass->setMenuBar(menuBar);
        statusBar = new QStatusBar(SnakeClass);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        SnakeClass->setStatusBar(statusBar);

        retranslateUi(SnakeClass);

        QMetaObject::connectSlotsByName(SnakeClass);
    } // setupUi

    void retranslateUi(QMainWindow *SnakeClass)
    {
        SnakeClass->setWindowTitle(QApplication::translate("SnakeClass", "Snake", 0));
    } // retranslateUi

};

namespace Ui {
    class SnakeClass: public Ui_SnakeClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SNAKE_H
