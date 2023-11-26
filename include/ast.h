#ifndef __AST_H__
#define __AST_H__

#include "location.h"

class AstVisitor;

class Node {
    protected:
        Location loc;
    public:
        const Location &getLocation() const;
};

#endif
