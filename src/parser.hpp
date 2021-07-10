#pragma once
#include "techprocess.hpp"
#include <QFile>
#include <QRegularExpression>

class Parser 
{
private:
    enum PreviousLine 
    {
        NONE,
        OR_MATERIAL,
        MATERIAL,
        OPERATION,
        TECHPROCESS,
    };
    PreviousLine previous = NONE;
    std::vector<Techprocess> techlist;
    static const QRegularExpression m_techprocessRegExp;
    QRegularExpressionMatch m_lastMatch;
    QRegularExpression m_materialLine;
    bool isOperation (const QString &operation);
    bool isMaterialDefinition(const QString &material);
    bool isTechprocess(const QString &techprocess);
    void scanDir(const QString &directory);
    void addNewTech(const QString &name);
    void addNewOperation(const QString &operation);
    void addNewMatetial(const QString &material);
    void addNewMatetial();
    double getNumber(QString number);
    MaterialEntry* getMaterial();
    
public:
    Parser(const QString &directory);
    void parseLine(const QString &line);
    std::vector<Techprocess> getResult ();
    void printToConsole();
};

