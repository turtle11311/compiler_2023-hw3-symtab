#include "subprogram.h"

SubprogramNode::SubprogramNode(std::string id, DeclarationNodeList *args_decls, Type *ret_type)
 : id(id), args_decls(args_decls), ret_type(ret_type)
{}

void SubprogramNode::accept(AstVisitor *visitor) {
    if (this->args_decls != nullptr) {
        for (auto decl : *this->decl_list) visitor->visit(decl);
    }
}