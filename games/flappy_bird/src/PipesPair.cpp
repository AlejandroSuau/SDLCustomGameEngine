#include "flappy_bird/include/PipesPair.h"

#include "flappy_bird/include/Constants.h"

PipesPair::PipesPair(Engine& engine, float x, float height_top, float height_bottom)
    : engine_(engine)
    , pipe_top_(engine_, Vec2{x, 0.f}, height_top)
    , pipe_bottom_(engine_, Vec2{x, height_top + kPipesPairGap}, height_bottom)
    , score_check_hit_box_(std::make_unique<Rectangle>(pipe_top_.GetPositionX() + kPipeWidth / 2.f,
                           height_top,
                           1.f,
                           kPipesPairGap)) {}

bool PipesPair::DoesBirdCollidesWithAPipe(const Bird& bird) const {
    const auto bird_hit_box = bird.GetHitBox();
    return (pipe_top_.GetHitBox().CollidesWith(bird_hit_box) ||
            pipe_bottom_.GetHitBox().CollidesWith(bird_hit_box));
}

bool PipesPair::DoesBirdCollidesWithScoreCheck(const Bird& bird) const {
    if (!score_check_hit_box_) return false;

    return score_check_hit_box_->CollidesWith(bird.GetHitBox());
}

void PipesPair::OnBirdCollisionWithScoreCheck() {
    score_check_hit_box_ = nullptr;
}

bool PipesPair::CanBeDestroyed() const {
    const auto pipe_top_rect = pipe_top_.GetHitBox();
    return ((pipe_top_rect.x + pipe_top_rect.w) <= 0);
}

void PipesPair::Update(float dt) {
    const auto dx = kScrollingVelocityX * dt;
    pipe_top_.SetPositionX(pipe_top_.GetPositionX() - dx);
    pipe_bottom_.SetPositionX(pipe_bottom_.GetPositionX() - dx);
    
    if (score_check_hit_box_) {
        score_check_hit_box_->x -= dx;
    }
}

void PipesPair::Render() {
    pipe_top_.Render();
    pipe_bottom_.Render();
    
    if (score_check_hit_box_ && DEBUG) {
        engine_.DrawRectangle(*score_check_hit_box_.get());
    }
}
