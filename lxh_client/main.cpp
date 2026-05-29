#include <AuthWindow.h>
#include <mainwindow.h>
#include <statistic.h>
#include <clientfunctions.h>
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    AuthWindow authw;
    MainWindow mainw;
    //StatWindow statw;
    if (load_setting("login") == "-1") {
        authw.show();
    }
    else {
        //statw.show();
        mainw.show();
    }
    return a.exec();
}
