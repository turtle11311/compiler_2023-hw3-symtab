#include "SymbolAstVisitor.h"
#include "SymbolTable.h"
#include "program.h"
#include "subprogram.h"
#include "declaration.h"
#include "info.h"

SymbolTableBuildVisitor::SymbolTableBuildVisitor(SymbolTable *symtab)
 : symtab(symtab)
{
}

void SymbolTableBuildVisitor::visit(ProgramNode *program_node)
{
    SHOW_NEWSCP();
    SHOW_NEWSYM(program_node->id.c_str());
    this->symtab->AddEntry(program_node->id, FunctionTypeBuilder().Return(nullptr)->Build());
    program_node->accept(this);
    SHOW_CLSSCP();
    this->symtab->Dump(0);
}

void SymbolTableBuildVisitor::visit(DeclarationNode *decl_node)
{
    for (auto id : decl_node->ids) {
        SHOW_NEWSYM(id.c_str());
        this->symtab->AddEntry(id, decl_node->type);
    }
}

void SymbolTableBuildVisitor::visit(SubprogramNode *subprogram_node)
{
    SHOW_NEWSYM(subprogram_node->id.c_str());
    SHOW_NEWSCP();
    subprogram_node->accept(this);
    SHOW_CLSSCP();
    this->symtab->Dump(0);
}
