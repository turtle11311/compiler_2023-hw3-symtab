#include "declaration.h"
#include <iostream>
using std::cout, std::endl;

DeclarationNode::DeclarationNode(Type *type, const IdentifierList ids)
: type(type), ids(ids)
{}

DeclarationNode::~DeclarationNode() {}

void DeclarationNode::accept(AstVisitor *visitor) {
    
}

DeclarationNodeList::~DeclarationNodeList()
{
    for (auto const &decl_p : *this) {
        if (decl_p == nullptr) continue;
        delete decl_p;
    }
}