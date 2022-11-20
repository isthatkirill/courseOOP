#ifndef RADIO_H
#define RADIO_H

#include <QString>
#include <QtAlgorithms>

class Radio {
 private:
    QString nominal = "";
    QString type = "";
    QString comment = "";
    QString country = "";
    QString year = "";

 public:

    Radio();

    explicit Radio(QString nominal, QString type, QString comment, QString country, QString year);

    Radio(const Radio &arg);

    Radio &operator=(const Radio &arg);

    Radio(Radio &&arg) noexcept;

    Radio &operator=(Radio &&arg) noexcept;

    virtual ~Radio();

    QString &operator[](int i);

    void clear();

    explicit operator bool();

    void setNominal(QString arg);

    const QString &getNominal();

    void setType(QString arg);

    const QString &getType();

    void setCountry(QString arg);

    const QString &getCountry();

    void setArt(QString arg);

    const QString &getArt();

    void setComment(QString arg);

    const QString &getComment();

    friend void swap(Radio &first, Radio &second) noexcept;
};

#endif // RADIO_H
