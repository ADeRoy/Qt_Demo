#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QDesktopServices>
#include <QUrl>
#include <QDebug>
#include <QFileDialog>
#include <QMessageBox>

#include <QtPrintSupport/QPrintDialog>
#include <QtPrintSupport/QPrinter>

#include <QPrintDialog>
#include <QPrintPreviewDialog>
#include <QPrinter>
#include <QFontMetrics>
#include <QFontDialog>


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    Init();
    on_newActiona_triggered();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::Init()
{
    this->Tab = new QTabWidget(this);
    this->setCentralWidget(Tab);
    this->Tab->setMovable(true);        //设置页面是否可被拖拽移动.
    this->Tab->setTabsClosable(true);   //设置页面是否可以关闭
    /*设置一秒定时器*/
    this->timer = new QTimer(this);
    timer->start(1000);


    connect(this->Tab, SIGNAL(tabCloseRequested(int)), this, SLOT(Del_Tab(int)));//关联删除信号才可以删除tab
    connect(this->Tab, SIGNAL(currentChanged(int)), this, SLOT(tabChange(int)));//关联TabWidget改变信号
    connect(ui->openAction,SIGNAL(triggered()),this,SLOT(on_actiona_open_triggered()));       /*打开文件 工具栏里面的打开 多加的*/
    connect(ui->saveAction,SIGNAL(triggered()),this,SLOT(on_actiona_saveFile_triggered()));   /*保存文件*/
    connect(ui->actiona_exit, SIGNAL(triggered()), this, SLOT(close()));                      /*退出程序*/
    connect(this->timer, SIGNAL(timeout()), this, SLOT(flushTime()));                         /*刷新时间*/

    this->filename = "new";
    this->ID = 0;

    //状态栏状态信息初始化
    this->stbar = this->statusBar();
    this->lb_fileinfo = new QLabel();
    this->lb_time = new QLabel();
    this->lab_tmp = new QLabel("                          ");
    this->lab_tmp1 = new QLabel("                          ");
    //添加状态栏信息
    stbar->addWidget(lb_fileinfo);
    stbar->addWidget(lab_tmp);
    stbar->addWidget(lab_tmp1);
    stbar->addWidget(lb_time);
}

/*  转CSDN   */
void MainWindow::on_actiona_CSDN_triggered()
{
    QDesktopServices::openUrl(QUrl(QLatin1String("https://blog.csdn.net/qq_44519484")));
}

/*    新建文件    */
void MainWindow::on_newActiona_triggered()
{
    QFont font;
    font.setFamily("Consolas");
    font.setFixedPitch(true);
    font.setPointSize(12);

    QTextEdit *newEdit = new QTextEdit();
    /*设置撤销和返回*/
    connect(newEdit->document(), &QTextDocument::undoAvailable,
            ui->undoAction, &QAction::setEnabled);
    connect(newEdit->document(), &QTextDocument::redoAvailable,
            ui->actionRedo, &QAction::setEnabled);
    connect(newEdit,SIGNAL(cursorPositionChanged()),this,SLOT(cursorChanged()));
    ui->undoAction->setEnabled(newEdit->document()->isUndoAvailable());
    ui->actionRedo->setEnabled(newEdit->document()->isUndoAvailable());
    /*设置字体*/
    newEdit->setFont(font);
    QFontMetrics metrics(newEdit->font());
    newEdit->setTabStopWidth(4 * metrics.width(' '));   //设置tab键为4个空格
    Highlighter*newLight = new Highlighter(newEdit->document());    //设置语法高亮
    EditList.append(newEdit);               //将newEdit添加进List里面，方便管理
    highlighterList.append(newLight);       //将newLight添加进List里面，方便管理
    this->Tab->addTab(newEdit, filename);   //新建空白文件
    this->Tab->setCurrentIndex(ID);         //设置当前Tab

    this->ID++;     //id加一
    this->lb_fileinfo->setText(filename);
    qDebug()<<"ID:"<<ID;
    qDebug()<<"SIZE:"<<EditList.size();
}

/*    打开文件    */
void MainWindow::on_actiona_open_triggered()
{
    qDebug()<<"打开文件";
    QString openName;
    openName = QFileDialog::getOpenFileName(this, "打开文件", "");
    if(openName.isEmpty()){
        qDebug()<<"文件打开失败";
        return;
    }
    qDebug()<<"打开文件成功";

    QFile file(openName);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)){
        qDebug()<<file.errorString();
        return;
    }

    //获取文件名
    QFileInfo fileinfo(openName);
    filename = fileinfo.fileName();
    this->lb_fileinfo->setText(filename);
    this->on_newActiona_triggered();    //新建空白TextEdit窗口
    this->Tab->setCurrentIndex(ID - 1);

    //读取    解决打开文件中文乱码  没有完全解决
    while (!file.atEnd()) {
        QByteArray line = file.readLine();
        QString str = QString(line);                  //QString(line)  QByteArray转化为QString
        this->EditList.at(ID - 1)->append(str);
    }
    file.close();
    qDebug()<<"读取文件成功";
    filename = "new";
}

