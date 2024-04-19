#include "mainudp.h"
#include "ui_mainudp.h"

#include <QTime>
#include <QHostAddress>




mainUdp::mainUdp(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::mainUdp)
{
    ui->setupUi(this);
    //连接到对方,也就是服务器的IP地址与端口
    // ui->ldtIpAdress->setText("192.168.1.88");
    ui->ldtIpPort->setText("9527");

    this->setWindowTitle(QString("UDPDemo--服务器端口: %1").arg(ui->ldtIpPort->text()));

    m_networkDatagram = new QNetworkDatagram;
    //1.实例化对象
    m_udpsocket = new QUdpSocket(this);

    //2.绑定端口
    //m_udpsocket->bind(QHostAddress::Any,ui->ldtIpPort->text().toInt());

    if(!m_udpsocket->bind(9527, QUdpSocket::ShareAddress))
    {
        ui->pltMessageShow->appendPlainText("bind failed !");
    }
    //3.处理对方发来的消息,收到消息以后,自动触发readyread,

        connect(m_udpsocket, &QUdpSocket::readyRead, this, [=](){


            //如果有数据
            while(m_udpsocket->hasPendingDatagrams())
            {
                QNetworkDatagram datagram = m_udpsocket->receiveDatagram();

                QByteArray data = datagram.data();

                QHostAddress adress = datagram.senderAddress();
                quint16 port = datagram.senderPort();
                m_udpsocket->readDatagram(data.data(), data.size(), &adress, &port);

                QString text = QString("[%1:%2]:%3").arg(adress.toString()).arg(port).arg(QString(data));

                ui->pltMessageShow->appendPlainText(text);
                ui->pltMessageShow->appendPlainText(QString("serveriP:%1,serverPort:%2").arg(adress.toString()).arg(port));
            }

        });

    ui->pbnSend->setFocus();
    ui->pbnSend->setDefault(true);

    //UDP读取广播,获取IP地址和端口


    //on_pbnSend_clicked();
    // udpBrocastSender = new QUdpBrocastSender(this);
    // udpBrocastSender->setPort(9527);
    // udpBrocastSender->setData("this is test for 9527");
    // udpBrocastSender->setInterval(6000);


}

mainUdp::~mainUdp()
{
    delete ui;
    delete udpBrocastSender;
    udpBrocastSender = nullptr;
}

void mainUdp::dealMessage()
{
    //设定每次读取的内容大小
    char buf[1024] = { 0 };
    //对方的IP地址
    //QHostAddress  clientAddress = QHostAddress("");
    QHostAddress  clientAddress = m_udpsocket->peerAddress();
    //对方端口
    qint16 port = m_udpsocket->peerPort();

    //1.获取读取到的数据长度,UDP数据报

    qint64 messageLength = m_udpsocket->readDatagram(buf, sizeof(buf));

    //2获取当前系统时间
    QTime currentTime = QTime::currentTime();
    QString timeInfomation = currentTime.toString("hh:mm:ss");
    //3.如果获取到数据
    if(messageLength > 0) {
        QString message = QString("[对方端口:%1] %2:%3")
                              .arg(port)
                              .arg(timeInfomation)
                              .arg(buf);
        ui->pltMessageShow->appendPlainText(message);
        qDebug()<<clientAddress;

    }


}

void mainUdp::on_pbnSend_clicked()
{
    //对方IP
    QString ipAdress = ui->ldtIpAdress->text();
    //对方端口
    qint16 port = ui->ldtIpPort->text().toInt();
    //要发送内容
    QString sendMessagexInformation = ui->pteSend->toPlainText();
    if(sendMessagexInformation == "") return;
    //写入数据
    //QByteArray data = sendMessagexInformation.toLatin1();
    m_udpsocket->writeDatagram(sendMessagexInformation.toLatin1().data(), sendMessagexInformation.length(), QHostAddress(ipAdress), port);

    // 清空txt;
    //ui->pltMessageShow->appendPlainText(QString("[ip:%1,port:%2]:%3;").arg(ipAdress).arg(port).arg(sendMessagexInformation));
    ui->pteSend->setPlainText("");


}

