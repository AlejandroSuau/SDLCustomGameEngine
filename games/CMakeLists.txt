INCLUDE_DIRECTORIES(include)

ADD_LIBRARY(
    flappy_bird
    flappy_bird/src/Bird.cpp
    flappy_bird/src/ScoreManager.cpp
    flappy_bird/src/Pipe.cpp
    flappy_bird/src/PipeFactory.cpp
    flappy_bird/src/FlappyBird.cpp
)