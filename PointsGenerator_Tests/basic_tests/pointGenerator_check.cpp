//
// Created by AK on 13/10/15.
//

#include "gtest/gtest.h"

#include "PointsGenerator.h"

class PointsGeneratorFixture : public ::testing::Test {
protected:
    virtual void TearDown() {
    }

    virtual void SetUp() {
    }

public:
    PointsGeneratorFixture() : Test() {
    }

    virtual ~PointsGeneratorFixture() {
    }
};

TEST_F(PointsGeneratorFixture, firstCheck) {
    PointsGenerator pg;
    bool expected = true;
    bool actual = pg.test;
    EXPECT_EQ(expected, actual);
}