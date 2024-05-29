#include "flappy_bird/include/FlappyBird.h"

#include <iostream>

FlappyBird::FlappyBird() 
    : engine_("Flappy Bird", 1080, 720)
    , bird_(engine_)
    , pipe_spawn_timer_(3.5f)
    , pipe_factory_(engine_)
    , is_paused_(false) {}

void FlappyBird::Start() {
    // Show Tutotial, show pause button
    engine_.Run(*this);
}

void FlappyBird::OnMouseEvent(EMouseEventType event_type, int x, int y) {
    return;
}

void FlappyBird::OnKeyboardEvent(EKeyEventType event_type, SDL_Scancode scancode) {
    bird_.OnKeyboardEvent(event_type, scancode);
}

void FlappyBird::Update(float dt) {
    if (is_paused_) return;

    pipe_spawn_timer_.Update(dt);
    if (pipe_spawn_timer_.DidFinish()) {
        AddPipesPair();
        pipe_spawn_timer_.Reset();
    }

    bird_.Update(dt);
    for (auto& pipe : pipes_) pipe->Update(dt);

    RemoveOutOfScreenPipes();
    
   if (DidBirdCollideWithAPipe()) Pause();
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

void FlappyBird::AddPipesPair() {
    auto pipe_pair = pipe_factory_.CreatePipePair();
    pipes_.push_back(std::move(pipe_pair.first));
    pipes_.push_back(std::move(pipe_pair.second));
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
    bird_.Render();
    for (auto& pipe : pipes_) pipe->Render();
}
