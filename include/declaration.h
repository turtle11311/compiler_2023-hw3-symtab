#ifndef __DECLARATION_H__
#define __DECLARATION_H__

#include "ast.h"
#include "type.h"
#include <list>
#include <string>

typedef std::list<std::string> IdentifierList;

class DeclarationNode : Node {
    public:
        DeclarationNode(Type *type, const IdentifierList ids);
        void accept(AstVisitor *visitor);

        ~DeclarationNode();

        Type *type;
        IdentifierList ids;
};

class DeclarationNodeList : public std::list<DeclarationNode*> {
    public:
        ~DeclarationNodeList();
};

#endif