#ifndef __DECLARATION_H__
#define __DECLARATION_H__

#include "ast.h"
#include "type.h"
#include <list>
#include <string>

class DeclarationNode : Node {
    public:
        DeclarationNode(Type *type, const std::string name);
        const Type *getType() const { return this->type; }
        const std::string &getName() const { return this->name; }
    private:
        Type *type;
        std::string name;
};

typedef std::list<DeclarationNode*> DeclarationNodeList;

#endif