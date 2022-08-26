#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);

    initProfile();
    initUI();

    QList<QString> userName;
    QList<QString> userPassword;
    userName<<"Mary"<<"Mike"<<"Jack"<<"Alice"<<"Rose"<<"Jane"<<"Apple"<<"Orange"<<"Peach"<<"Tree";
    userPassword<<"123"<<"456"<<"456"<<"456"<<"456"<<"456"<<"456"<<"456"<<"456"<<"456";

    loadUserInfo(userName, userPassword);
//    if(userCount != 0)
//    {
//        loadUserInfo();
//    }

    connect(m_creatBtn, &QPushButton::clicked, this, &Widget::addUser);
}

Widget::~Widget()
{
    delete ui;
    deleteButtons();
    if(m_tableWidget!=NULL)
    {
        delete m_tableWidget;
        m_tableWidget=nullptr;
    }
}

void Widget::initProfile()
{
    m_userInfo = new QSettings(m_filePath, QSettings::IniFormat);
    userCount = m_userInfo->allKeys().size()/3; //用户数量 == 组数 == 键数/每组键数
    qDebug()<<__LINE__<<"userCount: "<<userCount;
}

void Widget::initUI()
{
    m_tableWidget = new QTableWidget(this);
    m_creatBtn = new QPushButton(this);
    m_saveBtn = new QPushButton(this);
    m_cancelBtn = new QPushButton(this);
    m_gridLayout = new QGridLayout(this);

    /*设置布局*/
    QSpacerItem *verticalSpacer = new QSpacerItem(20, 60, QSizePolicy::Minimum, QSizePolicy::Fixed);
    m_gridLayout->addWidget(m_tableWidget, 0, 0, 1, 4);
    m_gridLayout->addWidget(m_creatBtn, 1, 1, 2, 2);    //位于第一行第一列，占两行两列是因为点击后出现的两个按钮需要占两列
    m_gridLayout->addWidget(m_saveBtn, 1, 1, 2, 1);
    m_gridLayout->addWidget(m_cancelBtn, 1, 2, 2, 1);
    m_gridLayout->addItem(verticalSpacer, 2, 1, 1, 1);
    m_gridLayout->setMargin(3);

    /*设置TableWidget属性*/
    m_tableWidget->setColumnCount(m_headerStr.size());
    m_tableWidget->setHorizontalHeaderLabels(m_headerStr);
    QFont font = m_tableWidget->horizontalHeader()->font();
    font.setBold(true); //加粗
    font.setPixelSize(16);
    m_tableWidget->horizontalHeader()->setFont(font);

    m_tableWidget->setColumnWidth(0, 200);
    m_tableWidget->setColumnWidth(1, 300);
    m_tableWidget->setColumnWidth(2, 100);
    m_tableWidget->setColumnWidth(3, 120);

    m_tableWidget->setShowGrid(true);
//    m_tableWidget->setGridStyle(Qt::DotLine);   //点线网格
//    m_tableWidget->setSortingEnabled(true);     //排序
    m_tableWidget->horizontalHeader()->setStretchLastSection(true);//最后一行可拉伸
    m_tableWidget->verticalHeader()->setVisible(false);
    m_tableWidget->setStyleSheet("QTableWidget{ background-color: #c0c0c0; alternate-background-color: #606060; selection-background-color:#282828;}");
    m_tableWidget->setAlternatingRowColors(true);
    m_tableWidget->setSelectionMode(QAbstractItemView::SingleSelection);
    m_tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
    m_tableWidget->setTextElideMode(Qt::ElideRight);

    /*设置按钮属性*/
    m_creatBtn->setText("New Account");
    m_creatBtn->setStyleSheet("QPushButton{background: white; color: blacke; border: 2px solid black; border-radius:10px; padding:2px 4px;}");
    m_saveBtn->setText("Save");
    m_saveBtn->setStyleSheet("QPushButton{background: white; color: blacke; border: 2px solid black; border-radius:10px; padding:2px 4px;}");
    m_saveBtn->hide();
    m_cancelBtn->setText("Cancel");
    m_cancelBtn->setStyleSheet("QPushButton{background: white; color: blacke; border: 2px solid black; border-radius:10px; padding:2px 4px;}");
    m_cancelBtn->hide();
    qDebug()<<__LINE__;
}

