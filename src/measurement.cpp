#include "measurement.hpp"

using namespace Measurement;


QString  Measurement::getRegExpMeasure(const std::map<QString, Measure>& map)
{
    QStringList stringList;
    for(auto &it: map)
    {
        stringList.append(it.first);
    }
    return stringList.join("|");
}

//Measurement::regExpMeasure = getRegExpMeasure (measureMap);

