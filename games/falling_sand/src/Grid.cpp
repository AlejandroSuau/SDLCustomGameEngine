#include "falling_sand/include/Grid.h"

#include <cmath>
#include <iostream>
#include <cassert>

Grid::Grid(Engine& engine, int width, int height)
    : engine_(engine)
    , width_(width)
    , height_(height)
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
    std::size_t row = rows_count_ - 1;
    while (row < rows_count_) {
        std::size_t column = columns_count_ - 1;
        while (column < columns_count_) {
            auto& particle = GetParticle(row, column);
            if (!particle.IsUpdated()) {
                particle.GridTick(*this, row, column);
            }
            --column;
        }
        --row;
    }

    for (auto& particles : cells_) {
        for (auto& particle : particles) {
            particle.SetUpdated(false);
        }
    }
}

bool Grid::IsWithinBounds(std::size_t row, std::size_t column) const {
    return (row >= 0 && row < rows_count_ && column >= 0 && column < columns_count_);
}

Particle& Grid::PlaceParticle(Particle& new_particle, std::size_t row, std::size_t column) {
    assert(row >= 0 && row < rows_count_ && column >= 0 && column < columns_count_);
    auto& current_particle = cells_[row][column];
    current_particle.SetParticleTypeAndColor(new_particle.GetType(), new_particle.GetColor());
    return current_particle;
}

Particle& Grid::GetParticle(std::size_t row, std::size_t column) {
    assert(row >= 0 && row < rows_count_ && column >= 0 && column < columns_count_);
    return cells_[row][column];
}

void Grid::ResetParticle(std::size_t row, std::size_t column) {
    assert(row >= 0 && row < rows_count_ && column >= 0 && column < columns_count_);
    cells_[row][column].SetToNone();
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

bool Grid::PlaceParticleInCoords(Particle& particle, int x, int y) {
    if (!AreCoordsInsideBounds(x, y)) return false;

    const std::size_t column = std::min(
        static_cast<std::size_t>(x) * columns_count_ / static_cast<std::size_t>(width_),
        columns_count_ - 1);
    const std::size_t row = std::min(
        static_cast<std::size_t>(y) * rows_count_ / static_cast<std::size_t>(height_),
        rows_count_ - 1);
    cells_[row][column].SetParticleTypeAndColor(particle.GetType(), particle.GetColor());

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
            particle.SetToNone();
        }
    }
}
