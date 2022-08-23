#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);

    initTableWidget();
}

Widget::~Widget()
{
    delete ui;
}

void Widget::initTableWidget()
{
    m_tableWidget = new QTableWidget(this);
    m_gridLayout = new QGridLayout(this);
    m_gridLayout->addWidget(m_tableWidget, 0, 0, 1, 1);

    m_gridLayout->setMargin(5);

    m_tableWidget->setColumnCount(4);
    m_tableWidget->setHorizontalHeaderLabels(m_headerStr);

    QFont font = m_tableWidget->horizontalHeader()->font();
    font.setBold(true); //加粗
    font.setPixelSize(16);
    m_tableWidget->horizontalHeader()->setFont(font);

    for(int i = 0; i < m_tableWidget->columnCount(); i++)
    {
        m_tableWidget->setColumnWidth(i,187);
    }

    m_tableWidget->horizontalHeader()->setStretchLastSection(true);//最后一行可拉伸
    m_tableWidget->verticalHeader()->setVisible(false);
}

