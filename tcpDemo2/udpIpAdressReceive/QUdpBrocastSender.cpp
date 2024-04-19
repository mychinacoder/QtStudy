#include "QUdpBrocastSender.h"

#include <QTimerEvent>

QUdpBrocastSender::QUdpBrocastSender(QObject *parent)
    : QObject{parent}
{
    m_timerId = startTimer(m_interval);
    m_brocastSocket = new QUdpSocket(this);
}

int QUdpBrocastSender::interval() const
{
    return m_interval;
}

void QUdpBrocastSender::setInterval(int newInterval)
{
    m_interval = newInterval;
    if(m_timerId > 0)
    {
        killTimer(m_timerId);
        m_timerId = startTimer(m_interval);
    }
}

quint16 QUdpBrocastSender::port() const
{
    return m_port;
}

void QUdpBrocastSender::setPort(quint16 newPort)
{
    m_port = newPort;
}

QByteArray QUdpBrocastSender::data() const
{
    return m_data;
}

void QUdpBrocastSender::setData(const QByteArray &newData)
{
    m_data = newData;
}

void QUdpBrocastSender::timerEvent(QTimerEvent *event)
{
    if(m_timerId == event->timerId())
    {
        m_brocastSocket->writeDatagram(m_data, QHostAddress::Any, m_port);
    }
}
