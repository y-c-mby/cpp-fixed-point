//
// Created by mby on 10/06/2020.
//
#include <gtest/gtest.h>
#include "Price.h"
int main(int argc ,char* argv[]){
    testing::InitGoogleTest(&argc,argv);
    return RUN_ALL_TESTS();
}
TEST(globaloperators,operatoEq){
    Price<int> p1(-3,45);
    Price<int> p2(-6,45);

    ASSERT_EQ(p1<=p2, false);
}
TEST(globaloperators,operatoplus){
    Price<int> p1(3,45);
    Price<int> p2(6,45);
    Price<int> p3(-9,90);
    ASSERT_EQ(p1+p2,p3);
}
