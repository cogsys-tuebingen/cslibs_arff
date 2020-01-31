#include <stdexcept>
#include <gtest/gtest.h>
#include <cslibs_arff/arff_value.h>

using namespace cslibs_arff;

TEST(arff_value, arff_value_enum) {
    EXPECT_EQ("INTEGER", arff_value_type_to_str(INTEGER));
    EXPECT_EQ("FLOAT",   arff_value_type_to_str(FLOAT));
    EXPECT_EQ("DATE",    arff_value_type_to_str(DATE));
    EXPECT_EQ("STRING",  arff_value_type_to_str(STRING));
    EXPECT_EQ("NUMERIC", arff_value_type_to_str(NUMERIC));
    EXPECT_EQ("NOMINAL", arff_value_type_to_str(NOMINAL));
    EXPECT_EQ("UNKNOWN", arff_value_type_to_str(UNKNOWN_VAL));
}

TEST(arff_value, usage_default) {
    ArffValue val;
    // int (default)
    EXPECT_EQ(INTEGER, val.type());
    EXPECT_EQ(0, (int32_t)val);
    EXPECT_FLOAT_EQ(0.0f, (float)val);
    EXPECT_EQ("0", (std::string)val);
    EXPECT_FALSE(val.missing());
    // explicitly float
    val.set(10.1f);
    EXPECT_EQ(FLOAT, val.type());
    EXPECT_EQ(10, (int32_t)val);
    EXPECT_FLOAT_EQ(10.1f, (float)val);
    EXPECT_EQ("10.1", (std::string)val);
    EXPECT_FALSE(val.missing());
    // explicitly string
    val.set("string");
    EXPECT_EQ(STRING, val.type());
    EXPECT_THROW((void) (int32_t)val, std::runtime_error);
    EXPECT_THROW((void) (float)val, std::runtime_error);
    EXPECT_EQ("string", (std::string)val);
    EXPECT_FALSE(val.missing());
    // explicitly int
    val.set((int32_t)111);
    EXPECT_EQ(INTEGER, val.type());
    EXPECT_EQ(111, (int32_t)val);
    EXPECT_FLOAT_EQ(111.0f, (float)val);
    EXPECT_EQ("111", (std::string)val);
    EXPECT_FALSE(val.missing());

    // copy
    ArffValue val1(val);
    EXPECT_EQ(INTEGER, val1.type());
    EXPECT_EQ(111, (int32_t)val1);
    EXPECT_FLOAT_EQ(111.0f, (float)val1);
    EXPECT_EQ("111", (std::string)val1);
    EXPECT_FALSE(val.missing());

    // equality
    EXPECT_TRUE(val == (int32_t)111);
    EXPECT_FALSE(val == 111.0f);
    EXPECT_TRUE((int32_t)111 == val);
    EXPECT_FALSE(111.0f == val);
    EXPECT_TRUE(val == val1);
    EXPECT_FALSE(val.missing());
}

TEST(arff_value, usage_float) {
    ArffValue val(10.1f);
    // float (default)
    EXPECT_EQ(FLOAT, val.type());
    EXPECT_EQ(10, (int32_t)val);
    EXPECT_FLOAT_EQ(10.1f, (float)val);
    EXPECT_EQ("10.1", (std::string)val);
    EXPECT_FALSE(val.missing());
}

TEST(arff_value, usage_string) {
    ArffValue val("string");
    // string (default)
    EXPECT_EQ(STRING, val.type());
    EXPECT_THROW((void) (int32_t)val, std::runtime_error);
    EXPECT_THROW((void) (float)val, std::runtime_error);
    EXPECT_EQ("string", (std::string)val);
    EXPECT_FALSE(val.missing());

    // implicit conversions
    ArffValue val1("123");
    EXPECT_EQ(FLOAT, val1.type());
    EXPECT_EQ((int32_t)123, (int32_t)val1);
    EXPECT_FLOAT_EQ(123.0f, (float)val1);
    EXPECT_EQ("123", (std::string)val1);
    EXPECT_FALSE(val.missing());
}

TEST(arff_value, usage_missing) {
    ArffValue val(STRING);
    EXPECT_TRUE(val.missing());
}
