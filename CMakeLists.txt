cmake_minimum_required(VERSION 3.27.3)

project(SFML_GAME_ENGINE)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17 -static")
set(CMAKE_CXX_STANDARD 17)

set(SOURCE_FILES
    src/main.cpp)

if (CMAKE_BUILD_TYPE STREQUAL "Release")
    add_executable(${PROJECT_NAME} WIN32 ${SOURCE_FILES})
else ()
    add_executable(${PROJECT_NAME} ${SOURCE_FILES})
endif ()

set(SFML_ROOT ${CMAKE_SOURCE_DIR}/external/SFML-2.5.1)
set(SFML_STATIC_LIBRARIES TRUE)

set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake_modules")

find_package(SFML REQUIRED COMPONENTS audio graphics window system)
if (SFML_FOUND)
target_include_directories(${PROJECT_NAME} 
PUBLIC ${SFML_INCLUDE_DIR}
PUBLIC include)
target_link_libraries(${PROJECT_NAME} ${SFML_LIBRARIES} ${SFML_DEPENDENCIES})
endif ()

# After SFML is found and linked correctly, link to the custom libraries.
add_subdirectory(${CMAKE_SOURCE_DIR}/external/sm)
target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_SOURCE_DIR}/external/sm/include)
target_link_directories(${PROJECT_NAME} PRIVATE ${CMAKE_SOURCE_DIR}/external/sm)
target_link_libraries(${PROJECT_NAME} SM)

add_subdirectory(${CMAKE_SOURCE_DIR}/external/spe)
target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_SOURCE_DIR}/external/spe/include)
target_link_directories(${PROJECT_NAME} PRIVATE ${CMAKE_SOURCE_DIR}/external/spe)
target_link_libraries(${PROJECT_NAME} SPE)

add_subdirectory(${CMAKE_SOURCE_DIR}/external/sge)
target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_SOURCE_DIR}/external/sge/include)
target_link_directories(${PROJECT_NAME} PRIVATE ${CMAKE_SOURCE_DIR}/external/sge)
target_link_libraries(${PROJECT_NAME} SGE)

add_subdirectory(${CMAKE_SOURCE_DIR}/src/TestingEngine)
target_include_directories(${PROJECT_NAME} PUBLIC ${CAMKE_SOURCE_DIR}/src/TestingEngine/include)
target_link_directories(${PROJECT_NAME} PRIVATE ${CMAKE_SOURCE_DIR}/src/TestingEngine)
target_link_libraries(${PROJECT_NAME} TestingEngine)