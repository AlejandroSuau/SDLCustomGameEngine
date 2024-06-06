#pragma once

#include "engine/Engine.h"
#include "engine/Rectangle.h"

#include "PipesPair.h"

#include <memory>

class PipesPairFactory {
public:
    PipesPairFactory(Engine& engine, const Rectangle& floor_);

    std::unique_ptr<PipesPair> CreatePipesPair();

private:
    Engine& engine_;
    const Rectangle& floor_;
};
