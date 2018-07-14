#include "login_form.h"

login_form::login_form(QWidget *parent) : QMainWindow(parent)
{
    frm_cre();
}

login_form::~login_form()
{
    db.close();
}

void login_form::frm_cre()
{
    QGridLayout *gl = new QGridLayout;

    lb_db = new QLabel("База данных");          // надпись "база данных"
    gl->addWidget(lb_db, 0, 0, 1, 1);           // надпись устанавливается в сетку

    le_db = new QLineEdit(settings.value("db/name").toString());   // поле ввода базы данных
    gl->addWidget(le_db, 0, 1, 1, 1);           // поле устанавливается в сетку
    le_db->setFocus();                          // устанавливается фокус на поле ввода логина

    lb_login = new QLabel("Логин");             // надпись "логин"
    gl->addWidget(lb_login, 1, 0, 1, 1);        // надпись устанавливается в сетку

    le_login = new QLineEdit("root");           // поле ввода логина
    gl->addWidget(le_login, 1, 1, 1, 1);        // поле устанавливается в сетку
//    le_login->setFocus();                     // устанавливается фокус на поле ввода логина

    lb_pass = new QLabel("Пароль");             // надпись "пароль"
    gl->addWidget(lb_pass, 2, 0, 1, 1);         // надпись устанавливается в сетку

    le_pass = new QLineEdit;   // поле ввода пароля
    gl->addWidget(le_pass, 2, 1, 1, 1);         // поле устанавливается в сетку
    le_pass->setEchoMode(QLineEdit::Password);  // неотображение пароля на экране
    connect(le_pass, SIGNAL(textEdited(QString)),this,SLOT(le_pass_finish()));   // активизация кнопки ввода после ввода пароля

    pb_conn = new QPushButton("Вход");          // кнопка ввода
    gl->addWidget(pb_conn, 3, 1, 1, 1);         // кнопка устанавливается в сетку
    pb_conn->setEnabled(false);                 // кнопка делается неактивной
    pb_conn->setShortcut(QKeySequence(Qt::Key_Return));   // связь с клавишей return
    connect(pb_conn, SIGNAL(clicked()), this, SLOT(pb_conn_click()));   // вызов функции соединения с базой данных

    QWidget *wgt = new QWidget (this);          // создаётся окно
    wgt->setLayout(gl);                         // устанавливается сетка в окне
    this->setCentralWidget(wgt);
    this->resize(300, 100);
    this->move(200, 200);                       // размеры формы
    this->setTabOrder(le_login, le_pass);       // порядок перрехода по tab
    this->setTabOrder(le_pass, pb_conn);        // порядок перрехода по tab
    this->setWindowTitle("Вход");               // название окна
}


void login_form::adm_form_show()
{
    adm_form *af = new adm_form;
    af->show();
}

int login_form::le_pass_finish()
{
    if (le_pass->text() != "")
        pb_conn->setEnabled(true);    // если в поле ввода введён пароль - кнопка ввода делается активной
    else
        pb_conn->setEnabled(false);   // иначе - неактивной
    return 0;
}

int login_form::pb_conn_click()
{
    db = QSqlDatabase::addDatabase("QMYSQL");   // создаётся база данных

    db.setHostName("localhost");                // название хоста
    db.setPort(3306);                           // номер порта
    db.setDatabaseName(le_db->text());          // название базы данных
    db.setUserName(le_login->text());           // имя пользователя
    db.setPassword(le_pass->text());            // пароль

    if (db.open())
    {
        statusBar()->showMessage("Соединение установлено");   // вывод результата соединения с базой данных в статусную строку
        adm_form_show();
        this->hide();
    }
    else
    {
        statusBar()->showMessage("Соединение не установлено");   // вывод результата соединения с базой данных в статусную строку
    }
    return 0;
}
