#include "ToolBoxPow.h"
#include "qDebug"
#include <QScrollBar>

#include <QLabel>

#define BUTTON_DOWN "QPushButton{"\
"background-image: url(:/arrow_down_normal.png);"\
"background-repeat: repeat-no-repeat;"\
"background-position: left;"\
"background-origin:content;"\
"padding-right: 10px;"\
"}"

#define BUTTON_RIGHT "QPushButton{"\
    "background-image: url(:/arrow_right_normal.png);"\
    "background-repeat: repeat-no-repeat;"\
    "background-position: left;"\
    "background-origin:content;"\
    "padding-right: 10px;"\
    "}"

ToolBoxPow::ToolBoxPow(QWidget *parent)
    :QWidget(parent)
{
    m_height = 0;
    m_fillWidget = new QWidget;

    scrollArea = new QScrollArea(this);
    scrollArea->setWidgetResizable(true);   //设置滚动
    //幕布
    scrollAreaWidgetContents = new QWidget;
    //格子布局管理器   他的父亲是幕布
    gridLayout = new QGridLayout(scrollAreaWidgetContents);
    gridLayout->setSpacing(0);
    gridLayout->setContentsMargins(0, 0, 0, 0);
    //垂直布局管理器
    verticalLayout = new QVBoxLayout();
    verticalLayout->setMargin(0); //设置外边距
    verticalLayout->setSpacing(0);//设置内边距
    verticalLayout->setObjectName(QStringLiteral("verticalLayout"));

    //将垂直布局管理器添加给格子布局管理器
    gridLayout->addLayout(verticalLayout, 0, 0, 1, 1);
    //给滚动区域添加 widget
    scrollArea->setWidget(scrollAreaWidgetContents);      //设置幕布

    //    //竖滚动条和横滚动条都可以一直显示
    //    scrollArea->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
    //    scrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOn);

    //设置滑动条的样式
    scrollArea->setStyleSheet("QScrollArea{border:0px solid;"
                            "border-radius: 2px;}"
                            "QScrollBar:vertical{width: 4px;border:0px solid;"
                            "border-radius: 2px;margin: 0px,0px,0px,0px;"
                            "background-color: transparent;background:#e1f0fa;}"
                            "QScrollBar:vertical:hover{width: 4px;"
                            "border:0px solid;margin: 0px,0px,0px,0px;background:#e1f0fa;}"
                            "QScrollBar::handle:vertical{width:4px;background:#c0ddee;"
                            "border-radius: 2px;height: 40px;}"
                            "QScrollBar::handle:vertical:hover{background:#c0ddee;"
                            "border-radius: 2px;}"
                            "QScrollBar::add-line:vertical{height:11px;background-color: transparent;"
                            "subcontrol-position:bottom;border:0px solid;"
                            "border-radius: 2px;}"
                            "QScrollBar::sub-line:vertical{height:11px;"
                            "background-color: transparent;subcontrol-position:top;"
                            "border:0px solid;border-radius: 2px;}"
                            "QScrollBar::add-page:vertical{background-color: #e1f0fa;"
                            "border:0px solid;border-radius: 2px;}"
                            "QScrollBar::sub-page:vertical{background-color: #e1f0fa;"
                            "border:0px solid;border-radius: 2px;}"
                            "QScrollBar::up-arrow:vertical{"
                            "border:0px solid;border-radius: 3px;}"
                            "QScrollBar::down-arrow:vertical {"
                            "border:0px solid;border-radius: 3px;}");
    mainGridLayout = new QGridLayout(this);
    mainGridLayout->setMargin(0); //设置外边距
    mainGridLayout->setSpacing(0);//设置内边距
    mainGridLayout->addWidget(scrollArea);
}
/**
 * @brief ToolBoxPow::AddGroup  添加分组    每个分组由一个PushButton和QListWidget组成
 * @param groupName             分组名为唯一标识变量
 */