/*    删除tab     */
void MainWindow::Del_Tab(int index)
{
    this->Tab->removeTab(index);
    //从列表中删除
    this->EditList.removeAt(index);
    this->highlighterList.removeAt(index);
    ID--;
    qDebug()<<"ID:"<<ID;
    qDebug()<<"SIZE:"<<EditList.size();
}

/*    Tab改变     */
void MainWindow::tabChange(int index)
{
    qDebug()<<Tab->currentIndex()<<"index:"<<index;
    this->lb_fileinfo->setText(this->Tab->tabText(index));
}

/*    保存文件     */
void MainWindow::on_actiona_saveFile_triggered()
{
    QString saveFileName = QFileDialog::getSaveFileName(this, "保存",QString("%1.txt").arg(ID));
    if(saveFileName.isEmpty()){
        qDebug()<<"文件保存失败";
        return;
    }
    //获取文件名
    QFileInfo fileinfo;
    fileinfo = QFileInfo(saveFileName);
    this->lb_fileinfo->setText(fileinfo.fileName());
    //更改文件名
    this->Tab->setTabText(Tab->currentIndex(),fileinfo.fileName());

    //进行写操作
    QString txt = this->EditList.at(this->Tab->currentIndex())->toPlainText();
    QFile file(saveFileName);
    file.open(QIODevice::WriteOnly|QIODevice::Text);
    file.write(txt.toUtf8());
    file.close();
    qDebug()<<"文件保存成功";
}

/*    另存为      */
void MainWindow::on_actiona_save_triggered()
{
    QString saveFileName = QFileDialog::getSaveFileName(this, "保存", "./");
    if(saveFileName.isEmpty()){
        qDebug()<<"文件保存失败";
        return;
    }
    //获取文件名
    QFileInfo fileinfo;
    fileinfo = QFileInfo(saveFileName);
    this->lb_fileinfo->setText(fileinfo.fileName());
    //更改文件名
    this->Tab->setTabText(Tab->currentIndex(),fileinfo.fileName());

    //进行写操作
    QString txt = this->EditList.at(this->Tab->currentIndex())->toPlainText();
    QFile file(saveFileName);
    file.open(QIODevice::WriteOnly|QIODevice::Text);
    file.write(txt.toUtf8());
    file.close();
    qDebug()<<"文件保存成功";
}

/*    刷新时间    */
void MainWindow::flushTime()
{
    this->currentTime = QDateTime::currentDateTime();
    QString str = this->currentTime.toString("yyyy-MM-dd hh:mm:ss ddd");    //设置显示格式
    this->lb_time->setText("                 当前时间: "+str);//在标签上显示时间
}

/*    打开新窗口    */
void MainWindow::on_actiona_new_triggered()
{
    MainWindow* newWindow = new MainWindow;
    newWindow->show();
}

/*    打印    */
void MainWindow::on_actiona_Painter_triggered()
{
    //创建打印机对象
    QPrinter printer (QPrinter::HighResolution);
    //打印机构造一个新的模态打印机对话框。
    QPrintDialog *dlg=new QPrintDialog(&printer,this);
    //如果选中文档 activeWindow为QTextEdit 声明的对象
    if(this->EditList.at(this->Tab->currentIndex())->textCursor().hasSelection())
    {
        dlg->addEnabledOption(QAbstractPrintDialog::PrintSelection);
    }
    dlg->setWindowTitle(tr("打印文档"));
    if(dlg->exec()==QDialog::Accepted)
    {
        //便于将文本编辑文档打印到给定打印机的功能。这相当于直接在文档上调用print方法
        this->EditList.at(this->Tab->currentIndex())->print(&printer);
    }
    delete dlg;
}

/*    打印预览    */
void MainWindow::on_action_PrintPreview_triggered()
{
    QPrinter printer(QPrinter::HighResolution);
    QPrintPreviewDialog preview(&printer, this);
    connect(&preview, SIGNAL(paintRequested(QPrinter*)), this,SLOT(printPreview(QPrinter*)));
    preview.exec();
}

/*    预览槽函数    */
void MainWindow::printPreview(QPrinter *printer)
{
    this->EditList.at(this->Tab->currentIndex())->print(printer);
}

