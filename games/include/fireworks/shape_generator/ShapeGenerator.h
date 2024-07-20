#pragma once

#include "engine/utils/Vec2.h"

#include <array>

namespace ShapeGenerator
{

template <std::size_t ROWS, std::size_t COLUMNS>
std::array<Vec2, ROWS * COLUMNS> GenerateShapeImpl(
    const std::array<std::array<bool, COLUMNS>, ROWS> shape,
    Vec2 position,
    float size) {
    std::array<Vec2, ROWS * COLUMNS> points;

    float points_spacing = size / 30.f;
    Vec2 centering_offset {
        static_cast<float>(COLUMNS) / 2.f * points_spacing,
        static_cast<float>(ROWS) / 2.f * points_spacing};
    
    for (std::size_t i = 0; i < ROWS; ++i) {
        for (std::size_t j = 0; j < COLUMNS; ++j) {
            if (!shape[i][j]) continue;
            
            const Vec2 spacing_vec {static_cast<float>(j) * points_spacing, 
                                    static_cast<float>(i) * points_spacing};
            points[i * COLUMNS + j] = (position + spacing_vec - centering_offset);
        }
    }

    return points;
}

template <std::size_t ROWS, std::size_t COLUMNS>
auto GenerateShape(
    const std::array<std::array<bool, COLUMNS>, ROWS> shape,
    Vec2 position,
    float size) {
    return GenerateShapeImpl(shape, position, size);
}

}
