#include "program.h"
#include "visitor.h"

ProgramNode::ProgramNode(const std::string name, DeclarationNodeList *decl_list)
: name(name), decl_list(decl_list) {}

void ProgramNode::accept(AstVisitor *visitor) {
    if (this->decl_list != nullptr) {
        for (auto decl : *this->decl_list) visitor->visit(decl);
    }
}

ProgramNode::~ProgramNode() {
    if (this->decl_list) delete this->decl_list;
}