#define CATCH_CONFIG_MAIN
#include "catch2/catch.hpp"
#include "../src/parser.hpp"


TEST_CASE("Парсинг")
{
    auto testparser = new Parser();
    testparser->parseLine("Техпроцесс Первый и главный");
    testparser->parseLine("Какой-либо коментарий");
    testparser->parseLine("005 Особенная операция");
    testparser->parseLine("Сурик свинцовый ГОСТ 19151-73    0,7г/дм2");
    testparser->parseLine("Калия бихромат технический ГОСТ 2652-78   15мг/дм2(площадь покрытия)* мкм(толщина покрытия)");
    testparser->parseLine("Еще один комментарий");
    testparser->parseLine("010 Простая операция");
    testparser->parseLine("Парафин нефтяной ГОСТ 23683-89   1.5г/кг(масса тары)");
    testparser->parseLine("Техпроцесс Второй");
    testparser->parseLine("005 Новая операция");
    testparser->parseLine("Олифа натуральная сорт высший ГОСТ 7931-76   0,2мл/м2");
    testparser->parseLine("или");
    testparser->parseLine("Олифа оксоль марки В ГОСТ 190-78   0,25мл/м2");
    
    auto techlist = testparser->getResult();
    auto firstTechOperations = techlist[0].getOperations();
    auto secondTechOperations = techlist[1].getOperations();
    
    SECTION("Парсинг техпроцессов")
    {
        REQUIRE(techlist.size() == 2);
        REQUIRE(QString("Первый и главный") == techlist[0].getName());
        REQUIRE(QString("Второй") == techlist[1].getName());
    }
    
    SECTION("Парсинг операций")
    {
        REQUIRE(QString("005 Особенная операция") == firstTechOperations[0]->getName());
        REQUIRE(firstTechOperations.size() == 2);    
        REQUIRE(secondTechOperations.size() == 1);
    }
    
    SECTION("Парсинг материалов")
    {
        std::vector<QString> material1{"Сурик свинцовый ГОСТ 19151-73", "грамм", "дециметр квадратный", "0.7"};
        REQUIRE(material1 == firstTechOperations[0]->getMaterial(0));
        std::vector<QString> material2{"Парафин нефтяной ГОСТ 23683-89", "грамм", "килограмм", "1.5", "(масса тары)"};
        REQUIRE(material2 == firstTechOperations[1]->getMaterial(0));
        std::vector<QString> material3{"Олифа натуральная сорт высший ГОСТ 7931-76", "миллилитр", "метр квадратный", "0.2",
            "Олифа оксоль марки В ГОСТ 190-78", "миллилитр", "метр квадратный", "0.25"};
        REQUIRE(material3 == secondTechOperations[0]->getMaterial(0));
        std::vector<QString> material4{"Калия бихромат технический ГОСТ 2652-78", "миллиграм", "дециметр квадратный", "15",
            "(площадь покрытия)", "микрон", "1", "(толщина покрытия)"};
        REQUIRE(material4 == firstTechOperations[0]->getMaterial(1));
        
    }
}
