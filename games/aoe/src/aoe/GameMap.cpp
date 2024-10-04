#pragma once

#include "aoe/GameMap.h"

#include <iostream>

static const std::size_t kCellSize = 16;
static const int kCellSizeInt = static_cast<int>(kCellSize);

GameMap::GameMap(int width, int height) 
    : width_(width)
    , height_(height) {
    Init();
}
    
void GameMap::Init() {
    cols_count_ = static_cast<std::size_t>(width_ / kCellSizeInt);
    rows_count_ = static_cast<std::size_t>(height_ / kCellSizeInt);
    cells_size_ = cols_count_ * rows_count_;
    cells_.reserve(cells_size_);
    for (std::size_t i = 0; i < rows_count_; ++i) {
        for (std::size_t j = 0; j < cols_count_; ++j) {
            cells_.emplace_back(
                i,
                j,
                static_cast<int>(i * kCellSize),
                static_cast<int>(j * kCellSize));
        }
    }
}

void GameMap::Update() {

}

void GameMap::Render(SDL_Renderer& renderer) {
    SDL_SetRenderDrawColor(&renderer, 150, 150, 150, 255);
    for (auto& cell : cells_) {
        SDL_Rect cell_rect {
            cell.x_,
            cell.y_,
            kCellSizeInt,
            kCellSizeInt};
        
        if (cell.is_occupied_) {
            SDL_RenderFillRect(&renderer, &cell_rect);
        } else {
            SDL_RenderDrawRect(&renderer, &cell_rect);
        }
    }
}

std::vector<Node> GameMap::GetNeighbours(int row, int col) const {
    static const std::array<std::tuple<int, int>, 4> directions {{
        {0, 1},
        {0, -1},
        {1, 0},
        {-1, 0}
    }};
    for (const auto& [dr, dc] : directions) {

    }
}

void GameMap::Occupy(std::size_t row, std::size_t col) {
    // check if it is occupied?
    SetOccupy(row, col, true);
}

void GameMap::Unoccupy(std::size_t row, std::size_t col) {
    SetOccupy(row, col, false);
}

void GameMap::SetOccupy(std::size_t row, std::size_t col, bool is_occupied) {
    const auto index = FromRowColToIndex(row, col);
    cells_[index].is_occupied_ = is_occupied;
}

std::size_t GameMap::FromRowColToIndex(std::size_t row, std::size_t col) const {
    std::cout << row << " " << cells_size_ << " " << col << "\n";
    return (row * cols_count_ + col);
}

std::tuple<std::size_t, std::size_t> GameMap::FromIndexToRowCol(std::size_t index) const {
    return {index / cells_size_, index % cells_size_};
}

std::tuple<std::size_t, std::size_t> GameMap::FromCoordsToRowCol(int coord_x, int coord_y) const {
    return {static_cast<std::size_t>(coord_y / kCellSizeInt), static_cast<std::size_t>(coord_x / kCellSizeInt)};
}

int GameMap::GetRowsCount() const {
    return rows_count_;
}

int GameMap::GetColumnsCount() const {
    return cols_count_;
}
