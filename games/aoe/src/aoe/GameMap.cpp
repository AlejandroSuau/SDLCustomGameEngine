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
    cells_count_ = cols_count_ * rows_count_;
    cells_.reserve(cells_count_);
    std::size_t index = 0;
    for (std::size_t row = 0; row < rows_count_; ++row) {
        for (std::size_t col = 0; col < cols_count_; ++col) {
            cells_.emplace_back(
                index,
                static_cast<int>(col * kCellSize),
                static_cast<int>(row * kCellSize));
        }
        ++index;
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
        
        SDL_SetRenderDrawColor(&renderer, 150, 150, 150, 255);
        SDL_RenderDrawRect(&renderer, &cell_rect);
        if (!cell.is_walkable_) {
            SDL_SetRenderDrawColor(&renderer, 220, 220, 220, 255);
            SDL_RenderFillRect(&renderer, &cell_rect);
        }
    }
}

void GameMap::Occupy(int row, int col) {
    // check if it is occupied?
    SetOccupy(row, col, true);
}

void GameMap::Unoccupy(int row, int col) {
    SetOccupy(row, col, false);
}

void GameMap::SetOccupy(int row, int col, bool is_occupied) {
    const auto index = FromRowColToIndex(row, col);
    cells_[index].is_occupied_ = is_occupied;
}

void GameMap::SetIsWalkable(int row, int col, bool is_walkable) {
    const auto index = FromRowColToIndex(row, col);
    cells_[index].is_walkable_ = is_walkable;
}

bool GameMap::IsWalkable(int row, int col) const {
    const auto index = FromRowColToIndex(row, col);
    return IsWalkable(index);
}

bool GameMap::IsWalkable(std::size_t index) const {
    return (IsInsideBoundaries(index) && cells_[index].is_walkable_);
}

std::size_t GameMap::FromRowColToIndex(int row, int col) const {
    return (row * cols_count_ + col);
}

GameMap::RowColPair GameMap::FromIndexToRowCol(std::size_t index) const {
    return std::make_pair(index / cols_count_, index % cols_count_);
}

GameMap::RowColPair GameMap::FromCoordsToRowCol(int coord_x, int coord_y) const {
    return std::make_pair(coord_y / kCellSizeInt, coord_x / kCellSizeInt);
}

bool GameMap::IsInsideBoundaries(std::size_t index) const {
    return (index >= 0 && index < cells_count_);
}

std::size_t GameMap::GetRowsCount() const {
    return rows_count_;
}

std::size_t GameMap::GetColumnsCount() const {
    return cols_count_;
}

std::size_t GameMap::GetCellsCount() const {
    return cells_count_;
}