void ToolBoxPow::AddGroup(QString groupName)
{
    BoxGroup* newGroup = new BoxGroup(scrollAreaWidgetContents);
    newGroup->setGroupName(groupName);

    verticalLayout->addWidget(newGroup->getButton(), buttonMap.count());
    verticalLayout->addWidget(newGroup->getWidget(), buttonMap.count() + 1);
    verticalLayout->addWidget(m_fillWidget,buttonMap.count() + 2);

    buttonMap.insert(groupName,newGroup);
}

/**
 * @brief ToolBoxPow::AddWidget 给分组添加成员
 * @param groupName 组名
 * @param name      成员名
 * @param path      头像路径
 */
void ToolBoxPow::AddQQWidget(QString groupName, QString name, QString path)
{
    QWidget *widget=new QWidget(scrollAreaWidgetContents);
    QLabel *touLabel = new QLabel(widget);
    QLabel *namelabel=new QLabel(widget);

    //设置不同控件的样式
    widget->setStyleSheet(" background: transparent");
    namelabel->setFixedSize(180,60);
    namelabel->move(80,10);
    namelabel->setText(name);
    namelabel->setAlignment(Qt::AlignLeft);
    namelabel->setAlignment(Qt::AlignVCenter);
    QFont font("微软雅黑",11,50);
    namelabel->setFont(font);
    namelabel->setStyleSheet("color: rgb(70,70,70)");
    touLabel->setFixedSize(50,50);
    touLabel->move(15,15);
    QPixmap pixmap=QPixmap(path);
    QPixmap fitpixmap = pixmap.scaled(50, 50, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
    touLabel->setPixmap(fitpixmap);
    touLabel->setScaledContents(true);  //设置图片缩放
    QMap<QString, BoxGroup *>::iterator ite = buttonMap.find(groupName);
    if(ite!=buttonMap.end())
    {
        BoxGroup* boxGroup = *ite;
        boxGroup->addWidget(widget);
    }
}

void ToolBoxPow::AddWidget(QString groupName, QWidget *widget)
{
    QMap<QString, BoxGroup *>::iterator ite = buttonMap.find(groupName);
    if(ite!=buttonMap.end())
    {
        BoxGroup* boxGroup = *ite;
        boxGroup->addWidget(widget);
    }
}

BoxGroup::BoxGroup(QWidget *parent)
{
    m_button = new QPushButton(parent);
    m_listWidget = new QListWidget(parent);
    m_widgetHeight = 0;
    m_button->setStyleSheet(BUTTON_RIGHT);   //设置样式表
    m_button->setMinimumHeight(23);

    m_listWidget->setFrameShape(QListWidget::NoFrame);  //这个接口可以使滚动条失效
    //先影藏Widget，因为没有成员
    m_listWidget->hide();
    m_listWidget->setFixedHeight(m_widgetHeight);          //设置 Widget 高度
    connect(m_button,SIGNAL(clicked()),this,SLOT(on_pushbutton_checked()));
}

void BoxGroup::on_pushbutton_checked()
{
    if(m_listWidget->isVisible())
    {
        m_listWidget->setVisible(false);    //or hide() 影藏Widget
        m_button->setStyleSheet(BUTTON_RIGHT);
    }
    else
    {
        m_listWidget->setVisible(true);
        m_button->setStyleSheet(BUTTON_DOWN);
    }
}

void BoxGroup::addWidget(QWidget *widget)
{
    QListWidgetItem *item=new QListWidgetItem;
    QSize size = item->sizeHint();              //获取item大小
    item->setSizeHint(QSize(size.width(), 80)); //设置固定高度
    m_listWidget->addItem(item);                //listWidget添加Item
    m_listWidget->setItemWidget(item, widget);  //给Item添加Widget
    size = item->sizeHint();              //获取item大小
    m_widgetHeight += size.height();
    m_listWidget->setFixedHeight(m_widgetHeight);          //设置 Widget 高度
}
