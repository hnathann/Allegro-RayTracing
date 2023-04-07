cmake_minimum_required(VERSION 3.23)
project(RayTracingV1_0 C)

set(CMAKE_C_STANDARD 99)

add_executable(RayTracingV1_0 main.c)

IF(WIN32)
    target_link_libraries(RayTracingV1_0 -lmingw32 -lallegro-5.0.10-monolith-md-debug)
ELSE()
    INCLUDE_DIRECTORIES(/opt/homebrew/Cellar/allegro/5.2.8.0_2/include)
    LINK_DIRECTORIES(/opt/homebrew/Cellar/allegro/5.2.8.0_2/lib)
    file(GLOB LIBRARIES "/opt/homebrew/Cellar/allegro/5.2.8.0_2/lib/*.dylib")
    message("LIBRARIES = ${LIBRARIES}")
    TARGET_LINK_LIBRARIES(RayTracingV1_0 ${LIBRARIES})

ENDIF(WIN32)