void Widget::loadUserInfo(QList<QString> userName, QList<QString> userPassword, QList<QString> permission)
{
//    ReadOnlyDelegate *readOnlyDelegate = new ReadOnlyDelegate(this);
    m_tableWidget->clearContents();
    if(userName.size() != userPassword.size())
    {
        return;
    }

    m_tableWidget->setRowCount(userCount);      //设置行数
    qDebug()<<__LINE__<<"userCount:"<<userCount;
    qDebug()<<__LINE__<<"rowCount:"<<m_tableWidget->rowCount();
    for(int i = 0; i < m_tableWidget->rowCount(); i++)
    {
        /*用户名*/
        QTableWidgetItem *nameItem = new QTableWidgetItem(tr("%1").arg(userName.at(i)));
        nameItem->setFlags(nameItem->flags() & (~Qt::ItemIsEditable));//第一列不可编辑
        nameItem->setTextAlignment(Qt::AlignCenter);
        m_tableWidget->setItem(i, 0, nameItem);

        /*密码*/
        QTableWidgetItem *pwdItem = new QTableWidgetItem(tr("%1").arg(userPassword.at(i)));
        pwdItem->setFlags(pwdItem->flags() & (~Qt::ItemIsEditable));//第二列不可编辑
        pwdItem->setTextAlignment(Qt::AlignCenter);
        m_tableWidget->setItem(i, 1, pwdItem);

        /*权限*/
        QTableWidgetItem *permissItem = new QTableWidgetItem(tr("%1").arg(permission.at(i)));
        permissItem->setFlags(permissItem->flags() & (~Qt::ItemIsEditable));//第三列不可编辑
        permissItem->setTextAlignment(Qt::AlignCenter);
        m_tableWidget->setItem(i, 2, permissItem);

        /*添加删除按钮和修改按钮*/
        QPushButton *btnDel = new QPushButton("Delete");
        btnDel->setStyleSheet(QString::fromUtf8("QPushButton{background: white; color: blacke; border: 2px solid black; border-radius:10px; padding:2px 4px;}"));
        QPushButton *btnUpdate = new QPushButton("Modify");
        btnUpdate->setStyleSheet(QString::fromUtf8("QPushButton{background: white; color: blacke; border: 2px solid black; border-radius:10px; padding:2px 4px;}"));

        btnVec.push_back(btnDel);
        btnVec.push_back(btnUpdate);

        QWidget *widget = new QWidget;
        QHBoxLayout *hboxlayout = new QHBoxLayout(widget);
        hboxlayout->setMargin(2);
        hboxlayout->addWidget(btnDel);
        hboxlayout->addWidget(btnUpdate);
        m_tableWidget->setCellWidget(i, 3,  widget);

        connect(btnDel, &QPushButton::clicked, [=](){this->removeUser(nameItem);});
        connect(btnUpdate, &QPushButton::clicked, [=](){this->modifyUserInfo(btnUpdate, nameItem);});
    }
}

void Widget::deleteButtons()
{
    /*释放table_user表格中动态申请的QPushButton*/
    int len = btnVec.length();
    for(int i = 0; i<len; i++)
    {
        QPushButton *btnPtr = btnVec.at(i);
        if(btnPtr != nullptr)
        {
            delete btnPtr;
            btnPtr = nullptr;
        }
    }
}

void Widget::removeUser(QTableWidgetItem *item)
{
    qDebug()<<__LINE__<<"userCount:"<<userCount;
    if(QMessageBox::question(this, "Tip","Are you sure you want to delete?", QMessageBox::Yes|QMessageBox::No)== QMessageBox::Yes)
    {
        userCount--;
        qDebug()<<__LINE__<<"userCount:"<<userCount;
        int row = m_tableWidget->row(item);
        m_tableWidget->removeRow(row);
        deleteUserData("User" + QString::number(userCount), "UserName");
        deleteUserData("User" + QString::number(userCount), "Password");
        deleteUserData("User" + QString::number(userCount), "Premission");
    }
}

void Widget::modifyUserInfo(QPushButton *btn, QTableWidgetItem *item)
{
    int row = m_tableWidget->row(item);
    int column = m_tableWidget->column(item);
    Qt::ItemFlags flag1 = m_tableWidget->item(row, column)->flags();
    Qt::ItemFlags flag2 = m_tableWidget->item(row, column)->flags();

    if(btn->text() == "Modify")
    {
        btn->setText("Save");
        m_tableWidget->item(row, 0)->setFlags(flag1 | (Qt::ItemIsEditable));   //密码->可编辑
        m_tableWidget->item(row, 1)->setFlags(flag2 | (Qt::ItemIsEditable));   //用户名->可编辑
        /*权限不可编辑*/
    }
    else
    {
        btn->setText("Modify");
        m_tableWidget->item(row, 0)->setFlags(flag1 & (~Qt::ItemIsEditable));   //密码->不可编辑
        m_tableWidget->item(row, 1)->setFlags(flag2 & (~Qt::ItemIsEditable));   //用户名->不可编辑
        /*权限不可编辑*/
    }
}

