#include "ClientForm.h"

#include <QApplication>
#include <LoginDialog.h>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    LoginDialog login;

    ClientForm w;
    if(login.exec()){
        w.show();
    }


    return a.exec();
}
