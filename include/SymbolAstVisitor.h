#ifndef __SYMBOL_AST_VISITOR_H__
#define __SYMBOL_AST_VISITOR_H__

#include "AstVisitor.h"
#include "SymbolTable.h"

class SymbolTableBuildVisitor : public AstVisitor {
    public:
        SymbolTableBuildVisitor(SymbolTable *symtab);
        void visit(ProgramNode *program_node);
        void visit(DeclarationNode *decl_node);
        void visit(SubprogramNode *subprogram_node);
    private:
        SymbolTable *symtab;
};

#endif