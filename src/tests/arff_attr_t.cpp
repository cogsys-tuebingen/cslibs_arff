#include <gtest/gtest.h>
#include <cslibs_arff/arff_attr.h>



TEST(arff_attr, usage) {
    ArffAttr attr("abc", INTEGER);
    EXPECT_EQ("abc", attr.name());
    EXPECT_EQ(INTEGER, attr.type());
}
