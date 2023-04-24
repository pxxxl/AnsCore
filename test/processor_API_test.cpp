#include <cfloat>
#include <iostream>
extern "C"{
    #include "../src/base/base.h"
    #include "../src/processor/processor.h"
    #include "../src/macros.h"
    #include "../src/units/units.h"
}
#include "gtest/gtest.h"

class ProcessorAPITest : public ::testing::Test {
protected:
    virtual void SetUp() {
        pro = init_processor(10, 10);
        //place a obstacle at 0,0

        for(int i = 0; i < 10; i++){
            wall[i] = create_obstacle_wall_object();
        }
        pro->api->request_place(pro, NULL, wall[0], 0, 0, UP);
        pro->api->request_place(pro, NULL, wall[1], 3, 3, UP);
        pro->api->request_place(pro, NULL, wall[2], 6, 6, UP);
        pro->api->request_place(pro, NULL, any, 0, 9, UP);
        pro->step(pro);

    }
    virtual void TearDown() {
        
    }
    Object* wall[10];
    Object* bullet;
    Object* any;
    Processor *pro;
};
/*
TEST_F(ProcessorAPITest, bullet_test){
    bullet = create_ordinary_bullet_object(RED_BULLET);
    pro->api->request_place(pro, NULL, bullet, 9, 9, LEFT);
    pro->step(pro);
    pro->step(pro);
    EXPECT_EQ(pro->api->get_object(pro, 8, 9), bullet);
    pro->step(pro);
    EXPECT_EQ(pro->api->get_object(pro, 7, 9), bullet);
}
*/

TEST_F(ProcessorAPITest, move_test){
    EXPECT_EQ(pro->api->get_object(pro, 0, 9), any);
    pro->api->request_move(pro, any, RIGHT, 3);
    pro->step(pro);
    EXPECT_EQ(pro->api->get_object(pro, 0, 9), nullptr);
    EXPECT_EQ(pro->api->get_object(pro, 3, 9), any);
    pro->api->request_move(pro, any, LEFT, 3);
    pro->step(pro);
    EXPECT_EQ(pro->api->get_object(pro, 0, 9), any);
    EXPECT_EQ(pro->api->get_object(pro, 3, 9), nullptr);
    pro->api->request_step(pro, any, UP);
    pro->step(pro);
    EXPECT_EQ(pro->api->get_object(pro, 0, 8), any);
    EXPECT_EQ(pro->api->get_object(pro, 0, 9), nullptr);
}

TEST_F(ProcessorAPITest, suiside_test){
    pro->api->request_suiside(pro, any);
    pro->step(pro);
    EXPECT_EQ(pro->api->get_object(pro, 0, 9), nullptr);
}

TEST_F(ProcessorAPITest, teleport_test){
    pro->api->request_teleport(pro, any, 9, 9);
    pro->step(pro);
    Object* obj = pro->api->get_object(pro, 0, 9);
    EXPECT_EQ(obj, nullptr);
    EXPECT_EQ(pro->api->get_object(pro, 9, 9), any);
}

TEST_F(ProcessorAPITest, freeze_test){
    pro->api->request_freeze(pro, any, any, 3);
    pro->step(pro);
    EXPECT_EQ(any->status.frozen_degree, 3);
    pro->step(pro);
    EXPECT_EQ(any->status.frozen_degree, 2);
    pro->step(pro);
    EXPECT_EQ(any->status.frozen_degree, 1);
    pro->step(pro);
    EXPECT_EQ(any->status.frozen_degree, 0);
    pro->step(pro);
    EXPECT_EQ(any->status.frozen_degree, 0);
}


TEST(ProcessorInitTest, init_test){
        Processor *pro;
        pro = init_processor(BASE_MAX_X, BASE_MAX_Y);
        //place a obstacle at 0,0
        auto obj = create_obstacle_wall_object();
        pro->api->request_place(pro, NULL, obj, 0, 0, UP);
        pro->step(pro);
}

int main() {
    testing::InitGoogleTest();
    return RUN_ALL_TESTS();
}