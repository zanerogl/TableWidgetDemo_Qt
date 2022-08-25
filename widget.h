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
#include <QVector>

// 设置tableview某行/列不可编辑 （未使用）
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

    /**
     * @brief deleteButtons     删除按钮
     */
    void deleteButtons();

public slots:

    /**
     * @brief removeUser    删除用户
     * @param item
     */
    void removeUser(QTableWidgetItem *item);

    /**
     * @brief modifyUserInfo    修改用户信息
     * @param btn
     * @param item
     */
    void modifyUserInfo(QPushButton *btn, QTableWidgetItem *item);

    /**
     * @brief addUser   添加用户
     */
    void addUser();

private:
    Ui::Widget *ui;

    QTableWidget *m_tableWidget;
    QGridLayout *m_gridLayout;
    QPushButton *btnDel;
    QPushButton *btnUpdate;
    QPushButton *m_creatBtn;
    QPushButton *m_saveBtn;
    QPushButton *m_cancelBtn;
    QStringList m_headerStr = {"User","Password","Option"};
    QVector<QPushButton*>  btnVec;  //定义这个按钮指针容器的目的是为了方便一次性释放按钮内存
//    void (Widget::*funtionPtr)(QTableWidgetItem *);

};
#endif // WIDGET_H


