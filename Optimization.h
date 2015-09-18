//
// Created by David Sere on 10/09/15.
//

#pragma once
#include "ModelSettings.h"
#include "Target.h"

namespace CGOpt{
    class Optimization {
    public:
        enum RandomDistr { normal, uniform  };

        __CUDA__ virtual Target &    init_func   (Target & state, double* rands) const = 0;
        __CUDA__ virtual Target &    next_func   (Target & state, double* rands) const = 0;
        __CUDA__ virtual double      energy_func (Target & state) const  = 0;
        __CUDA__ virtual double      temp_func   (double oldtemp) const  = 0;
    protected:
        ~Optimization(){};
    };
}



