file(GLOB_RECURSE ENGINE_SOURCES "engine/*.cpp")

ADD_LIBRARY(
    engine
    ${ENGINE_SOURCES}
)