#ifndef __AST_H__
#define __AST_H__

#include "location.h"
#include <list>

class Node;
class AstVisitor;

typedef std::list<Node*> NodeList;

class Node {
    public:
        const Location &getLocation() const;
        virtual void accept(AstVisitor *visitor) = 0;
        virtual ~Node() {};
    protected:
        Location loc;
};

#endif
