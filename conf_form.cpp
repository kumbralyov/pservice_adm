#include "conf_form.h"

conf_form::conf_form(QWidget *parent) : QMainWindow(parent)
{
    add_db_form_show();
}

conf_form::~conf_form()
{
    db.close();
}

int conf_form::frm_cre()
{

}

//- Форма создания базы данных -----------------------------------------------------------------------------------------------//
int conf_form::add_db_form_show()
{
    QGridLayout *gl = new QGridLayout;

    gl->addWidget(new QLabel("Базы данных не создана. Создайте её сейчас"), 0, 0, 1, 1);

    lb_db = new QLabel("Название базы данных");
    gl->addWidget(lb_db, 1, 0, 1, 1);       // надпись устанавливается в сетку

    le_db = new QLineEdit;                  // поле ввода базы данных
    gl->addWidget(le_db, 1, 1, 1, 1);       // поле устанавливается в сетку
    le_db->setFocus();                      // устанавливается фокус на поле ввода

    lb_pass = new QLabel("Пароль администратора базы данных (root)");
    gl->addWidget(lb_pass, 2, 0, 1, 1);     // надпись устанавливается в сетку

    le_pass = new QLineEdit;                // поле ввода пароля
    le_pass->setEchoMode(QLineEdit::Password);
    gl->addWidget(le_pass, 2, 1, 1, 1);     // поле устанавливается в сетку

    connect(le_pass, SIGNAL(textEdited(QString)),this,SLOT(le_db_finish()));   // активизация кнопки ввода после ввода пароля

    pb_show = new QPushButton("Создать");   // кнопка создания
    gl->addWidget(pb_show, 3, 1, 1, 1);     // кнопка устанавливается в сетку
    pb_show->setEnabled(false);             // кнопка делается неактивной
    pb_show->setShortcut(QKeySequence(Qt::Key_Return));   // связь с клавишей return
    connect(pb_show, SIGNAL(clicked()), this, SLOT(pb_show_click()));   // вызов функции создания базы данных

    QWidget *wgt = new QWidget (this);      // создаётся окно
    gl->setMenuBar(menu_bar);
    wgt->setLayout(gl);                     // устанавливается сетка в окне
    this->setCentralWidget(wgt);
    this->setWindowTitle("Создание базы данных");           // название окна

    return 0;
}

//- Активность кнопки "создать" ----------------------------------------------------------------------------------------------//
int conf_form::le_db_finish()
{
    if (le_db->text() != "")
        pb_show->setEnabled(true);    // если в поле ввода введено название - кнопка ввода делается активной
    else
        pb_show->setEnabled(false);   // иначе - неактивной
    return 0;
}

