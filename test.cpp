#include <gtest/gtest.h>
#include "functions.h"


TEST(sample_test_case, sample_test)
{
EXPECT_EQ(1, 1);
}

TEST(sample_test_case, another_test){
    EXPECT_FALSE(3<2);
}

TEST(another_test_case, test1){
    EXPECT_TRUE(stringIsValid("asdfasd"));
}

TEST(another_test_case, test2){
    EXPECT_FALSE(stringIsValid("asdf22asd"));
}
