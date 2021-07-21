#include <QFile>
#include <QTextStream>
#include <QDir>

#include <QMessageBox>

#include "techprocess.hpp"
#include "parser.hpp"


const QRegularExpression Parser::m_techprocessRegExp{"^\\s*техпроцесс\\s+(.+)\\s*$", QRegularExpression::CaseInsensitiveOption};

Parser::Parser(const QString& directory):Parser()
{
    scanDir(directory);
}

Parser::Parser()
{
    const QString rx = 
    "^\\s*(?<name>.+?)\\s+(?<number>\\d+[,\\.]?\\d*)\\s{0,6}(?<measure1>"
    + Measurement::regExpMeasure + 
    ")\\s{0,3}\\/\\s{0,3}(?<measure2>"
    + Measurement::regExpMeasure + 
    ")\\s{0,4}(?<special1>\\(.{2,20}\\))?(\\s{0,4}[\\*\\/]\\s{0,4}(?<number1>\\d+[,\\.]?\\d*)?\\s{0,4}(?<measure3>"
    + Measurement::regExpMeasure +
    ")\\s{0,3}(?<special2>\\(.{2,30}\\))?)?\\s*$";
    m_materialLine.setPattern(rx);
    m_materialLine.setPatternOptions(QRegularExpression::CaseInsensitiveOption);
}


void Parser::scanDir(const QString& directory)
{
    QDir dir = QDir(directory);
    dir.setFilter(QDir::NoDotAndDotDot | QDir::Files);
    if (!dir.exists())
    {
        setDemoMode();
        return;
    }
    QFileInfoList list = dir.entryInfoList();
    QFileInfoList::const_iterator constIterator;
    for (constIterator = list.constBegin(); constIterator != list.constEnd(); ++constIterator)
    {
        QFile file(constIterator->absoluteFilePath());
        if (!(file.open(QIODevice::ReadOnly | QIODevice::Text)))
        {
            continue;
        }
        QTextStream in(&file);
        while (!in.atEnd())
        {
            parseLine(in.readLine());
        }
        previous = NONE;
        m_initTechprocess = false;
    }
    if (techlist.size() == 0)
    {
        setDemoMode();
    }
}

void Parser::addNewTech()
{
    techlist.emplace_back(Techprocess(m_lastMatch.captured(1)));
    m_initTechprocess = true;
}


void Parser::addNewOperation(const QString &operation)
{
    techlist.back().addOperation(operation);
}

MaterialEntry* Parser::getMaterial()
{
    double expenseNumber1 = getNumber(m_lastMatch.captured("number"));
    if (m_lastMatch.captured("measure3").isEmpty())
    {
        return new MaterialEntry(
            m_lastMatch.captured("name"),
            expenseNumber1,
            Measurement::measureMap.at(m_lastMatch.captured("measure1")),
            m_lastMatch.captured("special1"),
            Measurement::measureMap.at(m_lastMatch.captured("measure2"))
        );
    }
    else
    {
        double expenseNumber2;
        if(m_lastMatch.captured("number1").isEmpty())
        {
            expenseNumber2 = 1;
        }
        else
        {
            expenseNumber2 = getNumber(m_lastMatch.captured("number1"));;
        }
        return new MaterialEntry(
            m_lastMatch.captured("name"),
            expenseNumber1,
            Measurement::measureMap.at(m_lastMatch.captured("measure1")),
            m_lastMatch.captured("special1"),
            Measurement::measureMap.at(m_lastMatch.captured("measure2")),
            m_lastMatch.captured("special2"),
            expenseNumber2,
            Measurement::measureMap.at(m_lastMatch.captured("measure3"))
        );
    }
}

double Parser::getNumber(QString number)
{
    int pos = number.indexOf(',');
    if(pos != -1)
    {
        number[pos] = '.';
    }
    return number.toDouble();
}


void Parser::addNewMatetial()
{
    techlist.back().addMaterial(getMaterial());
}


bool Parser::isTechprocess(const QString& techprocess)
{
    m_lastMatch = m_techprocessRegExp.match(techprocess);
    if(m_lastMatch.hasMatch())
        return true;
    else
        return false;
}

