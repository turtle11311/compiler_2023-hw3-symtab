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

ArrayType::ArrayType(Type *base, int from, int to) 
: base(base), from(from), to(to)
{}

const std::string ArrayType::name() const {
    std::stringstream ss;
    ss << this->base->name() << "[" << from << "~" << to << "]";
    return ss.str();
}