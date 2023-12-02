#ifndef __SYMBOLTABLE_H__
#define __SYMBOLTABLE_H__

#include <list>
#include <string>

#include "type.h"

struct SymbolEntry {
    std::string name;
    Type *type;
};

class SymbolTable {
    public:
        void AddEntry(std::string name, Type *type);
        void Dump(int layer);
    private:
        std::list<SymbolTable*> child_symtab;
        std::list<SymbolEntry> symbols;
};

#endif