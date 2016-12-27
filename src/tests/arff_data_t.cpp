#include <stdexcept>
#include <gtest/gtest.h>
#include <cslibs_arff/arff_data.h>



TEST(arff_data, usage) {
    ArffData data;

    // relation
    data.set_relation_name("ABC");
    EXPECT_EQ("ABC", data.get_relation_name());

    // attributes
    EXPECT_EQ(0, data.num_attributes());
    data.add_attr(std::make_shared<ArffAttr>(ArffAttr("attr1", NUMERIC)));
    data.add_attr(std::make_shared<ArffAttr>(ArffAttr("attr2", STRING)));
    data.add_attr(std::make_shared<ArffAttr>(ArffAttr("attr3", NOMINAL)));
    EXPECT_EQ(3, data.num_attributes());
    EXPECT_FALSE(!data.get_attr(2));
    EXPECT_EQ("attr3", data.get_attr(2)->name());

    // nominals
    data.add_nominal_val("attr3", "n1");
    data.add_nominal_val("attr3", "n2");
    data.add_nominal_val("attr3", "n3");
    data.add_nominal_val("attr3", "n4");
    EXPECT_EQ((size_t)4, data.get_nominal("attr3").size());

    // instances
    EXPECT_EQ(0, data.num_instances());
    ArffInstance::Ptr ins1(new ArffInstance());
    ins1->add(std::make_shared<ArffValue>(ArffValue((int32)10)));
    ins1->add(std::make_shared<ArffValue>(ArffValue("string")));
    ins1->add(std::make_shared<ArffValue>(ArffValue("n3")));
    data.add_instance(ins1);
    EXPECT_EQ(1, data.num_instances());
    EXPECT_FALSE(!data.get_instance(0));
    ArffInstance::Ptr bad1(new ArffInstance());
    bad1->add(std::make_shared<ArffValue>(ArffValue((int32)11)));
    bad1->add(std::make_shared<ArffValue>(ArffValue("string1")));
    bad1->add(std::make_shared<ArffValue>(ArffValue("not-exist")));
    EXPECT_THROW(data.add_instance(bad1), std::runtime_error);
    ArffInstance::Ptr bad2(new ArffInstance());
    bad2->add(std::make_shared<ArffValue>(ArffValue("string2")));
    bad2->add(std::make_shared<ArffValue>(ArffValue("string3")));
    bad2->add(std::make_shared<ArffValue>(ArffValue("n1")));
    EXPECT_THROW(data.add_instance(bad2), std::runtime_error);
}
