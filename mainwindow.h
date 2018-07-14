#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTextCodec>
#include <QSettings>
#include "conf_form.h"
#include "login_form.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();
    QSettings settings;

public slots:
    void frm_cre();
    void login_form_show();
    void conf_form_show();
};

#endif // MAINWINDOW_H
