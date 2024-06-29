#include "topo_sort.h"

#include <algorithm>
#include <deque>
#include <set>

// Topological sorting using BFS (Kahn's algorithm).
// https://en.wikipedia.org/wiki/Topological_sorting#Kahn's_algorithm
//
// Time complexity: O(V + E)
// Space complexity: O(V)
//
// Parameters:
// `number_of_nodes` is the number of nodes in the graph.
// `edges` is a list of edges in the form `(from, to)` where `from` and `to` are
// node indices.
std::optional<std::vector<Node>> topo_sort_kahn(uint32_t number_of_nodes,
                                                Edges edges) {
  std::vector<Node> result = {};
  result.reserve(number_of_nodes);

  auto degrees = std::vector<uint32_t>(number_of_nodes, 0);

  for (auto [from, to] : edges) {
    if (from != to) {
      degrees[to]++;
    }
  }

  std::deque<Node> queue{};

  for (auto i = 0; i < degrees.size(); i++) {
    if (degrees[i] == 0) {
      queue.push_back(i);
    }
  }

  while (!queue.empty()) {
    auto node = queue.front();
    queue.pop_front();
    result.push_back(node);

    // look up outgoing nodes
    for (auto [from, to] : edges) {
      if (from == node && --degrees[to] == 0) {
        queue.push_back(to);
      }
    }
  }

  if (result.size() != number_of_nodes) {
    return std::nullopt;
  }

  return result;
}

bool dfs(Node node, Edges edges, std::vector<bool> &visited,
         std::set<Node> &stack, std::vector<Node> &result) {
  if (!visited[node]) {
    visited[node] = true;

    for (auto [from, to] : edges) {
      if (from == node) {
        // Check if there is a cycle.

        if (!stack.insert(to).second) {
          // If `to` is already in `stack`, it means that there is a cycle.
          return false;
        }

        if (!dfs(to, edges, visited, stack, result)) {
          // Propagate detected cycle;
          return false;
        }

        stack.erase(to);
      }
    }

    result.push_back(node);
  }

  return true;
}

// Topological sorting using DFS.
//
// Time complexity: O(V + E)
// Space complexity: O(V)
//
// Parameters:
// `number_of_nodes` is the number of nodes in the graph.
// `edges` is a list of edges in the form `(from, to)` where `from` and `to` are
// node indices.
std::optional<std::vector<Node>> topo_sort_dfs(uint32_t number_of_nodes,
                                               Edges edges) {
  std::vector<Node> result = {};
  std::set<Node> stack = {};

  std::vector<bool> visited(number_of_nodes, false);

  for (auto i = 0; i < number_of_nodes; i++) {
    if (!visited[i]) {
      stack.insert(i);
      if (!dfs(i, edges, visited, stack, result)) {
        return std::nullopt;
      }
      stack.erase(i);
    }
  }

  std::reverse(result.begin(), result.end());
  return result;
}
