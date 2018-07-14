#include "mainwindow.h"
#include "adm_form.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
//    QTextCodec::setCodecForTr(QTextCodec::codecForName("UTF-8"));
//    QTextCodec::setCodecForCStrings(QTextCodec::codecForName("UTF-8"));

    frm_cre();
}

MainWindow::~MainWindow()
{

}

void MainWindow::frm_cre()
{
    if (settings.contains("db/name") == true)
        login_form_show();
    else
        conf_form_show();
}

void MainWindow::login_form_show()
{
    login_form *lf = new login_form;
    lf->show();
}

void MainWindow::conf_form_show()
{
    conf_form *cf = new conf_form;
    cf->show();
}
