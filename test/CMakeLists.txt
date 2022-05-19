cmake_minimum_required(VERSION 3.10)
project(uap-test)


# GoogleTest requires at least C++11
set(CMAKE_CXX_STANDARD 17)

include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/609281088cfefc76f9d0ce82e1ff6c30cc3591e5.zip
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)





enable_testing()

aux_source_directory(${PROJECT_SOURCE_DIR} SRCS)

add_executable(uaptest ${SRCS} )
target_link_libraries(uaptest gtest_main uap)

include(GoogleTest)
gtest_discover_tests(uaptest)



install(TARGETS uaptest
        EXPORT uap-testTargets
        CONFIGURATIONS Debug
        LIBRARY DESTINATION Debug/lib
        ARCHIVE DESTINATION Debug/lib
        RUNTIME DESTINATION Debug/bin
        PUBLIC_HEADER DESTINATION include
        )


install(TARGETS uaptest 
        EXPORT uap-testTargets
        CONFIGURATIONS Release
        LIBRARY DESTINATION Release/lib
        ARCHIVE DESTINATION Release/lib
        RUNTIME DESTINATION Release/bin
        PUBLIC_HEADER DESTINATION include
        )