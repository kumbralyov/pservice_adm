#ifndef CONF_FORM_H
#define CONF_FORM_H

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
#include "adm_form.h"

class conf_form : public QMainWindow
{
    Q_OBJECT
public:
    explicit conf_form(QWidget *parent = 0);
    ~conf_form();

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
    QMenuBar *menu_bar;
    QPushButton *pb_show;

signals:

public slots:
    int frm_cre();
    int add_db_form_show();
    int le_db_finish();
    int pb_show_click();
};

#endif // CONF_FORM_H
