#include "fireworks/Firework.h"

#include "fireworks/shape_generator/ShapeGenerator.h"
#include "fireworks/shape_generator/Shapes.h"

#include <array>

namespace {
    static const std::size_t kExplosionParticlesCount = 150;
}

Firework::Firework(Engine& engine)
    : engine_(engine)
    , color_{static_cast<Uint8>(engine_.GetRandomGenerator().Generate(200, 255)),
             static_cast<Uint8>(engine_.GetRandomGenerator().Generate(125, 255)),
             static_cast<Uint8>(engine_.GetRandomGenerator().Generate(125, 255)),
             255}
    , main_particle_(nullptr)
    , can_be_destroyed_(false) {
    const Vec2 random_position {
        static_cast<float>(engine_.GetRandomGenerator().Generate(100, engine_.GetWindowWidth() - 100)),
        engine_.GetFWindowHeight()};
    const Vec2 random_velocity {0.f, -1 * engine_.GetRandomGenerator().Generate(600.f, 1000.f)};
    main_particle_ = particles_.emplace_back(
        std::make_unique<Particle>(engine_, color_, random_position, random_velocity, 4.f, false, true)).get();
}

void Firework::Update(float dt) {
    if (main_particle_ && main_particle_->GetVelocity().y > 0.f) {
        Vec2 explosion_position = main_particle_->GetPosition();
        particles_.erase(particles_.begin());
        main_particle_ = nullptr;
        AddExplosionParticles(explosion_position);
    }

    for (auto& particle : particles_) {
        if (!main_particle_) {
            particle->SetVelocity(particle->GetVelocity() * 0.95f);
        }
        particle->Update(dt);
    }

    ClearDestroyableParticles();
}

void Firework::AddExplosionParticles(Vec2 position) {
    const auto radius = 2.f;
    auto& rand_generator = engine_.GetRandomGenerator();
    particles_.reserve(kExplosionParticlesCount);
    for (std::size_t i = 0; i < kExplosionParticlesCount; ++i) {
        auto random_velocity {Vec2::Random2D() * rand_generator.Generate(200.f, 600.f)};
        random_velocity.y -= rand_generator.Generate(100.f, 200.f);
        particles_.emplace_back(
            std::make_unique<Particle>(engine_, color_, position, random_velocity, radius, true, true));
    }


    const auto shape_points = ShapeGenerator::GenerateShape(kShapeTrueBooleanSkull, position, 150.f);
    for (const auto& point : shape_points) {
        if (point.x == 0 && point.y == 0) continue;
        particles_.emplace_back(
            std::make_unique<Particle>(engine_, color_, point, Vec2{}, radius, true, false, false));
    }
}

void Firework::ClearDestroyableParticles() {
    particles_.erase(
        std::remove_if(
            particles_.begin(), particles_.end(), [](const auto& p) { return p->CanBeDestroyed(); }),
        particles_.end()
    );
    can_be_destroyed_ = particles_.empty();
}

void Firework::Render() {
    for (auto& particle : particles_) {
        particle->Render();
    }
}

bool Firework::CanBeDestroyed() const {
    return can_be_destroyed_;
}