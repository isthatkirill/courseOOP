#ifndef ADD_DIALOG_H
#define ADD_DIALOG_H

#include <QDialog>
#include "Radio.h"

namespace Ui {
    class Add_Dialog;
}

class Add_Dialog : public QDialog
{
    Q_OBJECT

public:

    explicit Add_Dialog(QWidget *parent = nullptr);
    ~Add_Dialog();
    Radio getData();
    void setType(QString arg);
    void setNominal(QString arg);
    void setCountry(QString arg);
    void setComment(QString arg);
    void setArt(QString arg);

private:
    Ui::Add_Dialog *ui;
};

#endif // ADD_DIALOG_H
