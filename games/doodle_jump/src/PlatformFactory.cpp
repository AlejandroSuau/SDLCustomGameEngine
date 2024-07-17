#include "doodle_jump/include/PlatformFactory.h"

#include "engine/utils/Vec2.h"

#include <memory>

namespace {
    static const float kHeightBuffer = 300.f;
    static const int kMinGapBetweenPlatforms = 25;
    static const int kMaxGapBetweenPlatforms = 125;
    
    static const int kPlatformMaxWidth = 75;
    static const int kPlatformMaxHeight = 20;
}

PlatformFactory::PlatformFactory(Engine& engine)
    : engine_(engine) {}

void PlatformFactory::InstantiatePlatforms(
    std::vector<std::unique_ptr<Platform>>& platforms,
    float min_height,
    float max_height) {
    auto& random_generator = engine_.GetRandomGenerator();
    float current_height = min_height;
    while (current_height < max_height) {
        const float random_x = static_cast<float>(
            random_generator.Generate(0, engine_.GetWindowWidth() - kPlatformMaxWidth));
        const float random_y = static_cast<float>(
            random_generator.Generate(kMinGapBetweenPlatforms, kMaxGapBetweenPlatforms)) + kPlatformMaxHeight;
        current_height += random_y;
        SDL_Log("{x: %.5f, y: %.5f}", random_x, current_height - kHeightBuffer);

        platforms.emplace_back(
            std::make_unique<Platform>(engine_, Vec2{random_x, current_height - kHeightBuffer}));
    }
}