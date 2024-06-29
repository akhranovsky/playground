#pragma once

#include <optional>
#include <utility>
#include <vector>

typedef uint32_t Node;
typedef std::pair<Node, Node> Edge;
typedef std::vector<Edge> Edges;

std::optional<std::vector<Node>> topo_sort_kahn(uint32_t number_of_nodes,
                                                Edges edges);

std::optional<std::vector<Node>> topo_sort_dfs(uint32_t number_of_nodes,
                                               Edges edges);
