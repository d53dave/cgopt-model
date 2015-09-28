//
// Created by David Sere on 09/09/15.
//

#include <limits>
#include "TestConfig.h"
#include "../Optimization.h"

#define PROBLEM_SIZE 2

namespace CGOpt {

    //
    //

    class TestTarget : public Target {
    public:
        double coords[PROBLEM_SIZE];
        double energy;

        __CUDA__ size_t problemSize() { return PROBLEM_SIZE; }
    };


    class TestOpt : public Optimization {
    public:
        __CUDA__ virtual Target &initialize(Target &state, double *rands) const;

        __CUDA__ virtual Target &generateNext(Target &state, double *rands) const;

        __CUDA__ virtual OPT_TYPE_RETURN evaluate(Target &state) const;

        __CUDA__ virtual OPT_TYPE_RETURN cool(double oldtemp) const;

        __CUDA__ double denormalizeNext(double rand) const;
    };


    __CUDA__ Target &TestOpt::initialize(Target &state, double *rands) const {
        return generateNext(state, rands);
    }

    __CUDA__ Target &TestOpt::generateNext(Target &state, double *rands) const {
        for (size_t i = 0; i < ((TestTarget &) state).problemSize(); ++i) {
            ((TestTarget &) state).coords[i] += denormalizeNext(rands[i]);
        }
        return state;
    }

    __CUDA__ double TestOpt::evaluate(Target &state) const {
        double result, t1, t2;
        double *input = ((TestTarget &) state).coords;
        for (size_t i = 0; i < ((TestTarget &) state).problemSize() - 1; ++i) {
            t1 = (1 - input[i]);
            t2 = (input[i + 1] - input[i] * input[i]);
            result += t2 * t2 + 100 * (t1 * t1);
        }
        ((TestTarget &) state).energy = result;
        return result;
    }

    __CUDA__ double TestOpt::cool(double oldtemp) const {
        return oldtemp * .98;
    }

    double TestOpt::denormalizeNext(double rand) const {
        return rand * 2 - 1; // from 0..1 to -1..1
    }
}

TEST_CASE( "", "[vector]" ) {

    CGOpt::TestOpt opt;
    CGOpt::TestTarget target;
    target.energy = 42.0;

    double rands[]{1.0, 2.0};

    opt.initialize(target, rands);

    SECTION( "Temperature must be decreasing" ) {
        REQUIRE( opt.cool(99) < opt.cool(100));
    }

    SECTION( "2D Rosenbrock function has its minimum 0 at (1,1)" ){
        CGOpt::TestTarget state;

        CGOpt::TestTarget bestTarget;
        bestTarget.energy = HUGE_VAL;

        for(double i = -10; i <= 10; i+=.1 ){
            for(double j = -10; j<= 10; j+=.1){
                state.coords[0] = i;
                state.coords[1] = j;
                if( opt.evaluate(state) < bestTarget.energy){
                    bestTarget.energy = opt.evaluate(state);
                    bestTarget.coords[0] = state.coords[0];
                    bestTarget.coords[1] = state.coords[1];
                }
            }
        }

        REQUIRE( bestTarget.energy == Approx(0).scale(0).epsilon(1e7));
        REQUIRE( bestTarget.coords[0] == Approx(1).scale(0).epsilon(1e7));
        REQUIRE( bestTarget.coords[1] == Approx(1).scale(0).epsilon(1e7));
    }
}