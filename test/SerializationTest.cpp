//
// Created by David Sere on 14/09/15.
//

#include "TestConfig.h"
#include "../Target.h"
#include <regex>

struct InnerObject {
    int intAttr;

    REGISTER(intAttr);
};

class TestTarget : public CGOpt::Target {
public:
    std::string stringAttr;
    unsigned long long numberAttr;
    std::vector<std::string> vectorAttr;

    InnerObject innerObjectAttr;

    enum {arrSize = 3}; //enum trick to allow in-class initializer
    static constexpr double staticAttr1[arrSize]{4.2, 1337};

    REGISTER(stringAttr, numberAttr, vectorAttr, innerObjectAttr);
};

TEST_CASE( "Targets can be serialized and deserialized", "[target]" ) {
    TestTarget t;
    t.stringAttr = std::string{"test string 42"};
    t.numberAttr = 42;
    t.vectorAttr.push_back(std::string{"another test string"});
    t.innerObjectAttr.intAttr = 24;

    SECTION( "Serialization produces correct json" ) {

        std::stringstream ss; // any stream can be used

        cereal::JSONOutputArchive oarchive(ss); // Create an output archive
        oarchive(t); // Write the data to the archive

        std::string jsonString = ss.str();

        std::smatch match;
        std::regex stringRegex("\"value\\d+\"\\s*:\\s*\"test string 42\"");
        REQUIRE( std::regex_search(jsonString, match, stringRegex));

        std::regex numRegex("\"value\\d+\"\\s*:\\s*42");
        REQUIRE( std::regex_search(jsonString, match, numRegex) );

        std::regex listRegex("\"value\\d+\": \\[\\s*\"another test string\"\\s*\\]");
        REQUIRE( std::regex_search(jsonString, match, listRegex) );

        std::regex objectRegex("\"value\\d+\": \\{\\s*\"value\\d+\": 24\\s*\\}");
        REQUIRE( std::regex_search(jsonString, match, objectRegex) );
    }

    SECTION( "Deserialization should not include the static attributes (which we did not include)" ) {
        std::stringstream ss; // any stream can be used

        cereal::JSONOutputArchive oarchive(ss); // Create an output archive
        oarchive(t); // Write the data to the archive

        std::string jsonString = ss.str();

        std::smatch match;
        std::regex staticArrayRegex("4\\.2|1337");
        REQUIRE_FALSE( std::regex_search(jsonString, match, staticArrayRegex));
    }

    SECTION( "Deserialized object should still have the static array" ) {
        std::stringstream ss; // any stream can be used

        cereal::JSONOutputArchive oarchive(ss); // Create an output archive
        oarchive(t); // Write the data to the archive

        std::string jsonString = ss.str();

        std::smatch match;
        std::regex staticArrayRegex("4\\.2|1337");
        REQUIRE_FALSE( std::regex_search(jsonString, match, staticArrayRegex));
    }

    SECTION( "Deserialization should produce the same object" ) {

        std::stringstream ss; // any stream can be used

        {
            cereal::JSONOutputArchive oarchive(ss); // Create an output archive
            oarchive(t); // Write the data to the archive
        }

        {
            cereal::JSONInputArchive iarchive(ss); // Create an input archive

            TestTarget deserialized;
            iarchive(deserialized); // Read the data from the archive

            REQUIRE( deserialized.numberAttr == t.numberAttr);
            REQUIRE( deserialized.stringAttr.compare(t.stringAttr) == 0);
            REQUIRE( deserialized.vectorAttr == t.vectorAttr);
            REQUIRE( deserialized.innerObjectAttr.intAttr == t.innerObjectAttr.intAttr);
        }
    }
}