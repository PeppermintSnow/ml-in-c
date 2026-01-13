file(GLOB TESTS "*.c")

foreach(test_src ${TESTS})
    get_filename_component(test_name ${test_src} NAME_WE)
    add_executable(${test_name} ${test_src})
    target_link_libraries(${test_name} ml_in_c)
    add_test(NAME ${test_name} COMMAND ${test_name})
endforeach()
