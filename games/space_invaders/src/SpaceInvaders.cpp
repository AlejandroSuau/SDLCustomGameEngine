#include "space_invaders/include/SpaceInvaders.h"

#include "space_invaders/include/Constants.h"

#include "engine/utils/Vec2.h"

SpaceInvaders::SpaceInvaders() 
    : engine_("Space Invaders",
              static_cast<int>(kRectBackground.w),
              static_cast<int>(kRectBackground.h))
    , projectile_factory_(engine_)
    , ship_(engine_, projectile_factory_)
    , defenses_{{
        DefenseBlock{engine_, Vec2{static_cast<float>(engine_.GetWindowWidth()) * 0.05f, static_cast<float>(engine_.GetWindowHeight()) * 0.8f}}, 
        DefenseBlock{engine_, Vec2{static_cast<float>(engine_.GetWindowWidth()) * 0.30f, static_cast<float>(engine_.GetWindowHeight()) * 0.8f}},
        DefenseBlock{engine_, Vec2{static_cast<float>(engine_.GetWindowWidth()) * 0.55f, static_cast<float>(engine_.GetWindowHeight()) * 0.8f}},
        DefenseBlock{engine_, Vec2{static_cast<float>(engine_.GetWindowWidth()) * 0.80f, static_cast<float>(engine_.GetWindowHeight()) * 0.8f}}
    }}
    , aliens_(engine_, projectile_factory_, kAliensCount) 
    , score_manager_(engine_) {}

void SpaceInvaders::Start() {
    engine_.Run(*this);
}

void SpaceInvaders::OnMouseEvent(EMouseEventType event_type, int x, int y) {
    return;
}

void SpaceInvaders::OnKeyboardEvent(EKeyEventType event_type, SDL_Scancode scancode) {
    ship_.OnKeyboardEvent(event_type, scancode);
}

void SpaceInvaders::ResetGame() {
    /*bird_.Reset();
    score_manager_.Reset();
    pipes_.clear();*/
}

void SpaceInvaders::Update(float dt) {
    ship_.Update(dt);
    aliens_.Update(dt);
    
    const auto* projectile = ship_.GetProjectile();
    if (projectile) {
        const auto did_destroy_alien = aliens_.DidProjectileDestroyAnAlien(*projectile);
        const auto did_destroy_alien_projectile = false;
        const auto did_hit_defense = ProcessProjectileCollisionWithDefenses(*projectile); 
        const auto should_destroy_projectile = (
            did_destroy_alien || did_destroy_alien_projectile || did_hit_defense);
        if (should_destroy_projectile) {
            ship_.DestroyProjectile();
        }
    }
}

bool SpaceInvaders::ProcessProjectileCollisionWithDefenses(const Projectile& projectile) {
    bool did_find_collision = false; 
    std::size_t i = 0;
    while (!did_find_collision && i < defenses_.size()) {
        auto& defense = defenses_[i];
        if (defense.ProcessCollisionWith(projectile.GetRectangle())) {
            did_find_collision = true;
        }
        ++i;
    }

    return did_find_collision;
}

void SpaceInvaders::Render() {            
    ship_.Render();
    aliens_.Render();
    
    for (auto& defense : defenses_) {        
        defense.Render();
    }
}