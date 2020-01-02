#include <stdexcept>

#include <cslibs_arff/arff_utils.h>

using namespace cslibs_arff;

#define STR_LENGTH 2048
void cslibs_arff::throw_ex(const char* file, int64_t line, const char* fmt...) {
    char msg[STR_LENGTH];
    va_list va;
    va_start(va, fmt);
    vsprintf(msg, fmt, va);
    va_end(va);
    std::string err(file);
    err += ":" + num2str<int64_t>(line) + " -- ";
    err += msg;
    std::runtime_error ex(err);
    throw ex;
}
#undef STR_LENGTH

char cslibs_arff::to_lower(char c) {
    if((c >= 'A') && (c <= 'Z')) {
        return ((c - 'A') + 'a');
    }
    return c;
}

bool cslibs_arff::icompare(const std::string& str, const std::string& ref) {
    size_t s1 = str.size();
    size_t s2 = ref.size();
    if(s1 != s2) {
        return false;
    }
    const char* ch1 = str.c_str();
    const char* ch2 = ref.c_str();
    for(size_t i=0;i<s1;++i) {
        if(cslibs_arff::to_lower(ch1[i]) != cslibs_arff::to_lower(ch2[i])) {
            return false;
        }
    }
    return true;
}
