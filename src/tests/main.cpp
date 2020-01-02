#include <gtest/gtest.h>

int main(int argc, char **argv) {
    chdir(TEST_DIRECTORY);
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
