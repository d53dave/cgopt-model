//
// Created by David Sere on 09/09/15.
//

#include <limits>
#include "TestConfig.h"
#include "../src/Optimization.h"

#define PROBLEM_SIZE 2

namespace CSAOpt {

    //
    //

    class TestState : public State {
    public:
        double coords[PROBLEM_SIZE];
        double energy;

        __CUDA__ size_t problemSize() { return PROBLEM_SIZE; }
    };


    class TestOpt : public Optimization {
    public:
        __CUDA__ virtual State &initialize(State &state, double *rands) const;

        __CUDA__ virtual State &generateNext(State &state, double *rands) const;

        __CUDA__ virtual OPT_TYPE_RETURN evaluate(State &state) const;

        __CUDA__ virtual OPT_TYPE_RETURN cool(double oldtemp) const;

        __CUDA__ double denormalizeNext(double rand) const;
    };


    __CUDA__ State &TestOpt::initialize(State &state, double *rands) const {
        return generateNext(state, rands);
    }

    __CUDA__ State &TestOpt::generateNext(State &state, double *rands) const {
        for (size_t i = 0; i < ((TestState &) state).problemSize(); ++i) {
            ((TestState &) state).coords[i] += denormalizeNext(rands[i]);
        }
        return state;
    }

    __CUDA__ double TestOpt::evaluate(State &state) const {
        double result, t1, t2;
        double *input = ((TestState &) state).coords;
        for (size_t i = 0; i < ((TestState &) state).problemSize() - 1; ++i) {
            t1 = (1 - input[i]);
            t2 = (input[i + 1] - input[i] * input[i]);
            result += t2 * t2 + 100 * (t1 * t1);
        }
        ((TestState &) state).energy = result;
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

    CSAOpt::TestOpt opt;
    CSAOpt::TestState state;
    state.energy = 42.0;

    double rands[]{1.0, 2.0};

    opt.initialize(state, rands);

    SECTION( "Temperature must be decreasing" ) {
        REQUIRE( opt.cool(99) < opt.cool(100));
    }

    SECTION( "2D Rosenbrock function has its minimum 0 at (1,1)" ){
        CSAOpt::TestState state;

        CSAOpt::TestState bestState;
        bestState.energy = HUGE_VAL;

        for(double i = -10; i <= 10; i+=.1 ){
            for(double j = -10; j<= 10; j+=.1){
                state.coords[0] = i;
                state.coords[1] = j;
                if( opt.evaluate(state) < bestState.energy){
                    bestState.energy = opt.evaluate(state);
                    bestState.coords[0] = state.coords[0];
                    bestState.coords[1] = state.coords[1];
                }
            }
        }

        REQUIRE( bestState.energy == Approx(0).scale(0).epsilon(1e7));
        REQUIRE( bestState.coords[0] == Approx(1).scale(0).epsilon(1e7));
        REQUIRE( bestState.coords[1] == Approx(1).scale(0).epsilon(1e7));
    }
}