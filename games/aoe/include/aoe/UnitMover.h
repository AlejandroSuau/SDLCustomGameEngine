#pragma once

#include <cmath>
#include <queue>
#include <algorithm>

#include "Unit.h"

class GameMap;

struct Node {
    int row_, col_;
    float cost_g_, cost_h_;
    Node* parent_;

    Node(int row, int col, float cost_g, float cost_h, Node* parent)
        : row_(row), col_(col), cost_g_(cost_g), cost_h_(cost_h), parent_(parent) {}


    Node(int row, int col)
        : row_(row), col_(col), cost_g_(0.f), cost_h_(0.f), parent_(nullptr) {}

    float FCost() const { return cost_g_ + cost_h_; }

    bool operator<(const Node& other) const {
        return (FCost() > other.FCost());
    }
};

class UnitMover {
public:
    UnitMover(GameMap& map);

    std::vector<std::tuple<int, int>> FindPath(
        int row_from,
        int col_from,
        int row_to,
        int col_to);

    bool MoveUnit(
        Unit& unit,
        int from_row,
        int from_col,
        int row_to,
        int col_to);
    
    void Render(SDL_Renderer& renderer);

private:
    GameMap& map_;

    float Heuristic(int row1, int col1, int row2, int col2) const {
        return std::abs(row1 - row2) + std::abs(col1 - col2);
    }

    std::vector<std::tuple<int, int>> ReconstructPath(Node& node) const;
};
