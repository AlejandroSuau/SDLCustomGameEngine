#pragma once

#include "engine/Engine.h"

#include <vector>
#include <memory>
#include <array>

struct Cell {
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

    void SpawnSparkInCoords(int x, int y);
    void SpawnSparkInRowColumn(std::size_t row, std::size_t column);
    Cell& GetCell(std::size_t row, std::size_t column);
    void UpdateCells(float dt);
    void RenderCells();
    void ClearAllParticles();

    void UglyDraw();

    bool AreCoordsInsideBounds(int x, int y) const;

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

    void InitCells();
    void UpdateElectricPotential();
    void UpdateElectricField();

    std::array<std::pair<std::size_t, std::size_t>, 4> GetNeighbours(std::size_t row, std::size_t column);
};
