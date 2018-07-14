#ifndef adm_form_H
#define adm_form_H

#include <QMainWindow>
#include <QWidget>
#include <QPushButton>
#include <QLabel>
#include <QLineEdit>
#include <QTextEdit>
#include <QCheckBox>
#include <QRadioButton>
#include <QGridLayout>
#include <QMenuBar>
#include <QMenu>
#include <QMessageBox>
#include <QSqlQuery>
#include <QSqlError>
#include <QStatusBar>
#include <QDebug>
#include <QSettings>
#include <QComboBox>

class adm_form : public QMainWindow
{
    Q_OBJECT
public:
    explicit adm_form(QWidget *parent = 0);
    ~adm_form();

    QSettings settings;

    QMenuBar *menu_bar;
    QLabel *lb_db;
    QLineEdit *le_db;
    QPushButton *pb_show;

    QComboBox *cb_logins;
    QLabel *lb_login_nu;
    QLineEdit *le_login_nu;
    QLabel *lb_pass_nu;
    QLineEdit *le_pass_nu;
    QLabel *lb_db_nu;
    QLineEdit *le_db_nu;
    QLabel *lb_position_nu;
    QLineEdit *le_position_nu;
    QLabel *lb_surname_nu;
    QLineEdit *le_surname_nu;
    QLabel *lb_first_name_nu;
    QLineEdit *le_first_name_nu;
    QLabel *lb_father_name_nu;
    QLineEdit *le_father_name_nu;

    QLabel *lb_privs;
    QPushButton *pb_grant;
    QPushButton *pb_revoke;
    QCheckBox *cb_all;
    QCheckBox *cb_sel;
    QCheckBox *cb_ins;
    QCheckBox *cb_upd;
    QCheckBox *cb_del;
    bool sel;
    bool ins;
    bool upd;
    bool del;
//    QString priv;

    QLabel *lb_strg;
    QLineEdit *le_strg;
    QLabel *lb_user;
    QLineEdit *le_user;
    QLabel *lb_adr;
    QLineEdit *le_adr;
    QPushButton *pb_strg;

    QLabel *lb_db_del;
    QLineEdit *le_db_del;
    QPushButton *pb_db_del;

    QLabel *lb_login_del;
    QLineEdit *le_login_del;
    QPushButton *pb_login_del;

    QLabel *lb_adr_del;
    QLineEdit *le_adr_del;
    QPushButton *pb_strg_del;

signals:

public slots:
    int menu_show();
    int form_show();

//    int add_db_form_show();
    int add_user_form_show();

    int upd_user_form_show();
    int user_data_complete();

    int del_db_form_show();
    int del_user_form_show();

    int tables_form_show();
    int users_form_show();

    int about_form_show();

//    int le_db_finish();
//    int pb_show_click();

//    int rb_su_click();
//    int rb_user_click();
    int add_user();
    int upd_user();

    int pb_db_del_click();

    int pb_login_del_click();
};

#endif // adm_form_H
