#include <cslibs_arff/arff_instance.h>

ArffInstance::ArffInstance(): m_data() {
}

ArffInstance::~ArffInstance() {
}

std::size_t ArffInstance::size() const {
    return m_data.size();
}

void ArffInstance::add(const ArffValue::Ptr &val) {
    m_data.emplace_back(val);
}

ArffValue::Ptr ArffInstance::get(std::size_t idx) const {
    return m_data.at(idx);
}
