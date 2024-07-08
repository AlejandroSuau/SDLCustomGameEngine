#pragma once

#include "engine/Rectangle.h"

// Masks & Layers
static const unsigned int kShipLayer = 1; // 0001
static const unsigned int kShipMask = 12; // 0 1100 // enemy, enemy projectile
static const unsigned int kShipProjectileLayer = 2; // 0010
static const unsigned int kShipProjectileMask = 28; // 1 1100 // block, alien, enemy projectile

static const unsigned int kAlienLayer = 4; // 0100
static const unsigned int kAlienMask = 3; // 0 0011 // ship projectile, ship
static const unsigned int kAlienProjectileLayer = 8; // 0 1000
static const unsigned int kAlienProjectileMask = 19; // 1 0011 // block, ship, ship project

static const unsigned int kDefenseBlockLayer = 16; // 1 0000
static const unsigned int kDefenseBlockMask = 10; // 0 1010 // ship projectile, alien projectile

// UI
static const Rectangle kRectBackground {0.f, 0.f, 520.f, 720.f};

// AliensList
static const float kAlienListXGap = 10.f;
static const float kAlienListYGap = 20.f;
static const std::size_t kAliensPerRow = 10;
static const std::size_t kAliensCount = 50;
static const float kStartingMovementFrequencySeconds = 0.5f;
static const float kMaxProjectileSpawnTime = 3.f;
static const float kMinProjectileSpawnTime = 1.f;

// Alien
static const float kAlienWidth = 26.f;
static const float kAlienHeight = 20.f;
static const float kAlienMovementStepX = kAlienWidth * 0.5f;
static const float kAlienMovementStepY = kAlienHeight * 0.5f;

static const Rectangle kSourceAlienA1 {0.f, 0.f, kAlienWidth, kAlienHeight};
static const Rectangle kSourceAlienA2 {kAlienWidth, 0.f, kAlienWidth, kAlienHeight};

// Defense Blocks
static const float kDefenseBlockWidth = 8.f;
static const float kDefenseBlockHeight = 5.f;
static const int kDefenseBlockLifes = 3;
static const float kGapBetweenDefenses = 40.f;

// Projectile
static const float kProjectileVelocity = 350.f;
static const float kProjectileWidth = 5.f;
static const float kProjectileHeight = 5.f;

// Ship
static const float kShipVelocity = 200.f;
static const float kShipWidth = 20.f;
static const float kShipHeight = 20.f;