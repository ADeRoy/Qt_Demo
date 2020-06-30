#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    m_Translator = new QTranslator(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actiona_chinese_triggered()
{
    m_Translator->load("Translate_CN.qm");
    ui->calendarWidget->setLocale(QLocale::Chinese);
    qApp->installTranslator(m_Translator);
    ui->retranslateUi(this);
}

void MainWindow::on_actionb_English_triggered()
{
    m_Translator->load("Translate_EN.qm");
    qApp->installTranslator(m_Translator);

    ui->calendarWidget->setLocale(QLocale::C);

    ui->retranslateUi(this);
}
