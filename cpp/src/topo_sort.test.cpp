#include <gtest/gtest.h>

#include "topo_sort.h"

TEST(TopSortKahn, EmptyGraph) {
  EXPECT_EQ(topo_sort_kahn(0, Edges{}), std::vector<Node>{});
}
TEST(TopSortKahn, NoEdges) {
  EXPECT_EQ(topo_sort_kahn(3, Edges{}), std::vector<Node>({0, 1, 2}));
}
TEST(TopSortKahn, AllConnectedDirectly) {
  EXPECT_EQ(topo_sort_kahn(3, Edges{Edge(0, 1), Edge(1, 2)}),
            std::vector<Node>({0, 1, 2}));
}
TEST(TopSortKahn, AllConnectedDirectlyReversed) {
  EXPECT_EQ(topo_sort_kahn(3,
                           Edges{
                               Edge(2, 1),
                               Edge(1, 0),
                           }),
            std::vector<Node>({2, 1, 0}));
}

TEST(TopSortKahn, TwoTargets) {
  EXPECT_EQ(topo_sort_kahn(3,
                           Edges{
                               Edge(0, 1),
                               Edge(0, 2),
                           }),
            std::vector<Node>({0, 1, 2}));
}
TEST(TopSortKahn, TwoSources) {
  EXPECT_EQ(topo_sort_kahn(3,
                           Edges{
                               Edge(2, 0),
                               Edge(1, 0),
                           }),
            std::vector<Node>({1, 2, 0}));
}

TEST(TopSortKahn, Wiki) {
  EXPECT_EQ(topo_sort_kahn(12,
                           Edges{
                               Edge(3, 8),
                               Edge(3, 10),
                               Edge(5, 11),
                               Edge(7, 11),
                               Edge(7, 8),
                               Edge(8, 9),
                               Edge(11, 10),
                               Edge(11, 9),
                               Edge(11, 2),
                           }),
            std::vector<Node>({0, 1, 3, 4, 5, 6, 7, 11, 8, 10, 2, 9}));
}

TEST(TopSortKahn, FullCyclic2) {
  EXPECT_EQ(topo_sort_kahn(2,
                           Edges{
                               Edge(0, 1),
                               Edge(1, 0),
                           }),
            std::nullopt);
}
TEST(TopSortKahn, FullCyclic3) {
  EXPECT_EQ(topo_sort_kahn(3,
                           Edges{
                               Edge(0, 1),
                               Edge(1, 2),
                               Edge(2, 0),
                           }),
            std::nullopt);
}
TEST(TopSortKahn, PartCyclic) {
  EXPECT_EQ(topo_sort_kahn(3,
                           Edges{
                               Edge(0, 1),
                               Edge(1, 0),
                           }),
            std::nullopt);
}
TEST(TopSortKahn, SelfCycle) {
  EXPECT_EQ(topo_sort_kahn(3, Edges{Edge(0, 0), Edge(1, 2), Edge(2, 2)}),
            std::vector<Node>({0, 1, 2}));
}

TEST(TopSortDfs, EmptyGraph) {
  EXPECT_EQ(topo_sort_dfs(0, Edges{}), std::vector<Node>{});
}
TEST(TopSortDfs, NoEdges) {
  EXPECT_EQ(topo_sort_dfs(3, Edges{}), std::vector<Node>({2, 1, 0}));
}
TEST(TopSortDfs, AllConnectedDirectly) {
  EXPECT_EQ(topo_sort_dfs(3,
                          Edges{
                              Edge(0, 1),
                              Edge(1, 2),
                          }),
            std::vector<Node>({0, 1, 2}));
}
TEST(TopSortDfs, AllConnectedDirectlyReversed) {
  EXPECT_EQ(topo_sort_dfs(3,
                          Edges{
                              Edge(2, 1),
                              Edge(1, 0),
                          }),
            std::vector<Node>({2, 1, 0}));
}

TEST(TopSortDfs, TwoTargets) {
  EXPECT_EQ(topo_sort_dfs(3,
                          Edges{
                              Edge(0, 1),
                              Edge(0, 2),
                          }),
            std::vector<Node>({0, 2, 1}));
}
TEST(TopSortDfs, TwoSources) {
  EXPECT_EQ(topo_sort_dfs(3,
                          Edges{
                              Edge(2, 0),
                              Edge(1, 0),
                          }),
            std::vector<Node>({2, 1, 0}));
}

TEST(TopSortDfs, Wiki) {
  EXPECT_EQ(topo_sort_dfs(12,
                          Edges{
                              Edge(3, 8),
                              Edge(3, 10),
                              Edge(5, 11),
                              Edge(7, 11),
                              Edge(7, 8),
                              Edge(8, 9),
                              Edge(11, 10),
                              Edge(11, 9),
                              Edge(11, 2),
                          }),
            std::vector<Node>({7, 6, 5, 11, 4, 3, 10, 8, 9, 2, 1, 0}));
}

TEST(TopSortDfs, FullCyclic2) {
  EXPECT_EQ(topo_sort_dfs(2,
                          Edges{
                              Edge(0, 1),
                              Edge(1, 0),
                          }),
            std::nullopt);
}
TEST(TopSortDfs, FullCyclic3) {
  EXPECT_EQ(topo_sort_dfs(3,
                          Edges{
                              Edge(0, 1),
                              Edge(1, 2),
                              Edge(2, 0),
                          }),
            std::nullopt);
}
TEST(TopSortDfs, PartCyclic) {
  EXPECT_EQ(topo_sort_dfs(3,
                          Edges{
                              Edge(0, 1),
                              Edge(1, 0),
                          }),
            std::nullopt);
}
TEST(TopSortDfs, SelfCycle) {
  EXPECT_EQ(topo_sort_dfs(3, Edges{Edge(0, 0), Edge(1, 2), Edge(2, 2)}),
            std::nullopt);
}
