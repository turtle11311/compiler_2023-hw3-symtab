#ifndef __TYPE_H__
#define __TYPE_H__

#include "ast.h"
#include <string>
#include <vector>

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

class VoidType : public Type {
    public:
        const std::string name() const;
        ~VoidType() = default;
};

class FunctionType : public Type {
    public:
        FunctionType(Type *return_type, std::vector<Type*> *arguments_type);
        const std::string name() const;
    
    private:
        std::vector<Type*> *arguments_type;
        Type *return_type;
};

class FunctionTypeBuilder {
    public:
        FunctionTypeBuilder* Argument(Type *arg);
        FunctionTypeBuilder* Return(Type *ret);
        FunctionType* Build();
    private:
        std::vector<Type*> arguments_type;
        Type *return_type;
};

#endif