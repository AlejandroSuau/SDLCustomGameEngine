#include "flappy_bird/include/FlappyBird.h"

#include <tuple>

namespace {
    static const float kFloorHeight = 112.f;
    static const Color kFloorColor {116, 99, 78, 255};

    static const Rectangle kRectBackground {0.f, 0.f, 288.f, 512.f};
    static const Rectangle kRectTutorial {0.f, 25.f, 184.f, 267.f};
}

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
    , pipe_factory_(engine_, floor1_)
    , is_paused_(false)
    , tutorial_(kRectTutorial.x + kRectBackground.w * 0.5f - kRectTutorial.w * 0.5f,
                kRectTutorial.y,
                kRectTutorial.w,
                kRectTutorial.h)
    , texture_tutorial_(nullptr)
    , texture_background_(nullptr)
    , texture_floor_(nullptr) {
    
    texture_tutorial_ = engine_.LoadTexture("assets/flappy_bird/message.png");
    texture_background_ = engine_.LoadTexture("assets/flappy_bird/background-night.png");
    texture_floor_ = engine_.LoadTexture("assets/flappy_bird/base.png");
}

void FlappyBird::Start() {
    engine_.Run(*this);
}

void FlappyBird::OnMouseEvent(EMouseEventType event_type, int x, int y) {
    return;
}

void FlappyBird::OnKeyboardEvent(EKeyEventType event_type, SDL_Scancode scancode) {
    bird_.OnKeyboardEvent(event_type, scancode);
}

void FlappyBird::Update(float dt) {
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
    while (!found_collision && i < score_checkpoints_.size()) {
        if (bird_.GetRectangle().CollidesWith(score_checkpoints_[i])) {
            score_manager_.IncreaseScoreOneUnit();
            score_checkpoints_.erase(score_checkpoints_.begin() + i);
        }
        ++i;
    }
}

void FlappyBird::NofityBirdOnPipeCollision() {
    bool found_collision = false;
    std::size_t i = 0;
    while (!found_collision && i < pipes_.size()) {
        if (bird_.CollidesWith(*pipes_[i].get())) {
            bird_.OnCollisionWithPipe(*pipes_[i]);
        }
        ++i;
    }
}

void FlappyBird::NofityBirdOnFloorCollision() {
    const bool collision_detected = (floor1_.CollidesWith(bird_.GetRectangle()) ||
                                     floor2_.CollidesWith(bird_.GetRectangle()));
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
    floor1_.x -= 100.f * dt;
    floor2_.x -= 100.f * dt;
    if (floor1_.x + floor1_.w <= 0) {
        floor1_.x = static_cast<float>(engine_.GetWindowWidth());
    }
    if (floor2_.x + floor2_.w <= 0) {
        floor2_.x = static_cast<float>(engine_.GetWindowWidth());
    }
}

void FlappyBird::MovePipes(float dt) {
    for (auto& pipe : pipes_) {
        pipe->Update(dt);
    }

    for (auto& rect : score_checkpoints_) {
        rect.x -=  100.f * dt;
    }
}

void FlappyBird::AddPipesPair() {
    auto pipes_tuple = pipe_factory_.CreatePipePair();
    pipes_.push_back(std::move(std::get<0>(pipes_tuple)));
    pipes_.push_back(std::move(std::get<1>(pipes_tuple)));
    score_checkpoints_.push_back(std::get<2>(pipes_tuple));
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

void FlappyBird::Pause() {
    is_paused_ = true;
}

void FlappyBird::Render() {    
    engine_.RenderTexture(texture_background_, kRectBackground);
    
    engine_.RenderTexture(texture_floor_, floor1_);
    engine_.RenderTexture(texture_floor_, floor2_);
    
    // Debug.
    // engine_.DrawRectangle(floor1_, kFloorColor, false);
    // engine_.DrawRectangle(floor2_, kFloorColor, false);
    
    for (auto& pipe : pipes_) pipe->Render();
    
    // Debug.
    // for (auto& checkpoint : score_checkpoints_) engine_.DrawRectangle(checkpoint);
    
    bird_.Render();

    if (bird_.IsStanding()) {
        engine_.RenderTexture(texture_tutorial_, tutorial_);
    } else {
        score_manager_.Render();
    }
}
