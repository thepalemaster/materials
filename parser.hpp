#pragma once
#include "techprocess.hpp"
#include <QFile>

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
    QList<Techprocess> techlist;
    QStringList m_captured;
    QRegExp m_materialLine;
    bool isOperation (const QString &operation);
    bool isMaterialDef(const QString &material);
    void scanDir(const QString &directory);
    void addNewTech(const QString &name);
    void addNewOperation(const QString &operation);
    void addNewMatetial(const QString &material);
    void addNewMatetial();
    MaterialEntry* getMaterial();
    
public:
    Parser(const QString &directory);
    ~Parser();
    void parseLine(const QString &line);
    QList<Techprocess> parseResult ();
    void printToConsole();
};
