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

add_executable(uap-test ${SRCS} )
target_link_libraries(uap-test gtest_main uap)
set_target_properties(uap-test PROPERTIES OUTPUT_NAME "test")

include(GoogleTest)
gtest_discover_tests(uap-test)



install(TARGETS uap-test
        EXPORT uap-testTargets
        CONFIGURATIONS Debug
        LIBRARY DESTINATION lib
        ARCHIVE DESTINATION lib
        RUNTIME DESTINATION bin
        PUBLIC_HEADER DESTINATION include
        )


install(TARGETS uap-test 
        EXPORT uap-testTargets
        CONFIGURATIONS Release
        LIBRARY DESTINATION lib
        ARCHIVE DESTINATION lib
        RUNTIME DESTINATION bin
        PUBLIC_HEADER DESTINATION include
        )