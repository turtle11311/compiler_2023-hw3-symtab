#include "SymbolTable.h"
#include "info.h"

void SymbolTable::AddEntry(std::string name, Type *type)
{
    this->symbols.emplace_front(SymbolEntry{name, type});
}

void SymbolTable::Dump(int layer)
{
    SHOW_SYMTAB_HEAD();
    for (auto &entry : this->symbols) {
        printf(SYMTAB_ENTRY_FMT, entry.name.c_str(), layer, entry.type->name().c_str());
    }
    SHOW_SYMTAB_TAIL();
}
