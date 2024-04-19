#ifndef QUDPBROCASTSENDER_H
#define QUDPBROCASTSENDER_H

#include <QObject>
#include <QUdpSocket>

class QUdpBrocastSender : public QObject
{
    Q_OBJECT
public:
    explicit QUdpBrocastSender(QObject *parent = nullptr);

    int interval() const;
    void setInterval(int newInterval);

    quint16 port() const;
    void setPort(quint16 newPort);

    QByteArray data() const;
    void setData(const QByteArray &newData);

signals:

private:
    quint16 m_port = 20000;
    QByteArray m_data = "";
    int m_interval = 5000;

    int m_timerId = 0;
    QUdpSocket* m_brocastSocket = nullptr;

protected:
    void timerEvent(QTimerEvent *event) override;
};

#endif // QUDPBROCASTSENDER_H
