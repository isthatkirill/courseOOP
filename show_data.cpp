#include "show_data.h"
#include "ui_show_data.h"
#include "QPushButton"

Show_Data::Show_Data(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Show_Data)
{
    ui->setupUi(this);
    setWindowIcon(QIcon(":/images/icons/radio.png"));
}

void Show_Data::setText(const QString &str) {
    ui->textEdit->setText(str);
}

QString Show_Data::getText() {
    return ui->textEdit->toPlainText();
}

Show_Data::~Show_Data()
{
    delete ui;
}

void Show_Data::on_pushButton_clicked()
{
    this->close();
}
