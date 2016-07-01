//
// Created by David Sere on 28/09/15.
//

#include "TestConfig.h"
#include "../src/Options.h"

TEST_CASE("Some Test", "[options]"){
    SECTION("Options can be initialized from factory method"){
        CSAOpt::Options opt = CSAOpt::Options::defaultOptions();

        REQUIRE( opt.optimizationType == CSAOpt::Options::SINGLEPRECISION);
    }
}