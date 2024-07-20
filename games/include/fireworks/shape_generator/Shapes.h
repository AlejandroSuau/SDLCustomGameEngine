#pragma once

#include <array>

static const std::array<std::array<bool, 9>, 12> kShapeTrueBooleanSkull {{
    {0, 0, 1, 1, 1, 1, 1, 0, 0},
    {0, 1, 1, 1, 1, 1, 1, 1, 0},
    {1, 1, 1, 1, 1, 1, 1, 1, 1},
    {1, 1, 1, 1, 1, 1, 1, 1, 1},
    {1, 1, 1, 1, 1, 1, 1, 1, 1},
    {1, 1, 0, 1, 1, 1, 0, 1, 1},
    {0, 1, 1, 1, 1, 1, 1, 1, 1},
    {0, 0, 1, 0, 1, 0, 1, 0, 0},

    {0, 0, 0, 0, 0, 0, 0, 0, 0},

    {0, 0, 0, 1, 0, 1, 0, 0, 0},
    {0, 0, 1, 1, 1, 1, 1, 0, 0},
    {0, 0, 0, 1, 1, 1, 0, 0, 0},
}};

/* Heart
for (std::size_t i = 0; i < num_points; ++i) {
    float t = 2 * M_PI * i / num_points;
    float x = size * 16 * std::sin(t) * std::sin(t) * std::sin(t);
    float y = -size * (13 * std::cos(t) - 5 * std::cos(2 * t) - 2 * std::cos(3 * t) - std::cos(4 * t));
    points.push_back(position + Vec2(x, y));
}*/
