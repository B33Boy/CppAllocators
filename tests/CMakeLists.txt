include(GoogleTest)

function(add_test name file)
    add_executable(${name} ${file})
    target_link_libraries(${name} PRIVATE GTest::gtest_main allocators_lib)
    gtest_discover_tests(${name})
endfunction()

add_test(system_test system.cpp)
add_test(linear_test linear.cpp)