#include "adm_form.h"
#include "mainwindow.h"

QSqlDatabase db;

//----------------------------------------------------------------------------------------------------------------------------//
adm_form::adm_form(QWidget *parent)
    : QMainWindow(parent)
{
//    QTextCodec::setCodecForTr(QTextCodec::codecForName("UTF-8"));
//    QTextCodec::setCodecForCStrings(QTextCodec::codecForName("UTF-8"));

    menu_show();
    form_show();

}

//----------------------------------------------------------------------------------------------------------------------------//
adm_form::~adm_form()
{
    db.close();
}

//- Меню в режиме администратора ---------------------------------------------------------------------------------------------//
int adm_form::menu_show()
{
    menu_bar = new QMenuBar;

    QMenu *mnu_crt = new QMenu("&Создать", this);
    menu_bar->addMenu(mnu_crt);
    mnu_crt->addAction("&пользователя", this, SLOT(add_user_form_show()));

    QMenu *mnu_upd = new QMenu("&Изменить", this);
    menu_bar->addMenu(mnu_upd);
    mnu_upd->addAction("&пользователя", this, SLOT(upd_user_form_show()));

    QMenu *mnu_del = new QMenu("&Удалить", this);
    menu_bar->addMenu(mnu_del);
    mnu_del->addAction("&базу данных", this, SLOT(del_db_form_show()));
    mnu_del->addAction("&пользователя", this, SLOT(del_user_form_show()));

    QMenu *mnu_shw = new QMenu("&Показать", this);
    menu_bar->addMenu(mnu_shw);
    mnu_shw->addAction("&таблицы", this, SLOT(tables_form_show()));
    mnu_shw->addAction("по&льзователей", this, SLOT(users_form_show()));

    QMenu *mnu_help = new QMenu(tr("Справ&ка"), this);
    menu_bar->addMenu(mnu_help);
    mnu_help->addAction("&О программе", this, SLOT(about_form_show()));

    menu_bar->addMenu(mnu_help);

    return 0;
}

//- Форма режима администратора ----------------------------------------------------------------------------------------------//
int adm_form::form_show()
{
    QGridLayout *gl = new QGridLayout;

    QWidget *wgt = new QWidget (this);
    gl->setMenuBar(menu_bar);
    wgt->setLayout(gl);
    this->setCentralWidget(wgt);

    this->resize(500, 250);
    this->move(200, 200);
    this->setWindowTitle("Режим администратора");

    return 0;
}


