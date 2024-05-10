#include "falling_sand/include/Grid.h"


Grid::Grid(Engine& engine, int width, int height)
    : engine_(engine)
    , width_(width)
    , height_(height) {
    InitCells();
}

void Grid::InitCells() {
    const auto columns_count = static_cast<std::size_t>(width_ / Particle::kParticleSize);
    const auto rows_count = static_cast<std::size_t>(height_ / Particle::kParticleSize);
    for (std::size_t i = 0; i < rows_count; ++i) {
        cells_.emplace_back();
        for (std::size_t j = 0; j < columns_count; j++) {
            cells_[i].emplace_back(engine_);
        }
    }
}

void Grid::UpdateCells(float dt) {

}

void Grid::RenderCells() {
    float y = 0.f;
    for (auto& row : cells_) {
        float x = 0.f;
        for (auto& particle : row) {
            particle.Render(x, y);
            x += static_cast<float>(Particle::kParticleSize);
        }
        y += static_cast<float>(Particle::kParticleSize);
    }
}
