cmake_minimum_required(VERSION 2.6)

project(test)
 
# Setup testing

enable_testing()

find_package(GTest REQUIRED)

include_directories(${GTEST_INCLUDE_DIR} )




# Add test cpp file
#[[
add_executable(runUnitTests
processing_test.cpp
)
]]


add_executable(runUnitTests
box0_test.cpp
        detect_allocator_type_test.cpp
        detect_writingtype_test.cpp
        boxmk_test.cpp boxinl_test.cpp
        single_test.cpp
        detect_iterable_test.cpp
        app_rekurs_test.cpp
        boxm_test.cpp
        )

set(CMAKE_POSITION_INDEPENDENT_CODE ON) 

# Link test executable against gtest & gtest_main

target_link_libraries(runUnitTests ${GTEST_LIBRARY_DEBUG} ${GTEST_MAIN_LIBRARY_DEBUG} pthread ) #pthread i had to add (? -k.h.)


##target_link_libraries(runUnitTests gtest  pthread )

add_test(

    NAME runUnitTests

    COMMAND runUnitTests

)

 
