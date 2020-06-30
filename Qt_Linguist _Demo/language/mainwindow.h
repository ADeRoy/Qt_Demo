#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTranslator>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_actiona_chinese_triggered();

    void on_actionb_English_triggered();

private:
    Ui::MainWindow *ui;
    QTranslator *m_Translator;
};

#endif // MAINWINDOW_H
