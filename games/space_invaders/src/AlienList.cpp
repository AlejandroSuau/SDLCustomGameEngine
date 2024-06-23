#include "space_invaders/include/AlienList.h"

#include "engine/Rectangle.h"

#include "space_invaders/include/Constants.h"

AlienList::AlienList(Engine& engine, std::size_t aliens_count)
    : engine_(engine)
    , alien_factory_(engine_)
    , aliens_count_(aliens_count)
    , starting_position_(engine_.GetWindowWidth() * 0.1f,
                         engine_.GetWindowHeight() * 0.15f)
    , ending_position_(engine_.GetWindowWidth() * 0.9f,
                       engine_.GetWindowHeight() * 0.15f) 
    , step_timer_(kStartingMovementFrequencySeconds)
    , movement_direction_(EAlienMovementDirection::RIGHT)
    , movement_direction_scalar_(1.f)
    , pack_x_bound_left_(starting_position_.x)
    , pack_x_bound_right_(starting_position_.x + 
                          (kAlienWidth + kAlienListXGap) * static_cast<float>(kAliensPerRow) -
                          kAlienListXGap)
    , max_spawn_interval_(kMaxProjectileSpawnTime)
    , min_spawn_interval_(kMinProjectileSpawnTime)
    , spawn_projectile_timer_(max_spawn_interval_) {
    InitializeAliens();
}

void AlienList::InitializeAliens() {
    std::size_t alien_type = 0;
    Vec2 current_position = starting_position_;
    aliens_.reserve(aliens_count_);
    for (std::size_t i = 0; i < aliens_count_; ++i) {
        aliens_.emplace_back(alien_factory_.CreateAlien(current_position, alien_type));
        current_position.x += kAlienWidth + kAlienListXGap;
        if ((i + 1) % kAliensPerRow == 0) {
            pack_x_bound_right_ = current_position.x - kAlienListXGap;
            current_position.x = starting_position_.x;
            current_position.y += kAlienListYGap + kAlienHeight;
            ++alien_type;
        }
    }
}

bool AlienList::DidProjectileDestroyAnAlien(const Projectile& projectile) {
    bool found_collision = false;
    auto it = aliens_.begin();
    while (!found_collision && it != aliens_.end()) {
        const auto& alien_rect = (*it)->GetRectangle();
        if (projectile.CollidesWith(alien_rect)) {
            found_collision = true;
            it = aliens_.erase(it);
        } else {
            ++it;
        }
    }
    
    return found_collision;
}

void AlienList::Update(float dt) {
    for (auto& projectile : projectiles_) projectile->Update(dt);

    spawn_projectile_timer_.Update(dt);
    if (spawn_projectile_timer_.DidFinish()) {
        SpawnProjectile();
        spawn_projectile_timer_.Reset();
    }

    step_timer_.Update(dt);
    if (step_timer_.DidFinish()) {
        for (auto& alien : aliens_) {
            alien->MovementStep(movement_direction_);
        }

        if (IsMovingDown()) {
            SwapMovementDirection();
        } else {
            MovePackBounds();
        }

        step_timer_.Reset();
    }
    
    CleanProjectilesOutOfBounds();
}

void AlienList::SpawnProjectile() {
    auto* random_alien = GetRandomAlien();
    if (!random_alien) return;

    const auto random_alien_pos = random_alien->GetPosition();
    const auto x = random_alien_pos.x + kAlienWidth * 0.5f;
    const auto y = random_alien_pos.y + kAlienHeight * 0.5f;
    projectiles_.emplace_back(std::make_unique<Projectile>(
        engine_, EProjectileDirection::DOWN, x, y));

    auto& random_generator = engine_.GetRandomGenerator();
    const auto new_spawn_projectile_time = random_generator.Generate(
        min_spawn_interval_, max_spawn_interval_);
    spawn_projectile_timer_.SetSecondsToFinish(new_spawn_projectile_time);
}

void AlienList::SwapMovementDirection() {
    movement_direction_scalar_ *= -1;
    movement_direction_ = (movement_direction_scalar_ > 0) ? EAlienMovementDirection::RIGHT :
                                                             EAlienMovementDirection::LEFT;
}

void AlienList::MovePackBounds() {
    const float dx = kAlienMovementStepX * movement_direction_scalar_;
    pack_x_bound_left_ += dx;
    pack_x_bound_right_ += dx;

    if (pack_x_bound_left_ <= starting_position_.x) {
        movement_direction_ = EAlienMovementDirection::DOWN;
    }

    if (pack_x_bound_right_ >= ending_position_.x) {
        movement_direction_ = EAlienMovementDirection::DOWN;
    }
}

bool AlienList::IsMovingDown() const {
    return (movement_direction_ == EAlienMovementDirection::DOWN);
}

Alien* AlienList::GetRandomAlien() {
    if (aliens_.empty()) return nullptr;

    auto& random_generator = engine_.GetRandomGenerator();
    auto random_alien_index = static_cast<std::size_t>(random_generator.Generate(
        0, static_cast<int>(aliens_.size() - 1)));
    return aliens_[random_alien_index].get();
}

void AlienList::CleanProjectilesOutOfBounds() {
    for (auto it = projectiles_.begin(); it != projectiles_.end();) {
        if ((*it)->IsInsideBounds()) {
            ++it;
        } else {
            it = projectiles_.erase(it);
        }
    }
}

void AlienList::Render() {
    for (auto& alien: aliens_) alien->Render();
    for (auto& projectile: projectiles_) projectile->Render();

    engine_.DrawRectangle(Rectangle{starting_position_.x, starting_position_.y, 1.f, 300.f});
    engine_.DrawRectangle(Rectangle{ending_position_.x, ending_position_.y, 1.f, 300.f});

    engine_.DrawRectangle(Rectangle{pack_x_bound_left_, starting_position_.y, 1.f, 300.f});
    engine_.DrawRectangle(Rectangle{pack_x_bound_right_, starting_position_.y, 1.f, 300.f});
}