//*** Формы меню "Создать" ***************************************************************************************************//
//- Форма создания пользователей ---------------------------------------------------------------------------------------------//
int adm_form::add_user_form_show()
{
    QGridLayout *gl = new QGridLayout;

    lb_login_nu = new QLabel("Логин");
    gl->addWidget(lb_login_nu, 0, 0, 1, 1);

    le_login_nu = new QLineEdit;
    gl->addWidget(le_login_nu, 0, 1, 1, 1);
    le_login_nu->setFocus();

    lb_pass_nu = new QLabel("Пароль");
    gl->addWidget(lb_pass_nu, 1, 0, 1, 1);

    le_pass_nu = new QLineEdit;
    gl->addWidget(le_pass_nu, 1, 1, 1, 1);

    lb_db_nu = new QLabel("База данных");
    gl->addWidget(lb_db_nu, 2, 0, 1, 1);

    le_db_nu = new QLineEdit(settings.value("db/name").toString());
    gl->addWidget(le_db_nu, 2, 1, 1, 1);

    lb_position_nu = new QLabel("Должность");
    gl->addWidget(lb_position_nu, 3, 0, 1, 1);

    le_position_nu = new QLineEdit;
    gl->addWidget(le_position_nu, 3, 1, 1, 1);

    lb_surname_nu = new QLabel("Фамилия");
    gl->addWidget(lb_surname_nu, 4, 0, 1, 1);

    le_surname_nu = new QLineEdit;
    gl->addWidget(le_surname_nu, 4, 1, 1, 1);

    lb_first_name_nu = new QLabel("Имя");
    gl->addWidget(lb_first_name_nu, 5, 0, 1, 1);

    le_first_name_nu = new QLineEdit;
    gl->addWidget(le_first_name_nu, 5, 1, 1, 1);

    lb_father_name_nu = new QLabel("Отчество");
    gl->addWidget(lb_father_name_nu, 6, 0, 1, 1);

    le_father_name_nu = new QLineEdit;
    gl->addWidget(le_father_name_nu, 6, 1, 1, 1);

    lb_privs = new QLabel("Права пользователя");
    gl->addWidget(lb_privs, 0, 2, 1, 1);

    cb_sel = new QCheckBox("Select");
    gl->addWidget(cb_sel, 1, 2, 1, 1);

    cb_ins = new QCheckBox("Insert");
    gl->addWidget(cb_ins, 2, 2, 1, 1);

    cb_upd = new QCheckBox("Update");
    gl->addWidget(cb_upd, 3, 2, 1, 1);

    cb_del = new QCheckBox("Delete");
    gl->addWidget(cb_del, 4, 2, 1, 1);

    pb_grant = new QPushButton("Создать");
    gl->addWidget(pb_grant, 7, 1, 1, 1);
    pb_grant->setShortcut(QKeySequence(Qt::Key_Return));
    connect(pb_grant, SIGNAL(clicked()), this, SLOT(add_user()));   // вызов функции создания пользователя

    QLabel *lb_space = new QLabel;
    gl->addWidget(lb_space, 6, 0, 1, 1);

    QWidget *wgt = new QWidget (this);
    gl->setMenuBar(menu_bar);
    wgt->setLayout(gl);
    this->setCentralWidget(wgt);
    this->setWindowTitle("Создание пользователя");

    return 0;
}

int adm_form::upd_user_form_show()
{
    QSqlQuery *quer;
    QString strsql;

    quer = new QSqlQuery(db);

    QGridLayout *gl = new QGridLayout;

    lb_login_nu = new QLabel("Логин");
    gl->addWidget(lb_login_nu, 0, 0, 1, 1);

    cb_logins = new QComboBox;
    cb_logins->insertSeparator(-1);
    gl->addWidget(cb_logins, 0, 1, 1, 1);

    strsql = "select * from users";
    quer->exec(strsql);
    if (quer->isActive())
    {
        int i = 0;
        while (quer->next())
        {
            cb_logins->insertItem(i, quer->value(0).toString());
            i++;
            qDebug() << __FILE__ << __LINE__ << quer->value(0).toString();
        }
    }
    else
    {
        statusBar()->showMessage("Запрос не успешен");
    }

    connect(cb_logins, SIGNAL(currentIndexChanged(QString)), this, SLOT(user_data_complete()));

    lb_db_nu = new QLabel("База данных");
    gl->addWidget(lb_db_nu, 1, 0, 1, 1);

    le_db_nu = new QLineEdit(settings.value("db/name").toString());
    gl->addWidget(le_db_nu, 1, 1, 1, 1);

    lb_position_nu = new QLabel("Должность");
    gl->addWidget(lb_position_nu, 2, 0, 1, 1);

    le_position_nu = new QLineEdit;
    gl->addWidget(le_position_nu, 2, 1, 1, 1);
    le_position_nu->setFocus();

    lb_surname_nu = new QLabel("Фамилия");
    gl->addWidget(lb_surname_nu, 3, 0, 1, 1);

    le_surname_nu = new QLineEdit;
    gl->addWidget(le_surname_nu, 3, 1, 1, 1);

    lb_first_name_nu = new QLabel("Имя");
    gl->addWidget(lb_first_name_nu, 4, 0, 1, 1);

    le_first_name_nu = new QLineEdit;
    gl->addWidget(le_first_name_nu, 4, 1, 1, 1);

    lb_father_name_nu = new QLabel("Отчество");
    gl->addWidget(lb_father_name_nu, 5, 0, 1, 1);

    le_father_name_nu = new QLineEdit;
    gl->addWidget(le_father_name_nu, 5, 1, 1, 1);

    lb_privs = new QLabel("Права пользователя");
    gl->addWidget(lb_privs, 0, 2, 1, 1);

    cb_sel = new QCheckBox("Select");
    gl->addWidget(cb_sel, 1, 2, 1, 1);

    cb_ins = new QCheckBox("Insert");
    gl->addWidget(cb_ins, 2, 2, 1, 1);

    cb_upd = new QCheckBox("Update");
    gl->addWidget(cb_upd, 3, 2, 1, 1);

    cb_del = new QCheckBox("Delete");
    gl->addWidget(cb_del, 4, 2, 1, 1);

    pb_revoke = new QPushButton("Изменить");
    gl->addWidget(pb_revoke, 6, 1, 1, 1);
    connect(pb_revoke, SIGNAL(clicked()), this, SLOT(upd_user()));   // вызов функции изменения пользователя

    QLabel *lb_space = new QLabel;
    gl->addWidget(lb_space, 7, 0, 1, 1);

    QWidget *wgt = new QWidget (this);
    gl->setMenuBar(menu_bar);
    wgt->setLayout(gl);
    this->setCentralWidget(wgt);
    this->setWindowTitle("Создание пользователя");

    return 0;
}

