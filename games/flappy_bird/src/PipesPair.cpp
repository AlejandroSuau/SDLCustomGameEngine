#include "flappy_bird/include/PipesPair.h"

namespace {
    static const float kVelocity = 100.f;
}

const float PipesPair::kPipesGap = 105.f;

PipesPair::PipesPair(Engine& engine, float x, float height_top, float height_bottom)
    : engine_(engine)
    , pipe_top_(engine_, Vec2{x, 0.f}, height_top)
    , pipe_bottom_(engine_, Vec2{x, height_top + PipesPair::kPipesGap}, height_bottom)
    , score_check_(std::make_unique<Rectangle>(pipe_top_.GetPosition().x + pipe_top_.kWidth / 2.f,
                                               height_top,
                                               1.f,
                                               PipesPair::kPipesGap)) {}

bool PipesPair::DoesBirdCollidesWithAPipe(const Bird& bird) const {
    const auto bird_rect = bird.GetRectangle();
    return (pipe_top_.GetRectangle().CollidesWith(bird_rect) ||
            pipe_bottom_.GetRectangle().CollidesWith(bird_rect));
}

bool PipesPair::DoesBirdCollidesWithScoreCheck(const Bird& bird) const {
    if (!score_check_) return false;

    return score_check_->CollidesWith(bird.GetRectangle());
}

void PipesPair::OnBirdCollisionWithScoreCheck() {
    score_check_ = nullptr;
}

bool PipesPair::CanBeDestroyed() const {
    const auto pipe_top_rect = pipe_top_.GetRectangle();
    return ((pipe_top_rect.x + pipe_top_rect.w) <= 0);
}

void PipesPair::Update(float dt) {
    const auto dx = kVelocity * dt;
    pipe_top_.GetPosition().x -= dx;
    pipe_bottom_.GetPosition().x -= dx;
    
    if (score_check_) {
        score_check_->x -= dx;
    }
}

void PipesPair::Render() {
    pipe_top_.Render();
    pipe_bottom_.Render();
    
    /*if (score_check_) {
        engine_.DrawRectangle(*score_check_.get());
    }*/
}
