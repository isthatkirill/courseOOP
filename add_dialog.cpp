#include "add_dialog.h"
#include "ui_add_dialog.h"
#include "QPushButton"

Add_Dialog::Add_Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Add_Dialog)
{
    ui->setupUi(this);
    setFixedSize(size());

    ui->buttonBox->button(QDialogButtonBox::Ok)->setText("OK");
    ui->buttonBox->button(QDialogButtonBox::Cancel)->setText("Отмена");
    setWindowIcon(QIcon(":/images/icons/radio.png"));
}

Add_Dialog::~Add_Dialog()
{
    delete ui;
}

void Add_Dialog::setType(QString arg) {
    ui->lineEdit->setText(arg);
}

void Add_Dialog::setNominal(QString arg) {
    ui->lineEdit_2->setText(arg);
}

void Add_Dialog::setCountry(QString arg) {
    ui->lineEdit_3->setText(arg);
}

void Add_Dialog::setComment(QString arg) {
    ui->lineEdit_4->setText(arg);
}

void Add_Dialog::setArt(QString arg) {
    ui->lineEdit_5->setText(arg);
}

Radio Add_Dialog::getData() {
    Radio result;
    result.setType(ui->lineEdit->text().simplified().replace(";", ","));
    result.setNominal(ui->lineEdit_2->text().simplified().replace(";", ","));
    result.setCountry(ui->lineEdit_3->text().simplified().replace(";", ","));
    result.setComment(ui->lineEdit_4->text().simplified().replace(";", ","));
    result.setArt(ui->lineEdit_5->text().simplified().replace(";", ","));
    return result;
}
