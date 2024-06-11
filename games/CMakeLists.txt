INCLUDE_DIRECTORIES(include)

ADD_LIBRARY(
    space_invaders
    space_invaders/src/SpaceInvaders.cpp
    space_invaders/src/ScoreManager.cpp
    space_invaders/src/Alien.cpp
    space_invaders/src/AlienList.cpp
    space_invaders/src/Ship.cpp
    space_invaders/src/DefenseBlock.cpp
    space_invaders/src/Projectile.cpp
)