//- Функция создания базы данных ---------------------------------------------------------------------------------------------//
int conf_form::pb_show_click()
{
    db = QSqlDatabase::addDatabase("QMYSQL");   // создаётся база данных

    db.setHostName("localhost");                // название хоста
    db.setPort(3306);                           // номер порта
    db.setDatabaseName("mysql");                // название базы данных
    db.setUserName("root");                     // имя пользователя
    db.setPassword(le_pass->text());            // пароль

    if (db.open())
    {
        statusBar()->showMessage("Соединение установлено");   // вывод результата соединения с базой данных в статусную строку
    }
    else
    {
        statusBar()->showMessage("Соединение не установлено");   // вывод результата соединения с базой данных в статусную строку
    }

    QSqlQuery *quer;
    QString strsql;
    QString report = "";   // переменная для вывода отчёта об успешности создания базы данных и таблиц

    quer = new QSqlQuery(db);
    strsql = "create database %1";
    strsql = strsql.arg(le_db->text());
    qDebug() << __FILE__ << __LINE__ << "strsql = " << strsql;
    qDebug() << __FILE__ << __LINE__ << "(add_db) db/name: " << settings.contains("db/name") << "   " << settings.value("db/name").toString();
    quer->exec(strsql);

    if (quer->isActive())
    {
        report += "База данных успешно создана\n";

        strsql.clear();
        strsql = "use %1";
        strsql = strsql.arg(le_db->text());
        qDebug() << __FILE__ << __LINE__ << "strsql = " << strsql;
        quer->exec(strsql);
        if (quer->isActive())
        {
         //- Таблица in_operations ---//
            strsql.clear();
            strsql = "create table in_operations(id_in_oper bigint unsigned not null auto_increment primary key, "
                                                "date_in_oper date not null, "
                                                "sum_in_oper int not null, "
                                                "id_branch int unsigned not null, "
                                                "id_doc_type tinyint not null, "
                                                "contract_num varchar(20), "
                                                "contract_date date, "
                                                "id_customer int unsigned, "
                                                "id_pservice int unsigned not null, "
                                                "event_date date not null, "
                                                "annotation varchar(1000))";
            qDebug() << __FILE__ << __LINE__ << "strsql = " << strsql;
            quer->exec(strsql);
            if (quer->isActive())
            {
                report += "Таблица in_operations создана\n";
            }
            else
            {
                report += "Таблицу in_operations не удалось создать\n";
                report += quer->lastError().text() + "\n";
                QMessageBox::information(this, "Ошибка", quer->lastError().text(), QMessageBox::Yes);
            }

         //- Таблица out_operations ---//
            strsql.clear();
            strsql = "create table out_operations(id_out_oper bigint unsigned not null auto_increment primary key, "
                                                 "date_out_oper date not null, "
                                                 "sum_out_oper int not null, "
                                                 "id_branch int unsigned not null, "
                                                 "contract_num varchar(20), "
                                                 "contract_date date, "
                                                 "seller varchar(1000), "
                                                 "goods varchar(1000), "
                                                 "annotation varchar(1000))";
            qDebug() << __FILE__ << __LINE__ << "strsql = " << strsql;
            quer->exec(strsql);
            if (quer->isActive())
            {
                report += "Таблица out_operations создана\n";
            }
            else
            {
                report += "Таблицу out_operations не удалось создать\n";
                report += quer->lastError().text() + "\n";
                QMessageBox::information(this, "Ошибка", quer->lastError().text(), QMessageBox::Yes);
            }

         //- Таблица tickets_out ---//
            strsql.clear();
            strsql = "create table tickets_out(id_tickets_out bigint unsigned not null auto_increment primary key, "
                                              "tickets_out_date date not null, "
                                              "id_branch int unsigned not null, "
                                              "tickets_out_amount int not null, "
                                              "tickets_out_cost int not null, "
                                              "tickets_out_numbers varchar(10000) not null)";
            qDebug() << __FILE__ << __LINE__ << "strsql = " << strsql;
            quer->exec(strsql);
            if (quer->isActive())
            {
                report += "Таблица tickets_out создана\n";
            }
            else
            {
                report += "Таблицу tickets_out не удалось создать\n";
                report += quer->lastError().text() + "\n";
                QMessageBox::information(this, "Ошибка", quer->lastError().text(), QMessageBox::Yes);
            }

         //- Таблица tickets_reports ---//
            strsql.clear();
            strsql = "create table tickets_reports(id_tickets_reports bigint unsigned not null auto_increment primary key, "
                                              "tickets_report_date date not null, "
                                              "id_branch int unsigned not null, "
                                              "tickets_stub_amount int, "
                                              "tickets_stub_numbers varchar(5000), "
                                              "tickets_shortage_amount int, "
                                              "tickets_shortage_numbers varchar(5000), "
                                              "tickets_return_amount int, "
                                              "tickets_return_numbers varchar(5000), "
                                              "tickets_cost int, "
                                              "annotation varchar(1000))";
            qDebug() << __FILE__ << __LINE__ << "strsql = " << strsql;
            quer->exec(strsql);
            if (quer->isActive())
            {
                report += "Таблица tickets_reports создана\n";
            }
            else
            {
                report += "Таблицу tickets_reports не удалось создать\n";
                report += quer->lastError().text() + "\n";
                QMessageBox::information(this, "Ошибка", quer->lastError().text(), QMessageBox::Yes);
            }

         //- Таблица branches ---//
            strsql.clear();
            strsql = "create table branches(id_branch int unsigned not null auto_increment primary key, "
                                           "branch_name varchar(100) not null, "
                                           "director_name varchar(100) not null, "
                                           "address varchar(300), "
                                           "id_location int unsigned)";
            qDebug() << __FILE__ << __LINE__ << "strsql = " << strsql;
            quer->exec(strsql);
            if (quer->isActive())
            {
                report += "Таблица branches создана\n";
            }
            else
            {
                report += "Таблицу branches не удалось создать\n";
                report += quer->lastError().text() + "\n";
                QMessageBox::information(this, "Ошибка", quer->lastError().text(), QMessageBox::Yes);
            }

         //- Таблица locations ---//
            strsql.clear();
            strsql = "create table locations(id_location int unsigned not null auto_increment primary key, "
                                           "location_name varchar(100) not null)";
            qDebug() << __FILE__ << __LINE__ << "strsql = " << strsql;
            quer->exec(strsql);
            if (quer->isActive())
            {
                report += "Таблица locations создана\n";
            }
            else
            {
                report += "Таблицу locations не удалось создать\n";
                report += quer->lastError().text() + "\n";
                QMessageBox::information(this, "Ошибка", quer->lastError().text(), QMessageBox::Yes);
            }

         //- Таблица paid_services ---//
            strsql.clear();
            strsql = "create table paid_services(id_pservice int unsigned not null auto_increment primary key, "
                                                "pservice_name varchar(100) not null, "
                                                "price int)";
            qDebug() << __FILE__ << __LINE__ << "strsql = " << strsql;
            quer->exec(strsql);
            if (quer->isActive())
            {
                report += "Таблица paid_services создана\n";
            }
            else
            {
                report += "Таблицу paid_services не удалось создать\n";
                report += quer->lastError().text() + "\n";
                QMessageBox::information(this, "Ошибка", quer->lastError().text(), QMessageBox::Yes);
            }

         //- Таблица doc_type ---//
            strsql.clear();
            strsql = "create table doc_type(id_doc_type tinyint unsigned not null auto_increment primary key, "
                                           "doc_type varchar(20) not null)";
            qDebug() << __FILE__ << __LINE__ << "strsql = " << strsql;
            quer->exec(strsql);
            if (quer->isActive())
            {
                strsql.clear();
                strsql = "insert into doc_type(doc_type) values(\"билеты\"), (\"договор\")";
                quer->exec(strsql);
                if (quer->isActive())
                {
                    report += "Таблица doc_type создана\n";
                }
                else
                {
                    report += quer->lastError().text() + "\n";
                    QMessageBox::information(this, "Ошибка", quer->lastError().text(), QMessageBox::Yes);
                }
            }
            else
            {
                report += "Таблицу doc_type не удалось создать\n";
                report += quer->lastError().text() + "\n";
                QMessageBox::information(this, "Ошибка", quer->lastError().text(), QMessageBox::Yes);
            }

         //- Таблица customers ---//
            strsql.clear();
            strsql = "create table customers(id_customer int unsigned unsigned not null auto_increment primary key, "
                     "full_name varchar(100), "
                     "abbr_name varchar(100) not null, "
                     "director_position varchar(100), "
                     "director_surname varchar(30), "
                     "director_first_name varchar(30), "
                     "director_father_name varchar(30), "
                     "address varchar(1000), "
                     "tin varchar(30), "
                     "kpp varchar(30), "
                     "bank_account varchar(30), "
                     "cor_account varchar(30), "
                     "bic varchar(10), "
                     "bank_name varchar(100), "
                     "tel varchar(100), "
                     "other varchar(1000))";
            qDebug() << __FILE__ << __LINE__ << "strsql = " << strsql;
            quer->exec(strsql);
            if (quer->isActive())
            {
                report += "Таблица customers создана\n";
            }
            else
            {
                report += "Таблицу customers не удалось создать\n";
                report += quer->lastError().text() + "\n";
                QMessageBox::information(this, "Ошибка", quer->lastError().text(), QMessageBox::Yes);
            }

         //- Таблица users ---//
            strsql.clear();
            strsql = "create table users(login varchar(100) not null primary key, "
                     "position varchar(30), "
                     "surname varchar(30), "
                     "first_name varchar(30), "
                     "father_name varchar(30))";
            qDebug() << __FILE__ << __LINE__ << "strsql = " << strsql;
            quer->exec(strsql);
            if (quer->isActive())
            {
                report += "Таблица users создана\n";
            }
            else
            {
                report += "Таблицу users не удалось создать\n";
                report += quer->lastError().text() + "\n";
                QMessageBox::information(this, "Ошибка", quer->lastError().text(), QMessageBox::Yes);
            }

            settings.setValue("db/name", le_db->text());

            adm_form *af = new adm_form;
            af->show();
            this->hide();

            QMessageBox::information(this, "Результат", report, QMessageBox::Yes);   // вывод отчёта о создании БД и таблиц
        }
        else
        {
            QMessageBox::information(this, "Ошибка", quer->lastError().text(), QMessageBox::Yes);
        }
    }
    else
    {
        QMessageBox::information(this, "Ошибка", quer->lastError().text(), QMessageBox::Yes);
    }

    return 0;
}

