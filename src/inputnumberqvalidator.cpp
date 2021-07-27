#include "inputnumberqvalidator.hpp"

InputNumberQValidator::InputNumberQValidator(QObject *parent) : QValidator(parent)
{}

QValidator::State InputNumberQValidator::validate(QString& input, int& pos) const
{
    bool hasDecimalSeparator = false;
    QString::const_iterator itr;
    for (itr = input.begin(); itr != input.end(); ++itr)
    {
        QChar letter = *itr;
        if(letter.isDigit())
        {
            continue;
        }
        else if ( !hasDecimalSeparator && (letter == QChar('.') || letter == QChar(',')) )
        {
            if (itr + 1 == input.end() )
            {
                return QValidator::State::Intermediate;
            }
            hasDecimalSeparator = true;
            continue;
        }
        return QValidator::State::Invalid;
    }
    return QValidator::State::Acceptable;
}

