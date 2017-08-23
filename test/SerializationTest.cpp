//
// Created by David Sere on 14/09/15.
//

#include "TestConfig.h"
#include "../src/State.h"
#include <regex>

struct InnerObject {
    int intAttr;

    REGISTER(intAttr);
};

class TestState : public CSAOpt::State {
public:
    std::string stringAttr;
    unsigned long long numberAttr;
    std::vector<std::string> vectorAttr;

    InnerObject innerObjectAttr;

    REGISTER(stringAttr, numberAttr, vectorAttr, innerObjectAttr);
};

TEST_CASE( "States can be serialized and deserialized", "[target]" ) {
    TestState t;
    t.stringAttr = std::string{"test string 42"};
    t.numberAttr = 42;
    t.vectorAttr.push_back(std::string{"another test string"});
    t.innerObjectAttr.intAttr = 24;

    SECTION( "Serialization produces correct json" ) {
        std::stringstream ss;

        cereal::JSONOutputArchive oarchive(ss);
        oarchive(t);

        std::string jsonString = ss.str();

        std::smatch match;
        std::regex stringRegex("\"value\\d+\"\\s*:\\s*\"test string 42\"");
        REQUIRE( std::regex_search(jsonString, match, stringRegex));

        std::regex numRegex("\"value\\d+\"\\s*:\\s*\"?42\"?"); //ull is platform dependent, might be a string or a number
        REQUIRE( std::regex_search(jsonString, match, numRegex) );

        std::regex listRegex("\"value\\d+\": \\[\\s*\"another test string\"\\s*\\]");
        REQUIRE( std::regex_search(jsonString, match, listRegex) );

        std::regex objectRegex("\"value\\d+\": \\{\\s*\"value\\d+\": 24\\s*\\}");
        REQUIRE( std::regex_search(jsonString, match, objectRegex) );
    }

    SECTION( "Deserialization should produce the same object" ) {

        std::stringstream ss;

        {
            cereal::JSONOutputArchive oarchive(ss);
            oarchive(t);
        }

        {
            cereal::JSONInputArchive iarchive(ss);

            TestState deserialized;
            iarchive(deserialized);

            REQUIRE( deserialized.numberAttr == t.numberAttr);
            REQUIRE( deserialized.stringAttr.compare(t.stringAttr) == 0);
            REQUIRE( deserialized.vectorAttr == t.vectorAttr);
            REQUIRE( deserialized.innerObjectAttr.intAttr == t.innerObjectAttr.intAttr);
        }
    }
}