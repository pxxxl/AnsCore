#include <cfloat>
#include <iostream>
extern "C"{
    #include "../include/base.h"
    #include "../include/processor.h"
    #include "../include/macros.h"
    #include "../include/units.h"
}
#include "gtest/gtest.h"

class ProcessorAPITest : public ::testing::Test {
protected:
    virtual void SetUp() {
        pro = init_processor(BASE_MAX_X, BASE_MAX_Y);
        //place a obstacle at 0,0
        auto obj = create_obstacle_wall_object();
        pro->api->request_place(pro, NULL, obj, 0, 0);
        pro->step(pro);
    }
    virtual void TearDown() {
        
    }
    Processor *pro;
};

TEST(ProcessorInitTest, init_test){
        Processor *pro;
        pro = init_processor(BASE_MAX_X, BASE_MAX_Y);
        //place a obstacle at 0,0
        auto obj = create_obstacle_wall_object();
        pro->api->request_place(pro, NULL, obj, 0, 0);
        pro->step(pro);
}

int main() {
    testing::InitGoogleTest();
    return RUN_ALL_TESTS();
}