void Widget::addUser()
{
    qDebug()<<__LINE__<<"CreatBtn is clicked";
    m_tableWidget->setRowCount(m_tableWidget->rowCount()+1);

    qDebug()<<__LINE__<<"Row count: "<<m_tableWidget->rowCount()<< userCount;

    /*用户名*/
    QTableWidgetItem *nameItem = new QTableWidgetItem(tr("%1").arg("username"));
    nameItem->setTextAlignment(Qt::AlignCenter);
    m_tableWidget->setItem(m_tableWidget->rowCount()-1, 0, nameItem);

    /*密码*/
    QTableWidgetItem *pwdItem = new QTableWidgetItem(tr("%1").arg("password"));
    pwdItem->setTextAlignment(Qt::AlignCenter);
    m_tableWidget->setItem(m_tableWidget->rowCount()-1, 1, pwdItem);

    /*权限*/
    QTableWidgetItem *permissItem = new QTableWidgetItem(tr("%1").arg("1"));
    permissItem->setFlags(permissItem->flags() & (~Qt::ItemIsEditable));//第三列不可编辑
    permissItem->setTextAlignment(Qt::AlignCenter);
    m_tableWidget->setItem(m_tableWidget->rowCount()-1, 2, permissItem);

    /*添加删除按钮和修改按钮*/
    QPushButton *btnDel = new QPushButton("Delete");
    btnDel->setEnabled(false);
    btnDel->setStyleSheet(QString::fromUtf8("QPushButton{background: white; color: blacke; border: 2px solid black; border-radius:10px; padding:2px 4px;}"));
    QPushButton *btnUpdate = new QPushButton("Modify");
    btnUpdate->setEnabled(false);
    btnUpdate->setStyleSheet(QString::fromUtf8("QPushButton{background: white; color: blacke; border: 2px solid black; border-radius:10px; padding:2px 4px;}"));
    QWidget *widget = new QWidget;
    QHBoxLayout *hboxlayout = new QHBoxLayout(widget);
    hboxlayout->setMargin(2);
    hboxlayout->addWidget(btnDel);
    hboxlayout->addWidget(btnUpdate);
    m_tableWidget->setCellWidget(m_tableWidget->rowCount()-1, 3,  widget);

    /*隐藏creatBtn*/
    m_creatBtn->hide();

    m_gridLayout->removeWidget(m_creatBtn);     //这里不写remove的实现效果和写的一样，未找到原因

    m_saveBtn->show();
    m_cancelBtn->show();

    /*save按钮按下后添加行，写入配置文件*/
    connect(m_saveBtn, &QPushButton::clicked, this, [=]()
    {
        m_saveBtn->hide();
        m_gridLayout->removeWidget(m_saveBtn);      //这里不写remove的实现效果和写的一样，未找到原因
        m_cancelBtn->hide();
        m_gridLayout->removeWidget(m_cancelBtn);    //这里不写remove的实现效果和写的一样，未找到原因

        m_gridLayout->addWidget(m_creatBtn, 1, 1, 2, 2);

        btnDel->setEnabled(true);
        btnUpdate->setEnabled(true);

        nameItem->setFlags(nameItem->flags() & (~Qt::ItemIsEditable));  //第一列不可编辑
        pwdItem->setFlags(pwdItem->flags() & (~Qt::ItemIsEditable));    //第二列不可编辑

        connect(btnDel, &QPushButton::clicked, this, [=](){this->removeUser(nameItem);});
        connect(btnUpdate, &QPushButton::clicked, this, [=](){this->modifyUserInfo(btnUpdate, nameItem);});

        m_creatBtn->show();

        qDebug()<<__LINE__<<nameItem->text()<<pwdItem->text();

        /*写入用户数据*/
        writeUserData("User" + QString::number(userCount), "UserName", nameItem->text());
        writeUserData("User" + QString::number(userCount), "Password", pwdItem->text());
        writeUserData("User" + QString::number(userCount), "Premission", permissItem->text());
        userCount += 1;
    });

    connect(m_cancelBtn, &QPushButton::clicked, this, [=]()
    {
        m_saveBtn->hide();
        m_gridLayout->removeWidget(m_saveBtn);      //这里不写remove的实现效果和写的一样，未找到原因
        m_cancelBtn->hide();
        m_gridLayout->removeWidget(m_cancelBtn);    //这里不写remove的实现效果和写的一样，未找到原因
        m_gridLayout->addWidget(m_creatBtn, 1, 1, 2, 2);
        m_creatBtn->show();
        m_tableWidget->removeRow(m_tableWidget->rowCount()-1);  //删除未添加信息的行
    });
}

void Widget::writeUserData(QString group, QString keyName, QString valueName)
{
    m_userInfo->setValue(group + "/" + keyName, valueName);
}

void Widget::deleteUserData(QString group, QString keyName)
{
    qDebug()<<__LINE__<<userCount;
    qDebug()<<group + "/" + keyName;
    m_userInfo->remove(group + "/" + keyName);
}

void Widget::readUserData()
{

}

QWidget *ReadOnlyDelegate::createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const //final
{
    Q_UNUSED(parent)
    Q_UNUSED(option)
    Q_UNUSED(index)
    return NULL;
}
