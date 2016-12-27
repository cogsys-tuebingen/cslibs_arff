#include <cslibs_arff/arff_data.h>

#include <fstream>
#include <stdexcept>

using namespace cslibs_arff;

ArffData::ArffData(): m_rel(""),
    m_nominals(),
    m_formats(),
    m_attrs(),
    m_instances() {
}

ArffData::~ArffData() {
}

void ArffData::set_relation_name(const std::string& name) {
    m_rel = name;
}

std::string ArffData::get_relation_name() const {
    return m_rel;
}

std::size_t ArffData::num_attributes() const {
    return m_attrs.size();
}

void ArffData::add_attr(const ArffAttr::Ptr &attr) {
    m_attrs.emplace_back(attr);
}

ArffAttr::Ptr ArffData::get_attr(const std::size_t idx) const {
    return m_attrs.at(idx);
}

std::size_t ArffData::num_instances() const {
    return m_instances.size();
}

void ArffData::add_instance(const ArffInstance::Ptr &inst) {
    _cross_check_instance(inst);
    m_instances.emplace_back(inst);
}

ArffInstance::Ptr ArffData::get_instance(const std::size_t idx) const {
    return m_instances.at(idx);
}

void ArffData::add_nominal_val(const std::string& name,
                               const std::string& val) {
    m_nominals[name].push_back(val);
}

ArffNominal ArffData::get_nominal(const std::string& name) {
    if(m_nominals.find(name) == m_nominals.end()) {
        THROW("ArffData::get_nominal list named '%s' does not exist!",
              name.c_str());
    }
    return m_nominals[name];
}

void ArffData::add_date_format(const std::string& name,
                               const std::string& val) {
    m_formats[name] = val;
}

std::string ArffData::get_date_format(const std::string& name) {
    if(m_formats.find(name) == m_formats.end()) {
        THROW("ArffData::get_date_format date named '%s' does not exist!",
              name.c_str());
    }
    return m_formats[name];
}

void ArffData::_cross_check_instance(const ArffInstance::Ptr &inst) {
    if(!inst) {
        THROW("ArffData: input instance pointer is null!");
    }
    if(inst->size() != m_attrs.size()) {
        THROW("%s: instance size and num-attrs mismatch inst=%d attrs=%d",
              "ArffData", inst->size(), m_attrs.size());
    }
    for(int32_t i=0;i<m_attrs.size();++i) {
        ArffValue::Ptr val = inst->get(i);
        ArffAttr::Ptr attr = m_attrs[i];
        ArffValueEnum valType = val->type();
        ArffValueEnum attType = attr->type();
        bool a_is_num = (attr->type() == NUMERIC);
        bool a_is_nom = (attr->type() == NOMINAL);
        bool v_nan = ((valType != INTEGER) && (valType != FLOAT) &&
                      (valType != NUMERIC));
        bool v_nas = (valType != STRING);
        // bad numeric/nominal
        if((a_is_num && v_nan) || (a_is_nom && v_nas)) {
            THROW("%s: attr-name=%s attr-type=%s, but inst-type=%s!",
                  "ArffData", attr->name().c_str(),
                  arff_value_type_to_str(attType).c_str(),
                  arff_value_type_to_str(valType).c_str());
        }
        // bad nominal value
        if(a_is_nom) {
            ArffNominal nom = get_nominal(attr->name());
            ArffNominal::iterator itr;
            std::string str = (std::string)*val;
            for(itr=nom.begin();itr!=nom.end();++itr) {
                if(str == *itr) {
                    break;
                }
            }
            if(itr == nom.end()) {
                THROW("%s: attr:(name=%s type=%s) inst-val=%s not found!",
                      "ArffData", attr->name().c_str(),
                      arff_value_type_to_str(attType).c_str(), str.c_str());
            }
        }
        if(a_is_num || a_is_nom) {
            continue;
        }
        // data mismatch
        if(attType != valType) {
            THROW("%s: attr-name=%s attr-type=%s, but inst-type=%s!",
                  "ArffData", attr->name().c_str(),
                  arff_value_type_to_str(attType).c_str(),
                  arff_value_type_to_str(valType).c_str());
        }
        ///@todo: Check for date-format mismatch
    }
}

///@todo: implement the method write_arff

void ArffData::write_arff(const std::string &path)
{
    std::ofstream out(path);
    if(!out.is_open())
        throw std::runtime_error("Cannot open path '" + path + "'!");

    out << "@RELATION " << m_rel << std::endl;

    for(auto &a : m_attrs) {
        out << "@ATTRIBUTE " + a->name() << " ";
        if(a->type() == NOMINAL) {
            auto nominals = m_nominals[a->name()];
            if(nominals.size() > 0) {
                out << "{";
                for(std::size_t i = 0 ; i < nominals.size() - 1 ; ++i) {
                    out << nominals[i] << ", ";
                }
                out << nominals.back();
                out << "}";
            }
        } else {
            out << arff_value_type_to_str(a->type());
        }
        out << std::endl;
    }

    out << "@DATA" << std::endl;
    for(auto &inst : m_instances) {
        const std::size_t inst_size = inst->size();
        if(inst_size > 0) {
            for(std::size_t i = 0 ; i < inst_size - 1 ; ++i) {
                out << inst->get(i)->to_string() << ",";
            }
            out << inst->get(inst_size - 1)->to_string();
            out << std::endl;
        }
    }
    out.close();
}


