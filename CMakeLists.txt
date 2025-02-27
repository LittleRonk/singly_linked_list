cmake_minimum_required(VERSION 3.1)

project(singly_linked_list LANGUAGES C)

add_library(singly_linked_list
    STATIC 
    ${PROJECT_SOURCE_DIR}/src/singly_linked_list.c)

target_include_directories(singly_linked_list PUBLIC ${PROJECT_SOURCE_DIR}/include)

add_executable(driver ${PROJECT_SOURCE_DIR}/examples/driver.c)

target_link_libraries(driver PRIVATE singly_linked_list)
