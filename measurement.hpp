#pragma once
#include <QString>
#include <QStringList>

#include <QMap>
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
        MAX,
    };
    
    class Measure
    {
    public:
        const char *m_shortName;
        Measure(const char *shortName, QString name, Type type, double coef):
        m_shortName(shortName),
        m_name(name),
        m_type(type),
        m_coefficient(coef)
        {}
        
    private:
        QString m_name;
        Type m_type;
        double m_coefficient;
    };
    
    const std::map<QString, Measure> measureMap = {
        {"м", Measure{"м", "метр", LENGTH, 1}},
        {"см", Measure{"см", "сантиметр", LENGTH, 0.01}},
        {"мм", Measure{"мм", "милиметр", LENGTH, 0.001}},
        {"м3", Measure{"м3", "метр кубический", VOLUME, 1}},
        {"дм3", Measure{"дм3", "дециметр кубический", VOLUME, 0.001}},
        {"л", Measure{"л", "литр", VOLUME, 0.001}},
        {"см3", Measure{"см3", "сантиметр кубический", VOLUME, 0.000001}},
        {"мл", Measure{"мл", "миллилитр", VOLUME, 0.000001}},
        {"м2", Measure{"м2", "метр квадратный", AREA, 1}},
        {"см2", Measure{"см2", "сантиметр квадратный", AREA, 0.0001}},
        {"дм2", Measure{"дм2", "дециметр квадратный", AREA, 0.01}},
        {"мг", Measure{"мг", "миллиграм", MASS, 0.000001}},
        {"г", Measure{"г", "грам", MASS, 0.001}},
        {"кг", Measure{"кг", "килограм", MASS, 1}},
        {"т", Measure{"т", "тонна", MASS, 1000}},
        {"шт", Measure{"шт", "штук", UNITS, 1}}
    };
    
    QString getRegExpMeasure(const std::map<QString, Measure> &map);
    
    const QString regExpMeasure  = getRegExpMeasure (measureMap);
    
}
