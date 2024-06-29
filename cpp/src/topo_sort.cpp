#include "topo_sort.h"

#include <algorithm>
#include <deque>
#include <iostream>

// Topological sorting using BFS (Kahn's algorithm).
// https://en.wikipedia.org/wiki/Topological_sorting#Kahn's_algorithm
//
// Time complexity: O(V + E)
// Space complexity: O(V)
//
// `edges` is a list of edges in the form `(from, to)` where `from` and `to` are
// node indices.
std::optional<std::vector<Node>> topo_sort_kahn(uint32_t number_of_nodes,
                                                AdjacencyMatrix edges) {
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
    std::cout << i << ":" << degrees[i] << std::endl;
  }

  while (!queue.empty()) {
    std::cout << "Q: ";
    for (auto i = 0; i < queue.size(); i++) {
      std::cout << queue[i] << " ";
    }
    std::cout << std::endl;

    auto node = queue.front();
    queue.pop_front();
    result.push_back(node);
    // look up outgoing nodes
    for (auto [from, to] : edges) {
      if (from == node) {
        if (--degrees[to] == 0) {
          queue.push_back(to);
        }
      }
    }
  }

  if (result.size() != number_of_nodes) {
    return std::nullopt;
  }
  return result;
}

void print(std::vector<Node> result) {
  std::cout << "[";
  for (auto i = 0; i < result.size(); i++) {
    std::cout << result[i] << " ";
  }
  std::cout << "]" << std::endl;
}
bool dfs(std::vector<Node> &recursion_stack, Node node, AdjacencyMatrix edges,
         std::vector<bool> &visited, std::vector<Node> &result) {
  if (!visited[node]) {
    visited[node] = true;

    for (auto [from, to] : edges) {
      if (from == node) {
        // Check if there is a cycle.
        if (std::find(recursion_stack.begin(), recursion_stack.end(), to) !=
            recursion_stack.end()) {
          return false;
        }
        recursion_stack.push_back(to);

        if (!dfs(recursion_stack, to, edges, visited, result)) {
          // Propagate detected cycle;
          return false;
        }

        recursion_stack.pop_back();
      }
    }
    result.push_back(node);
  }
  return true;
}

std::optional<std::vector<Node>> topo_sort_dfs(uint32_t number_of_nodes,
                                               AdjacencyMatrix edges) {
  std::vector<Node> result = {};
  std::vector<Node> recursion_stack = {};

  std::vector<bool> visited(number_of_nodes, false);

  for (auto i = 0; i < number_of_nodes; i++) {
    if (!visited[i]) {
      recursion_stack.push_back(i);
      if (!dfs(recursion_stack, i, edges, visited, result)) {
        return std::nullopt;
      }
      recursion_stack.pop_back();
    }
  }
  std::reverse(result.begin(), result.end());
  return result;
}
