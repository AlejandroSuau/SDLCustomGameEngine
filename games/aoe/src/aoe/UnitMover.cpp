#include "aoe/UnitMover.h"

#include "aoe/GameMap.h"

UnitMover::UnitMover(GameMap& map) 
    : map_(map) {}

bool UnitMover::MoveUnit(
    Unit& unit,
    int from_col,
    int from_row,
    int row_to,
    int col_to) {

        return true;
}


std::vector<std::tuple<int, int>> UnitMover::FindPath(
    int row_from,
    int col_from,
    int row_to,
    int col_to) {

    std::priority_queue<Node> open_list;
    std::vector<std::vector<bool>> closed_list( // std::array 
        map_.GetRowsCount(),
        std::vector<bool>(map_.GetColumnsCount(), false));
    
    open_list.emplace(
        row_from,
        col_from,
        0.f,
        Heuristic(row_from, col_from, row_to, col_to),
        nullptr);
    /*while (!open_list.empty()) {
        auto current_node = open_list.top();
        open_list.pop();
        if (current_node.row_ == row_to && current_node.col_ == col_to) {
            return ReconstructPath(current_node); // reverse list
        }

        closed_list[current_node.row_][current_node.col_] = true;

        auto neighbours = map_.GetNeighbours(current_node.row_, current_node.col_);
        for (auto& neighbour : neighbours) {
            if (closed_list[neighbour.row_][neighbour.col_]) { // not walkable or closes_list
                continue;
            }

            neighbour.cost_g_ = current_node.cost_g_ + 1.f; // suponemos coste de movimiento constante
            neighbour.cost_h_ = Heuristic(neighbour.row_, neighbour.col_, row_to, col_to);
            neighbour.parent_ = &current_node;
            open_list.push(neighbour);
        }
    }*/

    return {}; // no way found
}

std::vector<std::tuple<int, int>> UnitMover::ReconstructPath(Node& node) const {
    std::vector<std::tuple<int, int>> path;

    Node* current_node = &node;
    while (current_node != nullptr) {
        path.push_back(std::make_tuple(current_node->row_, current_node->col_));
        current_node = current_node->parent_;
    }

    std::reverse(path.begin(), path.end());  // Invertimos la ruta
    return path;
}

void UnitMover::Render(SDL_Renderer& renderer) {
    // Renderizamos todas las puntuaciones.
    
    // Renderizamos donde está

    // 
}

/*openList = [startNode]
closedList = []

while openList is not empty:
    currentNode = node in openList with lowest f_cost
    remove currentNode from openList
    add currentNode to closedList
    
    if currentNode is targetNode:
        return retracePath(startNode, targetNode)
    
    foreach neighbor of currentNode:
        if neighbor is not walkable or neighbor is in closedList:
            continue
        
        newCostToNeighbor = currentNode.g_cost + getDistance(currentNode, neighbor)
        if newCostToNeighbor < neighbor.g_cost or neighbor is not in openList:
            neighbor.g_cost = newCostToNeighbor
            neighbor.h_cost = getDistance(neighbor, targetNode)
            neighbor.parent = currentNode
            
            if neighbor is not in openList:
                add neighbor to openList*/