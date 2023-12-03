#include "program.h"
#include "AstVisitor.h"
#include "type.h"

ProgramNode::ProgramNode(const std::string id, DeclarationNodeList *decl_list, SubprogramNodeList *subprogram_list)
: id(id), decl_list(decl_list), subprogram_list(subprogram_list) {
    signature = FunctionTypeBuilder().Return(nullptr)->Build();
}

void ProgramNode::accept(AstVisitor *visitor) {
    if (this->decl_list != nullptr) {
        for (auto decl : *this->decl_list) visitor->visit(decl);
    }
    if (this->subprogram_list != nullptr) {
        for (auto subprogram : *this->subprogram_list) visitor->visit(subprogram);
    }
}

ProgramNode::~ProgramNode() {
    if (this->decl_list) delete this->decl_list;
}