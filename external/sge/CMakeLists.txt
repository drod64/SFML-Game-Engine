cmake_minimum_required(VERSION 3.27.3)

project(SGE)

set(SOURCE_FILES
    # Utility
    src/util/Action.cpp
    src/util/Animation.cpp
    src/util/Assets.cpp
    src/util/GameEngine.cpp
    src/util/Scene.cpp

    # Components
    src/components/Component.cpp
    src/components/CAnimation.cpp
    src/components/CBoundingBox.cpp
    src/components/CTransform.cpp
    src/components/CShape.cpp
    src/components/CCollision.cpp
    src/components/CScore.cpp
    src/components/CLifespan.cpp
    src/components/CInput.cpp
    
    # Entities
    src/entities/Entity.cpp
    src/entities/EntityManager.cpp)

add_library(${PROJECT_NAME} STATIC ${SOURCE_FILES})

# Adding the custom Math Library
target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_SOURCE_DIR}/external/sm/include)
target_link_directories(${PROJECT_NAME} PRIVATE ${CMAKE_SOURCE_DIR}/external/sm)
target_link_libraries(${PROJECT_NAME} SM)

# NOTE: this library expects the SFML variables to have already been found (in the root level CMakeLists.txt)
if (SFML_FOUND)
target_include_directories(${PROJECT_NAME} 
PUBLIC ${SFML_INCLUDE_DIR}
PUBLIC include)
target_link_libraries(${PROJECT_NAME} ${SFML_LIBRARIES} ${SFML_DEPENDENCIES})
endif ()
# Once SFML is properly linked to, we include the libraries own header files.

target_include_directories(${PROJECT_NAME} PUBLIC include)