//
// Created by wolfy on 4/23/2024.
//
#pragma once
#ifndef TESTUTILCOMPONENT_H
#define TESTUTILCOMPONENT_H


#include "engine/components/Component.h"

class TestUtilComponent : public WEngine::Component {
public:
    TestUtilComponent();

    ~TestUtilComponent();

    virtual void Update(float deltaTime) override;
};


#endif //TESTUTILCOMPONENT_H
