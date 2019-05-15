cmake_minimum_required(VERSION 3.5)
SET(PROJECT_NAME effect)

SET(JERRY_PATH /Users/lan/Documents/workspace/jerryscript)

SET(MEM_HEAP_SIZE_KB 64)

project(${PROJECT_NAME})

aux_source_directory(src SOURCE_DIR)

add_executable(${PROJECT_NAME} ${SOURCE_DIR})

# link default lib
target_link_libraries(${PROJECT_NAME} "jerry-core" "jerry-ext" "jerry-port-default-minimal")

# include default header files.
target_include_directories(${PROJECT_NAME} PUBLIC "${JERRY_PATH}/jerry-core/include")
target_include_directories(${PROJECT_NAME} PUBLIC "${JERRY_PATH}/jerry-ext/include")

# register component. Lib of all components will be linked and header files will be included to project.
function(register_component)
  target_include_directories(${PROJECT_NAME} PUBLIC ${INCLUDE_DIR})
  target_link_libraries(${PROJECT_NAME} ${COMPONENT_NAME})
endfunction(register_component)

# add external component
add_subdirectory(${JERRY_PATH} jerryscript)

# add internal component
add_subdirectory(components/light)
add_subdirectory(components/module)
