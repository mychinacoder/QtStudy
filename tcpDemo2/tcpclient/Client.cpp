#include "Client.h"
#include <QDebug>

Client::Client(QObject *parent)
    : QObject{parent}
{
    m_tcpSocket = new QTcpSocket(this);

    connect(m_tcpSocket, &QTcpSocket::connected, this, [this](){

        QString peerAdress = m_tcpSocket->peerAddress().toString();
        quint16 port = m_tcpSocket->peerPort();
        QString sendString = QString("当前为:%1,%2连接测试消息").arg(peerAdress).arg(port);
        m_tcpSocket->write(sendString.toUtf8());
                                                 });

    connect(m_tcpSocket, &QTcpSocket::readyRead, this, [this](){
       // QString peerAdress = m_tcpSocket->peerAddress().toString();
       // quint16 port = m_tcpSocket->peerPort();

       // QByteArray receiversArray = m_tcpSocket->readAll();

        //QString sendString = QString("%1,%2:%3").arg(peerAdress).arg(port).arg(receiversArray.data());
       // qDebug()<<receiversArray<< sendString;
        //qDebug()<<m_tcpSocket->write(sendString.toUtf8());
    });

    connect(m_tcpSocket, &QTcpSocket::disconnected, this, [this](){
        QString peerAdress = m_tcpSocket->peerAddress().toString();
        quint16 port = m_tcpSocket->peerPort();
        QString sendString = QString("当前为:%1,%2连接断开消息").arg(peerAdress).arg(port);
        m_tcpSocket->write(sendString.toUtf8());
    });
}

void Client::tcpSocketDisconnected()
{
    if(NULL == m_tcpSocket)
    {
        return;
    }
    m_tcpSocket->disconnectFromHost();
    m_tcpSocket->close();
    delete m_tcpSocket;
}
