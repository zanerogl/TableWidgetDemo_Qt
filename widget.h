#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QTableWidget>
#include <QGridLayout>
#include <QStringList>
#include <QTableWidgetItem>
#include <QHeaderView>

QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

    /**
     * @brief initTableWidget   初始化控件
     */
    void initTableWidget();


private:
    Ui::Widget *ui;

    QTableWidget *m_tableWidget;
    QGridLayout *m_gridLayout;

    QStringList m_headerStr = {"User","Password","Delete","Update"};

};
#endif // WIDGET_H
