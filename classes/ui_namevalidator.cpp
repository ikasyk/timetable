#include "ui_namevalidator.h"

UI_NameValidator::UI_NameValidator(QObject *parent, bool nb) :QValidator(parent), numberic(nb) {};

UI_NameValidator::State UI_NameValidator::validate(QString &input, int &pos) const {
    QRegExp checker = numberic ? QRegExp("[^a-zA-Zа-яА-ЯїЇґҐёЁіІ\'єЄ\\- ]") :
                                 QRegExp("[^0-9a-zA-Zа-яА-ЯїЇґҐёЁіІ\'єЄ\\- ]");
    if (input.contains(checker))
        return Invalid;
    return Acceptable;
}
