find_package(GTest)
# include(FetchContent)
# FetchContent_Declare(googletest
#     GIT_REPOSITORY      https://github.com/google/googletest.git
#     GIT_TAG             v1.14.0)
# set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
# FetchContent_GetProperties(googletest)
# if(NOT googletest_POPULATED)
#     FetchContent_Populate(googletest)
#     set(CMAKE_SUPPRESS_DEVELOPER_WARNINGS 1 CACHE BOOL "")
#     add_subdirectory(${googletest_SOURCE_DIR} ${googletest_BINARY_DIR} EXCLUDE_FROM_ALL)
#     unset(CMAKE_SUPPRESS_DEVELOPER_WARNINGS)
# endif()

# include_directories(${GTEST_INCLUDE_DIRS} SYSTEM)


set(COMMON_BASE
    main.cpp
)

set(SPLINART_TESTS
    test_circle.cpp
    test_spline.cpp
)

foreach(filename IN LISTS SPLINART_TESTS)
    string(REPLACE ".cpp" "" targetname ${filename})
    add_executable(${targetname} ${COMMON_BASE} ${filename})
    target_link_libraries(${targetname} PRIVATE splinart gtest_main gtest)
endforeach()

add_executable(test_splinart ${COMMON_BASE} ${SPLINART_TESTS})
target_link_libraries(test_splinart PRIVATE splinart gtest_main gtest)
