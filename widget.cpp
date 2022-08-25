#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);

    initUI();

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

void Widget::initUI()
{
    m_tableWidget = new QTableWidget(this);
    m_creatBtn = new QPushButton(this);
    m_gridLayout = new QGridLayout(this);

    /*弹簧*/
    QSpacerItem *verticalSpacer = new QSpacerItem(20, 15, QSizePolicy::Minimum, QSizePolicy::Fixed);
    QSpacerItem *horizontalSpacer = new QSpacerItem(200, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);
    QSpacerItem *verticalSpacer_2 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Fixed);;
    QSpacerItem *horizontalSpacer_2 = new QSpacerItem(200, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

    /*设置布局*/
    m_gridLayout->addWidget(m_tableWidget, 0, 0, 1, 3);
    m_gridLayout->addWidget(m_creatBtn, 2, 1, 1, 1);
    m_gridLayout->addItem(verticalSpacer, 1, 1, 1, 1);
    m_gridLayout->addItem(verticalSpacer_2, 3, 1, 1, 1);
    m_gridLayout->addItem(horizontalSpacer, 2, 0, 1, 1);
    m_gridLayout->addItem(horizontalSpacer_2, 2, 2, 1, 1);
    m_gridLayout->setMargin(3);

    /*设置TableWidget属性*/
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
    m_tableWidget->setShowGrid(true);
    m_tableWidget->setGridStyle(Qt::DotLine);
//    m_tableWidget->setSortingEnabled(true);   //排序
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
}

void Widget::loadUserInfo(QList<QString> userName, QList<QString> userPassword)
{
//    ReadOnlyDelegate *readOnlyDelegate = new ReadOnlyDelegate(this);
    m_tableWidget->clearContents();

    if(userName.size() != userPassword.size())
    {
        return;
    }

    m_tableWidget->setRowCount(userName.size());

    for(int i = 0; i < m_tableWidget->rowCount(); i++)
    {
        /*用户名*/
        QTableWidgetItem *nameItem = new QTableWidgetItem(tr("%1").arg(userName.at(i)));
        nameItem->setFlags(nameItem->flags() & (~Qt::ItemIsEditable));//第一列不可编辑
//        nameItem->setFont(nullFont);
        nameItem->setTextAlignment(Qt::AlignCenter);
        m_tableWidget->setItem(i, 0, nameItem);
//        qDebug()<<m_tableWidget->item(i, 0)->flags();

        /*密码*/
        QTableWidgetItem *pwdItem = new QTableWidgetItem(tr("%1").arg(userPassword.at(i)));
        pwdItem->setFlags(pwdItem->flags() & (~Qt::ItemIsEditable));//第二列不可编辑
        pwdItem->setTextAlignment(Qt::AlignCenter);
//        pwdItem->setFont(nullFont);
        m_tableWidget->setItem(i, 1, pwdItem);

        /*添加删除按钮和修改按钮*/
        QPushButton *btnDel = new QPushButton("Delete");
        btnDel->setStyleSheet(QString::fromUtf8("QPushButton{background: white; color: blacke; border: 2px solid black; border-radius:10px; padding:2px 4px;}"));
        QPushButton *btnUpdate = new QPushButton("Modify");
        btnUpdate->setStyleSheet(QString::fromUtf8("QPushButton{background: white; color: blacke; border: 2px solid black; border-radius:10px; padding:2px 4px;}"));

        QWidget *widget = new QWidget;
        QHBoxLayout *hboxlayout = new QHBoxLayout(widget);
        hboxlayout->setMargin(2);
        hboxlayout->addWidget(btnDel);
        hboxlayout->addWidget(btnUpdate);
        m_tableWidget->setCellWidget(i, 2,  widget);

        connect(btnDel, &QPushButton::clicked, [=](){this->removeUser(nameItem);});
        connect(btnUpdate, &QPushButton::clicked, [=](){this->modifyUserInfo(btnUpdate, nameItem);});
    }

}

