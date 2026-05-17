add_executable(system_example
    system.cpp
)

target_link_libraries(system_example PRIVATE allocators_lib)