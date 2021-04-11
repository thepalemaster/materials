#include <QFile>
#include <QTextStream>
#include <QDir>

#include "techprocess.hpp"
#include "parser.hpp"

#include <iostream>



void Parser::scanDir(const QString& directory)
{

    QDir dir = QDir(directory);
    dir.setFilter(QDir::NoDotAndDotDot | QDir::Files);
    if (!dir.exists())
    {
        return;
    }
    QStringList list = dir.entryList();
    QStringList::const_iterator constIterator;
    for (constIterator = list.constBegin(); constIterator != list.constEnd(); ++constIterator)
    {
        
        QString tempstring = directory + '/' + *constIterator; 
        QFile file(tempstring);
        std::cout << file.fileName().toStdString()<<'\n';
        if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
            std::cout << "Файл"<< constIterator->toStdString();
        QTextStream in(&file);
        while (!in.atEnd())
        {
            QString currentLine = in.readLine();
            parseLine(currentLine);
        }
    }
}

Parser::Parser(const QString& directory)
{
    //регулярное выражение чтобы вычленять данные по операциям
    QString rx = 
    "^ *(.*) +(\\d+[,\\.]?\\d*) {0,5}("
    + Measurement::regExpMeasure + ")(\\/("
    + Measurement::regExpMeasure + "))? *$";
    //rx = "(\\d+[,\\.]?\\d*)";
    m_materialLine.setPatternSyntax(QRegExp::RegExp2);
    m_materialLine.setPattern(rx);
    m_materialLine.setCaseSensitivity(Qt::CaseInsensitive);
    
    if (m_materialLine.isValid())
        std::cout<<"Регулярка верная!"<<'\n';
    else
        std::cout<<rx.toStdString()<<'\n';
    scanDir(directory);
}


void Parser::addNewTech(const QString &name)
{
    techlist.push_back(Techprocess(name));
}


void Parser::addNewOperation(const QString &operation)
{
    techlist.back().addOperation(operation);
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
    MaterialEntry *entry;
    if (m_captured.length() == 3)
    {
        entry = new MaterialEntry(
            m_captured.at(0), 
            num,
            Measurement::measureMap.at(m_captured.at(2)),
            Measurement::measureMap.at("шт"));
    }
    else
    {
        entry = new MaterialEntry(
            m_captured.at(0), 
            num,
            Measurement::measureMap.at(m_captured.at(2)),
            Measurement::measureMap.at(m_captured.at(3)));
    }
    return entry;
}


void Parser::addNewMatetial()
{
    techlist.back().addMaterial(getMaterial());
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
    m_materialLine.indexIn(material);
    QStringList list = m_materialLine.capturedTexts();
    if (list.at(0).isEmpty())
    {
        return false;
    }
    m_captured.clear();
    if(list.at(5).isEmpty())
    {
        m_captured << list.at(1) << list.at(2) << list.at(3);
    }
    else
    {
        m_captured << list.at(1) << list.at(2) << list.at(3) << list.at(5);
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
    else if (techlist.isEmpty())
    {
        previous = NONE;
    }
    else if (line.isEmpty())
    {
        //если строка пустая, то ничего не делается
    }
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
            techlist.back().addAlternative(getMaterial());
            previous = MATERIAL;
        }
        else
        {
            previous = NONE;
        }
    }
    //проверка ключевого слова "или", работает только если приведущей записью был материал
    else if (!line.compare("или", Qt::CaseInsensitive) && previous == MATERIAL)
    {
        previous = OR_MATERIAL;
        //на следующем шаге  которая запоминается как допустимая замена приведущей
    }
    //проверка является ли стока определением материала
    else if (isMaterialDef(line))
    {
        addNewMatetial();
        previous = MATERIAL;
    }
    else
    {
        previous = NONE;
    }
}

QList<Techprocess> Parser::parseResult ()
{
    return techlist;
}

void Parser::printToConsole()
{
    QList<Techprocess>::iterator i;
    for (i = techlist.begin(); i != techlist.end(); ++i)
    {
        i->printToConsole();
    }
    
}
