# include <limits.h>
# include "gtest/gtest.h"
# include "Adder.h"

TEST(TestOne, Add)
{
	Adder a(0);
	EXPECT_EQ(1, a.Add(1));
	EXPECT_EQ(2, a.Add(2));
	EXPECT_EQ(-1, a.Add(-1));
	EXPECT_EQ(0x7fffffff, a.Add(0x7fffffff));
}

TEST(TestTwo, Add)
{
	Adder a(0x3f3f3f3f);
	EXPECT_EQ(0+0x3f3f3f3f, a.Add(0));
	EXPECT_EQ(0xdead+0x3f3f3f3f, a.Add(0xdead));
}

int main(int argc, char* argv[])
{
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}