void Widget::removeUser_()
{
    QObject *obj = sender();    //当一个obejct发生信号时，系统会记录下发生者，通过sender函数可以获取发送者的地址
    QPushButton *btn = qobject_cast<QPushButton*>(obj); //通过模板对类型进行动态的转换，这里是QObject->QPushButton

    int x = btn->frameGeometry().x();
    int y = btn->frameGeometry().y();

    QModelIndex index = m_tableWidget->indexAt(QPoint(x, y));
    int row = index.row();
    qDebug()<<__LINE__<<row;

    if(QMessageBox::question(this, "Tip","Are you sure you want to delete?", QMessageBox::Yes|QMessageBox::No)== QMessageBox::Yes)
    {
       m_tableWidget->removeRow(row);
    }
    qDebug()<<"removeUser";
}

void Widget::removeUser(QTableWidgetItem *item)
{
    int row = m_tableWidget->row(item);
    //   qDebug() << m_tableWidget->row(item);
    if(QMessageBox::question(this, "Tip","Are you sure you want to delete?", QMessageBox::Yes|QMessageBox::No)== QMessageBox::Yes)
    {
       m_tableWidget->removeRow(row);
    }
}

void Widget::modifyUserInfo_()
{
    QObject *obj = sender();
    QPushButton *btn = qobject_cast<QPushButton*>(obj);

    int x = btn->frameGeometry().x();
    int y = btn->frameGeometry().y();
    qDebug()<<__LINE__<<"x:"<<x<<"y:"<<y;

    QModelIndex index = m_tableWidget->indexAt(QPoint(x, y));
//    qDebug()<<__LINE__<<m_tableWidget->itemAt(x, y);
    int row = index.row();          //获取当前行
    int column = index.column();    //获取当前列
    qDebug()<<__LINE__<<"row:"<<row<<"column:"<<column;

    Qt::ItemFlags flag1 = m_tableWidget->item(row, 0)->flags();
    Qt::ItemFlags flag2 = m_tableWidget->item(row, 1)->flags();
    qDebug()<<__LINE__<<"Flag1:"<<flag1;
    qDebug()<<__LINE__<<"Flag2:"<<flag2;

    if(btn->text() == "Modify")
    {
        btn->setText("Confirm");
        qDebug()<<__LINE__<<m_tableWidget->item(row, column)->flags();

        m_tableWidget->item(row, 0)->setFlags(flag1 | (Qt::ItemIsEditable));   //密码
        m_tableWidget->item(row, 1)->setFlags(flag2 | (Qt::ItemIsEditable));   //用户名
    }
    else
    {
        btn->setText("Modify");
        m_tableWidget->item(row, 0)->setFlags(flag1 & (~Qt::ItemIsEditable));   //密码
        m_tableWidget->item(row, 1)->setFlags(flag2 & (~Qt::ItemIsEditable));   //用户名
    }

    qDebug()<<"modifyUserInfo";
}

void Widget::modifyUserInfo(QPushButton *btn, QTableWidgetItem *item)
{
    int row = m_tableWidget->row(item);
    int column = m_tableWidget->column(item);
    Qt::ItemFlags flag1 = m_tableWidget->item(row, column)->flags();
    Qt::ItemFlags flag2 = m_tableWidget->item(row, column)->flags();

    if(btn->text() == "Modify")
    {
        btn->setText("Confirm");
        qDebug()<<__LINE__<<m_tableWidget->item(row, column)->flags();

        m_tableWidget->item(row, 0)->setFlags(flag1 | (Qt::ItemIsEditable));   //密码
        m_tableWidget->item(row, 1)->setFlags(flag2 | (Qt::ItemIsEditable));   //用户名
    }
    else
    {
        btn->setText("Modify");
        m_tableWidget->item(row, 0)->setFlags(flag1 & (~Qt::ItemIsEditable));   //密码
        m_tableWidget->item(row, 1)->setFlags(flag2 & (~Qt::ItemIsEditable));   //用户名
    }
    qDebug() << m_tableWidget->row(item);
}

QWidget *ReadOnlyDelegate::createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const //final
{
    Q_UNUSED(parent)
    Q_UNUSED(option)
    Q_UNUSED(index)
    return NULL;
}
