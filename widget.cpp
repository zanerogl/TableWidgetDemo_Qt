#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);

    resetGroupOrder();
    initProfile();
    initUI();

    readUserData();

//    QList<QString> userName;
//    QList<QString> userPassword;
//    QList<QString> premission;
//    userName<<"Mary"<<"Mike"<<"Jack"<<"Alice"<<"Rose"<<"Jane"<<"Apple"<<"Orange"<<"Peach"<<"Tree";
//    userPassword<<"123"<<"456"<<"456"<<"456"<<"456"<<"456"<<"456"<<"456"<<"456"<<"456";
//    premission<<"1"<<"1"<<"1"<<"1"<<"1"<<"1"<<"1"<<"1"<<"1"<<"1";
//    loadUserInfo(userName, userPassword, premission);

    loadUserInfo(m_userName, m_password, m_premission);

    connect(m_creatBtn, &QPushButton::clicked, this, &Widget::addUser);

    connect(m_saveBtn, &QPushButton::clicked, this, &Widget::on_saveBtnisClicked);
    connect(m_cancelBtn, &QPushButton::clicked, this, &Widget::on_cancelBtnisClicked);

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
    qDebug()<<__LINE__<<__FUNCTION__<<"userCount:"<<userCount;
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
    qDebug()<<__LINE__<<__FUNCTION__;
}

void Widget::loadUserInfo(QList<QString> userName, QList<QString> userPassword, QList<QString> permission)
{
    qDebug()<<__LINE__;
    m_tableWidget->clearContents();
    if(userName.size() != userPassword.size() /*|| userCount == 0*/)
    {
        return;
    }

    m_tableWidget->setRowCount(userName.size());      //设置行数，用于测试
//    m_tableWidget->setRowCount(userCount);      //设置行数
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
    qDebug()<<__FUNCTION__;
}

