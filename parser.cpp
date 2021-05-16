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

Parser::~Parser()
{
    for (auto item: techlist)
    {
       delete item;
    }
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


bool Parser::isTechprocess(const QString& techprocess)
{
    if(m_techprocessRegExp.indexIn(techprocess) < 0)
    {
        return false;
    }
    m_captured.clear();
    m_captured <<  m_techprocessRegExp.cap(1);
    return true;
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
    if(m_materialLine.indexIn(material) < 0)
    {
        return false;
    }
    m_captured.clear();
    m_captured << m_materialLine.cap(1) << m_materialLine.cap(2) << m_materialLine.cap(3) << m_materialLine.cap(4);
    return true;
}
                
void Parser::parseLine(const QString &line)
{
    //для инициализации техпроцесса необходимо ключевое слово "техпроцесс"
    if (isTechprocess(line))
    {
        addNewTech(m_captured[0]);
        previous = TECHPROCESS;
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
    return techlist[1];
}

std::vector<Techprocess*>* Parser::getResult ()
{
    std::vector<Techprocess*>* ptr = &techlist;
    return ptr;
}

void Parser::printToConsole()
{
    for (auto i:techlist )
    {
        i->printToConsole();
    }
    
}
