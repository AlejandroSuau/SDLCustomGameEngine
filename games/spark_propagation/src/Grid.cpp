#include "spark_propagation/include/Grid.h"

#include "spark_propagation/include/Constants.h"

#include <cmath>
#include <cassert>
#include <array>
#include <numeric>
#include <ctime>
#include <iostream>

Grid::Grid(Engine& engine, int width, int height)
    : engine_(engine)
    , width_(width)
    , height_(height)
    , rows_count_(0)
    , columns_count_(0) {
    srand(static_cast<unsigned>(time(0)));
    InitCells();
}

void Grid::InitCells() {
    rows_count_ = static_cast<std::size_t>(height_ / kCellSize);
    columns_count_ = static_cast<std::size_t>(width_ / kCellSize);
    cells_.reserve(rows_count_);
    for (std::size_t i = 0; i < rows_count_; ++i) {
        cells_.emplace_back();
        cells_[i].reserve(columns_count_);
        for (std::size_t j = 0; j < columns_count_; j++) {
            cells_[i].emplace_back(i, j);
        }
    }

    // Add spark to mid.
    auto& cell = cells_[rows_count_ / 2][columns_count_ / 2];
    cell.has_spark = true;
    cell.electric_potential = 1.f;
}

void Grid::UpdateElectricPotential() {
    bool did_converge = false;
    while(!did_converge) {
        did_converge = true;

        for (std::size_t i = 1; i < rows_count_ - 1; ++i) {
            for (std::size_t j = 1; j < columns_count_ - 1; ++j) {
                auto& cell = cells_[i][j];
                if (cell.has_spark) continue;

                // Laplace
                const auto prev_potential = cell.electric_potential;
                cell.electric_potential = (
                    cells_[i-1][j].electric_potential + 
                    cells_[i+1][j].electric_potential + 
                    cells_[i][j-1].electric_potential + 
                    cells_[i][j+1].electric_potential) / 4.f;
                const auto electric_potential_diff = fabs(cell.electric_potential - prev_potential);
                if (electric_potential_diff > kPotentialDiffThreshold) {
                    did_converge = false;
                }
            }
        }
    }
}

void Grid::UpdateElectricField() {
    // celda vecina a la chispa
    // probabilidad de propagacion
    std::vector<std::pair<std::size_t, std::size_t>> sparks_neighbours;
    std::vector<float> sparks_neighbours_probs;
    auto spark_neighbours_sum_electric_potential = 0.f;
    for (std::size_t i = 1; i < rows_count_ - 1; ++i) {
        for (std::size_t j = 1; j < columns_count_ - 1; ++j) {
            auto& cell = cells_[i][j];
            if (!cell.has_spark) continue;

            auto neighbours = GetNeighbours(i, j);
            for (auto [nrow, ncol] : neighbours) {
                auto& cell_neighbour = cells_[nrow][ncol];
                if (cell_neighbour.has_spark) continue;
                
                cell_neighbour.electric_field = pow(
                    fabs(cell.electric_potential - cell_neighbour.electric_potential), 2.f
                );

                sparks_neighbours.emplace_back(nrow, ncol);
                sparks_neighbours_probs.push_back(cell_neighbour.electric_field);
                spark_neighbours_sum_electric_potential += cell_neighbour.electric_field;
            }
        }
    }

    if (sparks_neighbours_probs.empty()) return;

    for (std::size_t i = 0; i < sparks_neighbours_probs.size(); ++i) {
        sparks_neighbours_probs[i] /= spark_neighbours_sum_electric_potential;
    }

    float sum = 0.0;
    for (float prob : sparks_neighbours_probs) {
        sum += prob;
    }

    // Generar un número aleatorio entre 0 y la suma de las probabilidades
    float random = engine_.GetRandomGenerator().Generate(0.f, sum);//static_cast<float>(rand()) / static_cast<float>(RAND_MAX) * sum;

    //std::cout << "\n-------Probabilities-------- \n";

    // Seleccionar el índice basado en el número aleatorio
    std::size_t index = sparks_neighbours_probs.size() - 1;
    float cumulative = 0.0;
    for (int i = 0; i < sparks_neighbours_probs.size(); ++i) {
        //std::cout << random << " " << sparks_neighbours_probs[i] << "\n";
        cumulative += sparks_neighbours_probs[i];
        if (random < cumulative) {
            index = i;
            break;
        }
    }
    
    SpawnSparkInRowColumn(sparks_neighbours[index].first, sparks_neighbours[index].second);
}

void Grid::SpawnSparkInRowColumn(std::size_t row, std::size_t column) {
    auto& new_spark = cells_[row][column];
    new_spark.has_spark = true;
    new_spark.electric_potential = 1.f;
    new_spark.electric_field = 0.f;
}

void Grid::SpawnSparkInCoords(int x, int y) {
    if (!AreCoordsInsideBounds(x, y)) return;

    const std::size_t row = std::min(
        static_cast<std::size_t>(y) * rows_count_ / static_cast<std::size_t>(height_),
        rows_count_ - 1);
    const std::size_t column = std::min(
        static_cast<std::size_t>(x) * columns_count_ / static_cast<std::size_t>(width_),
        columns_count_ - 1);
    
    SpawnSparkInRowColumn(row, column);
}

bool Grid::AreCoordsInsideBounds(int x, int y) const {
    return (x <= width_ && x >= 0 &&
            y <= height_ && y >= 0);
}

std::array<std::pair<std::size_t, std::size_t>, 4> Grid::GetNeighbours(std::size_t row, std::size_t column) {
    return {{{row - 1, column}, {row + 1, column}, {row, column + 1}, {row, column - 1}}};
}


Cell& Grid::GetCell(std::size_t row, std::size_t column) {
    assert(row >= 0 && row < rows_count_ && column >= 0 && column < columns_count_);
    return cells_[row][column];
}

void Grid::UpdateCells(float dt) {
    UpdateElectricPotential();
    UpdateElectricField();
}

void Grid::RenderCells() {
    const float float_cell_size = static_cast<float>(kCellSize);
    float y = 0.f;
    for (auto& row : cells_) {
        float x = 0.f;
        for (auto& cell : row) {
            Color color_inside = (cell.has_spark) ? Color{255, 255, 255, 255} : Color{0, 0, 0, 255};
            engine_.DrawRectangle(
                {x, y, float_cell_size, float_cell_size},
                color_inside,
                true);
                
            Color color_outside = (cell.has_spark) ? Color{0, 150, 210, 255} : Color{0, 0, 0, 255};
            engine_.DrawRectangle(
                {x, y, float_cell_size, float_cell_size},
                color_outside,
                false);
            x += float_cell_size;
        }
        y += float_cell_size;
    }
}

void Grid::ClearAllParticles() {
    for (auto& particles : cells_) {
        for (auto& particle : particles) {
            particle.electric_field = 0.f;
            particle.electric_potential = 0.f;
            particle.has_spark = false;
        }
    }
}

void Grid::UglyDraw() {
    for (auto& particles : cells_) {
        for (auto& particle : particles) {
            if (particle.has_spark) {
                std::cout << "0";
            } else {
                std::cout << " ";
            }
        }
        std::cout << "\n";
    }
}
