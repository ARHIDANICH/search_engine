cmake_minimum_required(VERSION 3.5.0)
project(search_engine VERSION 0.1.0 LANGUAGES C CXX)

set(sources
    search_engine 
    main.cpp 
    test.cpp 
)

add_executable(${sources})

include(CTest)
enable_testing()

##JSON
include(FetchContent)
FetchContent_Declare(json URL https://github.com/nlohmann/json/releases/download/v3.11.3/json.tar.xz)
FetchContent_MakeAvailable(json)
##JSON

#GTEST
FetchContent_Declare(
googletest
URL https://github.com/google/googletest/archive/609281088cfefc76f9d0ce82e1ff6c30cc3591e5.zip
)
include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})
set(gtest_disable_pthreads on)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)
include(GoogleTest)
gtest_discover_tests(search_engine)
#GTEST

target_link_libraries(search_engine PRIVATE nlohmann_json::nlohmann_json gtest_main)