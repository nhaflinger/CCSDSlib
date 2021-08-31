// tests.cpp
#include "ccsds_test.cpp"
#include <gtest/gtest.h>

TEST(CCSDSTest, PositiveNos) 
{
    std::string ccsds_file = "testpacket.ccsds"; 
    std::string xtce_file = "xtce.xml";
    ASSERT_EQ(0, decodeCheck(ccsds_file, xtce_file, 100));
}

TEST(CCSDSTest, NegativeNos) 
{
    std::string ccsds_file = "testpacket.ccsds";
    std::string xtce_file = "xtce.xml";
    ASSERT_EQ(-1.0, decodeCheck(ccsds_file, xtce_file, 101));
}

int main(int argc, char **argv) 
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
