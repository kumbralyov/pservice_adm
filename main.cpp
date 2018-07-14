#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QCoreApplication::setOrganizationName("Kumbralyov");
    QCoreApplication::setApplicationName("PService");

    QApplication a(argc, argv);
    MainWindow w;
//    w.show();
//    w.hide();

    return a.exec();
}
