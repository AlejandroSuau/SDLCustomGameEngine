#pragma once

#include "engine/Color.h"
#include "engine/Rectangle.h"

#include <string>

// DEBUG MODE
static const bool DEBUG = 0;

static const std::string kAssetsFolder = "assets/flappy_bird/";

// Environment
static const float kScrollingVelocityX = 100.f;

// UI
static const Rectangle kRectBackground {0.f, 0.f, 288.f, 512.f};
static const Rectangle kRectTutorial {0.f, 25.f, 184.f, 267.f};
static const Rectangle kRectGameOver {0.f, 0.f, 192.f, 42.f};

// Score
static const float kScorePositionY = 25.f;
static const float kNumberTextureWidth = 24.f;
static const float kNumberTextureHeight = 36.f;

// Bird
static const float kBirdWidth = 34.f;
static const float kBirdHeight = 24.f;
static const Color kBirdHitBoxColor {255, 255, 255, 255};

static const float kBirdVelocity = 400.f;
static const float kBirdGravity = 1000.f;
static const float kBirdJumpForce = -300.f;

static const float kBirdFloatingAmplitude = 25.f;
static const float kBirdFloatingVelocity = 5.f;

// Pipe
static const float kPipeWidth = 52.f;
static const float kPipeMinimumHeight = 50.f;
static const Color kPipeHitBoxColor {100, 163, 119, 255};

// PipesPair
const float kPipesPairGap = 105.f;

// Floor
static const float kFloorHeight = 112.f;
static const Color kFloorHitBoxColor {116, 99, 78, 255};
