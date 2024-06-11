#pragma once

#include <SDL2/SDL_image.h>

#include "engine/IGame.h"
#include "engine/Engine.h"
#include "engine/timer/CountdownTimer.h"

#include "Ship.h"
#include "DefenseBlock.h"
#include "AlienList.h"
#include "ScoreManager.h"

#include <vector>
#include <memory>
#include <array>
#include <string>

class SpaceInvaders : public IGame {
public:
    SpaceInvaders();

    void Start() override;
    void Update(float dt) override;
    void Render() override;

    void OnMouseEvent(EMouseEventType event_type, int x, int y) override;
    void OnKeyboardEvent(EKeyEventType event_type, SDL_Scancode scancode) override;

private:
    Engine engine_;
    Ship ship_;
    std::array<DefenseBlock, 4> defenses_;
    AlienList aliens_;
    ScoreManager score_manager_;

    void ResetGame();

    bool ProcessProjectileCollisionWithDefenses(const Projectile& projectile);
};