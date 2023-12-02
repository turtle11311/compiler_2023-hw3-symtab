#ifndef __VISITOR_H__
#define __VISITOR_H__

#include "ast.h"

class ProgramNode;
class DeclarationNode;
class SubprogramNode;

class AstVisitor {
    public:
        virtual void visit(ProgramNode *program_node) = 0;
        virtual void visit(DeclarationNode *decl_node) = 0;
        virtual void visit(SubprogramNode *subprogram_node) = 0;
};

class PrintAstVisitor : public AstVisitor {
    public:
        void visit(ProgramNode *program_node);
        void visit(DeclarationNode *decl_node);
        void visit(SubprogramNode *subprogram_node);
    private:
        int indent_level;
};

#endif