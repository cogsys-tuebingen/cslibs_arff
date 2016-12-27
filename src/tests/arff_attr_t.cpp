#include <gtest/gtest.h>
#include <cslibs_arff/arff_attr.h>

using namespace cslibs_arff;

TEST(arff_attr, usage) {
    ArffAttr attr("abc", INTEGER);
    EXPECT_EQ("abc", attr.name());
    EXPECT_EQ(INTEGER, attr.type());
}
