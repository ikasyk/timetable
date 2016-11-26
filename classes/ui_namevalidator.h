#ifndef UI_NAMEVALIDATOR_H
#define UI_NAMEVALIDATOR_H

#include <QtWidgets>

class UI_NameValidator : public QValidator {
    bool numberic;
public:
    UI_NameValidator(QObject*, bool=false);
    virtual State validate(QString&, int &pos) const;
};

#endif // UI_NAMEVALIDATOR_H
