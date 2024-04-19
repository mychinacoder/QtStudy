#include "ClientForm.h"
#include "ui_ClientForm.h"

ClientForm::ClientForm(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::ClientForm)
{
    ui->setupUi(this);
}

ClientForm::~ClientForm()
{
    delete ui;
}

void ClientForm::on_pushButton_clicked()
{

}

