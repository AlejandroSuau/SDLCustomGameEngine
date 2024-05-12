#include "falling_sand/include/Grid.h"

#include <cmath>
#include <iostream>

Grid::Grid(Engine& engine, int width, int height)
    : engine_(engine)
    , width_(width)
    , height_(height)
    , tick_timer_(0.5f)
    , rows_count_(0)
    , columns_count_(0) {
    InitCells();
}

void Grid::InitCells() {
    columns_count_ = static_cast<std::size_t>(width_ / Particle::kParticleSize);
    rows_count_ = static_cast<std::size_t>(height_ / Particle::kParticleSize);
    for (std::size_t i = 0; i < rows_count_; ++i) {
        cells_.emplace_back();
        for (std::size_t j = 0; j < columns_count_; j++) {
            cells_[i].emplace_back(engine_);
        }
    }
}

void Grid::UpdateCells(float dt) {
    tick_timer_.Update(dt);
    if (tick_timer_.DidFinish()) {
        std::size_t row = 0;
        for (auto& particles : cells_) {
            std::size_t column = 0;
            for (auto& particle : particles) {
                if (!particle.IsUpdated()) {
                    particle.GridTick(*this, particle.GetParticleType(), row, column);
                }
                ++column;
            }
            ++row;
        }

        for (auto& particles : cells_) {
            for (auto& particle : particles) {
                particle.SetUpdated(false);
            }
        }
        tick_timer_.Reset();
    }
    // After N seconds, update all cells.
        // Update particle passing grid ref
}

bool Grid::IsFreeForPlacing(std::size_t row, std::size_t column) const {
    bool is_valid_spot = (row >= 0 && row < rows_count_ && column >= 0 && column < columns_count_);
    if (!is_valid_spot) return false;

    return (cells_[row][column].GetParticleType() == EParticleType::NONE);
}

void Grid::PlaceParticle(EParticleType particle_type, std::size_t row, std::size_t column) {
    cells_[row][column].SetParticleType(particle_type);
    cells_[row][column].SetUpdated(true);
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

bool Grid::PlaceParticleInCoords(EParticleType particle_type, int x, int y) {
    if (!AreCoordsInsideBounds(x, y)) return false;

    const std::size_t column = std::min(
        static_cast<std::size_t>(x) * columns_count_ / static_cast<std::size_t>(width_),
        columns_count_ - 1);
    const std::size_t row = std::min(
        static_cast<std::size_t>(y) * rows_count_ / static_cast<std::size_t>(height_),
        rows_count_ - 1);
    cells_[row][column].SetParticleType(particle_type);

    return true;
}

bool Grid::AreCoordsInsideBounds(int x, int y) const {
    std::cout << "\n{x: " << x << ", y: " << y << "}";
    return (x <= width_ && x >= 0 &&
            y <= height_ && y >= 0);
}

void Grid::ClearAllParticles() {
    for (auto& particles : cells_) {
        for (auto& particle : particles) {
            particle.SetParticleType(EParticleType::NONE);
        }
    }
}