int adm_form::user_data_complete()
{
    QSqlQuery *quer;
    QString strsql;

    quer = new QSqlQuery(db);
    strsql = "select * from users where login = '%1'";
    strsql = strsql.arg(cb_logins->currentText());
    quer->exec(strsql);
    if (quer->isActive())
    {
        quer->next();
        le_position_nu->setText(quer->value(1).toString());
        le_surname_nu->setText(quer->value(2).toString());
        le_first_name_nu->setText(quer->value(3).toString());
        le_father_name_nu->setText(quer->value(4).toString());
        qDebug() << __FILE__ << __LINE__ << quer->lastError() << quer->value(1).toString() << cb_logins->currentText() << strsql;
    }

    strsql = "show grants for %1@localhost";
    strsql = strsql.arg(cb_logins->currentText());
    quer->exec(strsql);
    if (quer->isActive())
    {
        quer->next();
        while (quer->value(0).toString().indexOf("ON `" + settings.value("db/name").toString() + "`.*") == -1 && quer->next())
            ;
        qDebug() << __FILE__ << __LINE__ << quer->value(0).toString();

        if (quer->value(0).toString().indexOf("ON `" + settings.value("db/name").toString() + "`.*") != -1)
        {
            if (quer->value(0).toString().indexOf("SELECT") > -1)
            {
                cb_sel->setChecked(true);
                sel = true;
            }
            else
            {
                cb_sel->setChecked(false);
                sel = false;
            }
            if (quer->value(0).toString().indexOf("INSERT") > -1)
            {
                cb_ins->setChecked(true);
                ins = true;
            }
            else
            {
                cb_ins->setChecked(false);
                ins = false;
            }
            if (quer->value(0).toString().indexOf("UPDATE") > -1)
            {
                cb_upd->setChecked(true);
                upd = true;
            }
            else
            {
                cb_upd->setChecked(false);
                upd = false;
            }
            if (quer->value(0).toString().indexOf("DELETE") > -1)
            {
                cb_del->setChecked(true);
                del = true;
            }
            else
            {
                cb_del->setChecked(false);
                del = false;
            }
        }
        else
        {
            cb_sel->setChecked(false);
            sel = false;
            cb_ins->setChecked(false);
            ins = false;
            cb_upd->setChecked(false);
            upd = false;
            cb_del->setChecked(false);
            del = false;
        }

    }
    qDebug() << __FILE__ << __LINE__ << quer->lastError();



    return 0;
}

