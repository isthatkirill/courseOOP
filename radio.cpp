#include "Radio.h"
#include <QtAlgorithms>

Radio::Radio() {}

Radio::Radio(QString nominal, QString type, QString comment, QString country, QString year)
    : nominal(nominal), type(type), comment(comment), country(country), year(year) {

}

Radio::Radio(const Radio &arg) : Radio(arg.nominal, arg.type, arg.comment, arg.country, arg.year) {

}

Radio & Radio::operator=(const Radio &arg) {
    Radio temp(arg);
    swap(*this, temp);
    return *this;
}

Radio::Radio(Radio &&arg) noexcept {
    nominal = std::move(arg.nominal);
    type = std::move(arg.type);
    country = std::move(arg.country);
    year = std::move(arg.year);
    comment = std::move(arg.comment);
    arg.nominal = arg.type = arg.comment = arg.country = arg.year = "";
}

Radio & Radio::operator=(Radio &&arg) noexcept {
    if (this != &arg) {
        swap(*this, arg);
        arg.nominal = arg.type = arg.comment = arg.country = arg.year = "";
    }
    return *this;
}

Radio::~Radio() {}


void Radio::clear() {
    nominal = type = comment = country = year = "";

}

Radio::operator bool() {
    return !nominal.isEmpty() || !type.isEmpty() || !comment.isEmpty() || !country.isEmpty() || !year.isEmpty();
}

void Radio::setNominal(QString arg) {
    nominal = arg;
}

const QString & Radio::getNominal() {
    return nominal;
}

void Radio::setCountry(QString arg) {
    country = arg;
}

const QString & Radio::getCountry() {
    return country;
}

void Radio::setArt(QString arg) {
    year = arg;
}

const QString & Radio::getArt() {
    return year;
}

void Radio::setType(QString arg) {
    type = arg;
}

const QString & Radio::getType() {
    return type;
}

void Radio::setComment(QString arg) {
    comment = arg;
}

const QString & Radio::getComment() {
    return comment;
}

void swap(Radio &first, Radio &second) noexcept {
    std::swap(first.nominal, second.nominal);
    std::swap(first.type, second.type);
    std::swap(first.year, second.year);
    std::swap(first.country, second.country);
    std::swap(first.comment, second.comment);
}
