#include <QFile>
#include <QTextStream>
#include <QDir>

#include "techprocess.hpp"
#include "parser.hpp"

#include <iostream>


Parser::Parser(const QString& directory)
{
    //регулярное выражение чтобы вычленять данные по операциям
    QString rx = 
    "^ *(.+) +(\\d+[,\\.]?\\d*) {0,5}("
    + Measurement::regExpMeasure + ")\\/("
    + Measurement::regExpMeasure + ") *$";
    //m_materialLine.setPatternSyntax(QRegExp::RegExp2);
    m_materialLine.setPattern(rx);
    m_materialLine.setCaseSensitivity(Qt::CaseInsensitive);
    scanDir(directory);
}

void Parser::scanDir(const QString& directory)
{

    QDir dir = QDir(directory);
    dir.setFilter(QDir::NoDotAndDotDot | QDir::Files);
    if (!dir.exists())
    {
        return;
    }
    QFileInfoList list = dir.entryInfoList();
    QFileInfoList::const_iterator constIterator;
    for (constIterator = list.constBegin(); constIterator != list.constEnd(); ++constIterator)
    {
        QFile file(constIterator->absoluteFilePath());
        if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        {
            continue;
        }
        QTextStream in(&file);
        while (!in.atEnd())
        {
            parseLine(in.readLine());
        }
        std::cout << file.fileName().toStdString()<<'\n';
    }
}

void Parser::addNewTech(const QString &name)
{
    techlist.push_back(new Techprocess(name));
}


void Parser::addNewOperation(const QString &operation)
{
    techlist.back()->addOperation(operation);
}

MaterialEntry * Parser::getMaterial()
{
    double num;
    if (m_captured.at(1).contains(","))
    {
        QString temp = m_captured.at(1);
        temp.replace(QString(","), QString("."));
        num = temp.toDouble();
    }
    else
    {
        num = m_captured.at(1).toDouble();
    }
    MaterialEntry *entry = new MaterialEntry(
            m_captured.at(0), 
            num,
            Measurement::measureMap.at(m_captured.at(2)),
            Measurement::measureMap.at(m_captured.at(3)));
    return entry;
}


void Parser::addNewMatetial()
{
    techlist.back()->addMaterial(getMaterial());
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

bool Parser::isMaterialDef(const QString &material)
{
    std::cout << "^"<<'\n';
    m_materialLine.indexIn(material);
    QStringList list = m_materialLine.capturedTexts();
    if (list.at(0).isEmpty())
    {
        return false;
    }
    m_captured.clear();
    m_captured << list.at(1) << list.at(2) << list.at(3) << list.at(4);
    QList<QString>::const_iterator i;
    std::cout << '\n';
    for (i = m_captured.cbegin()+1; i != m_captured.cend(); ++i)
    {
        std::cout << i->toStdString() << '\n';
    }
    
    return true;
}
                
void Parser::parseLine(const QString &line)
{
    //для инициализации техпроцесса необходимо ключевое слово "техпроцесс"
    if (line.startsWith("техпроцесс", Qt::CaseInsensitive))
    {
        addNewTech(line.right(7));
        previous = TECHPROCESS;
        std::cout << "Есть техпроцесс";
    }
    //если техпроцесс не инициализирован, то все строки ситаются просто комментариями
    else if (techlist.empty())
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
        if(isMaterialDef(line))
        {
            std::cout<<"OR";
            techlist.back()->addAlternative(getMaterial());
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
    else if (isMaterialDef(line))
    {
        addNewMatetial();
        std::cout << "[m+]";
        previous = MATERIAL;
    }
    else
    {
        previous = NONE;
    }
}

Techprocess* Parser::parseResult ()
{
    if(techlist.empty())
        std::cout << "Пусто";
    return techlist[0];
}

void Parser::printToConsole()
{
    //std::vector:iterator i;
    for (auto i:techlist )
    {
        i->printToConsole();
    }
    
}
