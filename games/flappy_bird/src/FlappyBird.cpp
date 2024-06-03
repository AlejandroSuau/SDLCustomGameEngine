#include "flappy_bird/include/FlappyBird.h"

#include <iostream>

namespace {
    static const float kFloorHeight = 112.f;
    static const Color kFloorColor {116, 99, 78, 255};

    static const Rectangle kBackground {0.f, 0.f, 288.f, 512.f};
}

FlappyBird::FlappyBird() 
    : engine_("Flappy Bird", 288, 512)
    , bird_(engine_)
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
    , is_paused_(false) {
    
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
    // Floor movement simulation.
    floor1_.x -= 100.f * dt;
    floor2_.x -= 100.f * dt;
    if (floor1_.x + floor1_.w <= 0) {
        floor1_.x = static_cast<float>(engine_.GetWindowWidth());
    }
    if (floor2_.x + floor2_.w <= 0) {
        floor2_.x = static_cast<float>(engine_.GetWindowWidth());
    }

    bird_.Update(dt);
    if (bird_.IsStanding() || bird_.IsDead()) return;

    pipe_spawn_timer_.Update(dt);
    if (pipe_spawn_timer_.DidFinish()) {
        AddPipesPair();
        pipe_spawn_timer_.Reset();
    }

    for (auto& pipe : pipes_) pipe->Update(dt);

    // Bonus Item
    if (bonus_item_) {
        bonus_item_->x -= 100.f * dt;
        
        if (bird_.GetRectangle().CollidesWith(*bonus_item_.get())) {
            for (auto& pipe : pipes_) pipe->SetStatusFlatting();
            bonus_item_ = nullptr;
        }
    }

    RemoveOutOfScreenPipes();

    // If hit tube => set dying.
    // If hit floor => set die

    if (ShouldBirdDie()) {
        // Only when colliding with the floor.
        // bird_.SetPositionY(floor_.y - bird_.GetDimension().y);
        bird_.SetStateDead();
    }
}

bool FlappyBird::ShouldBirdDie() const {
    return (DidBirdCollideWithAPipe() || DidBirdColliderWithFloor());
}

bool FlappyBird::DidBirdCollideWithAPipe() const {
    bool did_collide = false;
    std::size_t i = 0;
    while (!did_collide && i < pipes_.size()) {
        did_collide = bird_.CollidesWith(*pipes_[i].get());
        ++i;
    }
    
    return did_collide;
}

bool FlappyBird::DidBirdColliderWithFloor() const {
    return (floor1_.CollidesWith(bird_.GetRectangle()) || floor2_.CollidesWith(bird_.GetRectangle()));
}

void FlappyBird::AddPipesPair() {
    auto pipe_pair = pipe_factory_.CreatePipePair();
    pipes_.push_back(std::move(pipe_pair.first));
    pipes_.push_back(std::move(pipe_pair.second));
    if (pipes_.size() == 2) {
        SpawnBonusItem(pipes_[0]->GetRectangle());
    }
}

void FlappyBird::SpawnBonusItem(Rectangle pipe) {
    bonus_item_ = std::make_unique<Rectangle>(pipe.x, pipe.y + pipe.h + 50.f, 20.f, 10.f);
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
    engine_.RenderTexture(texture_background_, kBackground, kBackground);
    
    engine_.RenderTexture(texture_floor_, floor1_, floor1_);
    engine_.RenderTexture(texture_floor_, floor2_, floor2_);
    //engine_.DrawRectangle(floor_, kFloorColor, true);
    
    bird_.Render();
    for (auto& pipe : pipes_) pipe->Render();

    if (bonus_item_) {
        engine_.DrawRectangle(*bonus_item_.get(), {255, 221, 153, 255}, true);
    }
}
