add_executable(system_example
    system.cpp
)

add_executable(linear_example
    linear.cpp
)

add_executable(stack_example
    stack.cpp
)

target_link_libraries(system_example PRIVATE allocators_lib)
target_link_libraries(linear_example PRIVATE allocators_lib)
target_link_libraries(stack_example PRIVATE allocators_lib)