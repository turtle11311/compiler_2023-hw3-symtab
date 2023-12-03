#include "SymbolAstVisitor.h"
#include "SymbolTable.h"
#include "program.h"
#include "subprogram.h"
#include "declaration.h"
#include "info.h"

SymbolTableBuildVisitor::SymbolTableBuildVisitor(SymbolTableManager *symtab_manager)
 : symtab_manager(symtab_manager)
{
}

void SymbolTableBuildVisitor::visit(ProgramNode *program_node)
{
    this->symtab_manager->CreateScope();
    this->symtab_manager->AddEntry(program_node->id, program_node->signature);
    program_node->accept(this);
    this->symtab_manager->CloseScope();
}

void SymbolTableBuildVisitor::visit(DeclarationNode *decl_node)
{
    for (auto id : decl_node->ids) {
        this->symtab_manager->AddEntry(id, decl_node->type);
    }
}

void SymbolTableBuildVisitor::visit(SubprogramNode *subprogram_node)
{
    
    this->symtab_manager->AddEntry(subprogram_node->id, subprogram_node->signature);
    this->symtab_manager->CreateScope();
    subprogram_node->accept(this);
    this->symtab_manager->CloseScope();
}
