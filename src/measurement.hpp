#pragma once
#include <QString>
#include <QStringList>
#include <map>

namespace Measurement
{
    enum Type
    {
        MASS,
        LENGTH,
        AREA,
        VOLUME,
        UNITS,
        THICKNESS,
        LAYER,
        MAX,
    };
    
    inline const std::map<Measurement::Type, QString> inputLabel
    {
        {MASS, "Масса в г"},
        {LENGTH, "Длинна в м"},
        {AREA, "Площадь в дм<sup>2</sup>"},
        {VOLUME,"Объём в литрах(дм<sup>3</sup>)"},
        {UNITS, "Колличество в шт."},
        {THICKNESS, "Толщина в мкм"},
        {LAYER, "Количество слоёв"}
    };
    
    class Measure
    {
    public:
        QString m_shortName;
        QString m_name;
        Type m_type;
        double m_coefficient;
        
        Measure(QString shortName, QString name, Type type, double coef):
        m_shortName(shortName),
        m_name(name),
        m_type(type),
        m_coefficient(coef)
        {}
    };
    
    inline const std::map<QString, Measure> measureMap = {
        {"м", Measure{"м", "метр", LENGTH, 1}},
        {"см", Measure{"см", "сантиметр", LENGTH, 0.01}},
        {"мм", Measure{"мм", "милиметр", LENGTH, 0.001}},
        {"м3", Measure{"м<sup>3</sup>", "метр кубический", VOLUME, 1000}},
        {"дм3", Measure{"дм<sup>3</sup>", "дециметр кубический", VOLUME, 1}},
        {"л", Measure{"л", "литр", VOLUME, 1}},
        {"см3", Measure{"см<sup>3</sup>", "сантиметр кубический", VOLUME, 0.001}},
        {"мл", Measure{"мл", "миллилитр", VOLUME, 0.001}},
        {"м2", Measure{"м<sup>2</sup>", "метр квадратный", AREA, 100}},
        {"см2", Measure{"см<sup>2</sup>", "сантиметр квадратный", AREA, 0.01}},
        {"дм2", Measure{"дм<sup>2</sup>", "дециметр квадратный", AREA, 1}},
        {"мг", Measure{"мг", "миллиграм", MASS, 0.001}},
        {"г", Measure{"г", "грамм", MASS, 1}},
        {"кг", Measure{"кг", "килограмм", MASS, 1000}},
        {"т", Measure{"т", "тонна", MASS, 1000000}},
        {"шт", Measure{"шт", "штук", UNITS, 1}},
        {"мкм", Measure{"мкм", "микрон", THICKNESS, 1}},
        {"слой", Measure{"слой", "слой", LAYER, 1}}
    };
    
    QString getRegExpMeasure(const std::map<QString, Measure> &map);
    
    const QString regExpMeasure { getRegExpMeasure (measureMap) };
    
}
