#pragma once

#include "flappy_bird/include/PipeFactory.h"

#include "engine/utils/Vec2.h"

namespace {
    static const int kPipeMinimumHeight = 100;
    static const int kSpaceBetweenPipePair = 150;
}

PipeFactory::PipeFactory(Engine& engine) 
    : engine_(engine) {}

std::unique_ptr<Pipe> PipeFactory::CreatePipe(float x, float y, float height) {
    return std::make_unique<Pipe>(engine_, Vec2{x, y}, height);
}

std::pair<std::unique_ptr<Pipe>, std::unique_ptr<Pipe>> PipeFactory::CreatePipePair() {
    const float x1 = static_cast<float>(engine_.GetWindowWidth());
    const float y1 = 0.f;
    auto& random_generator = engine_.GetRandomGenerator();
    const int pipe1_max_height = engine_.GetWindowHeight() - kPipeMinimumHeight - kSpaceBetweenPipePair;
    const float pipe1_height = static_cast<float>(random_generator.Generate(kPipeMinimumHeight, pipe1_max_height));

    const float x2 = x1;
    const float y2 = pipe1_height + static_cast<float>(kSpaceBetweenPipePair);
    const float pipe2_height = static_cast<float>(engine_.GetWindowHeight()) - y2;

    return {CreatePipe(x1, y1, pipe1_height),
            CreatePipe(x2, y2, pipe2_height)};
}
