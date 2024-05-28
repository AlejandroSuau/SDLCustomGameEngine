#include "flappy_bird/include/FlappyBird.h"

#include <iostream>

FlappyBird::FlappyBird() 
    : engine_("Flappy Bird", 1080, 720)
    , bird_(engine_)
    , pipe_spawn_timer_(3.5f)
    , pipe_factory_(engine_) {}

void FlappyBird::Start() {
    auto pipe_pair = pipe_factory_.CreatePipePair();
    pipes_.push_back(std::move(pipe_pair.first));
    pipes_.push_back(std::move(pipe_pair.second));
    engine_.Run(*this);
}

void FlappyBird::OnMouseEvent(EMouseEventType event_type, int x, int y) {
    return;
}

void FlappyBird::OnKeyboardEvent(EKeyEventType event_type, SDL_Scancode scancode) {
    bird_.OnKeyboardEvent(event_type, scancode);
}

void FlappyBird::Update(float dt) {
    pipe_spawn_timer_.Update(dt);
    if (pipe_spawn_timer_.DidFinish()) {
        auto pipe_pair = pipe_factory_.CreatePipePair();
        pipes_.push_back(std::move(pipe_pair.first));
        pipes_.push_back(std::move(pipe_pair.second));
        pipe_spawn_timer_.Reset();
    }

    bird_.Update(dt);
    for (auto& pipe : pipes_) pipe->Update(dt);

    // Destroying all that went outside the screen.
    for (auto it = pipes_.begin(); it != pipes_.end();) {
        if ((*it)->CanBeDestroyed()) {
            it = pipes_.erase(it);
        } else {
            ++it;
        }
    }
}

void FlappyBird::Render() {
    bird_.Render();
    for (auto& pipe : pipes_) pipe->Render();
}
