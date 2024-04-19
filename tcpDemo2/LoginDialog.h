#ifndef LOGINDIALOG_H
#define LOGINDIALOG_H

#include <QDialog>
#include <Client.h>
#include <QMessageBox>
#include <QUdpBrocastSender.h>
#include <QUdpSocket>
#include <QHostAddress>



namespace Ui {
class LoginDialog;
}

class LoginDialog : public QDialog
{
    Q_OBJECT

public:
    explicit LoginDialog(QWidget *parent = nullptr);
    ~LoginDialog();
    QString userName = "";
    QString PassWord = "";
    QString flag = "";

private slots:
    void on_pbnLogin_clicked();

    void on_pbnExit_clicked();


private:
    Ui::LoginDialog *ui;
    Client *m_client = nullptr;
    QUdpBrocastSender *m_QUdpBrocastSender = nullptr;
    QUdpSocket *m_QUdpSocket = nullptr;
};

#endif // LOGINDIALOG_H
