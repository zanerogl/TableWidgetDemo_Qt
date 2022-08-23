#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);

    initTableWidget();
    QList<QString> userName;
    QList<QString> userPassword;
    userName<<"Mary"<<"Mike"<<"Jack"<<"Alice"<<"Rose"<<"Jane"<<"Apple"<<"Orange"<<"Peach"<<"Tree";
    userPassword<<"123"<<"456"<<"456"<<"456"<<"456"<<"456"<<"456"<<"456"<<"456"<<"456";
    loadUserInfo(userName, userPassword);
}

Widget::~Widget()
{
    delete ui;
}

void Widget::initTableWidget()
{
    m_tableWidget = new QTableWidget(this);
    m_creatBtn = new QPushButton(this);
    m_gridLayout = new QGridLayout(this);

    m_creatBtn->setText("New Account");

    m_gridLayout->addWidget(m_tableWidget, 0, 0, 1, 1);
    m_gridLayout->addWidget(m_creatBtn, 1, 0, 1, 1);

    m_gridLayout->setMargin(5);

    m_tableWidget->setColumnCount(m_headerStr.size());
    m_tableWidget->setHorizontalHeaderLabels(m_headerStr);

    QFont font = m_tableWidget->horizontalHeader()->font();
    font.setBold(true); //加粗
    font.setPixelSize(16);
    m_tableWidget->horizontalHeader()->setFont(font);

    for(int i = 0; i < m_tableWidget->columnCount(); i++)
    {
        m_tableWidget->setColumnWidth(i,230);
    }

    m_tableWidget->horizontalHeader()->setStretchLastSection(true);//最后一行可拉伸
    m_tableWidget->verticalHeader()->setVisible(false);
}

void Widget::loadUserInfo(QList<QString> userName, QList<QString> userPassword)
{
    m_tableWidget->clearContents();

    if(userName.size() != userPassword.size())
    {
        return;
    }

    m_tableWidget->setRowCount(userName.size()+1);

    for(int i = 0; i < userName.size(); i++)
    {
        /*设置用户名*/
        QTableWidgetItem *nameItem = new QTableWidgetItem(tr("%1").arg(userName.at(i)));
        nameItem->setFlags(nameItem->flags() & (~Qt::ItemIsEditable));//第一列不可编辑
//        nameItem->setFont(nullFont);
        nameItem->setTextAlignment(Qt::AlignCenter);
        m_tableWidget->setItem(i, 0, nameItem);

        /*设置密码*/
        QTableWidgetItem *pwdItem = new QTableWidgetItem(tr("%1").arg(userPassword.at(i)));
        pwdItem->setTextAlignment(Qt::AlignCenter);
//        pwdItem->setFont(nullFont);
        m_tableWidget->setItem(i, 1, pwdItem);

        /*添加删除按钮*/
        QPushButton *btnDel = new QPushButton("Delete");
        QPushButton *btnUpdate = new QPushButton("Modify");
        QWidget *widget = new QWidget;
        QHBoxLayout *hboxlayout = new QHBoxLayout(widget);
        hboxlayout->setMargin(2);
        hboxlayout->addWidget(btnDel);
        hboxlayout->addWidget(btnUpdate);
        m_tableWidget->setCellWidget(i, 2, widget);
    }
}

