#ifndef __PRINT_AST_VISITOR_H__
#define __PRINT_AST_VISITOR_H__

#include "AstVisitor.h"

class PrintAstVisitor : public AstVisitor {
    public:
        void visit(ProgramNode *program_node);
        void visit(DeclarationNode *decl_node);
        void visit(SubprogramNode *subprogram_node);
    private:
        int indent_level;
};

#endif