/*    自动换行    */
void MainWindow::on_actiona_auto_triggered()
{
    //QTextEdit默认自动换行
    if(ui->actiona_auto->isChecked()){
        qDebug()<<"checked";
        for(int i=0;i<EditList.size();i++)
        {
            EditList.at(i)->setWordWrapMode(QTextOption::WrapAnywhere);
        }
    }
    else {
        for(int i=0;i<EditList.size();i++)
        {
            EditList.at(i)->setWordWrapMode(QTextOption::NoWrap);
        }
    }
}

/*    另存为pdf    */
void MainWindow::on_action_pdf_triggered()
{
    QString saveFileName = QFileDialog::getSaveFileName(this, "另存为PDF",QString("%1.pdf").arg(ID));
    if(saveFileName.isEmpty()){
        qDebug()<<"文件保存失败";
        return;
    }

    QPrinter printer(QPrinter::HighResolution);
    printer.setOutputFormat(QPrinter::PdfFormat);
    printer.setOutputFileName(saveFileName);
    this->EditList.at(this->Tab->currentIndex())->document()->print(&printer);

}

void MainWindow::on_actiona_font_triggered()
{
    bool ok;
    QFont font = QFontDialog::getFont(&ok, QFont("Consolas", 12), this);
    if (ok) {
        for(int i=0;i<EditList.size();i++)
        {
            EditList.at(i)->setFont(font);
        }
        qDebug()<<"成功设置颜色";
    } else {
        qDebug()<<"颜色设置失败";
    }
}

void MainWindow::on_undoAction_triggered()
{
    EditList.at(Tab->currentIndex())->undo();   //撤销
}

void MainWindow::on_actionRedo_triggered()
{
    EditList.at(Tab->currentIndex())->redo();   //返回
}

void MainWindow::on_actiona_copy_triggered()
{
    EditList.at(Tab->currentIndex())->copy();   //复制
}

void MainWindow::on_actiona_paste_triggered()
{
    EditList.at(Tab->currentIndex())->paste();  //粘贴
}

void MainWindow::on_actiona_cat_triggered()
{
    EditList.at(Tab->currentIndex())->cut();    //剪贴
}

void MainWindow::on_actiona_all_triggered()
{
    EditList.at(Tab->currentIndex())->selectAll();  //全选
}

void MainWindow::on_actiona_about_triggered()
{
    QMessageBox::about(this, tr("关于"), tr("这是一个基于 Qt5 实现的NotePad软件\r\n具备类似 记事本 NotePad++ 的功能。"));
}

void MainWindow::cursorChanged()
{
//    currentCursor = EditList.at(Tab->currentIndex())->textCursor();
//    QString selextStr = EditList.at(Tab->currentIndex())->textCursor().selectedText();
//    if (selextStr.isEmpty()) {
//        if(isundo)
//        {
//            isundo = false;
//            //EditList.at(Tab->currentIndex())->undo();
//        }
//    }
//    else {
//        if(isundo)
//        {
//            isundo = false;
//            EditList.at(Tab->currentIndex())->undo();
//        }
//        findText(selextStr);
//        isundo = true;
//    }
//    EditList.at(Tab->currentIndex())->setTextCursor(currentCursor);
}

void MainWindow::findText(QString selextStr)
{
    QTextDocument *document = EditList.at(Tab->currentIndex())->document(); //QTextDocument富文本文档

/*
    * QTextCursor是专门用来协助处理和获取QTextDocument内容的一组api.
    * 它包含的信息既有QTextDocument内的光标位置（position()），
    * 以及所做的selection（anchor() 和 position()之间）。
    * current character是指position之前的那个character.
    * current block是指包含position()位置的block.
*/
    QTextCursor highlightCursor(document);  //编辑QTextDocument对象
    QTextCursor cursor(document);           //编辑QTextDocument对象

    cursor.beginEditBlock();


    QTextCharFormat plainFormat(highlightCursor.charFormat());  //取得format信息
    QTextCharFormat colorFormat = plainFormat;          //设置信息

    //colorFormat.setForeground(Qt::green);
    colorFormat.setBackground(Qt::green);   //设置背景为绿色

    while (!highlightCursor.isNull() && !highlightCursor.atEnd()) {
        highlightCursor = document->find(selextStr, highlightCursor,
                                         QTextDocument::FindWholeWords);

        if (!highlightCursor.isNull()) {

            highlightCursor.movePosition(QTextCursor::WordRight,
                                         QTextCursor::KeepAnchor);
            highlightCursor.mergeCharFormat(colorFormat);
        }
    }

    cursor.endEditBlock();

}

void MainWindow::on_actiona_data_triggered()
{
    EditList.at(Tab->currentIndex())->append("时间:" + this->currentTime.toString("yyyy-MM-dd hh:mm:ss ddd"));
}
