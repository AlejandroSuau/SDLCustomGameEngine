#include "space_invaders/include/AlienFactory.h"

#include "space_invaders/include/Constants.h"

#include <array>

AlienFactory::AlienFactory(Engine& engine)
    : engine_(engine) {}

std::unique_ptr<Alien> AlienFactory::CreateAlien(Vec2 position, std::size_t alien_index) {
    const float alien_asset_width = 14.f;
    const float alien_asset_height = 12.f;
    const float source_y = 2.f + 16.f * static_cast<float>(alien_index % kAlienTypesCount);

    std::array<Rectangle, 2> source_rects {{
        Rectangle{1.f, source_y, alien_asset_width, alien_asset_height},
        Rectangle{17.f, source_y, alien_asset_width, alien_asset_height}
    }};
    return std::make_unique<Alien>(engine_, position, source_rects);
}
