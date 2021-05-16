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
    std::vector<Techprocess*> techlist;
    
    int counter = 0;
    
    QStringList m_captured;
    QRegExp m_materialLine;
    QRegExp m_techprocessRegExp{"\\s*техпроцесс\\s+(.+)\\s*", Qt::CaseInsensitive};
    bool isOperation (const QString &operation);
    bool isMaterialDef(const QString &material);
    bool isTechprocess(const QString &techprocess);
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
    Techprocess* parseResult ();
    std::vector<Techprocess*>* getResult ();
    void printToConsole();
};
