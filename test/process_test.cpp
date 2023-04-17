#include <cfloat>
#include <iostream>
extern "C"{
    #include "../include/base.h"
    #include "../include/processor.h"
}
#include "gtest/gtest.h"

TEST(processor_test, init_test){
    auto pro = init_processor();
}

int main() {
    testing::InitGoogleTest();
    return RUN_ALL_TESTS();
}