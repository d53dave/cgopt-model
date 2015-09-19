cmake_minimum_required(VERSION 3.3)
project(model)

set (PROJECT_INCLUDE_DIR ${PROJECT_SOURCE_DIR}/include)
set(CMAKE_CXX_STANDARD 11) # adds -std=c++11
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(SOURCE_FILES main.cpp ModelSettings.h Target.cpp Target.h Optimization.h Options.h)

include_directories("${PROJECT_INCLUDE_DIR}")
add_executable(model ${SOURCE_FILES})

enable_testing()
file(GLOB TEST_FILES "test/*.cpp")

#Run through each source
foreach(testFile ${TEST_FILES})
    #Extract the filename without an extension (NAME_WE)
    get_filename_component(testName ${testFile} NAME_WE)

    #Add compile target
    add_executable(${testName} ${testFile})
    add_test(NAME ${testName} COMMAND ${testName} )
endforeach(testFile)

