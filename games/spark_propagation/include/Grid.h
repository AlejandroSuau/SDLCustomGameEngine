#pragma once

#include "engine/Engine.h"

#include <vector>
#include <memory>
#include <array>

struct Cell {
    static const int kCellSize = 5;

    Cell(std::size_t row_, std::size_t column_) 
        : row(row_), column(column_) {}

    std::size_t row {0};
    std::size_t column {0};
    float electric_field {0.0f};
    float electric_potential {0.0f};
    bool has_spark {false};
};

class Grid {
public:
    Grid(Engine& engine, int width, int height);

    void FillSparks();

    Cell& GetCell(std::size_t row, std::size_t column);
    void UpdateCells(float dt);
    void RenderCells();
    void ClearAllParticles();

private:
    Engine& engine_;
    const int width_;
    const int height_;
    std::size_t columns_count_;
    std::size_t rows_count_;

    // Condición de Dirichlet (potencial constante en los bordes):
    // Se especifica un valor fijo de potencial en los bordes.
    // Por ejemplo, se puede fijar el potencial a 0 en los bordes 
    // para representar una situación donde el borde está conectado a tierra.

    std::vector<std::vector<Cell>> cells_;

    // Sparks
    int sparks_count_{0};
    const int kMaxSparksCount = 550;
    const float kPotentialDiffThreshold = 0.01f; // After updating potentials, all of them should be bellow the Threshold.

    void InitCells();
    void UpdateElectricPotential();
    void UpdateElectricField();
    void PropagateSpark();

    std::array<std::pair<std::size_t, std::size_t>, 4> GetNeighbours(std::size_t row, std::size_t column);
};
