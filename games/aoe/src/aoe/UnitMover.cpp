#include "aoe/UnitMover.h"

#include <functional>

#include "aoe/GameMap.h"

UnitMover::UnitMover(
    GameMap& map,
    int start_row,
    int start_col,
    int target_row,
    int target_col)
    : map_(map)
    , target_index_(0)
    , start_row_(start_row)
    , start_col_(start_col)
    , target_row_(target_row)
    , target_col_(target_col)
    , solution_node_(nullptr)
    , did_finish_(false)
    , solution_nodes_count_(0) {

    Reset(start_row, start_col, target_row, target_col);
}

UnitMover::MapNode* UnitMover::FindPath(SDL_Renderer& renderer, TTF_Font& font) {
    while (!did_finish_) {
        Step(renderer, font);
    }

    return solution_node_;
}

void UnitMover::Reset(int start_row, int start_col, int target_row, int target_col) {
    start_row_ = start_row;
    start_col_ = start_col;
    target_row_ = target_row;
    target_col_ = target_col;
    
    did_finish_ = false;
    solution_node_ = nullptr;
    
    target_index_ = map_.FromRowColToIndex(target_row_, target_col_);
    std::cout << "To " << target_index_ << " [" << target_row_ << ", " << target_col << "]\n";

    // Map Nodes
    open_nodes_.clear();
    map_nodes_.clear();
    const auto map_cells_count = map_.GetCellsCount();
    map_nodes_.reserve(map_cells_count);
    for (std::size_t i = 0; i < map_cells_count; ++i) {
        map_nodes_.emplace_back(i);
    }

    // Nodes Open
    // TODO: Crear método para reiniciarla
    // nodes_open_ = std::priority_queue<UnitMover::MapNode*>();
    const auto node_index = map_.FromRowColToIndex(start_row_, start_col_);
    target_index_ = map_.FromRowColToIndex(target_row_, target_col_);
    auto& starting_node = map_nodes_[node_index];
    starting_node.h = Heuristic(start_row, start_col, target_row_, target_col_);
    starting_node.is_closed = true;

    nodes_open_.Push(&starting_node);
    open_nodes_.emplace(&starting_node);

    // Clear used number textures
    for (auto& data : texture_rects_numbers_) {
        SDL_DestroyTexture(data.tx);
    }
    texture_rects_numbers_.clear();
}

void UnitMover::Step(SDL_Renderer& renderer, TTF_Font& font) {
    if (did_finish_ || open_nodes_.empty()) {
        std::cout << "No need to step. Algoritm already finished or nodes_open is empty\n";
        target_node_ = nullptr;
        did_finish_ = true;
        return;
    }

    std::cout << "Open nodes:";
    for (auto& n : open_nodes_) {
        auto [nr, nc] = map_.FromIndexToRowCol(n->map_index);
        std::cout << "\n\t[" << nr << ", " << nc << "] -> g(" << n->g << "), h(" << n->h << ") = f(" << n->FCost() << ")\n";
    }
    std::cout << "\n";

    auto* node = *open_nodes_.begin();
    open_nodes_.erase(open_nodes_.begin());
    const auto [cr, cc] = map_.FromIndexToRowCol(node->map_index);
    std::cout << "\n* Best candidate: [" << cr << ", " << cc << "] -> g(" << node->g << "), h(" << node->h << ") = f(" << node->FCost() << ")\n";
    if (node->map_index == target_index_) {
        std::cout << "##### Reached the target!: [" << node->map_index << " = " << target_index_ << "]\n";
        target_node_ = node;
        did_finish_ = true;
        return;
    }

    node->is_closed = true;
    auto neighbours = GetNeighbours(node->map_index);
    auto [row, col] = map_.FromIndexToRowCol(node->map_index);
    for (auto* neighbour : neighbours) {
        const bool skip_neighbour = (!neighbour || neighbour->is_closed);
        if (skip_neighbour) continue;

        const int g_cost = node->g + 1; // (weight * heuristic) 1 in our case
        if (!neighbour->is_open || g_cost < neighbour->g) {
            neighbour->g = g_cost;
            const auto [nrow, ncol] = map_.FromIndexToRowCol(neighbour->map_index);
            neighbour->h = Heuristic(nrow, ncol, target_row_, target_col_);
            neighbour->parent = node;
            if (neighbour->is_open) {
                std::cout << "ALERT! TRYING TO UPDATE POS\n";
                // Update neighbour values (remove and insert?)
            } else {
                neighbour->is_open = true;
                open_nodes_.emplace(neighbour);
            }
        }
    }

    CreateTextureRectNumbers(renderer, font);
}

