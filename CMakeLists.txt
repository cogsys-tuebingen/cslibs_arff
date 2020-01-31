cmake_minimum_required(VERSION 2.8.3)
project(cslibs_arff)

## Find catkin macros and libraries
## if COMPONENTS list like find_package(catkin REQUIRED COMPONENTS xyz)
## is used, also find other catkin packages
find_package(catkin REQUIRED)

include(cmake/add_unit_test.cmake)
include(cmake/c++11.cmake)

set(CSLIBS_ARFF_BUILD_TESTS True)

include_directories(
    include
)

catkin_package(
  INCLUDE_DIRS include
  LIBRARIES ${PROJECT_NAME}
)

## Declare a C++ library
add_library(${PROJECT_NAME}
   src/library/arff_attr.cpp
   src/library/arff_data.cpp
   src/library/arff_instance.cpp
   src/library/arff_lexer.cpp
   src/library/arff_parser.cpp
   src/library/arff_scanner.cpp
   src/library/arff_token.cpp
   src/library/arff_utils.cpp
   src/library/arff_value.cpp
)

add_custom_target(show_${PROJECT_NAME}_headers_in_qt SOURCES
    include/cslibs_arff/arff_attr.h
    include/cslibs_arff/arff_data.h
    include/cslibs_arff/arff_instance.h
    include/cslibs_arff/arff_lexer.h
    include/cslibs_arff/arff_parser.h
    include/cslibs_arff/arff_scanner.h
    include/cslibs_arff/arff_token.h
    include/cslibs_arff/arff_utils.h
    include/cslibs_arff/arff_value.h
)

if(${CSLIBS_ARFF_BUILD_TESTS})
    include_directories(${GTEST_INCLUDE_DIRS})

    set(TEST_SRCS
        src/tests/arff_attr_t.cpp
        src/tests/arff_data_t.cpp
        src/tests/arff_instance_t.cpp
        src/tests/arff_lexer_t.cpp
        src/tests/arff_parser_t.cpp
        src/tests/arff_scanner_t.cpp
        src/tests/arff_token_t.cpp
        src/tests/arff_utils_t.cpp
        src/tests/arff_value_t.cpp
        src/tests/main.cpp)

    add_unit_test(${PROJECT_NAME}_tests
                  "${TEST_SRCS}"
                  "${PROJECT_NAME}"
                   ${CMAKE_CURRENT_LIST_DIR})
    target_compile_definitions(${PROJECT_NAME}_tests
        PRIVATE
            -DTEST_DIRECTORY="${CMAKE_CURRENT_LIST_DIR}/src/tests"
    )

endif()

install(DIRECTORY include/${PROJECT_NAME}/
        DESTINATION ${CATKIN_PACKAGE_INCLUDE_DESTINATION})

# WORKING_DIRECTORY  ${CMAKE_BINARY_DIR}
