/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.12.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCalendarWidget>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actiona_chinese;
    QAction *actionb_English;
    QWidget *centralWidget;
    QCalendarWidget *calendarWidget;
    QLabel *label;
    QMenuBar *menuBar;
    QMenu *menua;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(407, 318);
        actiona_chinese = new QAction(MainWindow);
        actiona_chinese->setObjectName(QString::fromUtf8("actiona_chinese"));
        actionb_English = new QAction(MainWindow);
        actionb_English->setObjectName(QString::fromUtf8("actionb_English"));
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        calendarWidget = new QCalendarWidget(centralWidget);
        calendarWidget->setObjectName(QString::fromUtf8("calendarWidget"));
        calendarWidget->setGeometry(QRect(70, 10, 248, 197));
        label = new QLabel(centralWidget);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(30, 210, 331, 41));
        QFont font;
        font.setFamily(QString::fromUtf8("\345\215\216\346\226\207\346\226\260\351\255\217"));
        font.setPointSize(15);
        label->setFont(font);
        label->setLineWidth(1);
        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 407, 23));
        menua = new QMenu(menuBar);
        menua->setObjectName(QString::fromUtf8("menua"));
        MainWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        MainWindow->setStatusBar(statusBar);

        menuBar->addAction(menua->menuAction());
        menua->addAction(actiona_chinese);
        menua->addAction(actionb_English);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "\347\254\254\344\270\200\344\270\252qt\347\250\213\345\272\217", nullptr));
        actiona_chinese->setText(QApplication::translate("MainWindow", "\344\270\255\346\226\207", nullptr));
        actionb_English->setText(QApplication::translate("MainWindow", "English", nullptr));
        label->setText(QApplication::translate("MainWindow", "\346\254\242\350\277\216\345\205\263\346\263\250\345\276\256\344\277\241\345\205\254\344\274\227\345\217\267\343\200\220\347\274\226\347\250\213\345\255\246\344\271\240\345\237\272\345\234\260\343\200\221", nullptr));
        menua->setTitle(QApplication::translate("MainWindow", "\350\257\255\350\250\200", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
