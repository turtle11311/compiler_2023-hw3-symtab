#ifndef __SUBPROGRAM_H__
#define __SUBPROGRAM_H__

#include "ast.h"
#include "visitor.h"
#include "declaration.h"
#include "type.h"

#include <string>

class SubprogramNode : public Node {
    public:
        SubprogramNode(std::string id, DeclarationNodeList *args_decls, Type *ret_type);
        void accept(AstVisitor *visitor);

        std::string id;
        DeclarationNodeList *args_decls;
        Type *ret_type;
};

#endif