//- Функция создания пользователя --------------------------------------------------------------------------------------------//
int adm_form::add_user()
{
    QSqlQuery *quer;
    QString strsql;

    quer = new QSqlQuery(db);

    QString priv;
    priv.clear();

    if (cb_del->isChecked())
        priv += " delete,";
    if (cb_ins->isChecked())
        priv += " insert,";
    if (cb_sel->isChecked())
        priv += " select,";
    if (cb_upd->isChecked())
        priv += " update,";
    priv = priv.left(priv.size()-1);
    qDebug() << __FILE__ << __LINE__ << priv << endl;

    strsql = "create user %3@%4 identified by '%5'; ";
    strsql = strsql.arg(le_login_nu->text())
            .arg("localhost")
            .arg(le_pass_nu->text());

    if (priv != "")
    {
        strsql = "grant %1 on %2.* to %3@%4 identified by '%5'; ";
        strsql = strsql.arg(priv)
                .arg(le_db_nu->text())
                .arg(le_login_nu->text())
                .arg("localhost")
                .arg(le_pass_nu->text());
        qDebug() << __FILE__ << __LINE__ << "strsql = " << strsql;
    }

    strsql += "insert into users values('%1', '%2', '%3', '%4', '%5')";
    strsql = strsql.arg(le_login_nu->text())
                   .arg(le_position_nu->text())
                   .arg(le_surname_nu->text())
                   .arg(le_first_name_nu->text())
                   .arg(le_father_name_nu->text());

    quer->exec(strsql);
    if (quer->isActive())
    {
        statusBar()->showMessage("Запрос успешен");
    }
    else
    {
        statusBar()->showMessage("Ошибка при создании нового пользователя");
        qDebug() << __FILE__ << __LINE__ << quer->lastError().text();
    }

    return 0;
}

//- Функция изменения пользователя ----------------------------------------------------------------------------------------------//
int adm_form::upd_user()
{
    QSqlQuery *quer;
    QString strsql;

    quer = new QSqlQuery(db);

    QString priv_grant;
    priv_grant.clear();

    if (cb_del->isChecked() && del == false)
        priv_grant += " delete,";
    if (cb_ins->isChecked() && ins == false)
        priv_grant += " insert,";
    if (cb_sel->isChecked() && sel == false)
        priv_grant += " select,";
    if (cb_upd->isChecked() && upd == false)
        priv_grant += " update,";

    if (priv_grant != "")
    {
        priv_grant = priv_grant.left(priv_grant.size()-1);
        qDebug() << __FILE__ << __LINE__ << priv_grant << endl;

        strsql = "grant %1 on %2.* to %3@%4; ";
        strsql = strsql.arg(priv_grant)
                .arg(le_db_nu->text())
                .arg(cb_logins->currentText())
                .arg("localhost");
        qDebug() << __FILE__ << __LINE__ << "strsql = " << strsql;
    }

    QString priv_revoke;
    priv_revoke.clear();

    if (cb_del->isChecked() == false && del == true)
        priv_revoke += " delete,";
    if (cb_ins->isChecked() == false && ins == true)
        priv_revoke += " insert,";
    if (cb_sel->isChecked() == false && sel == true)
        priv_revoke += " select,";
    if (cb_upd->isChecked() == false && upd == true)
        priv_revoke += " update,";
    qDebug() << __FILE__ << __LINE__ << priv_revoke;

    if (priv_revoke != "")
    {
        priv_revoke = priv_revoke.left(priv_revoke.size()-1);
        qDebug() << __FILE__ << __LINE__ << priv_revoke << endl;
        strsql += "revoke %1 on %2.* from %3@%4; ";
        strsql = strsql.arg(priv_revoke)
                .arg(le_db_nu->text())
                .arg(cb_logins->currentText())
                .arg("localhost");
        qDebug() << __FILE__ << __LINE__ << "strsql = " << strsql;
    }

    strsql += "update users set position = '%1', surname = '%2', first_name = '%3', father_name = '%4' where login = '%5'";
    strsql = strsql.arg(le_position_nu->text())
                   .arg(le_surname_nu->text())
                   .arg(le_first_name_nu->text())
                   .arg(le_father_name_nu->text())
                   .arg(cb_logins->currentText());

    qDebug() << __FILE__ << __LINE__ << "strsql = " << strsql;
    quer->exec(strsql);
    if (quer->isActive())
    {
        statusBar()->showMessage("Запрос успешен");
        upd_user_form_show();
    }
    else
    {
        statusBar()->showMessage("Запрос не успешен");
    }
    qDebug() << __FILE__ << __LINE__ << quer->lastError().text();

    return 0;
}

