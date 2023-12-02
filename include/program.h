#ifndef __PROGRAM_H__
#define __PROGRAM_H__

#include "ast.h"
#include "declaration.h"
#include <string>

class ProgramNode : public Node {
    public:
        ProgramNode(const std::string name, DeclarationNodeList *decl_list);
        ~ProgramNode();
        void accept(AstVisitor *visitor);

        std::string name;
        DeclarationNodeList *decl_list;
};

#endif