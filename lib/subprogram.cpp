#include "subprogram.h"
#include "AstVisitor.h"

SubprogramNode::SubprogramNode(std::string id, DeclarationNodeList *args_decl_list, Type *ret_type)
 : id(id), args_decl_list(args_decl_list), ret_type(ret_type)
{
    auto tb = FunctionTypeBuilder();
    
    if (this->args_decl_list != nullptr) {
        for (auto arg_decl : *this->args_decl_list) {
            for (auto arg_id : arg_decl->ids) {
                tb.Argument(arg_decl->type);
            }
        }
    }
    
    tb.Return(ret_type);
    signature = tb.Build();
}

SubprogramNode::SubprogramNode(SubprogramNode *subprogram_head, DeclarationNodeList *decl_list, SubprogramNodeList *subprogram_list)
 : id(subprogram_head->id), args_decl_list(subprogram_head->args_decl_list), ret_type(subprogram_head->ret_type),
   decl_list(decl_list), subprogram_list(subprogram_list), signature(subprogram_head->signature)
{
    // clear old subprogram_head
    subprogram_head->args_decl_list = nullptr;
    subprogram_head->ret_type = nullptr;
}

void SubprogramNode::accept(AstVisitor *visitor) {
    if (this->args_decl_list != nullptr) {
        for (auto args_decl : *this->args_decl_list) visitor->visit(args_decl);
    }
    if (this->decl_list != nullptr) {
        for (auto decl : *this->decl_list) visitor->visit(decl);
    }
    if (this->subprogram_list != nullptr) {
        for (auto subprogram : *this->subprogram_list) visitor->visit(subprogram);
    }
}