UnitMover::Neighbours UnitMover::GetNeighbours(std::size_t node_index) {
    Neighbours neighbours {nullptr, nullptr, nullptr, nullptr};

    const int columns_count = static_cast<int>(map_.GetColumnsCount());
    const int index = static_cast<int>(node_index);

    const int e_index = index + 1;
    if (map_.IsWalkable(e_index) && e_index % columns_count != 0) neighbours[0] = &map_nodes_[e_index];
    
    const int w_index = index + -1;
    if (map_.IsWalkable(w_index) && w_index % columns_count != columns_count - 1) neighbours[1] = &map_nodes_[w_index];

    const int n_index = index - columns_count;
    if (map_.IsWalkable(n_index) && n_index >= 0) neighbours[2] = &map_nodes_[n_index];

    const int nodes_count = static_cast<int>(map_.GetCellsCount());
    const int s_index = index + columns_count;
    if (map_.IsWalkable(s_index) && s_index < nodes_count) neighbours[3] = &map_nodes_[s_index];

    return neighbours;
}

int UnitMover::Heuristic(int row1, int col1, int row2, int col2) const {
    return std::abs(row1 - row2) + std::abs(col1 - col2);
}

/*std::vector<std::tuple<int, int>> UnitMover::ReconstructPath(Node& node) const {
    std::vector<std::tuple<int, int>> path;

    Node* current_node = &node;
    while (current_node != nullptr) {
        path.push_back(std::make_tuple(current_node->row_, current_node->col_));
        current_node = current_node->parent_;
    }

    std::reverse(path.begin(), path.end());  // Invertimos la ruta
    return path;
}*/

void UnitMover::CreateTextureRectNumbers(SDL_Renderer& renderer, TTF_Font& font) {
    SDL_Color text_color {255, 255, 255, 255};
    for (auto& node : map_nodes_) {
        if (node.h <= 0) continue;
        SDL_Surface* text_surface = TTF_RenderText_Solid(&font, std::to_string(node.FCost()).c_str(), text_color);
        if (!text_surface) {
            std::cerr << " Error: " << SDL_GetError() << "\n";
            throw std::runtime_error("Error al crear la surface: " + std::string(SDL_GetError()));
        }
        
        SDL_Texture* text_texture = SDL_CreateTextureFromSurface(&renderer, text_surface);
        if (!text_texture) {
            throw std::runtime_error("Error al crear la texture: " + std::string(SDL_GetError()));
        }

        const auto [row, col] = map_.FromIndexToRowCol(node.map_index);
        SDL_Rect text_rect {col * 16 + 4, row * 16 + 2, text_surface->w, text_surface->h};
        SDL_Color color_blue{108, 130, 220, 255};
        SDL_Color color_green{127, 181, 150, 255};
        SDL_Color c = color_green;
        if (node.FCost() > 0 && !node.is_closed) {
            c = color_blue;
        }
        texture_rects_numbers_.emplace_back(text_texture, text_rect, c);

        SDL_FreeSurface(text_surface);
    }
}

void UnitMover::Render(SDL_Renderer& renderer) {
    SDL_Rect starter_rect {start_col_ * 16, start_row_ * 16, 16, 16};
    SDL_SetRenderDrawColor(&renderer, 0, 0, 255, 255);
    SDL_RenderFillRect(&renderer, &starter_rect);

    SDL_Rect target_rect {target_col_ * 16, target_row_ * 16, 16, 16};
    SDL_SetRenderDrawColor(&renderer, 0, 255, 0, 255);
    SDL_RenderFillRect(&renderer, &target_rect);

    // std::cout << "target: " << target_row_ << ", " << target_col_ << "\n"; 
    
    for (auto& data : texture_rects_numbers_) {
        SDL_SetRenderDrawColor(&renderer, data.color.r, data.color.g, data.color.b, data.color.a);
        SDL_RenderFillRect(&renderer, &data.rect);

        SDL_SetRenderDrawColor(&renderer, 0, 255, 255, 255);
        SDL_RenderCopy(&renderer, data.tx, nullptr, &data.rect);
    }
    
    // Renderizamos donde está

    // 
}

bool UnitMover::DidFinish() const {
    return did_finish_;
}