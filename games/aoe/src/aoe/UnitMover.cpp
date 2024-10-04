#pragma once

#include "aoe/UnitMover.h"

UnitMover::UnitMover(GameMap& map) 
    : map_(map) {}

bool UnitMover::MoveUnit(
    Unit& unit,
    int from_col,
    int from_row,
    int row_to,
    int col_to) {


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
    while (!open_list.empty()) {
        auto current_node = open_list.top();
        open_list.pop();
        if (current_node.row_ == row_to && current_node.col_ == col_to) {
            return {{current_node.row_, current_node.col_}}; // reverse list
        }

        closed_list[current_node.row_][current_node.col_] = true;

        auto neighbours = map_.GetNeighbours(current_node);
        for (auto& neighbour : neighbours) {
            if (closed_list[neighbour.row_][neighbour.column_]) { // not walkable or closes_list
                continue;
            }

            neighbour.cost_g = current_node.cost_g_ + 1.f; // suponemos coste de movimiento constante
            neighbour.cost_h = Heuristic(neighbour.row_, neighbour.col_, row_to, col_to);
            neighbour.parent = &current_node;
            open_list.push(neighbour);
        }
    }

    return {}; // no way found
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