//*** Формы меню "Удалить" ***************************************************************************************************//
//- Форма удаления базы данных -----------------------------------------------------------------------------------------------//
int adm_form::del_db_form_show()
{
    QGridLayout *gl = new QGridLayout;

    lb_db_del = new QLabel("Название базы данных");
    gl->addWidget(lb_db_del, 0, 0, 1, 1);

    le_db_del = new QLineEdit(settings.value("db/name").toString());
    gl->addWidget(le_db_del, 0, 1, 1, 1);
    le_db_del->setFocus();

    pb_strg_del = new QPushButton("Удалить");
    gl->addWidget(pb_strg_del, 1, 1, 1, 1);
    pb_strg_del->setShortcut(QKeySequence(Qt::Key_Return));
    connect(pb_strg_del, SIGNAL(clicked()), this, SLOT(pb_db_del_click()));   // вызов функции удаления БД

    QLabel *lb_space = new QLabel;
    gl->addWidget(lb_space, 2, 0, 1, 1);

    QWidget *wgt = new QWidget (this);
    gl->setMenuBar(menu_bar);
    wgt->setLayout(gl);
    this->setCentralWidget(wgt);
    this->setWindowTitle("Удаление базы данных");
    return 0;
}

//- Функция удаления базы данных -------------------------------------------------------------------------------------------------//
int adm_form::pb_db_del_click()
{
    QSqlQuery *quer;
    QString strsql;

    quer = new QSqlQuery(db);
    strsql.clear();
    strsql = "drop database %1";
    strsql = strsql.arg(le_db_del->text());
    quer->exec(strsql);
    if (quer->isActive())
    {
        statusBar()->showMessage("Запрос drop user успешен");
//        settings.contains("db/name");
        settings.remove("db/name");
    }
    else
    {
        statusBar()->showMessage("Запрос drop user не успешен");
        qDebug() << "strsql = " << strsql;
        qDebug() << "ошибка: " << quer->lastError().text();
    }
    return 0;
}

//- Форма удаления пользователя ----------------------------------------------------------------------------------------------//
int adm_form::del_user_form_show()
{
    QGridLayout *gl = new QGridLayout;

    lb_login_del = new QLabel("Логин пользователя");
    gl->addWidget(lb_login_del, 0, 0, 1, 1);

    le_login_del = new QLineEdit;
    gl->addWidget(le_login_del, 0, 1, 1, 1);
    le_login_del->setFocus();

    pb_login_del = new QPushButton("Удалить");
    gl->addWidget(pb_login_del, 1, 1, 1, 1);
    pb_login_del->setShortcut(QKeySequence(Qt::Key_Return));
    connect(pb_login_del, SIGNAL(clicked()), this, SLOT(pb_login_del_click()));   // вызов функции удаления пользователя

    QLabel *lb_space = new QLabel;
    gl->addWidget(lb_space, 2, 0, 1, 1);

    QWidget *wgt = new QWidget (this);
    gl->setMenuBar(menu_bar);
    wgt->setLayout(gl);
    this->setCentralWidget(wgt);
    this->setWindowTitle("Удаление базы данных");
    return 0;
}

