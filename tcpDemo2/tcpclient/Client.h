#ifndef CLIENT_H
#define CLIENT_H

#include <QObject>
#include <QTcpSocket>
#include <QHostAddress>



class Client : public QObject
{
    Q_OBJECT
public:
    explicit Client(QObject *parent = nullptr);
    void tcpSocketDisconnected();

    QTcpSocket *m_tcpSocket = nullptr;

signals:
private:

};

#endif // CLIENT_H
