#ifndef CLIENTFORM_H
#define CLIENTFORM_H

#include <QWidget>

QT_BEGIN_NAMESPACE
namespace Ui {
class ClientForm;
}
QT_END_NAMESPACE

class ClientForm : public QWidget
{
    Q_OBJECT

public:
    ClientForm(QWidget *parent = nullptr);
    ~ClientForm();

private slots:
    void on_pushButton_clicked();

private:
    Ui::ClientForm *ui;
};
#endif // CLIENTFORM_H
