#ifndef SERVER_H
#define SERVER_H

#include <QObject>
#include <QTcpServer>
#include <QTcpSocket>
#include <QHostAddress>

class Server : public QObject
{
    Q_OBJECT
public:
    explicit Server(QObject *parent = nullptr);

signals:

private:
    QTcpServer *m_tcpServer = nullptr;
    QTcpSocket *m_tcpSocket = nullptr;
};

#endif // SERVER_H
