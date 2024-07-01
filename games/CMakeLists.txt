INCLUDE_DIRECTORIES(include)

ADD_LIBRARY(
    flappy_bird
    flappy_bird/src/Bird.cpp
    flappy_bird/src/ScoreManager.cpp
    flappy_bird/src/Pipe.cpp
    flappy_bird/src/PipesPair.cpp
    flappy_bird/src/PipesPairFactory.cpp
    flappy_bird/src/SnowStorm.cpp
    flappy_bird/src/FlappyBird.cpp
)