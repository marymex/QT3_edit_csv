#include "dialog.h"
#include "ui_dialog.h"

Dialog::Dialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Dialog)
{
    ui->setupUi(this);
}

Dialog::~Dialog()
{
    delete ui;
}

void Dialog::on_buttonBox_accepted()
{
    value =  ui->lineEdit->text();
    ui->lineEdit->setText("");
    //ui->isChanged = true;
    this->close();
    emit valueChanged();
}


void Dialog::on_buttonBox_rejected()
{
    ui->lineEdit->setText("");
    //ui->isChanged = false;

    this->close();
    emit firstWindow();

}

