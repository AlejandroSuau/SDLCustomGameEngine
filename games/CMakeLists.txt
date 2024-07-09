INCLUDE_DIRECTORIES(include)

FILE(GLOB_RECURSE SOURCES "flappy_bird/src/*.cpp")

ADD_LIBRARY(
    flappy_bird
    ${SOURCES}
)