#include "SymbolTable.h"
#include "info.h"

SymbolTable::SymbolTable(int layer)
: layer(layer)
{}

void SymbolTable::AddEntry(std::string name, Type *type)
{
    this->symbols.emplace_front(SymbolEntry{name, type});
    this->hash_table[name] = &this->symbols.front();
}

void SymbolTable::AppendChild(SymbolTable *symtab)
{
    this->child_symtab.push_back(symtab);
}

void SymbolTableManager::CreateScope()
{
    SHOW_NEWSCP();
    if (!this->symtab_stack.size()) {
        this->symtab_stack.emplace_back(new SymbolTable(0));
        return;
    }
    int current_layer = this->symtab_stack.back()->layer;
    this->symtab_stack.emplace_back(new SymbolTable(current_layer+1));
}

void SymbolTableManager::CloseScope()
{
    if (!this->symtab_stack.size()) {
        return;
    }
    SHOW_CLSSCP();
    Dump();
    this->symtab_stack.pop_back();
}

void SymbolTableManager::AddEntry(std::string name, Type *type)
{
    if (!this->symtab_stack.size()) {
        return;
    }
    SymbolTable *symtab = this->symtab_stack.back();
    if (symtab->hash_table.find(name) != symtab->hash_table.end()) {
        return;
    }
    SHOW_NEWSYM(name.c_str());
    symtab->AddEntry(name, type);
}

void SymbolTableManager::Dump()
{
    SHOW_SYMTAB_HEAD();
    for (auto tab_it = symtab_stack.rbegin(); tab_it != symtab_stack.rend(); ++tab_it) {
        for (auto sym_it = (*tab_it)->symbols.begin(); sym_it !=(*tab_it)->symbols.end(); ++sym_it) {
            printf(SYMTAB_ENTRY_FMT, sym_it->name.c_str(), (*tab_it)->layer, sym_it->type->name().c_str());
        }
    }
    SHOW_SYMTAB_TAIL();
}
