
#include "cpu.h"
#include "memory.h"
#include <gtest/gtest.h>

TEST(thing, me)
{
    const auto data = 300;
    
    Memory mem;
    CPU GB_CPU(mem);
    GB_CPU.write_16_bit(0xABCD,data);
    
    ASSERT_EQ(data, GB_CPU.read_16_bit(0xABCD));
}


int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}