//
// Created by David Sere on 09/09/15.
//
#pragma once
#include <string>
#include "ModelSettings.h"
#include <vector>

class Target {
public:
    std::string name;
    unsigned long long num;
    std::vector<std::string> v;

    REGISTER(name, num, v);
};


