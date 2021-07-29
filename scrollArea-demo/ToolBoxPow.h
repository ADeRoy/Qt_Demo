#ifndef TOOLBOXPOW_H
#define TOOLBOXPOW_H

#include <QHBoxLayout>
#include <QObject>
#include <QWidget>
#include <QScrollArea>
#include <QPushButton>
#include <QMap>
#include <QListWidget>
class BoxGroup:public QObject
{
    Q_OBJECT
public:
    BoxGroup(QWidget *parent = nullptr);
private slots:
    void on_pushbutton_checked();
public:
    void setGroupName(QString str){
        m_button->setText(str);
    }
    void addWidget(QWidget* widget);
    int getHeight(){ return m_widgetHeight; }
public:
    QPushButton* getButton(){return m_button;}
    QWidget* getWidget(){return m_listWidget;}
private:
    QPushButton* m_button;
    QListWidget* m_listWidget;
    int m_widgetHeight;
};

class ToolBoxPow : public QWidget
{
    Q_OBJECT
public:
    ToolBoxPow(QWidget *parent = nullptr);
public:
    void AddGroup(QString groupName);
    void AddQQWidget(QString groupName,QString name,QString path);
    void AddWidget(QString groupName,QWidget* widget);
public:
    QVBoxLayout* getLayout(){return verticalLayout;}
private:
    QGridLayout*mainGridLayout;
    QScrollArea* scrollArea;
    QVBoxLayout *verticalLayout;
    QGridLayout *gridLayout;
    QWidget *m_fillWidget;
    int m_height;
    QWidget* scrollAreaWidgetContents;
    QMap<QString, BoxGroup*> buttonMap;
};


#endif // TOOLBOXPOW_H
