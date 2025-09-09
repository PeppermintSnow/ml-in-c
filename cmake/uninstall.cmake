# Remove installed files

# Remove library
if(EXISTS "${CMAKE_INSTALL_PREFIX}/lib/libml_in_c.a")
    file(REMOVE "${CMAKE_INSTALL_PREFIX}/lib/libml_in_c.a")
endif()

# Remove headers
file(GLOB headers "${CMAKE_INSTALL_PREFIX}/include/ml-in-c/*.h")
foreach(header ${headers})
    file(REMOVE ${header})
endforeach()

message(STATUS "Library uninstalled successfuly.")
