cmake_minimum_required(VERSION 3.5)
SET(COMPONENT_NAME module)

file(GLOB SOURCE_SRC *.c)
SET(INCLUDE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/include")

add_library(${COMPONENT_NAME} ${SOURCE_SRC})

target_include_directories(${COMPONENT_NAME} PUBLIC ${INCLUDE_DIR})

target_include_directories(${COMPONENT_NAME} PUBLIC "${JERRY_PATH}/jerry-core/include")
target_include_directories(${COMPONENT_NAME} PUBLIC "${JERRY_PATH}/jerry-ext/include")

register_component()
