#ifndef __SYMBOLTABLE_H__
#define __SYMBOLTABLE_H__

#include <list>
#include <string>
#include <vector>

#include "type.h"

struct SymbolEntry {
    std::string name;
    Type *type;
};

class SymbolTableManager;

class SymbolTable {
    public:
        SymbolTable() = delete;
        void AddEntry(std::string name, Type *type);
        void AppendChild(SymbolTable *symtab);
        friend class SymbolTableManager;
    private:
        SymbolTable(int layer);
        std::list<SymbolTable*> child_symtab;
        std::list<SymbolEntry> symbols;
        int layer;
};

class SymbolTableManager {
    public:
        void CreateScope();
        void CloseScope();
        void AddEntry(std::string name, Type *type);
        void Dump();
    private:
        std::vector<SymbolTable*> symtab_stack;
};

#endif