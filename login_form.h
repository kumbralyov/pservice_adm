#ifndef LOGIN_FORM_H
#define LOGIN_FORM_H

#include <QMainWindow>
#include <QPushButton>
#include <QLabel>
#include <QLineEdit>
#include <QGridLayout>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QString>
#include <QStatusBar>
#include <QSettings>
#include "adm_form.h"

class login_form : public QMainWindow
{
    Q_OBJECT
public:
    explicit login_form(QWidget *parent = 0);
    ~login_form();

    QSettings settings;
    QSqlDatabase db;
    QLabel *lb_db;
    QLineEdit *le_db;
    QLabel *lb_login;
    QLineEdit *le_login;
    QLabel *lb_pass;
    QLineEdit *le_pass;
    QPushButton *pb_conn;
    QGridLayout *gl;

signals:

public slots:
    void frm_cre();
    void adm_form_show();
    int le_pass_finish();
    int pb_conn_click();
};

#endif // LOGIN_FORM_H
