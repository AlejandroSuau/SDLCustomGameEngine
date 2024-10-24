#pragma once

#include <cmath>
#include <queue>
#include <algorithm>
#include <optional>
#include <iostream>
#include <stdexcept>
#include <string>
#include <set>

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

#include "Unit.h"
#include "utils/BinaryHeap.h"

class GameMap;

class UnitMover {
private:
    struct MapNode {
            std::size_t map_index;
            int g; // distance from starting_node
            int h; // heuristic (distance from target node)
            bool is_open, is_closed;
            MapNode* parent;

            MapNode(std::size_t map_idx)
                : map_index(map_idx), g(0), h(0), is_open(false), is_closed(false), parent(nullptr) {}

            int FCost() const { return g + h; }

            struct Comparator {
                int operator()(const MapNode* n1, const MapNode* n2) const {
                    if (n1->FCost() == n2->FCost()) {
                        return n1->map_index < n2->map_index;  // Comparar por map_index si FCost es igual
                    }

                    return (n1->FCost() < n2->FCost());
                }
            };
        };
public:
    UnitMover(
        GameMap& map,    
        int start_row,
        int start_col,
        int target_row,
        int target_col);

    MapNode* FindPath(SDL_Renderer& renderer, TTF_Font& font);
    void Step(SDL_Renderer& renderer, TTF_Font& font);
    void Render(SDL_Renderer& renderer);
    void Reset(int start_row, int start_col, int target_row, int target_col);
    bool DidFinish() const;

private:
    GameMap& map_;
    std::vector<MapNode> map_nodes_;
    std::set<MapNode*, MapNode::Comparator> open_nodes_;
    std::size_t solution_nodes_count_;

    //std::priority_queue<MapNode*> nodes_open_;
    BinaryHeap<MapNode*, MapNode::Comparator> nodes_open_;
    std::size_t target_index_;
    UnitMover::MapNode* target_node_;
    UnitMover::MapNode* solution_node_;

    using Neighbours = std::array<MapNode*, 4>;
    Neighbours GetNeighbours(std::size_t node_index);

    /////////
    int start_row_, start_col_;
    int target_row_, target_col_;
    bool did_finish_;

    int Heuristic(int row1, int col1, int row2, int col2) const;

    struct CellData {
        SDL_Texture* tx;
        SDL_Rect rect;
        SDL_Color color;
    };

    std::vector<CellData> texture_rects_numbers_; //std::pair<SDL_Texture*, SDL_Rect>
    void CreateTextureRectNumbers(SDL_Renderer& renderer, TTF_Font& font);
};
