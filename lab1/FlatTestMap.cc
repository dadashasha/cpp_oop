#include "FlatMap.h"
#include "gtest/gtest.h"

namespace {

TEST() {
    FlatMap map;

    map["key_1"] = "aaaa";
    map["key_2"] = "bbbb";
    map["key_3"] = "cccc";

    EXPECT_EQ(map["key_1"], "aaaa");
    EXPECT_EQ(map["key_2"], "bbbb");
    EXPECT_EQ(map["key_3"], "cccc");
}

}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
