#ifndef __VISITOR_H__
#define __VISITOR_H__

#include "ast.h"
#include "program.h"
#include "declaration.h"

class AstVisitor {
    public:
        virtual void visit(ProgramNode *program_node) = 0;
        virtual void visit(DeclarationNode *decl_node) = 0;
};

class PrintAstVisitor : public AstVisitor {
    public:
        void visit(ProgramNode *program_node);
        void visit(DeclarationNode *decl_node);
    private:
        int indent_level;
};

#endif