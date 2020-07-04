#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QDateTime>
#include <QLabel>
#include <QMainWindow>
#include <QPrinter>
#include <QTextEdit>
#include <QTimer>
#include "highlighter.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void Init();
private slots:
    void Del_Tab(int);
    void flushTime();
    void printPreview(QPrinter *);
    void tabChange(int);
    void cursorChanged();
    void findText(QString);
private slots:
    void on_actiona_CSDN_triggered();   //转CSDN

    void on_newActiona_triggered();     //新建文件

    void on_actiona_open_triggered();   //打开文件

    void on_actiona_saveFile_triggered();//保存文件

    void on_actiona_save_triggered();   //另存为

    void on_actiona_new_triggered();

    void on_actiona_Painter_triggered();

    void on_action_PrintPreview_triggered();

    void on_actiona_auto_triggered();

    void on_action_pdf_triggered();

    void on_actiona_font_triggered();

    void on_undoAction_triggered();

    void on_actionRedo_triggered();

    void on_actiona_copy_triggered();

    void on_actiona_paste_triggered();

    void on_actiona_cat_triggered();

    void on_actiona_all_triggered();

    void on_actiona_about_triggered();

    void on_actiona_data_triggered();

private:
    Ui::MainWindow *ui;

//    QTextCursor currentCursor;  //当前光标位置

    QStatusBar *stbar;
    QLabel *lb_fileinfo;
    QLabel *lb_time;
    QLabel *lab_tmp;
    QLabel *lab_tmp1;

    QTabWidget *Tab;
    QString filename;
    QList<QTextEdit*> EditList;     /*  定义QList容器 */
    QList<Highlighter*> highlighterList;
    int ID;                         /*  textedit ID */

    //状态栏显示时间
    QDateTime currentTime;
    QTimer *timer;
};

#endif // MAINWINDOW_H
