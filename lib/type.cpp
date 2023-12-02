#include "type.h"
#include <sstream>

StandardType::StandardType(StandardTypeEnum t)
: type(t)
{}

const std::string StandardType::name() const {
    switch (this->type)
    {
    case StandardTypeEnum::Void:
        return std::string("void");
    case StandardTypeEnum::Real:
        return std::string("real");
    case StandardTypeEnum::Integer:
        return std::string("int");
    case StandardTypeEnum::String:
        return std::string("string");
    }
    return std::string("unknown");
}

StandardType::~StandardType() {}

ArrayType::ArrayType(Type *base, int from, int to) 
: base(base), from(from), to(to)
{}

const std::string ArrayType::name() const {
    std::stringstream ss;
    ss << this->base->name() << "[" << from << "~" << to << "]";
    return ss.str();
}

ArrayType::~ArrayType() {
    delete this->base;
}

FunctionType::FunctionType(Type *return_type, std::list<Type *> *arguments_type)
 : return_type(return_type), arguments_type(arguments_type)
{
}

const std::string FunctionType::name() const
{
    std::stringstream ss;
    ss << ((this->return_type == nullptr) ? "void" : this->return_type->name());
    if (this->arguments_type == nullptr) {
        return ss.str();
    }
    ss <<" (";
    for (auto it = this->arguments_type->begin(); it != this->arguments_type->end(); ++it) {
        ss << (*it)->name() << ", ";
    }
    ss << ")";
    return ss.str();
}

FunctionTypeBuilder *FunctionTypeBuilder::Argument(Type *arg)
{
    this->arguments_type.push_back(arg);
    return this;
}

FunctionTypeBuilder *FunctionTypeBuilder::Return(Type *ret)
{
    this->return_type = ret;
    return this;
}

FunctionType *FunctionTypeBuilder::Build()
{
    if (this->arguments_type.size() == 0) {
        return new FunctionType(this->return_type, nullptr);
    }
    return new FunctionType(this->return_type, new std::list<Type*>(this->arguments_type));
}

