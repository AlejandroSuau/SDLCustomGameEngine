#pragma once

#include "engine/Rectangle.h"

// UI
static const Rectangle kRectBackground {0.f, 0.f, 480.f, 720.f};

// AliensList
static const float kAlienListXGap = 10.f;
static const float kAlienListYGap = 20.f;
static const std::size_t kAliensPerRow = 10;
static const std::size_t kAliensCount = 50;
static const float kStartingMovementFrequencySeconds = 0.5f;

// Alien
static const float kAlienWidth = 26.f;
static const float kAlienHeight = 20.f;
static const float kAlienMovementStepX = kAlienWidth * 0.5f;
static const float kAlienMovementStepY = kAlienHeight * 0.5f;

static const Rectangle kSourceAlienA1 {0.f, 0.f, kAlienWidth, kAlienHeight};
static const Rectangle kSourceAlienA2 {kAlienWidth, 0.f, kAlienWidth, kAlienHeight};

// Defense Blocks
static const float kDefenseBlockWidth = 60.f;
static const float kDefenseBlockHeight = 40.f;
static const int kDefenseBlockLifes = 3;
static const float kGapBetweenDefenses = 40.f;

// Projectile
static const float kProjectileVelocity = 350.f;
static const float kProjectileWidth = 1.f;
static const float kProjectileHeight = 6.f;

// Ship
static const float kShipVelocity = 200.f;
static const float kShipWidth = 20.f;
static const float kShipHeight = 20.f;