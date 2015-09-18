//
// Created by David Sere on 09/09/15.
//

#include "TestConfig.h"
#include "../Optimization.h"

#define PROBLEM_SIZE 20

namespace CGOpt {
    class TestTarget : public Target {
    public:
        double coords[PROBLEM_SIZE];
        double energy;

        __CUDA__ size_t problemSize() { return PROBLEM_SIZE; }
    };


    class TestOpt : public Optimization {
    public:
        __CUDA__ virtual Target &init_func(Target &state, double *rands) const;

        __CUDA__ virtual Target &next_func(Target &state, double *rands) const;

        __CUDA__ virtual double energy_func(Target &state) const;

        __CUDA__ virtual double temp_func(double oldtemp) const;

        __CUDA__ double denormalizeNext(double rand) const;
    };


    __CUDA__ Target &TestOpt::init_func(Target &state, double *rands) const {
        return next_func(state, rands);
    }

    __CUDA__ Target &TestOpt::next_func(Target &state, double *rands) const {
        for (size_t i = 0; i < ((TestTarget &) state).problemSize(); ++i) {
            ((TestTarget &) state).coords[i] += denormalizeNext(rands[i]);
        }
        return state;
    }

    __CUDA__ double TestOpt::energy_func(Target &state) const {
        double result, t1, t2;
        double *input = ((TestTarget &) state).coords;
        for (size_t i = 0; i < ((TestTarget &) state).problemSize() - 1; ++i) {
            t1 = (1 - input[i]);
            t2 = (input[i + 1] - input[i] * input[i]);
            result += t1 * t1 + 100 * (t2 * t2);
        }
        ((TestTarget &) state).energy = result;
        return result;
    }

    __CUDA__ double TestOpt::temp_func(double oldtemp) const {
        return oldtemp * .98;
    }

    double TestOpt::denormalizeNext(double rand) const {
        return rand * 2 - 1; // from 0..1 to -1..1
    }
}

TEST_CASE( "vectors can be sized and resized", "[vector]" ) {

    CGOpt::TestOpt opt;
    CGOpt::TestTarget target;
    target.energy = 42.0;

    double rands[]{1.0, 2.0};

    opt.init_func(target, rands);

//    REQUIRE( v.size() == 5 );
//    REQUIRE( v.capacity() >= 5 );

    SECTION( "Temperature must be decreasing" ) {
        REQUIRE( opt.temp_func(99) < opt.temp_func(100));
//        REQUIRE( );
    }
//    SECTION( "resizing smaller changes size but not capacity" ) {
//        v.resize( 0 );
//
//        REQUIRE( v.size() == 0 );
//        REQUIRE( v.capacity() >= 5 );
//    }
//    SECTION( "reserving bigger changes capacity but not size" ) {
//        v.reserve( 10 );
//
//        REQUIRE( v.size() == 5 );
//        REQUIRE( v.capacity() >= 10 );
//    }
//    SECTION( "reserving smaller does not change size or capacity" ) {
//        v.reserve( 0 );
//
//        REQUIRE( v.size() == 5 );
//        REQUIRE( v.capacity() >= 5 );
//    }
}