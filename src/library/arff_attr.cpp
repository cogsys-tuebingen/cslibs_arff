#include <cslibs_arff/arff_attr.h>

using namespace cslibs_arff;

ArffAttr::ArffAttr(const std::string& name, ArffValueEnum type):
    m_name(name),
    m_enum(type) {
}

ArffAttr::~ArffAttr() {
}

std::string ArffAttr::name() const {
    return m_name;
}

ArffValueEnum ArffAttr::type() const {
    return m_enum;
}
