#ifndef __TYPE_H__
#define __TYPE_H__

#include "ast.h"
#include <string>

class Type {
    public:
        virtual const std::string name() const = 0;
        virtual ~Type() {};
};

enum StandardTypeEnum {
    Void, Real, Integer, String 
};

class StandardType : public Type {
    public:
        StandardType(StandardTypeEnum t);
        const std::string name() const;

        ~StandardType();
    private:
        StandardTypeEnum type;
};

class ArrayType : public Type {
    public:
        ArrayType(Type *base, int from, int to);
        const std::string name() const;

        ~ArrayType();
    private:
        Type *base;
        int from, to;
};

#endif