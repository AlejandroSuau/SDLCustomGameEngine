#pragma once

#include <cmath>
#include <queue>
#include <algorithm>

#include "Unit.h"
#include "GameMap.h"

struct Node {
    int row_, col_;
    float cost_g_, cost_h_;
    Node* parent_;

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

private:
    GameMap& map_;

    float Heuristic(int row1, int col1, int row2, int col2) const {
        return std::abs(row1 - row2) + std::abs(col1 - col2);
    }
};