//- Функция удаления пользователя --------------------------------------------------------------------------------------------//
int adm_form::pb_login_del_click()
{
    QSqlQuery *quer;
    QString strsql;

    quer = new QSqlQuery(db);
    strsql.clear();
    strsql = "drop user '%1'@'%2'; delete from users where login = %1";
    strsql = strsql.arg(le_login_del->text())
                   .arg("localhost");
    quer->exec(strsql);
    if (quer->isActive())
    {
        statusBar()->showMessage("Запрос drop user успешен");
    }
    else
    {
        statusBar()->showMessage("Запрос drop user не успешен");
        qDebug() << "strsql = " << strsql;
        qDebug() << "ошибка: " << quer->lastError().text();
    }
    return 0;
}

//*** Формы меню "Показать" **************************************************************************************************//
//- Показ списка таблиц ------------------------------------------------------------------------------------------------------//
int adm_form::tables_form_show()
{
    QGridLayout *gl = new QGridLayout;

    QWidget *wgt = new QWidget (this);
    gl->setMenuBar(menu_bar);

    QTextEdit *te_view = new QTextEdit;
    gl->addWidget(te_view, 0, 0, 1, 1);

    QSqlQuery *quer;
    QString strsql;
    QString columns;

    quer = new QSqlQuery(db);

    te_view->append("Список таблиц:");
    strsql.clear();
    strsql = "show tables";
    quer->exec(strsql);
    if (quer->isActive())
    {
        statusBar()->showMessage("Запрос show tables успешен");
        while (quer->next())
        {
            te_view->append("--- <b>" + quer->value(0).toString() + "</b> ---");
            strsql.clear();
            strsql = "show full columns from %1";
            strsql = strsql.arg(quer->value(0).toString());
            QSqlQuery *querc = new QSqlQuery(db);
            querc->exec(strsql);
            if (querc->isActive())
            {
                columns.clear();
                while (querc->next())
                {
                    columns += querc->value(0).toString() + "\t";
                }
                te_view->append(columns + "\n");
            }
        }
    }
    else
    {
        statusBar()->showMessage("Запрос show tables не успешен");
    }

    wgt->setLayout(gl);
    this->setCentralWidget(wgt);
    this->setWindowTitle("Таблицы");
    return 0;
}

//- Показ списка пользователей -----------------------------------------------------------------------------------------------//
int adm_form::users_form_show()
{
    QGridLayout *gl = new QGridLayout;

    QWidget *wgt = new QWidget (this);
    gl->setMenuBar(menu_bar);

    QTextEdit *te_view = new QTextEdit;
    gl->addWidget(te_view, 0, 0, 1, 1);

    QSqlQuery *quer;
    QString strsql;
    QString grants;

    quer = new QSqlQuery(db);

    te_view->append("Список пользователей:");
    strsql.clear();
    strsql = "select user, host from mysql.user;";
    quer->exec(strsql);
    if (quer->isActive())
    {
        statusBar()->showMessage("Запрос select user успешен");
        while (quer->next())
        {
            te_view->append("--- <b>" + quer->value(0).toString() + "</b> ---");
            strsql.clear();
            strsql = "show grants for %1@%2";
            strsql = strsql.arg(quer->value(0).toString())
                           .arg("localhost");
            QSqlQuery *querc = new QSqlQuery(db);
            querc->exec(strsql);
            if (querc->isActive())
            {
                grants.clear();
                while (querc->next())
                {
                    grants += querc->value(0).toString() + "\n";
                }
                te_view->append(grants + "\n");
            }
        }
    }
    else
    {
        statusBar()->showMessage("Запрос show tables не успешен");
    }

    wgt->setLayout(gl);
    this->setCentralWidget(wgt);
    this->setWindowTitle("Таблицы");
    return 0;
}

//*** Формы меню "Справка" ***************************************************************************************************//
//- О программе --------------------------------------------------------------------------------------------------------------//
int adm_form::about_form_show()
{
    QMessageBox::information(0, "О программе", "(c) Anton Kumbralyov, 2018");
    return 0;
}
