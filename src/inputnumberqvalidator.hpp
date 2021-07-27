#pragma once

#include <QValidator>

class InputNumberQValidator : public QValidator
{
    Q_OBJECT
public:
    explicit InputNumberQValidator(QObject *parent = nullptr);
    virtual QValidator::State validate(QString &input, int &pos) const;
};

