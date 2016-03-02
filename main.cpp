#include "mainwindow.h"
#include <QApplication>
#include <QtPlugin>
#ifdef _WIN32
Q_IMPORT_PLUGIN(QWindowsIntegrationPlugin);
#endif
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    w.setFixedWidth(370);
    return a.exec();
}
