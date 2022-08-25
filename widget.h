#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QTableWidget>
#include <QPushButton>
#include <QGridLayout>
#include <QStringList>
#include <QTableWidgetItem>
#include <QHeaderView>
#include <QDebug>
#include <QMessageBox>
#include <QItemDelegate>

// 设置tableview某行/列不可编辑,
class ReadOnlyDelegate: public QItemDelegate
{

public:
    ReadOnlyDelegate(QWidget *parent = NULL):QItemDelegate(parent)
    {}

    QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &option,const QModelIndex &index) const override;
};



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
     * @brief initUI   初始化界面
     */
    void initUI();

    /**
     * @brief loadUserInfo      加载用户数据
     * @param userName
     * @param userPassword
     */
    void loadUserInfo(QList<QString> userName, QList<QString> userPassword);

public slots:
    /**
     * @brief removeUser_
     */
    void removeUser_();

    /**
     * @brief removeUser
     * @param item
     */
    void removeUser(QTableWidgetItem *item);

    /**
     * @brief modifyUserInfo_    修改用户信息
     */
    void modifyUserInfo_();

    /**
     * @brief modifyUserInfo
     * @param item
     */
    void modifyUserInfo(QPushButton *btn, QTableWidgetItem *item);


private:
    Ui::Widget *ui;

    QTableWidget *m_tableWidget;
    QGridLayout *m_gridLayout;
    QPushButton *btnDel;
    QPushButton *btnUpdate;
    QPushButton *m_creatBtn;
    QStringList m_headerStr = {"User","Password","Option"};
//    void (Widget::*funtionPtr)(QTableWidgetItem *);

};
#endif // WIDGET_H