bool Parser::isOperation (const QString &operation)
{
        if ((operation[0].isDigit())&&
            (operation[1].isDigit())&&
            (operation[2].isDigit())&&
            operation[3] == ' ')
            return true;
        else
            return false;
}

bool Parser::isMaterialDefinition(const QString &material)
{
    m_lastMatch = m_materialLine.match(material);
    if(m_lastMatch.hasMatch())
    {
        return true;
    }
    else
    {
        return false;
    }
}
                
void Parser::parseLine(const QString &line)
{
    //для инициализации техпроцесса необходимо ключевое слово "техпроцесс"
    if (isTechprocess(line))
    {
        addNewTech();
        previous = TECHPROCESS;
    }
    //если техпроцесс не инициализирован, то все строки ситаются просто комментариями
    else if (!m_initTechprocess)
    {
        previous = NONE;
    }
    //если строка пустая, то ничего не делается
    else if (line.isEmpty())
    {}
    //проверка является ли стока объявлением операции
    else if (isOperation(line))
    {
        addNewOperation(line);
        previous = OPERATION;
    }
    //провеключевого слова ИЛИ
    else if (previous == OR_MATERIAL)
    {
        if(isMaterialDefinition(line))
        {
            addNewMatetial();
            previous = MATERIAL;
        }
        else
        {
            previous = NONE;
        }
    }
    //проверка ключевого слова "или", работает только если приведущей записью был материал
    else if (line.compare("или", Qt::CaseInsensitive) == 0 && previous == MATERIAL) //возможно стоит убирать пробелы
    {
        previous = OR_MATERIAL;
        //на следующем шаге  которая запоминается как допустимая замена приведущей
    }
    //проверка является ли стока определением материала
    else if (isMaterialDefinition(line))
    {
        addNewMatetial();
        previous = MATERIAL;
    }
    else
    {
        previous = NONE;
    }
}

std::vector<Techprocess> Parser::getResult ()
{
    return std::move(techlist);
}

void Parser::setDemoMode()
{
    std::vector<QString> demoText {
        "Техпроцесс Окрашивание (демострация)",
        "005 Обезжиривание",
        "Уайт-спирит ГОСТ 3134-78  0,6мл/дм2",
        "Бязь ГОСТ 29298-2005  0,5 дм2/дм2",
        "010 Грунтование",
        "Грунтовка АК-070 ГОСТ 25718-83   0,2г/дм2",
        "015 Окраска",
        "Эмаль ЭП-51 ГОСТ 9640-85    0,3г/дм2",
        "Техпроцесс Оловинирование (демострация)",
        "005 Травление",
        "Кислота серная ГОСТ 4204-77 0,3 г/дм2",
        "Уротропин  ГОСТ 1381-73 0,02 г/дм2",
        "010 Никелирование",
        "Никель сернокислый  ГОСТ 4465-2016   0,42 г/дм2 * мкм (толщина никелевого подслоя)",
        "Натрий хлористый   ГОСТ 4233-77    0,2 г/дм2 * мкм (толщина никелевого подслоя)",
        "Борная кислота   ГОСТ 9656-75  0,05 г/дм2 * мкм (толщина никелевого подслоя)",
        "Аноды никелевые МД НПА1  ГОСТ 2132-2015   0,72 г/дм2 * мкм (толщина никелевого подслоя)",
        "015 Оловинирование",
        "Олово хлористое ГОСТ 36-78 0,6 г/дм2 * мкм (толщина оловяного покрытия)",
        "Кислота соляная ГОСТ 857-95 0,02 г/дм2 * мкм (толщина оловяного покрытия)",
        "Аноды оловянные ГОСТ 860-75 0,9г/дм2 * мкм (толщина оловяного покрытия)"
    };
    for(auto &line: demoText)
    {
        parseLine(line);
    }
    QString message ("Технологических данных не обнаружено, программа запущена демонстрационном режиме.");
    QMessageBox demoMsgBox;
    demoMsgBox.setText(message);
    demoMsgBox.exec(); 
    
}

