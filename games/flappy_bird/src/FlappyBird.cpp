#include "flappy_bird/include/FlappyBird.h"

#include "flappy_bird/include/Constants.h"

FlappyBird::FlappyBird() 
    : engine_("Flappy Bird",
              static_cast<int>(kRectBackground.w),
              static_cast<int>(kRectBackground.h))
    , bird_(engine_, static_cast<float>(engine_.GetWindowWidth()) * 0.45f, static_cast<float>(engine_.GetWindowHeight()) * 0.45f)
    , score_manager_(engine_)
    , pipe_spawn_timer_(2.f)
    , floor1_(0.f,
              static_cast<float>(engine_.GetWindowHeight()) - kFloorHeight,
              static_cast<float>(engine_.GetWindowWidth()),
              kFloorHeight)
    , floor2_(static_cast<float>(engine_.GetWindowWidth()),
              static_cast<float>(engine_.GetWindowHeight()) - kFloorHeight,
              static_cast<float>(engine_.GetWindowWidth()),
              kFloorHeight)
    , pipes_pair_factory_(engine_, floor1_)
    , snow_storm_(engine_, 5.f)
    , tutorial_(kRectTutorial.x + kRectBackground.w * 0.5f - kRectTutorial.w * 0.5f,
                kRectTutorial.y,
                kRectTutorial.w,
                kRectTutorial.h)
    , gameover_(kRectGameOver.x + kRectBackground.w * 0.5f - kRectGameOver.w * 0.5f,
                kRectBackground.w * 0.5f,
                kRectGameOver.w,
                kRectGameOver.h)
    , texture_tutorial_(nullptr)
    , texture_gameover_(nullptr)
    , texture_background_(nullptr)
    , texture_floor_(nullptr) {
    
    texture_tutorial_ = engine_.LoadTexture(kAssetsFolder + "message.png");
    texture_gameover_ = engine_.LoadTexture(kAssetsFolder + "gameover.png");
    texture_background_ = engine_.LoadTexture(kAssetsFolder + "background-night.png");
    texture_floor_ = engine_.LoadTexture(kAssetsFolder + "base.png");
}

void FlappyBird::Start() {
    engine_.Run(*this);
}

void FlappyBird::OnMouseEvent(EMouseEventType event_type, int x, int y) {
    return;
}

void FlappyBird::OnKeyboardEvent(EKeyEventType event_type, SDL_Scancode scancode) {
    if (bird_.IsDead()) {
        bool space_key_pressed = (event_type == EKeyEventType::KEY_DOWN && scancode == SDL_SCANCODE_SPACE);
        if (space_key_pressed) ResetGame();
    } else {
        bird_.OnKeyboardEvent(event_type, scancode);
    }
}

void FlappyBird::ResetGame() {
    bird_.Reset();
    score_manager_.Reset();
    pipes_.clear();
}

void FlappyBird::Update(float dt) {
    snow_storm_.Update(dt);

    if (bird_.IsDead()) return;

    bird_.Update(dt);
    
    IncreaseScoreOnCheckpointCollision();
    NofityBirdOnPipeCollision();
    NofityBirdOnFloorCollision();

    bool should_move_floor = (bird_.IsStanding() || bird_.IsFlying());
    if (should_move_floor) {
        MoveFloor(dt);
    }

    if (bird_.IsFlying()) {
        SpawnPipesIfNeeded(dt);
        MovePipes(dt);
        RemoveOutOfScreenPipes();
    }
}

void FlappyBird::IncreaseScoreOnCheckpointCollision() {
    bool found_collision = false;
    std::size_t i = 0;
    while (!found_collision && i < pipes_.size()) {
        if (pipes_[i]->DoesBirdCollidesWithScoreCheck(bird_)) {
            pipes_[i]->OnBirdCollisionWithScoreCheck();
            score_manager_.IncreaseScoreOneUnit();
        }
        ++i;
    }
}

void FlappyBird::NofityBirdOnPipeCollision() {
    bool found_collision = false;
    std::size_t i = 0;
    while (!found_collision && i < pipes_.size()) {
        if (pipes_[i]->DoesBirdCollidesWithAPipe(bird_)) {
            bird_.OnCollisionWithPipe();
            found_collision = true;
        }
        ++i;
    }
}

void FlappyBird::NofityBirdOnFloorCollision() {
    const bool collision_detected = (floor1_.CollidesWith(bird_.GetHitBox()) ||
                                     floor2_.CollidesWith(bird_.GetHitBox()));
    if (collision_detected) {
        bird_.OnCollisionWithFloor(floor1_.y);
    }
}

void FlappyBird::SpawnPipesIfNeeded(float dt) {
    pipe_spawn_timer_.Update(dt);
    if (!pipe_spawn_timer_.DidFinish()) return;

    AddPipesPair();
    pipe_spawn_timer_.Reset();
}

void FlappyBird::MoveFloor(float dt) {
    const auto dx = kScrollingVelocityX * dt;
    floor1_.x -= dx;
    floor2_.x -= dx;
    if (floor1_.x + floor1_.w <= 0) {
        floor1_.x = static_cast<float>(engine_.GetWindowWidth());
    }
    if (floor2_.x + floor2_.w <= 0) {
        floor2_.x = static_cast<float>(engine_.GetWindowWidth());
    }
}

void FlappyBird::MovePipes(float dt) {
    for (auto& pipe : pipes_) pipe->Update(dt);
}

void FlappyBird::AddPipesPair() {
    pipes_.push_back(std::move(pipes_pair_factory_.CreatePipesPair()));
}

void FlappyBird::RemoveOutOfScreenPipes() {
    for (auto it = pipes_.begin(); it != pipes_.end();) {
        if ((*it)->CanBeDestroyed()) {
            it = pipes_.erase(it);
        } else {
            ++it;
        }
    }
}

void FlappyBird::Render() {   
    if (DEBUG) {
        engine_.DrawRectangle(floor1_, kFloorHitBoxColor, false);
        engine_.DrawRectangle(floor2_, kFloorHitBoxColor, false);
    } else {
        engine_.RenderTexture(texture_background_, kRectBackground);
        
        engine_.RenderTexture(texture_floor_, floor1_);
        engine_.RenderTexture(texture_floor_, floor2_);
    }
    
    for (auto& pipe : pipes_) pipe->Render();
    
    bird_.Render();

    if (bird_.IsDead()) {
        engine_.RenderTexture(texture_gameover_, gameover_);
    }

    if (bird_.IsStanding()) {
        engine_.RenderTexture(texture_tutorial_, tutorial_);
    } else {
        score_manager_.Render();
    }

    snow_storm_.Render();
}
