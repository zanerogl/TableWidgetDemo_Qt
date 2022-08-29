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
#include <QSettings>
#include <QString>
#include <QtCore>

#include <iostream>
#include <fstream>
#include <cstring>
#include <string>
using namespace std;

/*隐式BUG：item未双击进入可编辑状态前，编辑item会导致程序崩溃退出*/
/*显式BUG：ini文件如果已经有了信息则程序崩溃退出*/

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
     * @brief initProfile
     */
    void initProfile();

    /**
     * @brief initUI   初始化界面
     */
    void initUI();

    /**
     * @brief loadUserInfo      加载用户数据
     * @param userName
     * @param userPassword
     */
    void loadUserInfo(QList<QString> userName = {}, QList<QString> userPassword = {}, QList<QString> permission = {});

    /**
     * @brief deleteButtons     删除按钮
     */
    void deleteButtons();

    /**
     * @brief resetGroupOrder   重置组序（在删除用户后组的序列会打乱，需要重新修改组的序列）
     */
    void resetGroupOrder();

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

    /**
     * @brief on_saveBtnisClicked
     */
    void on_saveBtnisClicked();

    /**
     * @brief on_cancelBtnisClicked
     */
    void on_cancelBtnisClicked();

    /**
     * @brief writeUserData     写入用户数据
     * @param group             组名：User*
     * @param keyName           键名：UserName Password Premission
     * @param valueName         键值：xxxx *** 1
     */
    void writeUserData(QString group, QString keyName, QString valueName);

    /**
     * @brief deleteUserData    删除用户数据
     * @param group             组名：User*
     * @param keyName           键名：UserName Password Premission
     */
    void deleteUserData(QString group, QString keyName);

    /**
     * @brief readUserData  读取用户数据
     */
    void readUserData();

    /**
     * @brief ModifyLineData    修改文件行数据
     * @param fileName
     * @param lineNum
     * @param lineData
     */
    void ModifyLineData(const char* fileName, int lineNum, const char* lineData);

    /**
     * @brief CharToStr     Char 转 string
     * @param contentChar
     * @return
     */
    string CharToStr(const char * contentChar);

private:
    Ui::Widget *ui;

    QTableWidget *m_tableWidget;
    QGridLayout *m_gridLayout;
    QPushButton *btnDel;
    QPushButton *btnUpdate;
    QPushButton *m_creatBtn;
    QPushButton *m_saveBtn;
    QPushButton *m_cancelBtn;
    QStringList m_headerStr = {"User","Password", "Permission","Option"};
    QVector<QPushButton*>  btnVec;  //定义这个按钮指针容器的目的是为了方便一次性释放按钮内存
    QSettings *m_userInfo;
    QString m_filePath = QCoreApplication::applicationDirPath()+"/config/userinfo.ini";
    int userCount = 0;

    QStringList m_userName;
    QStringList m_password;
    QStringList m_premission;
};
#endif // WIDGET_H


