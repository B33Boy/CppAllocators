add_executable(system_example
    system.cpp
)

add_executable(linear_example
    linear.cpp
)


target_link_libraries(system_example PRIVATE allocators_lib)
target_link_libraries(linear_example PRIVATE allocators_lib)