#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QTableWidget>
#include <QPushButton>
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

    /**
     * @brief loadUserInfo
     */
    /**
     * @brief loadUserInfo      加载用户数据
     * @param userName
     * @param userPassword
     */
    void loadUserInfo(QList<QString> userName, QList<QString> userPassword);






private:
    Ui::Widget *ui;

    QTableWidget *m_tableWidget;
    QGridLayout *m_gridLayout;

    QPushButton *m_creatBtn;
    QPushButton *m_closeBtn;
    QStringList m_headerStr = {"User","Password","Option"};

};
#endif // WIDGET_H
