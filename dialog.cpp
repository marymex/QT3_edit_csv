#include "dialog.h"
#include "ui_dialog.h"
#include "mainwindow.h"

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
    *MainWindow::changedData = ui->lineEdit->text();
    ui->lineEdit->setText("");
    this->close();

}


void Dialog::on_buttonBox_rejected()
{
    ui->lineEdit->setText("");
    this->close();
}

