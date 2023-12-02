#include "visitor.h"
#include <iostream>
using std::cout, std::endl;

void PrintAstVisitor::visit(ProgramNode *program_node) {
    cout << "program: " << program_node->name << endl;
    program_node->accept(this);
}

void PrintAstVisitor::visit(DeclarationNode *decl_node) {
    cout << "Declaration Node type[" << decl_node->type->name() << "] => ";
    for (auto &id : decl_node->ids) {
        cout << id << ", ";
    }
    cout << endl;
}