#pragma once

#include <set>
#include <utility>
#include <vector>

typedef uint32_t Node;
typedef std::set<std::pair<Node, Node>> AdjacencyMatrix;

std::optional<std::vector<Node>> topo_sort_kahn(uint32_t number_of_nodes,
                                                AdjacencyMatrix edges);

std::optional<std::vector<Node>> topo_sort_dfs(uint32_t number_of_nodes,
                                               AdjacencyMatrix edges);