void Widget::deleteButtons()
{
    qDebug()<<__FUNCTION__;
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

void Widget::resetGroupOrder()
{
    for(int i = 1; i < userCount*5; i+=5)	//i是行数
    {
        string group = "[User" + to_string((i-1)/5) + "]";
        char chr[20];
        strcpy(chr, group.c_str());
//        qDebug()<<__LINE__<<m_filePath;
//        QByteArray ba = m_filePath.toLatin1();
//        char *path = ba.data();
//        ModifyLineData(path, i, chr);
        ModifyLineData("D:\\Project\\C++\\Qt\\Demo\\build-TableWidgetDemo-Desktop_Qt_5_14_2_MinGW_64_bit-Debug\\debug\\config\\userinfo.ini", i, chr);
    }
}

void Widget::removeUser(QTableWidgetItem *item)
{
    qDebug()<<__FUNCTION__;
    if(QMessageBox::question(this, "Tip","Are you sure you want to delete?", QMessageBox::Yes|QMessageBox::No)== QMessageBox::Yes)
    {
        userCount--;
        qDebug()<<__LINE__<<"userCount:"<<userCount;
        int row = m_tableWidget->row(item);
        qDebug()<<row;
        m_tableWidget->removeRow(row);
        deleteUserData("User" + QString::number(row), "UserName");
        deleteUserData("User" + QString::number(row), "Password");
        deleteUserData("User" + QString::number(row), "Premission");
        resetGroupOrder();
//        deleteUserData("User" + QString::number(userCount), "UserName");
//        deleteUserData("User" + QString::number(userCount), "Password");
//        deleteUserData("User" + QString::number(userCount), "Premission");

    }
}

void Widget::modifyUserInfo(QPushButton *btn, QTableWidgetItem *item)
{
    qDebug()<<__FUNCTION__;
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
    qDebug()<<__FUNCTION__;
    qDebug()<<__LINE__<<"CreatBtn is clicked";
    m_tableWidget->setRowCount(m_tableWidget->rowCount()+1);

    qDebug()<<__LINE__<<"Row count:"<<m_tableWidget->rowCount()<<"userCount:"<<userCount;

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

    /*按钮列未设置，在点击save按钮后设置，目前存在BUG：按钮列在未设置之前可编辑*/

    /*隐藏creatBtn*/
    m_creatBtn->hide();
    m_saveBtn->show();
    m_cancelBtn->show();
}

void Widget::on_saveBtnisClicked()
{
    m_saveBtn->hide();
    m_cancelBtn->hide();
    m_creatBtn->show();

    /*添加删除按钮和修改按钮*/
    QPushButton *btnDel = new QPushButton("Delete");
    btnDel->setEnabled(true);
    btnDel->setStyleSheet(QString::fromUtf8("QPushButton{background: white; color: blacke; border: 2px solid black; border-radius:10px; padding:2px 4px;}"));
    QPushButton *btnUpdate = new QPushButton("Modify");
    btnUpdate->setEnabled(true);
    btnUpdate->setStyleSheet(QString::fromUtf8("QPushButton{background: white; color: blacke; border: 2px solid black; border-radius:10px; padding:2px 4px;}"));
    QWidget *widget = new QWidget;
    QHBoxLayout *hboxlayout = new QHBoxLayout(widget);
    hboxlayout->setMargin(2);
    hboxlayout->addWidget(btnDel);
    hboxlayout->addWidget(btnUpdate);
    m_tableWidget->setCellWidget(m_tableWidget->rowCount()-1, 3,  widget);

    /*这里用了偷懒的方式给最后一行里的3列设置属性，这可能存在隐患，如果后期要用插入的方式创建新用户则会有BUG*/
    int num = m_tableWidget->rowCount()-1;      //获取最后一行的编号

    QTableWidgetItem *tempItem0 = m_tableWidget->item(num, 0);
    tempItem0->setFlags(m_tableWidget->item(num, 0)->flags() & (~Qt::ItemIsEditable));  //第一列不可编辑

    QTableWidgetItem *tempItem1 = m_tableWidget->item(num, 1);
    tempItem1->setFlags(tempItem1->flags() & (~Qt::ItemIsEditable));    //第二列不可编辑

    QTableWidgetItem *tempItem2 = m_tableWidget->item(num, 2);

    QTableWidgetItem *tempItem3 = m_tableWidget->item(num, 2);  //第三列没有item，用第二列的，因为removeUser()和modifyUserInfo()只需要通过item获取行号就可以了
    connect(btnDel, &QPushButton::clicked, [=](){ this->removeUser(tempItem3); });
    connect(btnUpdate, &QPushButton::clicked, [=](){ this->modifyUserInfo(btnUpdate, tempItem3); });

    writeUserData("User" + QString::number(userCount), "UserName", tempItem0->text());
    writeUserData("User" + QString::number(userCount), "Password", tempItem1->text());
    writeUserData("User" + QString::number(userCount), "Premission", tempItem2->text());

    userCount++;

    qDebug()<<__FUNCTION__;
}

void Widget::on_cancelBtnisClicked()
{
    m_saveBtn->hide();
    m_cancelBtn->hide();
    m_creatBtn->show();
    m_tableWidget->removeRow(m_tableWidget->rowCount()-1);  //删除未添加信息的行
    qDebug()<<__FUNCTION__;
}

void Widget::writeUserData(QString group, QString keyName, QString valueName)
{
    qDebug()<<__FUNCTION__;
    m_userInfo->setValue(group + "/" + keyName, valueName);
}

void Widget::deleteUserData(QString group, QString keyName)
{
    qDebug()<<__FUNCTION__;
    m_userInfo->remove(group + "/" + keyName);
//    resetGroupOrder();
}

void Widget::readUserData()
{
    QString group = "User";
    QString keyName0 = "UserName";
    QString keyName1 = "Password";
    QString keyName2 = "Premission";

    qDebug()<<__FUNCTION__;
    for(int i = 0; i < m_userInfo->childGroups().size(); i++)
    {
//        qDebug()<<m_userInfo->value(group + QString::number(i+10) + "/" + keyName0, 1024).toString();
//        m_userName<<m_userInfo->value(group + QString::number(i+10) + "/" + keyName0, 1024).toString();
//        m_password<<m_userInfo->value(group + QString::number(i+10) + "/" + keyName1, 1024).toString();
//        m_premission<<m_userInfo->value(group + QString::number(i+10) + "/" + keyName2, 1024).toString();
        qDebug()<<m_userInfo->value(group + QString::number(i) + "/" + keyName0, 1024).toString();
        m_userName<<m_userInfo->value(group + QString::number(i) + "/" + keyName0, 1024).toString();
        m_password<<m_userInfo->value(group + QString::number(i) + "/" + keyName1, 1024).toString();
        m_premission<<m_userInfo->value(group + QString::number(i) + "/" + keyName2, 1024).toString();
    }
}

void Widget::ModifyLineData(const char *fileName, int lineNum, const char *lineData)
{
//    qDebug()<<__FUNCTION__;
    ifstream in;
    in.open(fileName);

    string strFileData = "";
    int line = 1;
    char tmpLineData[1024] = {0};
    while(in.getline(tmpLineData, sizeof(tmpLineData)))
    {
        if (line == lineNum)
        {
            strFileData += CharToStr(lineData);
            strFileData += "\n";
        }
        else
        {
            strFileData += CharToStr(tmpLineData);
            strFileData += "\n";
        }
        line++;
    }
    in.close();

    //写入文件
    ofstream out;
    out.open(fileName);
    out.flush();
    out<<strFileData;
    out.close();
}

string Widget::CharToStr(const char *contentChar)
{
    string tempStr;
    for(int i=0; contentChar[i]!='\0'; i++)
    {
        tempStr+=contentChar[i];
    }
    return tempStr;
}
