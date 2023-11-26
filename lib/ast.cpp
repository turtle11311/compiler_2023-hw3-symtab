#include "ast.h"

const Location &Node::getLocation() const {
    return this->loc;
}