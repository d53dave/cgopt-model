//
// Created by David Sere on 28/09/15.
//

#include "TestConfig.h"
#include "../src/Options.h"

TEST_CASE("Some Test", "[options]"){
    SECTION("Options can be initialized from factory method"){
        CGOpt::Options opt = CGOpt::Options::defaultOptions();

        REQUIRE( opt.optimizationType == CGOpt::Options::SINGLEPRECISION);
    }
}