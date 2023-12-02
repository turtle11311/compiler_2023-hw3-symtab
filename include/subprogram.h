#ifndef __SUBPROGRAM_H__
#define __SUBPROGRAM_H__

#include "ast.h"
#include "declaration.h"
#include "type.h"

#include <string>
#include <list>

class SubprogramNode;

typedef std::list<SubprogramNode*> SubprogramNodeList;

class SubprogramNode : public Node {
    public:
        SubprogramNode(std::string id, DeclarationNodeList *args_decl_list, Type *ret_type);
        SubprogramNode(SubprogramNode *subprogram_head, DeclarationNodeList *decl_list, SubprogramNodeList *subprogram_list);
        void accept(AstVisitor *visitor);

        std::string id;
        DeclarationNodeList *args_decl_list;
        DeclarationNodeList *decl_list;
        SubprogramNodeList *subprogram_list;
        Type *ret_type;
};


#endif