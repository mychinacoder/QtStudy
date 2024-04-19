#ifndef MAINUDP_H
#define MAINUDP_H

#include <QWidget>
#include <QUdpSocket>
#include <QUdpBrocastSender.h>
#include <QDebug>
#include <QNetworkDatagram>



QT_BEGIN_NAMESPACE
namespace Ui {
class mainUdp;
}
QT_END_NAMESPACE

class mainUdp : public QWidget
{
    Q_OBJECT

public:
    mainUdp(QWidget *parent = nullptr);
    ~mainUdp();
    void dealMessage();//处理对方发来的消息
protected:
    //事件过滤器

private slots:
    void on_pbnSend_clicked();

private:
    Ui::mainUdp *ui;
    QUdpSocket *m_udpsocket = nullptr;
    QUdpBrocastSender* udpBrocastSender = nullptr;
    QNetworkDatagram *m_networkDatagram = nullptr;
};
#endif // MAINUDP_H
