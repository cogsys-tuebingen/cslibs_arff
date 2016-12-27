#include <stdexcept>
#include <gtest/gtest.h>
#include <cslibs_arff/arff_parser.h>

using namespace cslibs_arff;

TEST(arff_parser, usage) {
    ArffParser parser("cases/case3.arff");
    ArffData::Ptr data = parser.parse();
    EXPECT_FALSE(!data);
}

TEST(arff_parser, missing_usage) {
    ArffParser parser("cases/case4.arff");
    ArffData::Ptr data = parser.parse();
    EXPECT_FALSE(!data);
}
