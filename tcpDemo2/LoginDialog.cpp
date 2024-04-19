#include "LoginDialog.h"
#include "ui_LoginDialog.h"
#include <QLocalSocket>



LoginDialog::LoginDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::LoginDialog)
{
    ui->setupUi(this);
    m_client = new Client(this);
    m_QUdpBrocastSender = new QUdpBrocastSender(this);
    m_QUdpSocket = new QUdpSocket(this);


    ui->ldtUsername->setText("user1");
    ui->ldtPassword->setText("12345678");

    m_QUdpSocket->bind(QHostAddress::Any,m_QUdpBrocastSender->port());

    connect(m_QUdpSocket, &QUdpSocket::readyRead, this, [=]() {
        while (m_QUdpSocket->hasPendingDatagrams()) {
            QByteArray datagram;
            datagram.resize(m_QUdpSocket->pendingDatagramSize());
            QHostAddress sender;
            quint16 senderPort;

            m_QUdpSocket->readDatagram(datagram.data(), datagram.size(), &sender, &senderPort);

            qDebug() << "Received UDP message from: " << sender.toString();
        }
    });

}

LoginDialog::~LoginDialog()
{
    delete ui;
}

void LoginDialog::on_pbnLogin_clicked()
{
    m_client->m_tcpSocket->waitForConnected(5000);


    m_QUdpBrocastSender->setData("111111");




    quint16 receivePort = m_QUdpBrocastSender->port();


    QString receiveAdress = m_QUdpSocket->peerAddress().toString();


    //m_client->m_tcpSocket->connectToHost("192.168.1.2",8888);

    m_client->m_tcpSocket->connectToHost(receiveAdress,9527);

    //m_client->m_tcpSocket->connectToHost("127.0.0.1",9527);




    m_client->m_tcpSocket->waitForBytesWritten();

    QString loginiIformation = "Login\nuser1\n12345678\n";

    qDebug()<<m_client->m_tcpSocket->write(loginiIformation.toUtf8()) << loginiIformation;


    m_client->m_tcpSocket->waitForReadyRead();
    QByteArray receiversMessage = m_client->m_tcpSocket->readAll();


    qDebug() <<receiversMessage;

    QList<QByteArray> userInfoList = receiversMessage.split('\n');

    for (int i = 0; i < userInfoList.count(); ++i) {
        //flag = userInfoList.value(0);
        userName = userInfoList.value(0);

        PassWord = userInfoList.value(1);
    }
    qDebug()<<userInfoList;
    //if (userName == ui->ldtUsername->text() && PassWord == ui->ldtPassword->text())
    if( "success" == userInfoList.value(1) ||  "Login" == userInfoList.value(0))
    {
        this->accept();
    }else{
        this->reject();
        QMessageBox::warning(0,tr("提示"),"用户名或者密码不正确,请确认后重新输入!");
        ui->ldtUsername->setText("");
        ui->ldtPassword->setText("");
        ui->ldtUsername->setFocus();
    }

}


void LoginDialog::on_pbnExit_clicked()
{
    if(NULL == m_client->m_tcpSocket){
        return;
    }
    m_client->tcpSocketDisconnected();
}

