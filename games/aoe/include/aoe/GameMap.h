#pragma once

#include <vector>
#include <array>

#include <SDL2/SDL.h>

class GameMap {
public:
    GameMap(int width, int height);

    void Init();
    void Update();
    void Render(SDL_Renderer& renderer);

    void Occupy(std::size_t row, std::size_t col);
    void Unoccupy(std::size_t row, std::size_t col);

    std::size_t FromRowColToIndex(std::size_t row, std::size_t col) const;
    std::tuple<std::size_t, std::size_t> FromIndexToRowCol(std::size_t index) const;
    std::tuple<std::size_t, std::size_t> FromCoordsToRowCol(int coord_x, int coord_y) const;

    int GetRowsCount() const;
    int GetColumnsCount() const;

    std::vector<Node> GetNeighbours() const;

private:    
    struct Cell {
        Cell(std::size_t row, std::size_t col, int x, int y)
            : row_(row), col_(col), x_(x), y_(y), is_occupied_(false) {}
        
        std::size_t row_, col_;
        int x_, y_;
        bool is_occupied_;
    };

    int width_;
    int height_;
    std::size_t rows_count_;
    std::size_t cols_count_;
    std::size_t cells_size_;

    std::vector<Cell> cells_;

    void SetOccupy(std::size_t row, std::size_t col, bool is_occupied);
};
