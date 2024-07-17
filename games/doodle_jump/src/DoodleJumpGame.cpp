#include "doodle_jump/include/DoodleJumpGame.h"

DoodleJumpGame::DoodleJumpGame() 
    : engine_("Doodle Jump", 400, 750) 
    , player_(engine_)
    , platform_factory_(engine_)
    , is_moving_down_platforms_(false) {
    platform_factory_.InstantiatePlatforms(platforms_, -1200.f, engine_.GetWindowHeight());
}

void DoodleJumpGame::OnMouseEvent(EMouseEventType event_type, int x, int y) {
    return;
}

void DoodleJumpGame::OnKeyboardEvent(EKeyEventType event_type, SDL_Scancode scancode) {
    player_.OnKeyboardEvent(event_type, scancode);
}

void DoodleJumpGame::Start() {
    engine_.Run(*this);
}

void DoodleJumpGame::Update(float dt) {
    player_.Update(dt);
    
    const auto player_position = player_.GetPosition();
    if (player_position.y < 400.f && player_.IsJumping()) {
        is_moving_down_platforms_ = true;
        platform_factory_.InstantiatePlatforms(platforms_, -800.f, -400.f);
    }
    
    if (player_.IsFalling()) {
        is_moving_down_platforms_ = false;
    }

    if (is_moving_down_platforms_) {
        MoveDownPlatforms(dt);
    }
}

void DoodleJumpGame::MoveDownPlatforms(float dt) {
    for (auto& platform : platforms_) {
        auto pos = platform->GetPosition();
        pos.y += dt * 100.f;
        platform->SetPosition(pos);
    }
}

void DoodleJumpGame::Render() {
    player_.Render();
    
    for (auto& platform : platforms_) {
        platform->Render();
    }
}

